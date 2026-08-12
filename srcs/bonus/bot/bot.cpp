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

//   fonction checkbot qui sert a recuperer le msg pour voir si il declanche le trigger BOT <- ou autre nom a debattre mdr

 //	 donc dans l'ordre elle regarde si le caractere '#' est present et il n'y a que des espace
//   -> return dans si elle trouve car ce ne lui est pas destiner

//	 comparer la string trigger voir si on la trouve dans msg <- une comparaison sur la lenght en gros

//	 renvoyer une string "reply" si tout est good -> on a besoin de savoir quoi rep 
//	 -> dice (lancer aleatoire sur 6 ou 100 ?)
//	 -> lancer de piece (resultat true/false 1/2)
//	 -> ascii (renvoie un dessins ascii)
//	 -> joke (on met des blague nul dans une struct de string et on en renvoie une au pif)
//	 -> user (renvoie le nombre d'utilisateur sur le server)
//	 -> ping (repond pong mdr)
//	 -> 

void CheckBot(int fd, std::string Destination, std::string Msg)
{
	if (Destination.find('#') != std::string::npos)
		return;

	std::string trigger = "BOT";
	size_t start = Msg.find_first_not_of(" ");

	if (start == std::string::npos)
   		return;

	std::string trim = Msg.substr(start);

}

std::string BuildBotReply(const std::string &msg)
{

}

