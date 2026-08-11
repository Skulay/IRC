/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 20:07:20 by alehamad          #+#    #+#             */
/*   Updated: 2026/08/04 20:07:20 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include <vector>
#include <map>
#include "Client.hpp"
class Channel
{
private:
	std::string _name;
	std::string _topic;
	std::string _key;
	std::map<int, Client> _members;
	std::vector<std::string> _operators;
	std::vector<std::string> _invited;
	bool _inviteOnly;
	bool _topicRestricted;
	size_t _userLimit;

public:
	Channel();
	Channel(const std::string &name);
	Channel(const Channel &src);
	Channel &operator=(const Channel &src);
	~Channel();

	// Getters
	std::string getName() const;
	std::string getTopic() const;
	std::string getKey() const;
	bool isInviteOnly() const;
	bool isTopicRestricted() const;
	size_t getUserLimit() const;
const std::map<int, Client>& getMembers() const;
	// Setters
	void setTopic(const std::string &topic);
	void setKey(const std::string &key);
	void setInviteOnly(bool value);
	void setTopicRestricted(bool value);
	void setUserLimit(size_t limit);
	void removeKey();
	void removeUserLimit();

	// membre
	void addMember(int fd, const Client& newClient);
	// void addMember(const std::string &nickname);
	void removeMember(const std::string &nickname);
	bool hasMember(const std::string &nickname) const;

	// op
	void addOperator(const std::string &nickname);
	void removeOperator(const std::string &nickname);
	bool isOperator(const std::string &nickname) const;

	// Invit
	void addInvited(const std::string &nickname);
	bool isInvited(const std::string &nickname) const;

	// isFull solo dans son coin
	bool isFull() const;
};


#endif