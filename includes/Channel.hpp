/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 20:07:20 by alehamad          #+#    #+#             */
/*   Updated: 2026/08/04 20:07:20 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*		 - Change the channel’s mode:
		· i: Set/remove Invite-only channel										| variable mise mais pas de fonction
		· t: Set/remove the restrictions of the TOPIC command to channel		| variable mise mais pas de fonction
		operators
		· k: Set/remove the channel key (password)								| variable mise mais pas de fonction
		· o: Give/take channel operator privilege								| ????? contener pour gerer une liste de membre ???
		· l: Set/remove the user limit to channel								| variable mise mais pas de fonction
*/
class Channel
{
	private:
		std::string	name;
		std::string	topic; // genre TOPIC #channel ou TOPIC #channel :nouveau topic ici <- pour le modifier
		std::string	key; // pour le mode -k, nommer key au lieux de password parce ->
						 // -> que si on a deja password quelque part sa seras plus clair
		bool		inviteOnly; // 
		bool		topicRestricted; // mode +t
		size_t		userLimit; // je te fait pas un dessin ta capter, mode +l (0 = pas de limite)
	public:
		channel(); //constructeur
		channel(channel& src); //contructeur de copy
		channel& operator=(const channel& src); // operator=
		~channel(); // destructeur
}