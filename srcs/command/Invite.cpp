/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/12 15:43:45 by amkhelif          #+#    #+#             */
/*   Updated: 2026/08/16 17:44:01 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

void Server::ExecuteInvite(int fd, std::string Argv)
{
    if (Argv.empty())
    {
        std::string errMsg = ":irc.local 461 " + _Client[fd].getNickname() + " INVITE :Not enough parameters\r\n";
        send(fd, errMsg.c_str(), errMsg.length(), 0);
        return;
    }

    std::string cible;
    std::string channel;

    size_t space = Argv.find(' ');
    if (space != std::string::npos)
    {
        cible = Argv.substr(0, space);

        std::string reste = Argv.substr(space + 1);
        size_t first_char = reste.find_first_not_of(' ');
        if (first_char != std::string::npos)
        {
            size_t second_space = reste.find(' ', first_char);
            if (second_space != std::string::npos)
                channel = reste.substr(first_char, second_space - first_char);
            else
                channel = reste.substr(first_char);
        }
    }

    if (cible.empty() || channel.empty())
    {
        std::string errMsg = ":irc.local 461 " + _Client[fd].getNickname() + " INVITE :Not enough parameters\r\n";
        send(fd, errMsg.c_str(), errMsg.length(), 0);
        return;
    }
    if (!ValideInvite(fd, cible, channel))
        return;
    // invite le user
    Channel *chan = getChannelByName(channel);
    if (chan)
        chan->addInvited(cible);
    std::string rplMsg = ":irc.local 341 " + _Client[fd].getNickname() + " " + cible + " " + channel + "\r\n";
    send(fd, rplMsg.c_str(), rplMsg.length(), 0);
    int targetFd = getFdByNickname(cible);
    if (targetFd != -1)
    {
        std::string inviteNotif = ":" + _Client[fd].getNickname() + "!" + _Client[fd].getUsername() + "@localhost INVITE " + cible + " :" + channel + "\r\n";
        send(targetFd, inviteNotif.c_str(), inviteNotif.length(), 0);
    }
}

bool Server::ValideInvite(int fd, std::string cible, std::string channel)
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
    else if (!CheckClientExists(cible))
    {
        std::string errMsg = ":irc.local 401 " + _Client[fd].getNickname() + " " + cible + " :No such nick/channel\r\n";
        send(fd, errMsg.c_str(), errMsg.length(), 0);
        return false;
    }
    else if (CheckCible(cible, channel))
    {
        std::string errMsg = ":irc.local 443 " + _Client[fd].getNickname() + " " + cible + " " + channel + " :is already on channel\r\n";
        send(fd, errMsg.c_str(), errMsg.length(), 0);
        return false;
    }
    Channel *chan = getChannelByName(channel);

    if (chan && chan->isInviteOnly() && !IsOperator2(_Client[fd].getNickname(), channel))
    {
        std::string errMsg = ":irc.local 482 " + _Client[fd].getNickname() + " " + channel + " :You're not channel operator\r\n";
        send(fd, errMsg.c_str(), errMsg.length(), 0);
        return false;
    }
    return true;
}
