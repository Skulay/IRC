/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 15:43:54 by amkhelif          #+#    #+#             */
/*   Updated: 2026/08/17 12:11:11 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"



void Server::ExecutePass(int fd, std::string Argv)
{
    if (Argv.empty())
    {
        std::string msg = ":irc.local 461 * PASS :Not enough parameters\r\n";
        send(fd, msg.c_str(), msg.length(), 0);
        return;
    }
    if (_Client[fd].GetPassClient()) // si le client a deja valide son mdp
    {
        std::string err = ":irc.local 462 * :You may not reregister\r\n";
        send(fd, err.c_str(), err.length(), 0);
        return;
    }
    if (this->_PassWord == Argv) // si le texte corspond au mdp du serveur c bon
    {
        _Client[fd].SetPass(true);
    }
    else // so le mdp nes pas celui du serveur
    {
        std::string msg = ":irc.local 464 * :Password incorrect\r\n";
        send(fd, msg.c_str(), msg.length(), 0);
        DisconnectClient(fd, "Password incorrect");
    }
}
