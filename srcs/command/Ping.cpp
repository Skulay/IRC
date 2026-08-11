/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhelif <amkhelif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 18:58:10 by amkhelif          #+#    #+#             */
/*   Updated: 2026/08/10 19:06:57 by amkhelif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

void Server::ExecutePing(int fd, std::string Argv)
{
    std::cout << "je suis dans execute Ping " << std::endl;
    // if (Argv.empty())
    // {
    //     std::string errMsg = ":irc.local 409 * :No origin specified\r\n";
    //     send(fd, errMsg.c_str(), errMsg.length(), 0);
    //     return;
    // }
    // (void)Argv;
    std::string pongMsg = "PONG " + Argv + "\r\n";

    send(fd, pongMsg.c_str(), pongMsg.length(), 0);
}