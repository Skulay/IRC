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

#include "../../includes/Client.hpp"

Client::Client() : _nickname(""), _username(""), _buffer(""),
    _CheckPass(false), _HasNick(false), _UserName(false), _validClient(false) {}

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
std::string Client::getNickname() const { return _nickname; }
std::string Client::getUsername() const { return _username; }
std::string Client::getBuffer() const { return _buffer; }
int Client::GetPassClient() const { return _CheckPass; }
int Client::GetNickClient() const { return _HasNick; }
int Client::GetUserNameClient() const { return _UserName; }
int Client::GetValidClient() const { return _validClient; }

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
void Client::SetNick(int IsValide)
{
	_HasNick = IsValide;
}

// int Client::GetNickClient()
// {
// 	return _HasNick;
// }
// int Client::GetUserNameClient()
// {
// 	return _UserName;
// }
// void Client::SetValidClient(int IsValide)
// {
// 	_validClient = IsValide;
// }

void Client::SetUserNameB(int IsValide)
{
	_UserName = IsValide;
}

// int Client::GetValidClient()
// {
// 	return _validClient;
// }
