/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:34:50 by dhubleur          #+#    #+#             */
/*   Updated: 2023/12/06 17:09:17 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runner.h"

bool convert_hash_to_string(uint8_t *hash, int hash_length, char **buffer)
{
	*buffer = malloc(hash_length * 2 + 1);
	if (!*buffer)
	{
		ft_putstr_fd("A malloc failed\n", 2);
		return (false);
	}
	for (int i = 0; i < hash_length; i++)
	{
		sprintf(*buffer + (i * 2), "%02x", hash[i]);
	}
	(*buffer)[hash_length * 2] = '\0';
	return (true);
}

bool run(t_parser parser, t_argument argument, char **res)
{
	if (ft_strcmp(parser.command, "md5") == 0)
	{
		uint8_t hash[16];
		if (argument.type == STRING)
			md5_string(argument.name, hash);
		else
		{
			int fd = 0;
			if (argument.name != NULL)
				fd = open(argument.name, O_RDONLY);
			if (fd == -1)
			{
				ft_putstr_fd("ft_ssl: ", 2);
				ft_putstr_fd(argument.name, 2);
				ft_putstr_fd(": No such file or directory\n", 2);
				return false;
			}
			bool res = md5_file(fd, hash);
			close(fd);
			if (!res)
				return false;
		}
		return convert_hash_to_string(hash, 16, res);
	}
	ft_putstr_fd("ft_ssl: ", 2);
	ft_putstr_fd(parser.command, 2);
	ft_putstr_fd(": command not found\n", 2);
	return false;
}