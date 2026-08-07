/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhelif <amkhelif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 14:22:39 by amkhelif          #+#    #+#             */
/*   Updated: 2026/08/07 16:09:32 by amkhelif         ###   ########.fr       */
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



class Server
{
private:
    int _port;             // port du server
    std::string _PassWord; // PassWord du server
    int _ServerFd;
    int _EpollFD; // fd qui srocke tout mos clients
    struct epoll_event events[10];
    std::map<int, Client> _Client;

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
    void ExecutePass(int fd, std::string Argv);
    void ExecuteNick(int fd, std::string Argv);
    bool IsValidNickName(std::string Argv, int fd);
};

#endif