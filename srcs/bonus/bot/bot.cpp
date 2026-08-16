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

void Server::CheckBot(int fd, std::string Destination, std::string Msg) {
    if (Destination != "BOT")
        return;

    std::string reply = BuildBotReply(Msg);
    std::string fullMsg = ":BOT!bot@localhost PRIVMSG " + Destination + " :" + reply + "\r\n";
    send(fd, fullMsg.c_str(), fullMsg.length(), 0);
}

std::string Server::BuildBotReply(const std::string &msg) {
    size_t space = msg.find(' ');
    std::string cmd = (space == std::string::npos) ? msg : msg.substr(0, space);
    std::map<std::string, BotCmd>::iterator it = _botCommands.find(cmd);

    if (it == _botCommands.end())
        return "Unknown command: Type help";
    return (this->*(it->second))();
}

