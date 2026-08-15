/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UtilsServer.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhelif <amkhelif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/12 14:30:57 by amkhelif          #+#    #+#             */
/*   Updated: 2026/08/15 18:16:23 by amkhelif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

bool Server::CheckChannel(std::string channel)
{
    std::vector<Channel>::const_iterator it;
    for (it = _Channel.begin(); it != _Channel.end(); it++)
    {
        if (it->getName() == channel)
            return true;
    }
    return (false);
}

bool Server::CheckHasMenber(std::string name, std::string channel)
{
    for (std::vector<Channel>::iterator it = this->_Channel.begin(); it != this->_Channel.end(); ++it)
    {
        if (it->getName() == channel)
        {
            if (it->hasMember(name))
                return (true);
            break;
        }
    }
    return (false);
}

bool Server::CheckCible(std::string name, std::string channel)
{
    for (std::vector<Channel>::iterator it = this->_Channel.begin(); it != this->_Channel.end(); ++it)
    {
        if (it->getName() == channel)
        {
            if (it->hasMember(name))
                return (true);
            break;
        }
    }
    return false;
}

bool Server::IsOperator2(std::string name, std::string channel)
{
    for (std::vector<Channel>::iterator it = this->_Channel.begin(); it != this->_Channel.end(); ++it)
    {
        if (it->getName() == channel)
        {
            if (it->isOperator(name))
                return (true);
        }
    }
    return (false);
}

bool Server::CheckClientExists(const std::string &nickname)
{
    std::map<int, Client>::const_iterator it;
    for (it = _Client.begin(); it != _Client.end(); ++it)
    {
        if (it->second.getNickname() == nickname)
            return true;
    }
    return false;
}

int Server::getFdByNickname(const std::string &nickname)
{
    std::map<int, Client>::const_iterator it;
    for (it = _Client.begin(); it != _Client.end(); ++it)
    {
        if (it->second.getNickname() == nickname)
            return it->first;
    }
    return -1;
}