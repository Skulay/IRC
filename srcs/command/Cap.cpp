/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cap.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhelif <amkhelif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 18:15:52 by amkhelif          #+#    #+#             */
/*   Updated: 2026/08/10 18:59:29 by amkhelif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

void Server::ExecuteCap(int fd, std::string Argv)
{
    // std::cout << "je suis dans execute Cap " << std::endl;
    (void)Argv;

    std::string msg = "CAP * LS :\r\n";

    send(fd, msg.c_str(), msg.length(), 0);
}