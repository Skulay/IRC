/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhelif <amkhelif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 19:11:10 by amkhelif          #+#    #+#             */
/*   Updated: 2026/08/17 18:37:41 by amkhelif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

// parse channel and modes arguments then display current modes or execute changes
void Server::ExecuteMode(int fd, std::string Argv)
{
    if (Argv.empty())
    {
        std::string errMsg = ":irc.local 461 " + _Client[fd].getNickname() + " MODE :Not enough parameters\r\n";
        send(fd, errMsg.c_str(), errMsg.length(), 0);
        return;
    }
    std::string ChannelN;
    std::string Mode;
    std::string ArgMode;
    size_t pos = Argv.find(" ");
    if (pos != std::string::npos)
    {
        ChannelN = Argv.substr(0, pos);
        std::string reste = Argv.substr(pos + 1);
        pos = reste.find(" ");
        if (pos != std::string::npos)
        {
            Mode = reste.substr(0, pos);
            if (pos + 1 != reste.length())
                ArgMode = reste.substr(pos + 1);
        }
        else
            Mode = reste.substr(0);
    }
    else
    {
        ChannelN = Argv;
        Mode = "";
    }

    Channel *chan = getChannelByName(ChannelN);
    if (!chan)
        return;
    if (Mode.empty())
    {
        std::string currentModes = "+";
        std::string modeArgs = "";

        if (chan->isInviteOnly())
            currentModes += "i";
        if (chan->isTopicRestricted())
            currentModes += "t";
        if (!chan->getKey().empty())
        {
            currentModes += "k";
            modeArgs += " " + chan->getKey();
        }
        if (chan->getUserLimit() > 0)
        {
            std::stringstream ss;
            ss << chan->getUserLimit();
            currentModes += "l";
            modeArgs += " " + ss.str();
        }

        std::string rpl324 = ":irc.local 324 " + _Client[fd].getNickname() + " " + chan->getName() + " " + currentModes + modeArgs + "\r\n";
        send(fd, rpl324.c_str(), rpl324.length(), 0);

        std::stringstream ssTime;
        ssTime << time(NULL);
        std::string rpl329 = ":irc.local 329 " + _Client[fd].getNickname() + " " + chan->getName() + " " + ssTime.str() + "\r\n";
        send(fd, rpl329.c_str(), rpl329.length(), 0);
        return;
    }
    if (!ValidExecuteMode(fd, ChannelN, Mode, ArgMode))
        return;
    Execute(fd, ChannelN, Mode, ArgMode);
}

// apply specified channel mode change and broadcast notification to all members
void Server::Execute(int fd, std::string ChannelName, std::string Mode, std::string ArgMode)
{
    Channel *chan = getChannelByName(ChannelName);
    if (!chan)
        return;
    char sign = Mode[0];
    char flag = Mode[1];
    std::cout << "sign = " + sign << "flag = " + flag << std::endl;
    if (flag == 'i')
    {
        if (sign == '-')
            chan->setInviteOnly(false);
        else
            chan->setInviteOnly(true);
    }
    else if (flag == 't')
    {
        if (sign == '-')
            chan->setTopicRestricted(false);
        else
            chan->setTopicRestricted(true);
    }
    else if (flag == 'l')
    {
        if (sign == '+')
            chan->setUserLimit(std::atoi(ArgMode.c_str()));
        else
            chan->removeUserLimit();
    }
    else if (flag == 'k')
    {
        if (sign == '-')
            chan->removeKey();
        else
            chan->setKey(ArgMode);
    }
    else if (flag == 'o')
    {
        if (sign == '-')
            chan->removeOperator(ArgMode);
        else
            chan->addOperator(ArgMode);
    }

    std::string notif = ":" + _Client[fd].getNickname() + "!" + _Client[fd].getUsername() + "@localhost MODE " + chan->getName() + " " + Mode;
    if (!ArgMode.empty())
        notif += " " + ArgMode;
    notif += "\r\n";

    const std::map<int, Client> &members = chan->getMembers();
    for (std::map<int, Client>::const_iterator it = members.begin(); it != members.end(); ++it)
        send(it->first, notif.c_str(), notif.length(), 0);
}

// check if mode syntax is valid and required argument is provided
bool Server::ValideMode(int fd, std::string Mode, std::string ArgMode)
{
    if (Mode.length() < 2 || (Mode[0] != '+' && Mode[0] != '-'))
        return false;

    char sign = Mode[0];
    char flag = Mode[1];
    char validModes[5] = {'i', 't', 'k', 'o', 'l'};
    bool found = false;

    for (int i = 0; i < 5; i++)
    {
        if (validModes[i] == flag)
        {
            found = true;
            break;
        }
    }
    if (!found)
    {
        std::string errMsg = ":irc.local 472 " + _Client[fd].getNickname() + " " + flag + " :is unknown mode char to me\r\n";
        send(fd, errMsg.c_str(), errMsg.length(), 0);
        return false;
    }

    if ((sign == '+' && (flag == 'k' || flag == 'l' || flag == 'o')) || (sign == '-' && flag == 'o'))
    {
        if (ArgMode.empty())
        {
            std::string errMsg = ":irc.local 461 " + _Client[fd].getNickname() + " MODE :Not enough parameters\r\n";
            send(fd, errMsg.c_str(), errMsg.length(), 0);
            return false;
        }
    }
    return true;
}

// validate channel existence operator rights and specific mode constraints before execution
bool Server::ValidExecuteMode(int fd, std::string Channel, std::string Mode, std::string ArgvMode)
{
    std::string userNick = _Client[fd].getNickname();
    if (!CheckChannel(Channel))
    {
        std::string errMsg = ":irc.local 403 " + userNick + " " + Channel + " :No such channel\r\n";
        send(fd, errMsg.c_str(), errMsg.length(), 0);
        return false;
    }
    if (!CheckHasMenber(userNick, Channel))
    {
        std::string errMsg = ":irc.local 442 " + userNick + " " + Channel + " :You're not on that channel\r\n";
        send(fd, errMsg.c_str(), errMsg.length(), 0);
        return false;
    }
    if (!IsOperator2(userNick, Channel))
    {
        std::string errMsg = ":irc.local 482 " + userNick + " " + Channel + " :You're not channel operator\r\n";
        send(fd, errMsg.c_str(), errMsg.length(), 0);
        return false;
    }
    if (!ValideMode(fd, Mode, ArgvMode))
        return false;

    char sign = Mode[0];
    char flag = Mode[1];

    if (flag == 'o')
    {
        if (!CheckClientExists(ArgvMode))
        {
            std::string errMsg = ":irc.local 401 " + userNick + " " + ArgvMode + " :No such nick/channel\r\n";
            send(fd, errMsg.c_str(), errMsg.length(), 0);
            return false;
        }
        if (!CheckHasMenber(ArgvMode, Channel))
        {
            std::string errMsg = ":irc.local 441 " + userNick + " " + ArgvMode + " " + Channel + " :They aren't on that channel\r\n";
            send(fd, errMsg.c_str(), errMsg.length(), 0);
            return false;
        }
    }

    if (sign == '+' && flag == 'l')
    {
        for (size_t i = 0; i < ArgvMode.length(); ++i)
        {
            if (!isdigit(ArgvMode[i]))
                return false;
        }
        if (std::atoi(ArgvMode.c_str()) <= 0)
            return false;
    }
    return true;
}
