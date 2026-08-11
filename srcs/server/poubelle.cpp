#include "../../includes/Server.hpp"





// this function split a buffer first string is
// cmd second is argv


// void Server::ExecuteJoin(int fd, std::string Argv)
// {
// }

// void Server::ExecutePrivmsg(int fd, std::string Argv)
// {
// }

// void Server::ExecuteKick(int fd, std::string Argv)
// {
// }

// void Server::ExecuteInvite(int fd, std::string Argv)
// {
// }

// void Server::ExecuteTopic(int fd, std::string Argv)
// {
// }

// void Server::ExecuteMode(int fd, std::string Argv)
// {
// }

bool Server::IsValidNickName(std::string Argv, int fd)
{
    if (Argv.empty())
    {
        std::string ErrorEmpty = ":ircserv 431 * :No nickname given\r\n";
        send(fd, ErrorEmpty.c_str(), ErrorEmpty.length(), 0);
        return true;
    }

    std::map<int, Client>::iterator it;
    for (it = _Client.begin(); it != _Client.end(); ++it)
    {
        if (it->second.getNickname() == Argv)
        {
            std::string ErrorUse = ":ircserv 433 * " + Argv + " :Nickname is already in use\r\n";
            send(fd, ErrorUse.c_str(), ErrorUse.length(), 0);
            return true;
        }
    }

    return false;
}

