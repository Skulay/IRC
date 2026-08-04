/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 20:07:20 by alehamad          #+#    #+#             */
/*   Updated: 2026/08/04 20:07:20 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

class Channel
{
	public:
		Channel(); //constructeur
		Channel(Channel& src); //contructeur de copy
		Channel& operator=(const Channel& src); // operator=
		~Channel(); // destructeur
};