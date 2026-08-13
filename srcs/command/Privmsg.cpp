/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 14:09:01 by amkhelif          #+#    #+#             */
/*   Updated: 2026/08/13 14:03:25 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

void Server::ExecutePrivmsg(int fd, std::string Argv)
{
    std::string phrase;
    std::string destination;

    size_t space = Argv.find(' ');
    if (space == std::string::npos)
    {
        // std::cerr << "commandes invalide" << std::endl;
        return;
    }
    destination = Argv.substr(0, space);

    size_t pos = Argv.find(':');
    if (pos == std::string::npos || pos + 1 == Argv.length())
    {
        // std::cerr << "commandes invalide" << std::endl;
        return;
    }
    phrase = Argv.substr(pos + 1);

    SendDestinataire(fd, destination, phrase);
    CheckBot(fd, destination, phrase);
}

void Server::SendDestinataire(int fd, std::string Destination, std::string Msg)
{
    // std::cout << "je suis dansla fonction senddestination" << std::endl;

    size_t pos = Destination.find("#");
    if (pos == std::string::npos)
    {
        int fd_destination = -1;
        std::map<int, Client>::const_iterator it;

        for (it = _Client.begin(); it != _Client.end(); it++)
        {
            // std::cout << "je cherche " + Destination << " je suis sur le " + it->second.getNickname() << std::endl;
            // std::cout << "len de destination " + Destination.length() << " len du client actuelle " + it->second.getNickname().length() << std::endl;
            if (Destination == it->second.getNickname())
            {
                // std::cout << "destinataire trouver" << std::endl;
                fd_destination = it->first;
                break;
            }
        }

        if (fd_destination != -1)
        {
            // std::cout << "message emvoyer" << std::endl;
            std::string fullMsg = ":" + _Client[fd].getNickname() + " PRIVMSG " + Destination + " :" + Msg + "\r\n";
            send(fd_destination, fullMsg.c_str(), fullMsg.length(), 0);
        }
        else
        {
            // std::cout << "destinataire pas trouber" << std::endl;
            std::string errMsg = ":irc.local 401 " + _Client[fd].getNickname() + " " + Destination + " :No such nick/channel\r\n";
            send(fd, errMsg.c_str(), errMsg.length(), 0);
        }
    }
    else
    {
        // std::cout << "je suis dans le else de la fonctionsenddestination" << std::endl;
        std::cout << "je cherche" + Destination << std::endl;
        std::vector<Channel>::iterator it;

        for (it = _Channel.begin(); it != _Channel.end(); ++it)
        {
            // On accède aux membres de Channel avec l'opérateur ->
            std::cout << it->getName() << std::endl;

            // Ou en déréférençant l'itérateur avec *
            // (*it).nomDuCanal();

            if (it->getName() == Destination)
            {
                std::string fullMsg = ":" + _Client[fd].getNickname() + " PRIVMSG " + Destination + " :" + Msg + "\r\n";
                std::map<int, Client>::const_iterator it_member;

                for (it_member = it->getMembers().begin(); it_member != it->getMembers().end(); ++it_member)
                {
                    if (it_member->first != fd)
                    {
                        send(it_member->first, fullMsg.c_str(), fullMsg.length(), 0);
                    }
                }
            }
        }
        // channel
    }
}

// bool Server::ClientValid(std::string name)
// {
//     std::cout << "je suis dans client valid" << "je checher  " + name << std::endl;
//     // printf("je suis dans client valid\n");
//     std::map<int, Client>::const_iterator it;

//     for (it = _Client.begin(); it != _Client.end(); it++)
//     {
//         std::cout << "je suis dans la boucle de client valid" << std::endl;
//         std::cout << "janalyse   le nom " + it->second.getUsername() << std::endl;
//         if (name == it->second.getNickname())
//         {
//             std::cout << "je suis dans le if de client valid" << std::endl;

//             return true;
//         }
//     }
//     std::cout << "je ne trouve pas le nom" << std::endl;
//     return false;
// }