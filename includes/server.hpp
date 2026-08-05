/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhelif <amkhelif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 14:22:39 by amkhelif          #+#    #+#             */
/*   Updated: 2026/08/05 12:06:33 by amkhelif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Server_HPP
#define Server_HPP

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

class Server
{
private:
    int _port; // port du Server
    std::string _PassWord; // PassWord du Server
    int _ServerFd;

public:
    Server();
    ~Server();
    bool CheckAv(char **av);
    bool isStringPrintable(const std::string &str);
    void RunServer();
};

Server::Server()
{
}

Server::~Server()
{
}

#endif