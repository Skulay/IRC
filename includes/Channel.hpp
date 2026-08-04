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

class Channel
{
	public:
		channel(); //constructeur
		channel(channel& src); //contructeur de copy
		channel& operator=(const channel& src); // operator=
		~channel(); // destructeur


}