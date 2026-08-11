/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhelif <amkhelif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 19:11:10 by amkhelif          #+#    #+#             */
/*   Updated: 2026/08/10 19:17:34 by amkhelif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

void Server::ExecuteMode(int fd, std::string Argv)
{

    std::cout << "je suis dans execute Mode " << std::endl;
    // si le clients tente de changer les mode on refuse
    if (_Client[fd].getUsername() == Argv)
    {

        return;
    }
}