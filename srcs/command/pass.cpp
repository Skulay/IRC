/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhelif <amkhelif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 15:43:54 by amkhelif          #+#    #+#             */
/*   Updated: 2026/08/10 18:41:04 by amkhelif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"



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
    // std::cout << std::endl << this->_PassWord << this->_PassWord.length() << Argv << Argv.length() << std::endl;
    std::cout << this->_PassWord.length() << this->_PassWord << std::endl;
    std::cout << Argv.length() << Argv << std::endl;
    if (this->_PassWord == Argv) // si le texte corspond au mdp du serveur c bon
    {
        _Client[fd].SetPass(true);
    }
    else // so le mdp nes pas celui du serveur
    {
        std::cout << "test\n";
        std::string msg = ":ircserv 464 * :Password incorrect\r\n";
        send(fd, msg.c_str(), msg.length(), 0);
    }
}
