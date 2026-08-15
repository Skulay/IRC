/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhelif <amkhelif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 14:55:19 by amkhelif          #+#    #+#             */
/*   Updated: 2026/08/15 16:17:24 by amkhelif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

Server::Server() { InitCommands(); }
// Server::Server(const Server &src)
// {
//     *this = src;
// }

// Server &Server::operator=(const Server &src)
// {
//     if (this != &src)
//     {
//         this->_port = src._port;
//         this->_password = src._password;
//         this->_serverSocket = src._serverSocket;
//         this->_Client = src._Client;
//         this->_Channel = src._Channel;
//         this->_pollFds = src._pollFds;
//     }
//     return *this;
// }

Server::~Server() {}

// check le port et la password
bool Server::CheckAv(char **av)
{

    this->_port = atoi(av[1]);
    if (this->_port < 1024 || this->_port > 65535)
    {
        std::cerr << "port incorect" << std::endl;
        return (true);
    }
    this->_PassWord = av[2];
    if (_PassWord.length() < 4 || isStringPrintable(_PassWord))
    {
        std::cerr << " error password" << std::endl;
        return (true);
    }
    return (false);
}

bool Server::isStringPrintable(const std::string &str)
{
    for (size_t i = 0; i < str.length(); ++i)
    {
        if (!std::isprint(static_cast<unsigned char>(str[i])))
            return true;
    }
    return false;
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
    _commamds["PART"] = Server::ExecutePart;
}
