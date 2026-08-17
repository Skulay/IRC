/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerNetwork.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhelif <amkhelif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 15:54:12 by amkhelif          #+#    #+#             */
/*   Updated: 2026/08/17 13:19:29 by amkhelif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

void Server::RunServer()
{
    this->_ServerFd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->_ServerFd == -1)
        throw std::runtime_error("Erreur : impossible de creer le serveur.");
    int opt = 1;
    // permet que le port soit reutilisable directement apres avoir etait liberer
    if (setsockopt(this->_ServerFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
        throw std::runtime_error("Erreur : impossible de configurer loption SO_REUSEADDR.");
    // rend le socket non bloquant
    if (fcntl(this->_ServerFd, F_SETFL, O_NONBLOCK) == -1)
        throw std::runtime_error("Erreur : impossible de passer le socket en non bloquant.");

    // struct qui stocke les iformation dune adresse ip
    struct sockaddr_in test;

    // Nettoyage de la structure
    memset(&test, 0, sizeof(test));

    //  Remplissage des parametres
    test.sin_family = AF_INET;         // famille de ladresse (ipv4 pour nous)
    test.sin_addr.s_addr = INADDR_ANY; // ecoute sur tout les adresse ip disponible sur la machine
    test.sin_port = htons(this->_port);

    // Attachement du socket au port avec bind()
    if (bind(this->_ServerFd, (struct sockaddr *)&test, sizeof(test)) == -1)
        throw std::runtime_error("Erreur");
    // mais le socket en attente de connexion entrante
    if (listen(this->_ServerFd, SOMAXCONN) == -1)
        throw std::runtime_error("error");
    this->_EpollFD = epoll_create1(0);
    if (this->_EpollFD == -1)
        throw std::runtime_error("Erreur");
    struct epoll_event struct_epoll;
    memset(&struct_epoll, 0, sizeof(struct_epoll));
    struct_epoll.events = EPOLLIN; //  previens si des donnees ou une nouvelle commexion est en attente
    struct_epoll.data.fd = this->_ServerFd;
    if (epoll_ctl(this->_EpollFD, EPOLL_CTL_ADD, this->_ServerFd, &struct_epoll) == -1)
        throw std::runtime_error("epoll ctl fail\n");

    LoopServer();
}

bool Server::LoopServer()
{
    while (true)
    {
        int nfds = epoll_wait(this->_EpollFD, this->events, 10, -1);
        for (int i = 0; i < nfds; i++)
        {
            int FdClient = events[i].data.fd;
            // si c un nouveau clients
            if (FdClient == this->_ServerFd)
                AcceptNewClient();
            else // sinon c un cleint qui est deja dans notre seveur
                ReceiveFromClient(FdClient);
        }
    }
}

void Server::AcceptNewClient(void)
{
    int NewFdClient = accept(this->_ServerFd, NULL, NULL);
    if (NewFdClient == -1)
        return;
    if (fcntl(NewFdClient, F_SETFL, O_NONBLOCK) == -1)
    {
        close(NewFdClient);
        return;
    }
    struct epoll_event client_event;
    memset(&client_event, 0, sizeof(client_event));
    client_event.events = EPOLLIN;
    client_event.data.fd = NewFdClient;

    if (epoll_ctl(this->_EpollFD, EPOLL_CTL_ADD, NewFdClient, &client_event) == -1)
    {
        std::cerr << "Erreur : impossible d'ajouter le client à epoll." << std::endl;
        close(NewFdClient);
        return;
    }
    _Client[NewFdClient] = Client();
}

void Server::ReceiveFromClient(int fd)
{
    char Receive[1024];
    int SizeMax = sizeof(Receive) - 1;

    ssize_t DataClient = recv(fd, Receive, SizeMax, 0);
    if (DataClient > 0)
    {
        Receive[DataClient] = '\0';
        _Client[fd].addToBuffer(Receive);
        std::cout << "Données reçues : " << Receive << std::endl;
        ParsBuffer(fd);
    }
    else if (DataClient == 0)
        DisconnectClient(fd, "");
    else
        DisconnectClient(fd, "");
}

void Server::DisconnectClient(int fd, std::string reason)
{
    std::map<int, Client>::iterator itClient = _Client.find(fd);
    if (itClient == _Client.end())
        return;

    std::string nick = itClient->second.getNickname();
    std::string user = itClient->second.getUsername();
    std::string quitMsg = ":" + nick + "!" + user + "@localhost QUIT :" + reason + "\r\n";

    std::vector<Channel>::iterator it = _Channel.begin();
    while (it != _Channel.end())
    {
        if (it->hasMember(nick))
        {
            const std::map<int, Client> &members = it->getMembers();
            for (std::map<int, Client>::const_iterator it_mem = members.begin(); it_mem != members.end(); ++it_mem)
            {
                if (it_mem->first != fd)
                    send(it_mem->first, quitMsg.c_str(), quitMsg.length(), 0);
            }
            it->removeMember(nick);
        }
        if (it->getMembers().empty())
            it = _Channel.erase(it);
        else
            ++it;
    }

    epoll_ctl(this->_EpollFD, EPOLL_CTL_DEL, fd, NULL);
    close(fd);
    _Client.erase(itClient);
}