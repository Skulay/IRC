/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhelif <amkhelif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 14:55:19 by amkhelif          #+#    #+#             */
/*   Updated: 2026/08/17 18:10:58 by amkhelif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

// clean up all allocated resources sockets and containers on server
Server::~Server()
{
    for (std::map<int, Client>::iterator it = _Client.begin(); it != _Client.end(); ++it)
    {
        epoll_ctl(this->_EpollFD, EPOLL_CTL_DEL, it->first, NULL);
        close(it->first);
    }
    _Client.clear();
    _Channel.clear();

    if (this->_EpollFD != -1)
        close(this->_EpollFD);
    if (this->_ServerFd != -1)
        close(this->_ServerFd);
}

// validate port range and password requirements from command line arguments
bool Server::CheckAv(char **av)
{

    this->_port = atoi(av[1]);
    if (this->_port < 1024 || this->_port > 65535)
    {
        std::cerr << "port incorect" << std::endl;
        return (true);
    }
    this->_PassWord = av[2];
    if (_PassWord.length() < 4 || !isStringPrintable(_PassWord))
    {
        std::cerr << " error password" << std::endl;
        return (true);
    }
    return (false);
}

// check if all characters in string are printable ascii
bool Server::isStringPrintable(const std::string &str)
{
    for (size_t i = 0; i < str.length(); ++i)
    {
        if (!std::isprint(static_cast<unsigned char>(str[i])))
            return false;
    }
    return true;
}

void Server::InitCommands(void)
{
    _commands["PASS"] = &Server::ExecutePass;
    _commands["NICK"] = &Server::ExecuteNick;
    _commands["USER"] = &Server::ExecuteUser;
    _commands["CAP"] = &Server::ExecuteCap;
    _commands["JOIN"] = &Server::ExecuteJoin;
    _commands["PING"] = &Server::ExecutePing;
    _commands["MODE"] = &Server::ExecuteMode;
    _commands["PRIVMSG"] = &Server::ExecutePrivmsg;
    _commands["KICK"] = &Server::ExecuteKick;
    _commands["INVITE"] = &Server::ExecuteInvite;
    _commands["TOPIC"] = &Server::ExecuteTopic;
    _commands["QUIT"] = &Server::ExecuteQuit;
    _commands["PART"] = &Server::ExecutePart;
}

void Server::InitBotCommands(void)
{
    _botCommands["ping"] = &Server::BotPing;
    _botCommands["dice"] = &Server::BotDice;
    _botCommands["coin"] = &Server::BotCoin;
    _botCommands["fact"] = &Server::Botfacts;
    _botCommands["users"] = &Server::BotUsers;
    _botCommands["help"] = &Server::BotHelp;
}

// intercept ctrl c
static void capte(int sig)
{
    (void)sig;
}

Server::Server()
{
    signal(SIGPIPE, SIG_IGN); // client qui ce deco
    signal(SIGINT, capte); // capte ctrl c
    InitCommands();
    InitBotCommands();
}