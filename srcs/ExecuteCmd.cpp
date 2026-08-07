/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteCmd.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhelif <amkhelif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/07 14:56:12 by amkhelif          #+#    #+#             */
/*   Updated: 2026/08/07 16:41:36 by amkhelif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::ExecutePass(int fd, std::string Argv)
{
    printf("je suis dans pass\n");
    if (Argv.empty())
    {
        std::string msg = ":ircserv 461 * PASS :Not enough parameters\r\n";
        send(fd, msg.c_str(), msg.length(), 0);
        return;
    }
    if (_Client[fd].GetPassClient()) // si le client a deja valide son mdp
    {
        std::string err = ":ircserv 462 * :You may not reregister\r\n";
        send(fd, err.c_str(), err.length(), 0);
        return;
    }
    if (this->_PassWord == Argv) // si le texte corspond au mdp du serveur c bon
        _Client[fd].SetPass(true);
    else // so le mdp nes pas celui du serveur
    {
        std::string msg = ":ircserv 464 * :Password incorrect\r\n";
        send(fd, msg.c_str(), msg.length(), 0);
    }
}

void Server::ExecuteNick(int fd, std::string Argv)
{
    printf("je suis dans ExecuteNick");
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
