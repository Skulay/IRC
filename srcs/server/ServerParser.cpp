/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerParser.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhelif <amkhelif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 15:55:16 by amkhelif          #+#    #+#             */
/*   Updated: 2026/08/15 18:37:49 by amkhelif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

void Server::ParsBuffer(int fd)
{
    std::string buffer = _Client[fd].getBuffer();
    size_t pos = buffer.find("\n");

    while (pos != std::string::npos)
    {
        std::string command = buffer.substr(0, pos);

        SplitBuffer(command, fd);

        buffer = buffer.substr(pos + 1);

        _Client[fd].setBuffer(buffer);

        pos = buffer.find("\n");
    }
}

void Server::SplitBuffer(std::string buffer, int fd)
{
    if (!buffer.empty() && buffer[buffer.length() - 1] == '\r')
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
        return;
    }
    (this->*(it->second))(fd, Argv);
}