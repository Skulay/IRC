/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhelif <amkhelif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 18:55:43 by amkhelif          #+#    #+#             */
/*   Updated: 2026/08/10 18:56:05 by amkhelif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

void Server::ExecuteJoin(int fd, std::string Argv)
{
    for (std::vector<Channel>::size_type i = 0; i < _Channel.size(); ++i)
    {
        // si le channel exoste deja
        if (_Channel[i].getName() == Argv)
        {
            std::string Welcome = "Welcome" + _Client[fd].getNickname() + "in the" + Argv;
            _Channel[i].addMember(fd, _Client[fd]);
            send(fd, Welcome.c_str(), Welcome.length(), 0);
            return;
        }
    }
    // si le channel nexiste pas
    Channel newSalon(Argv);

    newSalon.addMember(fd, _Client[fd]);

    newSalon.addOperator(_Client[fd].getNickname());

    _Channel.push_back(newSalon);
}