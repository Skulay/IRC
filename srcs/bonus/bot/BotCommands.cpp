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

std::string Server::BotPing(const std::string &arg)
{
    (void)arg;
    return "pong !";
}

std::string Server::BotDice(const std::string &arg)
{
    (void)arg;
    std::stringstream ss;
    ss << "You rolled a " << (rand() % 6 + 1) << " !";
    return ss.str();
}

std::string Server::BotCoin(const std::string &arg)
{
    (void)arg;
    return (rand() % 2 == 0) ? "Heads !" : "Tails !";
}

std::string Server::Botfacts(const std::string &arg)
{
    (void)arg;
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

std::string Server::BotUsers(const std::string &arg)
{
    (void)arg;
    std::stringstream ss;
    ss << "There " << (_Client.size() > 1 ? "are " : "is ") << _Client.size()
       << " user" << (_Client.size() > 1 ? "s" : "") << " connected.";
    return ss.str();
}

std::string Server::BotAscii(const std::string &arg)
{
    (void)arg;
    return "( o.o )\r\n > ^ <";
}