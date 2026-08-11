/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhelif <amkhelif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 15:47:47 by amkhelif          #+#    #+#             */
/*   Updated: 2026/08/10 18:16:25 by amkhelif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

void Server::ExecuteNick(int fd, std::string Argv)
{
    printf("je suis dans ExecuteNick\n");
    if (!_Client[fd].GetPassClient())
    {
        std::string msg = ":ircserv 462 * :Password invalide tu ne peut pas le faire";
        send(fd, msg.c_str(), msg.length(), 0);
        return;
    }
    else if (IsValidNickName(Argv, fd))
        return;
    else
    {
        _Client[fd].setNickname(Argv);
        _Client[fd].SetNick(true);
    }
}
