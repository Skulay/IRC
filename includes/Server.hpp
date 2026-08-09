/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 14:22:39 by amkhelif          #+#    #+#             */
/*   Updated: 2026/08/09 19:58:52 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <cstdio>
#include <sys/epoll.h>
#include <sstream>
#include <algorithm>
#include <map>
#include "Client.hpp"
#include <algorithm>
#include "Channel.hpp"

class Server
{
    private:
        int _port;             // port du server
        std::string _PassWord; // PassWord du server
        int _ServerFd;
        int _EpollFD; // fd qui srocke tout mos clients
        struct epoll_event events[10];
        std::map<int, Client> _Client;
        std::vector<Channel> _Channel; // tableau de channel
        std::map<std::string, void (Server::*)(int, std::string)> _commands;

        void InitCommands(void);
        void ExecutePass(int fd, std::string Argv);
        void ExecuteNick(int fd, std::string Argv);
        bool IsValidNickName(std::string Argv, int fd);
        void ExecuteUser(int fd, std::string Argv);
        void ExecuteJoin(int fd, std::string Argv);
        void ExecutePrivmsg(int fd, std::string Argv);
        void ExecuteKick(int fd, std::string Argv);
        void ExecuteInvite(int fd, std::string Argv);
        void ExecuteTopic(int fd, std::string Argv);
        void ExecuteMode(int fd, std::string Argv);

    public:
        Server();
        ~Server();
        bool CheckAv(char **av);
        bool isStringPrintable(const std::string &str);
        void RunServer(void);
        bool LoopServer(void);
        void AcceptNewClient(int fd);
        void ReceiveFromClient(int fd);
        void ParsBuffer(int fd);
        void SplitBuffer(std::string buffer, int fd);
        void ExecuteCommand(int fd, std::string Cmd, std::string Argv);
};

void Server::ExecuteJoin(std::string Argv, int fd)
{
    for (std::vector<Channel>::size_type i = 0; i < _Channel.size(); ++i)
    {
        // si le channel exoste deja
        if (_Channel[i].getName() == Argv)
        {
            std::string Welcome = "Welcome" + _Client[fd].getNickname() + "in the" + Argv;
            _Channel[i].addMember(fd, _Client[fd]);
            send(fd,Welcome.c_str(),Welcome.length(),0);
            return;
        }
    }
    // si le channel nexiste pas
    
    
}
#endif