/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 16:02:21 by alehamad          #+#    #+#             */
/*   Updated: 2026/08/05 16:02:21 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Channel.hpp"
#include "../../includes/Server.hpp"

Channel::Channel() : _name(""), _topic(""), _key(""), _inviteOnly(false), _topicRestricted(false), _userLimit(0) {}

Channel::Channel(const std::string &name) : _name(name), _topic(""), _key(""), _inviteOnly(false), _topicRestricted(false), _userLimit(0) {}

Channel::Channel(const Channel &src) { *this = src; }

Channel &Channel::operator=(const Channel &src) {
    if (this != &src)
    {
        _name = src._name;
        _topic = src._topic;
        _key = src._key;
        _members = src._members;
        _operators = src._operators;
        _invited = src._invited;
        _inviteOnly = src._inviteOnly;
        _topicRestricted = src._topicRestricted;
        _userLimit = src._userLimit;
    }
    return *this;
}

Channel::~Channel() {}

std::string Channel::getName() const { return _name; }
std::string Channel::getTopic() const { return _topic; }
std::string Channel::getKey() const { return _key; }
const std::map<int, Client> &Channel::getMembers() const { return _members; }
size_t Channel::getUserLimit() const { return _userLimit; }

bool Channel::isInviteOnly() const { return _inviteOnly; }
bool Channel::isTopicRestricted() const { return _topicRestricted; }

void Channel::setTopic(const std::string &topic) { _topic = topic; }
void Channel::setKey(const std::string &key) { _key = key; }
void Channel::setInviteOnly(bool value) { _inviteOnly = value; }
void Channel::setTopicRestricted(bool value) { _topicRestricted = value; }
void Channel::setUserLimit(size_t limit) { _userLimit = limit; }
void Channel::removeKey() { _key = ""; }
void Channel::removeUserLimit() { _userLimit = 0; }

void Channel::addMember(int fd, const Client& newClient) { _members[fd] = newClient; }

void Channel::removeMember(const std::string &nickname) {
    for (std::map<int, Client>::iterator it = _members.begin(); it != _members.end(); ++it)
    {
        if (it->second.getNickname() == nickname)
        {
            _members.erase(it);
            break;
        }
    }
}

bool Channel::hasMember(const std::string &nickname) const {
    for (std::map<int, Client>::const_iterator it = _members.begin(); it != _members.end(); ++it)
    {
        if (it->second.getNickname() == nickname)
            return true;
    }
    return false;
}

void Channel::addOperator(const std::string &nickname) {
    if (!isOperator(nickname))
        _operators.push_back(nickname);
}

void Channel::removeOperator(const std::string &nickname) {
    for (std::vector<std::string>::iterator it = _operators.begin(); it != _operators.end(); ++it)
    {
        if (*it == nickname)
        {
            _operators.erase(it);
            break;
        }
    }
}

bool Channel::isOperator(const std::string &nickname) const {
    for (std::vector<std::string>::const_iterator it = _operators.begin(); it != _operators.end(); ++it)
    {
        if (*it == nickname)
            return true;
    }
    return false;
}

void Channel::addInvited(const std::string &nickname) {
    if (!isInvited(nickname))
        _invited.push_back(nickname);
}

bool Channel::isInvited(const std::string &nickname) const {
    for (std::vector<std::string>::const_iterator it = _invited.begin(); it != _invited.end(); ++it)
    {
        if (*it == nickname)
            return true;
    }
    return false;
}

bool Channel::isFull() const {
    if (_userLimit == 0)
        return false;
    return _members.size() >= _userLimit;
}

Channel *Server::getChannelByName(const std::string &name)
{
    std::vector<Channel>::iterator it;
    for (it = _Channel.begin(); it != _Channel.end(); ++it)
    {
        if (it->getName() == name)
            return &(*it); 
    }
    return NULL; 
}