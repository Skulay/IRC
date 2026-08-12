/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerParser.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhelif <amkhelif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 15:55:16 by amkhelif          #+#    #+#             */
/*   Updated: 2026/08/12 12:13:54 by amkhelif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

void Server::ParsBuffer(int fd)
{
    std::string buffer = _Client[fd].getBuffer();

    // std::cout << "DEBUG - Buffer brut recu : [" << buffer << "]" << std::endl;
    // printf("je suis la dans parsbuffer\n");
    // if (buffer == "CAP LS")
    // {
    //     std::cout << " jai recu cap ls" << std::endl;
    // }
    size_t pos = buffer.find("\n");

    while (pos != std::string::npos)
    {
        // printf("je suis dans la boucle while\n");

        std::string command = buffer.substr(0, pos);

        // if (!command.empty() && command[command.length() - 1] == '\r')
        //     buffer.erase(buffer.length() - 1, 1);

        SplitBuffer(command, fd);

        buffer = buffer.substr(pos + 1);

        _Client[fd].setBuffer(buffer);

        pos = buffer.find("\n");
    }
}

void Server::SplitBuffer(std::string buffer, int fd)
{
    std::string cmd;
    std::string argv;

    size_t pos = buffer.find(" ");

    if (pos == std::string::npos)
    {
        cmd = buffer;
        cmd.push_back('\0');
        argv = "";
    }
    else
    {
        cmd = buffer.substr(0, pos);
        buffer.erase(0, pos + 1);
        size_t pos = buffer.find("\r");
        argv = buffer.substr(0, pos);
        // std::cout << "salut" << argv << std::endl;
        // argv.push_back('\0');
    }
    ExecuteCommand(fd, cmd, argv);
    // std::cout << "Client " << fd << " | Commande: [" << cmd << "] | Args: [" << argv << "]\n";
}

void Server::ExecuteCommand(int fd, std::string Cmd, std::string Argv)
{

    std::map<std::string, void (Server::*)(int, std::string)>::iterator it = _commands.find(Cmd);
    // std::cout << "je suis dans Execute Command " << std::endl;
    // std::cout << Cmd << Argv << std::endl;
    if (it == _commands.end())
    {
        std::cerr << "this CMD " << Cmd << " is not available" << std::endl;
        std::cerr << "Command: " << Cmd + " " << Argv << std::endl;
        return;
    }
    (this->*(it->second))(fd, Argv);
}