/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/12 17:40:24 by amkhelif          #+#    #+#             */
/*   Updated: 2026/08/16 17:45:39 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

void Server::ExecuteTopic(int fd, std::string Argv)
{
    std::string Subject;
    std::string Channel;
    if (Argv.empty())
    {
        std::string errMsg = ":irc.local 461 " + _Client[fd].getNickname() + " TOPIC :Not enough parameters\r\n";
        send(fd, errMsg.c_str(), errMsg.length(), 0);
        return;
    }
    bool IsNewSubject = 0;
    size_t pos = Argv.find(":");
    if (pos != std::string::npos)
    {
        IsNewSubject = 1;
        Subject = Argv.substr(pos + 1);
        Channel = Argv.substr(0, pos);
        size_t space = Channel.find(" ");
        if (space != std::string::npos)
            Channel = Channel.substr(0, space);
    }
    else
    {
        size_t pos = Argv.find(" ");
        if (pos != std::string::npos)
            Channel = Argv.substr(0, pos);
        else
            Channel = Argv.substr(0);
    }
    if (ParsTopic(fd, Channel, IsNewSubject))
        return;
    ExecuteCmd(fd, Channel, IsNewSubject, Subject);
    return;
}

bool Server::ParsTopic(int fd, std::string ChannelC, bool NewSubject)
{
    if (!CheckChannel(ChannelC))
    {
        std::string errMsg = ":irc.local 403 " + _Client[fd].getNickname() + " " + ChannelC + " :No such channel\r\n";
        send(fd, errMsg.c_str(), errMsg.length(), 0);
        return true;
    }
    else if (!CheckHasMenber(_Client[fd].getNickname(), ChannelC))
    {
        std::string errMsg = ":irc.local 442 " + _Client[fd].getNickname() + " " + ChannelC + " :You're not on that channel\r\n";
        send(fd, errMsg.c_str(), errMsg.length(), 0);
        return true;
    }

    if (NewSubject)
    {
        Channel *chan = getChannelByName(ChannelC);
        if (chan && chan->isTopicRestricted())
        {
            if (!chan->isOperator(_Client[fd].getNickname()))
            {
                std::string errMsg = ":irc.local 482 " + _Client[fd].getNickname() + " " + ChannelC + " :You're not channel operator\r\n";
                send(fd, errMsg.c_str(), errMsg.length(), 0);
                return true;
            }
        }
    }
    return false;
}

void Server::ExecuteCmd(int fd, std::string channel, bool NewTopic, std::string Topic)
{
    Channel *Chan = getChannelByName(channel);
    if (!Chan)
        return;

    if (NewTopic) // modifier le topic
    {
        Chan->setTopic(Topic);
        std::string Msg = ":" + _Client[fd].getNickname() + "!" + _Client[fd].getUsername() + "@localhost TOPIC " + Chan->getName() + " :" + Topic + "\r\n";

        const std::map<int, Client> &members = Chan->getMembers();
        for (std::map<int, Client>::const_iterator it = members.begin(); it != members.end(); ++it)
            send(it->first, Msg.c_str(), Msg.length(), 0);
    }
    else // consulter le topic
    {
        if (Chan->getTopic().empty())
        {
            std::string msg = ":irc.local 331 " + _Client[fd].getNickname() + " " + Chan->getName() + " :No topic is set\r\n";
            send(fd, msg.c_str(), msg.length(), 0);
        }
        else
        {
            std::string msg = ":irc.local 332 " + _Client[fd].getNickname() + " " + Chan->getName() + " :" + Chan->getTopic() + "\r\n";
            send(fd, msg.c_str(), msg.length(), 0);
        }
    }
}