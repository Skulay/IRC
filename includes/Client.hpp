/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 20:07:44 by alehamad          #+#    #+#             */
/*   Updated: 2026/08/04 20:07:44 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

class client
{
	private:
		std::string nickname;
		std::string username;

	public:
		client(); // constructeur
		client(const client& src); // constructeur de copy
		client& operator=(const client& src); // operator=
		~client(); // destructeur

			// GETTERR
		std::string getNickname();
		std::string getUsername();
};

