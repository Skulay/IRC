/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhelif <amkhelif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 14:09:01 by amkhelif          #+#    #+#             */
/*   Updated: 2026/08/11 17:41:05 by amkhelif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

void Server::ExecutePrivmsg(int fd, std::string Argv)
{

    std::string phrase;
    size_t pos = Argv.find(":");
    if (pos == std::string::npos)
    {
        std::cerr << "commandes invalide" << std::endl;
        return;
    }
    std::string destination;

    destination = Argv.substr(0, pos);
    if (Argv.length() == pos || pos + 1 == Argv.length())
    {
        std::cerr << "commandes invalide" << std::endl;
        return;
    }
    phrase = Argv.substr(pos + 1);
    SendDestinataire(fd, destination, phrase);
    // std::cout << " resulatatatat     " << std::endl;
    // std::cout << destination + "  " << phrase << std::endl;
    // std::cout << " je suis dans Privmsg" << std::endl;
}

void Server::SendDestinataire(int fd, std::string Destination, std::string Msg)
{
    std::cout << "je suis dansla fonction senddestination" << std::endl;

    size_t pos = Destination.find("#");
    if (pos == std::string::npos)
    {
        int fd_destination = -1;
        std::map<int, Client>::const_iterator it;

        for (it = _Client.begin(); it != _Client.end(); it++)
        {
            std::cout << "je cherche " + Destination << " je suis sur le " + it->second.getNickname() << std::endl;
            std::cout << "len de destination " + Destination.length() << " len du client actuelle " + it->second.getNickname().length() << std::endl;
            if (Destination == it->second.getNickname())
            {
                std::cout << "destinataire trouver" << std::endl;
                fd_destination = it->first;
                break;
            }
        }

        if (fd_destination != -1)
        {
            std::cout << "message emvoyer" << std::endl;
            std::string fullMsg = ":" + _Client[fd].getNickname() + " PRIVMSG " + Destination + " :" + Msg + "\r\n";
            send(fd_destination, fullMsg.c_str(), fullMsg.length(), 0);
        }
        else
        {
            std::cout << "destinataire pas trouber" << std::endl;
            std::string errMsg = ":irc.local 401 " + _Client[fd].getNickname() + " " + Destination + " :No such nick/channel\r\n";
            send(fd, errMsg.c_str(), errMsg.length(), 0);
        }
    }
    else
    {
        std::cout << "je suis dans le else de la fonctionsenddestination" << std::endl;

        // channel
    }
}

bool Server::ClientValid(std::string name)
{
    std::cout << "je suis dans client valid" << "je checher  " + name << std::endl;
    // printf("je suis dans client valid\n");
    std::map<int, Client>::const_iterator it;

    for (it = _Client.begin(); it != _Client.end(); it++)
    {
        std::cout << "je suis dans la boucle de client valid" << std::endl;
        std::cout << "janalyse   le nom " + it->second.getUsername() << std::endl;
        if (name == it->second.getNickname())
        {
            std::cout << "je suis dans le if de client valid" << std::endl;

            return true;
        }
    }
    std::cout << "je ne trouve pas le nom" << std::endl;
    return false;
}