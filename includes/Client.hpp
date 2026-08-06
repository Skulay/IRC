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

class Client
{
	private:
		std::string _nickname;
		std::string _username;

	public:
		Client(); // constructeur
		Client(const Client& src); // constructeur de copy
		Client& operator=(const Client& src); // operator=
		~Client(); // destructeur

			// GETTERR
		std::string getNickname();
		std::string getUsername();

			// SETTERR
		void setNickname(std::string nickName);
		void setUsername(std::string userName);
};

