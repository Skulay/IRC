/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhelif <amkhelif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 18:55:43 by amkhelif          #+#    #+#             */
/*   Updated: 2026/08/15 19:05:09 by amkhelif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"
void Server::ExecuteJoin(int fd, std::string Argv)
{
    std::string channel;
    std::string pass;

    size_t space = Argv.find(" ");
    if (space != std::string::npos)
    {
        channel = Argv.substr(0, space);
        pass = Argv.substr(space + 1);
    }
    else
        channel = Argv;
    for (std::vector<Channel>::size_type i = 0; i < _Channel.size(); ++i)
    {
        if (_Channel[i].getName() == Argv)
        {
            if (_Channel[i].isInviteOnly() && !_Channel[i].isInvited(_Client[fd].getNickname()))
            {
                std::string errMsg = ":irc.local 473 " + _Client[fd].getNickname() + " " + _Channel[i].getName() + " :Cannot join channel (+i)\r\n";
                send(fd, errMsg.c_str(), errMsg.length(), 0);
                return;
            }
            if (_Channel[i].isFull())
            {
                std::string errMsg = ":irc.local 471 " + _Client[fd].getNickname() + " " + _Channel[i].getName() + " :Cannot join channel (+l)\r\n";
                send(fd, errMsg.c_str(), errMsg.length(), 0);
                return;
            }
            if (!_Channel[i].getKey().empty() && pass != _Channel[i].getKey())
            {
                std::string errMsg = ":irc.local 475 " + _Client[fd].getNickname() + " " + _Channel[i].getName() + " :Cannot join channel (+k)\r\n";
                send(fd, errMsg.c_str(), errMsg.length(), 0);
                return;
            }
            _Channel[i].addMember(fd, _Client[fd]);
            SendMessage(fd, Argv);
            return;
        }
    }

    Channel newSalon(Argv);

    newSalon.addMember(fd, _Client[fd]);

    newSalon.addOperator(_Client[fd].getNickname());

    _Channel.push_back(newSalon);
    std::string Welcome2 = ":" + _Client[fd].getNickname() + "!" + _Client[fd].getUsername() + "@localhost JOIN :" + Argv + "\r\n";

    send(fd, Welcome2.c_str(), Welcome2.length(), 0);
}

void Server::SendMessage(int fd, std::string Argv)
{
    for (std::vector<Channel>::iterator it = this->_Channel.begin(); it != this->_Channel.end(); ++it)
    {
        if (Argv == it->getName())
        {
            std::map<int, Client>::const_iterator it_member;
            std::string AllUser;
            for (it_member = it->getMembers().begin(); it_member != it->getMembers().end(); it_member++)
            {
                std::string joinMsg = ":" + _Client[fd].getNickname() + "!" + _Client[fd].getUsername() + "@localhost JOIN :" + Argv + "\r\n";
                int new_fd = it_member->first;  
                if (it->isOperator(it_member->second.getNickname()))
                    AllUser += "@" + it_member->second.getNickname() + " ";
                else
                    AllUser += it_member->second.getNickname() + " ";
                send(new_fd, joinMsg.c_str(), joinMsg.length(), 0);
            }
            std::string reply;

            if (it->getTopic().empty())
                reply += ":irc.local 331 " + _Client[fd].getNickname() + " " + Argv + " :No topic is set\r\n";
            else
                reply += ":irc.local 332 " + _Client[fd].getNickname() + " " + Argv + " :" + it->getTopic() + "\r\n";

            reply += ":irc.local 353 " + _Client[fd].getNickname() + " = " + Argv + " :" + AllUser + "\r\n";
            reply += ":irc.local 366 " + _Client[fd].getNickname() + " " + Argv + " :End of /NAMES list.\r\n";
            send(fd, reply.c_str(), reply.length(), 0);
        }
    }
}