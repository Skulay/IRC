/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cap.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 18:15:52 by amkhelif          #+#    #+#             */
/*   Updated: 2026/08/16 17:43:55 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

void Server::ExecuteCap(int fd, std::string Argv)
{
    (void)Argv;
    std::string msg = "CAP * LS :\r\n";
    send(fd, msg.c_str(), msg.length(), 0);
}