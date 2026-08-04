/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 14:22:39 by amkhelif          #+#    #+#             */
/*   Updated: 2026/08/04 20:17:11 by alehamad         ###   ########.fr       */
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

class Server
{
private:
    int _port; // port du server
    std::string _PassWord; // PassWord du server
    int _ServerFd;

public:
    server();
    ~server();
    bool CheckAv(char **av);
    bool isStringPrintable(const std::string &str);
    void RunServer();
};

server::server()
{
}

server::~server()
{
}

#endif