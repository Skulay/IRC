/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BotCommands.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/12 15:52:45 by alehamad          #+#    #+#             */
/*   Updated: 2026/08/12 15:52:45 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/Server.hpp"

// vu qu'on parse pas la ligne je peux enlever arg des argument sauf si on fait une commande avec un besoin de parse
// ex: /dice 100 <- pour avoir un resultat sur 100 au lieux de 6

std::string Server::BotPing() {
    return "pong !";
}

std::string Server::BotDice() {
    std::stringstream ss;
    ss << "You rolled a " << (rand() % 6 + 1) << " !";
    return ss.str();
}

std::string Server::BotCoin() {
    return (rand() % 2 == 0) ? "Heads !" : "Tails !";
}

std::string Server::Botfacts() {
    std::vector<std::string> facts;
    facts.push_back("Google's first server was made with LEGO.");
    facts.push_back("RollerCoaster Tycoon was mostly written in Assembly.");
    facts.push_back("Linux was created by a 21-year-old student.");
    facts.push_back("The first website is still online");
    facts.push_back("C was created to build Unix");
    facts.push_back("A floppy disk could hold less than one modern photo.");
    facts.push_back("Doom has been ported to a pregnancy test.");
    facts.push_back("YouTube was almost a dating website.");
    facts.push_back("Creeper and Reaper were basically the first computer virus war.");
    facts.push_back("Your phone has more computing power than the Apollo spacecraft.");
    return facts[rand() % facts.size()];
}

std::string Server::BotUsers() {
    std::stringstream ss;
    ss << "There " << (_Client.size() > 1 ? "are " : "is ") << _Client.size()
       << " user" << (_Client.size() > 1 ? "s" : "") << " connected.";
    return ss.str();
}
