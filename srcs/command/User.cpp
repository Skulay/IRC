/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhelif <amkhelif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 15:48:23 by amkhelif          #+#    #+#             */
/*   Updated: 2026/08/15 16:15:32 by amkhelif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

    void Server::ExecuteUser(int fd, std::string Argv)
    {
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
            _Client[fd].SetValidClient(fd, true);
    }

void Client::SetValidClient(int fd, int IsValide)
{

    std::string nick = getNickname();
    std::string welcome = ":irc.local 001 " + nick + " :Welcome to the Internet Relay Chat network " + nick + "\r\n";
    welcome += ":irc.local 002 " + nick + " :Your host is irc.local, running version 1.0\r\n";
    welcome += ":irc.local 003 " + nick + " :This server was created just for 42\r\n";
    welcome += ":irc.local 004 " + nick + " irc.local 1.0 o o\r\n";
    send(fd, welcome.c_str(), welcome.length(), 0);
}