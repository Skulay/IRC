/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhelif <amkhelif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/12 12:12:58 by amkhelif          #+#    #+#             */
/*   Updated: 2026/08/15 19:01:54 by amkhelif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

void Server::ExecuteKick(int fd, std::string Argv)
{
    size_t space_pos1 = Argv.find(' ');
    if (space_pos1 == std::string::npos)
    {
        std::string errMsg = ":irc.local 461 " + _Client[fd].getNickname() + " KICK :Not enough parameters\r\n";
        send(fd, errMsg.c_str(), errMsg.length(), 0);
        return;
    }

    std::string channel = Argv.substr(0, space_pos1);
    if (channel.empty() || channel[0] != '#')
    {
        std::string errMsg = ":irc.local 403 " + _Client[fd].getNickname() + " " + channel + " :No such channel\r\n";
        send(fd, errMsg.c_str(), errMsg.length(), 0);
        return;
    }

    std::string reste = Argv.substr(space_pos1 + 1);
    std::string pseudo;
    std::string reason = "";

    size_t space_pos2 = reste.find(' ');
    if (space_pos2 != std::string::npos)
    {
        pseudo = reste.substr(0, space_pos2);
        reason = reste.substr(space_pos2 + 1);
        if (!reason.empty() && reason[0] == ':')
            reason = reason.substr(1);
    }
    else
        pseudo = reste;

    if (pseudo.empty())
    {
        std::string errMsg = ":irc.local 461 " + _Client[fd].getNickname() + " KICK :Not enough parameters\r\n";
        send(fd, errMsg.c_str(), errMsg.length(), 0);
        return;
    }
    else if (!valideKick(fd, pseudo, channel))
        return;

    kickuser(fd, pseudo, channel, reason);
}

void Server::kickuser(int fd, std::string pseudo, std::string channel, std::string reason)
{

    std::string kickMsg = ":" + _Client[fd].getNickname() + "!" + _Client[fd].getUsername() + "@localhost KICK " + channel + " " + pseudo + " :" + reason + "\r\n";
    std::vector<Channel>::iterator it_chan;
    for (it_chan = _Channel.begin(); it_chan != _Channel.end(); ++it_chan)
    {
        if (it_chan->getName() == channel)
        {
            const std::map<int, Client> &members = it_chan->getMembers();
            std::map<int, Client>::const_iterator it_mem;
            for (it_mem = members.begin(); it_mem != members.end(); ++it_mem)
                send(it_mem->first, kickMsg.c_str(), kickMsg.length(), 0);
            it_chan->removeMember(pseudo);
            if (it_chan->getMembers().empty())
                _Channel.erase(it_chan);
            break;
        }
    }
}

bool Server::valideKick(int fd, std::string name, std::string channel)
{
    std::string userNick = _Client[fd].getNickname();

    if (!CheckChannel(channel))
    {
        std::string errMsg = ":irc.local 403 " + userNick + " " + channel + " :No such channel\r\n";
        send(fd, errMsg.c_str(), errMsg.length(), 0);
        return false;
    }
    else if (!CheckHasMenber(userNick, channel))
    {
        std::string errMsg = ":irc.local 442 " + userNick + " " + channel + " :You're not on that channel\r\n";
        send(fd, errMsg.c_str(), errMsg.length(), 0);
        return false;
    }
    else if (!IsOperator2(userNick, channel))
    {
        std::string errMsg = ":irc.local 482 " + userNick + " " + channel + " :You're not channel operator\r\n";
        send(fd, errMsg.c_str(), errMsg.length(), 0);
        return false;
    }
    else if (!CheckCible(name, channel))
    {
        std::string errMsg = ":irc.local 441 " + userNick + " " + name + " " + channel + " :They aren't on that channel\r\n";
        send(fd, errMsg.c_str(), errMsg.length(), 0);
        return false;
    }
    return true;
}