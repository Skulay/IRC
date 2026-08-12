/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhelif <amkhelif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/12 17:40:24 by amkhelif          #+#    #+#             */
/*   Updated: 2026/08/12 19:06:01 by amkhelif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

void Server::ExecuteTopic(int fd, std::string Argv)
{
    std::string cible;
    std::string contenue;

    size_t space = Argv.find(" ");
    if (space != std::string::npos)
    {
        cible = Argv.substr(0, space);
        contenue = Argv.substr(space + 1);
    }
    else
        cible = Argv.substr(0);

    if (CheckTopicValid(fd, cible))
    {
    }

    // // std::cout << "je suis dans Execute topic" << std::endl;
    // std::cout << cible << std::endl;
    // std::cout << contenue << std::endl;
}

bool Server::CheckTopicValid(int fd, std::string cible, std::string contenue)
{
    // le channel mexisre pas
    if (!CheckChannel(fd, cible))
    {
        std::string errMsg = ":irc.local 403 " + userNick + " " + channel + " :No such channel\r\n";
        send(fd, errMsg.c_str(), errMsg.length(), 0);
        return false;
    }
    Channel *chan = getChannelByName(channel);

    if (!CheckHasMenber(userNick, channel))
    {
        std::string errMsg = ":irc.local 442 " + userNick + " " + channel + " :You're not on that channel\r\n";
        send(fd, errMsg.c_str(), errMsg.length(), 0);
        return false;
    }
    // reprend ici demain
    else if (!contenue.empty() && chan->getTopic() && IsOperator2() )
    {
        std::string msg = ":irc.local 331 " + _Client[fd].getNickname() + " " + chan->getName() + " :No topic is set\r\n";
        send(fd, msg.c_str(), msg.length(), 0);
    }
}

// je suis dans Execute topic
// jnjngd
