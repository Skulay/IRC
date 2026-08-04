/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 23:57:07 by alehamad          #+#    #+#             */
/*   Updated: 2026/08/04 23:57:07 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client() : nickname(""), username("")
{
}

Client::Client(const Client& src)
{
	*this = src;
}

Client& Client::operator=(const Client& src)
{
	if (this != &src)
	{
		nickname = src.nickname;
		username = src.username;
	}
	return *this;
}

Client::~Client()
{
}

std::string Client::getNickname() const
{
	return nickname;
}

std::string Client::getUsername() const
{
	return username;
}