/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 14:22:39 by amkhelif          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/08/15 16:20:47 by amkhelif         ###   ########.fr       */
=======
/*   Updated: 2026/08/14 17:44:57 by alehamad         ###   ########.fr       */
>>>>>>> origin/master
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <cstdio>
#include <sys/epoll.h>
#include <sstream>
#include <algorithm>
#include <map>
#include "Client.hpp"
#include <algorithm>
#include "Channel.hpp"

class Channel;

class Server
{
private:
    int _port;
    std::string _PassWord;
    int _ServerFd;
    int _EpollFD;
    struct epoll_event events[10];
    std::map<int, Client> _Client;
    std::vector<Channel> _Channel;
    std::map<std::string, void (Server::*)(int, std::string)> _commands;

    void InitCommands(void);
    void ExecutePass(int fd, std::string Argv);
    void ExecuteNick(int fd, std::string Argv);
    bool IsValidNickName(std::string Argv, int fd);
    void ExecuteUser(int fd, std::string Argv);
    void ExecuteJoin(int fd, std::string Argv);
    void ExecuteCap(int fd, std::string Argv);
    void ExecutePing(int fd, std::string Argv);
    void SendMessage(int fd, std::string Argv);
    void SendDestinataire(int fd, std::string Destination, std::string Msg);
    void ExecutePrivmsg(int fd, std::string Argv);
    void ExecuteKick(int fd, std::string Argv);
    void ExecuteInvite(int fd, std::string Argv);
    void ExecuteTopic(int fd, std::string Argv);
    void ExecuteMode(int fd, std::string Argv);
    void ExecuteQuit(int fd, std::string Argv);
    void ExecutePart(int fd, std::string Argv);

    //BOT
    typedef std::string (Server::*BotCmd)();
    std::map<std::string, BotCmd> _botCommands;

    void InitBotCommands(void);
    void CheckBot(int fd, std::string Destination, std::string Msg);
    std::string BuildBotReply(const std::string &msg);

    std::string BotPing();
    std::string BotDice();
    std::string BotCoin();
    std::string Botfacts();
    std::string BotUsers();
    std::string BotHelp();

public:
    Server();
    ~Server();
    bool CheckAv(char **av);
    bool isStringPrintable(const std::string &str);
    bool IsOperator2(int fd, std::string name, std::string channel);
    void RunServer(void);
    bool LoopServer(void);
    void AcceptNewClient(int fd);
    void ReceiveFromClient(int fd);
    void ParsBuffer(int fd);
    void SplitBuffer(std::string buffer, int fd);
    void ExecuteCommand(int fd, std::string Cmd, std::string Argv);
    bool CheckChannel(int fd, std::string channel);
    bool CheckHasMenber(std::string name, std::string channel);
    bool CheckCible(std::string name, std::string channel);
    bool valideKick(int fd, std::string name, std::string channel);
    void kickuser(int fd, std::string pseudo, std::string channel, std::string reason);
    bool ValideInvite(int fd, std::string cible, std::string channel);
    bool CheckClientExists(const std::string &nickname);
    Channel *getChannelByName(const std::string &name);
    int getFdByNickname(const std::string &nickname);
    bool ParsTopic(int fd, std::string Channel, bool NewSubject);
    bool ValidExecuteMode(int fd, std::string Channel, std::string Mode, std::string ArgMode);
    bool ValideMode(int fd, std::string Mode, std::string ArgvMode);
    void ExecuteCmd(int fd, std::string channel, bool NewTopic, std::string Topic);
    void Execute(int fd, std::string Channel, std::string Mode, std::string ArgMode);
    void DisconnectClient(int fd, std::string reason);
};

#endif