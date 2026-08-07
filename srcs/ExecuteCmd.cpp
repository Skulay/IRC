/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteCmd.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhelif <amkhelif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/07 14:56:12 by amkhelif          #+#    #+#             */
/*   Updated: 2026/08/07 18:08:58 by amkhelif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::ExecutePass(int fd, std::string Argv)
{
    printf("je suis dans pass\n");
    if (Argv.empty())
    {
        std::string msg = ":ircserv 461 * PASS :Not enough parameters\r\n";
        send(fd, msg.c_str(), msg.length(), 0);
        return;
    }
    if (_Client[fd].GetPassClient()) // si le client a deja valide son mdp
    {
        std::string err = ":ircserv 462 * :You may not reregister\r\n";
        send(fd, err.c_str(), err.length(), 0);
        return;
    }
    if (this->_PassWord == Argv) // si le texte corspond au mdp du serveur c bon
    {

        _Client[fd].SetPass(true);
    }
    else // so le mdp nes pas celui du serveur
    {
        std::string msg = ":ircserv 464 * :Password incorrect\r\n";
        send(fd, msg.c_str(), msg.length(), 0);
    }
}

void Server::ExecuteNick(int fd, std::string Argv)
{
    printf("je suis dans ExecuteNick\n");
    if (!_Client[fd].GetPassClient())
    {
        std::string msg = ":ircserv 462 * :Password invalide tu ne peut pas le faire";
        send(fd, msg.c_str(), msg.length(), 0);
        return;
    }
    else if (IsValidNickName(Argv, fd))
        return;
    else
    {
        _Client[fd].setNickname(Argv);
        _Client[fd].SetNick(true);
    }
}

void Server::ExecuteUser(std::string Argv, int fd)
{
    printf("je suis dans ExecuteUser\n");
    if (!_Client[fd].GetPassClient())
    {
        std::string err = ":ircserv 464 * :Password required first\r\n";
        send(fd, err.c_str(), err.length(), 0);
        return;
    }
    if (!_Client[fd].getUsername().empty())
    {
        std::string err = ":ircserv 462 * :You may not reregister\r\n";
        send(fd, err.c_str(), err.length(), 0);
        return;
    }
    if (Argv.empty())
    {
        std::string err = ":ircserv 461 USER :Not enough parameters\r\n";
        send(fd, err.c_str(), err.length(), 0);
        return;
    }

    size_t pos = Argv.find(" ");
    std::string username;
    if (pos != std::string::npos)
        username = Argv.substr(0, pos);
    else
        username = Argv;

    _Client[fd].setUsername(username);
    _Client[fd].SetUserNameB(true);
    if (_Client[fd].GetPassClient() && _Client[fd].GetNickClient() && _Client[fd].GetUserNameClient())
    {
        _Client[fd].SetValidClient(true);
    }
}