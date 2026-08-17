/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhelif <amkhelif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 14:17:55 by amkhelif          #+#    #+#             */
/*   Updated: 2026/08/17 17:42:34 by amkhelif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

int main(int ac, char **av)
{
    Server server;
    if (ac != 3)
    {
        std::cerr << "Erreur : Mauvais nombre d'arguments." << std::endl;
        return (1);
    }
    else if (server.CheckAv(av))
        return (1);

    try
    {
        server.RunServer();
    }
    catch (const std::exception &e)
    {
        std::cerr << "ERROR " << e.what() << std::endl;
        return 1;
    }
    return (0);
}
