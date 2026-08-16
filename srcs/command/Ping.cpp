/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 18:58:10 by amkhelif          #+#    #+#             */
/*   Updated: 2026/08/16 17:44:59 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

void Server::ExecutePing(int fd, std::string Argv)
{
    std::string pongMsg = "PONG " + Argv + "\r\n";

    send(fd, pongMsg.c_str(), pongMsg.length(), 0);
}