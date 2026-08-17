/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UtilsServer.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhelif <amkhelif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/12 14:30:57 by amkhelif          #+#    #+#             */
/*   Updated: 2026/08/17 17:47:58 by amkhelif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

// check if channel exist on server
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

// check if user is a member of channel
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

// check if user is in channel
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

// check if user is opeator is channel
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

// check if user exist on server
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

// get fd by nickname
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