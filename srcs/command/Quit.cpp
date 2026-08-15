/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhelif <amkhelif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 15:57:51 by amkhelif          #+#    #+#             */
/*   Updated: 2026/08/15 19:01:01 by amkhelif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

void Server::ExecuteQuit(int fd, std::string Argv)
{
    std::string reason = "Client Quit";

    if (!Argv.empty())
    {
        if (Argv[0] == ':')
            reason = Argv.substr(1);
        else
            reason = Argv;
    }
    DisconnectClient(fd, reason);
}

void Server::ExecutePart(int fd, std::string Argv)
{
    if (Argv.empty())

    {
        std::string errMsg = ":irc.local 461 " + _Client[fd].getNickname() + " PART :Not enough parameters\r\n";
        send(fd, errMsg.c_str(), errMsg.length(), 0);
        return;
    }

    std::string reason;
    std::string channel;

    size_t pos = Argv.find(" ");
    if (pos != std::string::npos)
    {
        channel = Argv.substr(0, pos);
        reason = Argv.substr(pos + 1);
        if (!reason.empty() && reason[0] == ':')
            reason = reason.substr(1);
    }
    else
    {
        channel = Argv;
        reason = "";
    }

    if (!CheckChannel(channel))
    {
        std::string errMsg = ":irc.local 403 " + _Client[fd].getNickname() + " " + channel + " :No such channel\r\n";
        send(fd, errMsg.c_str(), errMsg.length(), 0);
        return;
    }

    if (!CheckHasMenber(_Client[fd].getNickname(), channel))
    {
        std::string errMsg = ":irc.local 442 " + _Client[fd].getNickname() + " " + channel + " :You're not on that channel\r\n";
        send(fd, errMsg.c_str(), errMsg.length(), 0);
        return;
    }

    Channel *chan = getChannelByName(channel);
    if (!chan)
        return;

    std::string partMsg = ":" + _Client[fd].getNickname() + "!" + _Client[fd].getUsername() + "@localhost PART " + channel;
    if (!reason.empty())
        partMsg += " :" + reason;
    partMsg += "\r\n";

    const std::map<int, Client> &members = chan->getMembers();
    for (std::map<int, Client>::const_iterator it_member = members.begin(); it_member != members.end(); ++it_member)
        send(it_member->first, partMsg.c_str(), partMsg.length(), 0);

    chan->removeMember(_Client[fd].getNickname());

    if (chan->getMembers().empty())
    {
        for (std::vector<Channel>::iterator it_c = _Channel.begin(); it_c != _Channel.end(); ++it_c)
        {
            if (it_c->getName() == channel)
            {
                _Channel.erase(it_c);
                break;
            }    
                
        }
    }
}