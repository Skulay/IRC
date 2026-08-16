/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 14:09:01 by amkhelif          #+#    #+#             */
/*   Updated: 2026/08/16 17:45:11 by alehamad         ###   ########.fr       */
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
        std::string errMsg = ":irc.local 411 " + _Client[fd].getNickname() + " :No recipient given (PRIVMSG)\r\n";
        send(fd, errMsg.c_str(), errMsg.length(), 0);
        return;
    }
    destination = Argv.substr(0, space);

    size_t pos = Argv.find(':');
    if (pos != std::string::npos)
    {
        if (pos + 1 >= Argv.length())
        {
            std::string errMsg = ":irc.local 412 " + _Client[fd].getNickname() + " :No text to send\r\n";
            send(fd, errMsg.c_str(), errMsg.length(), 0);
            return;
        }
        phrase = Argv.substr(pos + 1);
    }
    else
    {
        phrase = Argv.substr(space + 1);
        if (phrase.empty())
        {
            std::string errMsg = ":irc.local 412 " + _Client[fd].getNickname() + " :No text to send\r\n";
            send(fd, errMsg.c_str(), errMsg.length(), 0);
            return;
        }
    } 
    if (destination == "BOT")
        CheckBot(fd, destination, phrase);
    else
        SendDestinataire(fd, destination, phrase);
}

void Server::SendDestinataire(int fd, std::string Destination, std::string Msg)
{

    size_t pos = Destination.find("#");
    if (pos == std::string::npos)
    {
        int fd_destination = -1;
        std::map<int, Client>::const_iterator it;

        for (it = _Client.begin(); it != _Client.end(); it++)
        {
            if (Destination == it->second.getNickname())
            {
                fd_destination = it->first;
                break;
            }
        }

        if (fd_destination != -1)
        {
            std::string fullMsg = ":" + _Client[fd].getNickname() + " PRIVMSG " + Destination + " :" + Msg + "\r\n";
            send(fd_destination, fullMsg.c_str(), fullMsg.length(), 0);
        }
        else
        {
            std::string errMsg = ":irc.local 401 " + _Client[fd].getNickname() + " " + Destination + " :No such nick/channel\r\n";
            send(fd, errMsg.c_str(), errMsg.length(), 0);
        }
    }
    else
    {
        std::vector<Channel>::iterator it;

        int find = -1;
        for (it = _Channel.begin(); it != _Channel.end(); ++it)
        {
            std::cout << it->getName() << std::endl;

            if (it->getName() == Destination)
            {
                find = 1;
                std::string fullMsg = ":" + _Client[fd].getNickname() + " PRIVMSG " + Destination + " :" + Msg + "\r\n";
                std::map<int, Client>::const_iterator it_member;
                if (it->hasMember(_Client[fd].getNickname())) // on verifie si le client est menbre sinon
                {
                    for (it_member = it->getMembers().begin(); it_member != it->getMembers().end(); ++it_member)
                    {
                        if (it_member->first != fd)
                            send(it_member->first, fullMsg.c_str(), fullMsg.length(), 0);
                    }
                }
                else
                {
                    std::string errMsg = ":irc.local 404 " + _Client[fd].getNickname() + " " + Destination + " :Cannot send to channel\r\n";
                    send(fd, errMsg.c_str(), errMsg.length(), 0);
                }
                break;
            }
        }
        if (find == -1) // channel pas trouver
        {
            std::string errMsg = ":irc.local 401 " + _Client[fd].getNickname() + " " + Destination + " :No such nick/channel\r\n";
            send(fd, errMsg.c_str(), errMsg.length(), 0);
        }
    }
}


