/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhelif <amkhelif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 14:55:19 by amkhelif          #+#    #+#             */
/*   Updated: 2026/08/05 17:50:33 by amkhelif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <fcntl.h>
// check le port et la password
bool Server::CheckAv(char **av)
{

    this->_port = atoi(av[1]);
    if (this->_port < 1024 || this->_port > 65535)
    {
        std::cerr << "port incorect" << std::endl;
        return (true);
    }
    this->_PassWord = av[2];
    if (_PassWord.length() < 4 || isStringPrintable(_PassWord))
    {
        std::cerr << " error password" << std::endl;
        return (true);
    }
    return (false);
}

bool Server::isStringPrintable(const std::string &str)
{
    for (size_t i = 0; i < str.length(); ++i)
    {
        if (!std::isprint(static_cast<unsigned char>(str[i])))
            return true;
    }
    return false;
}

void Server::RunServer()
{
    // ouvre le fd
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

    //  Remplissage des paramètres
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
                AcceptNewClient(FdClient);
            else // sinon c un cleint qui est deja dans notre seveur
                ReceiveFromClient(FdClient);
        }
    }
}

void Server::ReceiveFromClient(int fd)
{
    char Receive[1024];
    int SizeMax = sizeof(Receive) - 1;

    ssize_t DataClient = recv(fd, Receive, SizeMax, 0);
    if (DataClient > 0)
    {
        Receive[DataClient] = '\0';
        std::cout << "Données reçues : " << Receive << std::endl;
    }
    else if (DataClient == 0)
    {
        std::cout << "Connexion fermée par le serveur." << std::endl;
    }
    else
        std::cerr << "Erreur lors de la réception." << std::endl;
}

// fonction qui acppre kes new clients
void Server::AcceptNewClient(int fd)
{
    int NewFdClient = accept(this->_ServerFd, NULL, NULL);
    if (NewFdClient == -1)
        throw std::runtime_error("error funtion accept");
    struct epoll_event client_event;
    memset(&client_event, 0, sizeof(client_event));
    client_event.events = EPOLLIN;     
    client_event.data.fd = NewFdClient; 

    if (epoll_ctl(this->_EpollFD, EPOLL_CTL_ADD, NewFdClient, &client_event) == -1)
    {
        std::cerr << "Erreur : impossible d'ajouter le client à epoll." << std::endl;
        return;
    }
    std::cout << "Nouveau client accepté ! FD : " << NewFdClient << std::endl;
}

Server::Server()
{
}

Server::~Server()
{
}
