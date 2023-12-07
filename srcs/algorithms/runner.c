/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:34:50 by dhubleur          #+#    #+#             */
/*   Updated: 2023/12/07 12:33:15 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runner.h"

#define RUNNERS_COUNT 2
const static t_runner runners[RUNNERS_COUNT] = {
	(t_runner){ "md5", md5_string, md5_file, 16 },
	(t_runner){ "sha256", sha256_string, sha256_file, 32 },
};

bool is_valid_command(char *command)
{
	for (int i = 0; i < RUNNERS_COUNT; i++)
	{
		if (ft_strcmp(runners[i].name, command) == 0)
			return true;
	}
	return false;
}

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
		(*buffer)[i * 2] = "0123456789abcdef"[hash[i] / 16];
		(*buffer)[i * 2 + 1] = "0123456789abcdef"[hash[i] % 16];
	}
	(*buffer)[hash_length * 2] = '\0';
	return (true);
}

bool run(t_parser parser, t_argument argument, char **res)
{
	t_runner runner = { 0 };
	for (int i = 0; i < RUNNERS_COUNT; i++)
	{
		if (ft_strcmp(runners[i].name, parser.command) == 0)
		{
			runner = runners[i];
			break;
		}
	}
	if (runner.name == NULL)
		return false;
	uint8_t hash[runner.hash_length];
	if (argument.type == STRING)
		runner.string_runner(argument.name, hash);
	else
	{
		int fd = open(argument.name, O_RDONLY);
		if (fd == -1)
		{
			ft_putstr_fd("ft_ssl: ", 2);
			ft_putstr_fd(argument.name, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return false;
		}
		bool res = runner.file_runner(fd, hash);
		close(fd);
		if (!res)
			return false;
	}
	if (!convert_hash_to_string(hash, runner.hash_length, res))
		return false;
	return true;
}