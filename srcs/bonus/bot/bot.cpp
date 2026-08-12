/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/12 13:21:10 by alehamad          #+#    #+#             */
/*   Updated: 2026/08/12 13:21:10 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/Server.hpp"

void CheckBot(int fd, std::string Destination, std::string Msg)
{
	std::string trigger = "BOT";
	
	if (Destination.find('#') != std::string::npos)
		return;
}

std::string BuildBotReply(const std::string &msg)
{

}

