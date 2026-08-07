// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   Client.cpp                                         :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2026/08/04 23:57:07 by alehamad          #+#    #+#             */
// /*   Updated: 2026/08/04 23:57:07 by alehamad         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "Client.hpp"

Client::Client() : _nickname(""), _username(""), _buffer("") {}

Client::Client(const Client &src)
{
	*this = src;
}

Client &Client::operator=(const Client &src)
{
	if (this != &src)
	{
		_nickname = src._nickname;
		_username = src._username;
		_buffer = src._buffer;
	}
	return *this;
}

Client::~Client() {}

// ---- Getters ----

std::string Client::getNickname() { return _nickname; }
std::string Client::getUsername() { return _username; }
std::string Client::getBuffer() { return _buffer; }
int Client::GetPassClient() { return _CheckPass; }

// ---- Setters ----

void Client::setNickname(std::string nickName) { _nickname = nickName; }
void Client::setUsername(std::string userName) { _username = userName; }
void Client::setBuffer(std::string buffer) { _buffer = buffer; }
void Client::SetPass(int IsValide) { _CheckPass = IsValide; }
// ---- Util ----
void Client::addToBuffer(std::string bufferTwo)
{
	_buffer += bufferTwo;
}