/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 20:07:44 by alehamad          #+#    #+#             */
/*   Updated: 2026/08/04 20:07:44 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <fcntl.h>
#include <string>
class Client
{
private:
	std::string _nickname;
	std::string _username;
	std::string _buffer;
	bool _CheckPass;
	bool _HasNick;

public:
	Client();							  // constructeur
	Client(const Client &src);			  // constructeur de copy
	Client &operator=(const Client &src); // operator=
	~Client();							  // destructeur
	// GETTERR
	std::string getNickname();
	std::string getUsername();
	std::string getBuffer();
	int GetPassClient();
	int GetNickClient();
	// SETTERR
	void setNickname(std::string nickName);
	void setUsername(std::string userName);
	void setBuffer(std::string buffer);
	void SetPass(int IsValide);
	void SetNick(int IsValide);
	// UTIL
	void addToBuffer(std::string bufferTwo);
};


#endif
