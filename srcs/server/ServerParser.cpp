/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerParser.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhelif <amkhelif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 15:55:16 by amkhelif          #+#    #+#             */
/*   Updated: 2026/08/18 14:10:56 by amkhelif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

// extract complete lines delimited by newline
void Server::ParsBuffer(int fd)
{
    std::string buffer = _Client[fd].getBuffer();
    if (buffer.size() > 65536)
    {
        DisconnectClient(fd, "Excess flood");
        return;
    }
    size_t pos = buffer.find("\n");
    while (pos != std::string::npos)
    {
        std::string command = buffer.substr(0, pos);
        SplitBuffer(command, fd);
        buffer = buffer.substr(pos + 1);
        _Client[fd].setBuffer(buffer);
        pos = buffer.find("\n");
    }
    return;
}

// delet a '\n' and split line into command name and arguments
void Server::SplitBuffer(std::string buffer, int fd)
{
    if (!buffer.empty() && (buffer[buffer.length() - 1] == '\r' || buffer[buffer.length() - 1] == '\n'))
        buffer.erase(buffer.length() - 1);

    std::string cmd;
    std::string argv;
    size_t pos = buffer.find(" ");

    if (pos == std::string::npos)
    {
        cmd = buffer;
        argv = "";
    }
    else
    {
        cmd = buffer.substr(0, pos);
        argv = buffer.substr(pos + 1);
    }
    ExecuteCommand(fd, cmd, argv);
}

void Server::ExecuteCommand(int fd, std::string Cmd, std::string Argv)
{
    std::map<std::string, void (Server::*)(int, std::string)>::iterator it = _commands.find(Cmd);
    if (it == _commands.end())
    {
        std::cerr << "this CMD " << Cmd << " is not available" << std::endl;
        std::cerr << "Command: " << Cmd + " " << Argv << std::endl;
        std::string errMsg = ":irc.local 421 " + _Client[fd].getNickname() + " " + Cmd + " :Unknown command\r\n";
        send(fd, errMsg.c_str(), errMsg.length(), 0);
        return;
    }
    (this->*(it->second))(fd, Argv);
}

// check if nickname is empty or already in use and send error message
bool Server::IsValidNickName(std::string Argv, int fd)
{
    if (Argv.empty())
    {
        std::string ErrorEmpty = ":ircserv 431 * :No nickname given\r\n";
        send(fd, ErrorEmpty.c_str(), ErrorEmpty.length(), 0);
        return true;
    }
    std::map<int, Client>::iterator it;
    for (it = _Client.begin(); it != _Client.end(); ++it)
    {
        if (it->second.getNickname() == Argv)
        {
            std::string ErrorUse = ":ircserv 433 * " + Argv + " :Nickname is already in use\r\n";
            send(fd, ErrorUse.c_str(), ErrorUse.length(), 0);
            return true;
        }
    }
    return false;
}