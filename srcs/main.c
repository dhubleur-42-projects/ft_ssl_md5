/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:33:28 by dhubleur          #+#    #+#             */
/*   Updated: 2023/12/06 17:10:13 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runner.h"
#include "parser.h"

void print_help()
{
	ft_putstr_fd("Usage: ./ft_ssl COMMAND [OPTIONS] [ARGUMENTS]\n\n", 1);
	ft_putstr_fd("Hash stdin/file/string using a specifed algorithm\n\n", 1);
	ft_putstr_fd("The COMMAND argument must be one of:\n", 1);
	ft_putstr_fd("\tmd5\n", 1);
	ft_putstr_fd("\tsha256\n", 1);
	ft_putstr_fd("\nOPTIONS:\n", 1);
	ft_putstr_fd("\t-h\tPrint this help\n", 1);
	ft_putstr_fd("\t-p\tPrint content of stdin to stdout\n", 1);
	ft_putstr_fd("\t-q\tQuiet mode. Print just the hash\n", 1);
	ft_putstr_fd("\t-r\tReverse the format of the output\n", 1);
	ft_putstr_fd("\t-s\tPrint the sum of the given string\n", 1);
}

int	main(int argc, char **argv)
{
	t_parser parser;
	if (!parse(&parser, argc, argv))
	{
		free_parser(&parser);
		return (1);
	}

	if (parser.help)
	{
		print_help();
		free_parser(&parser);
		return (0);
	}

	bool read_stdin = parser.arguments_count == 0 || parser.printing;
	char *buffer;
	for (int i = read_stdin ? -1 : 0; i < parser.arguments_count; i++)
	{
		t_argument argument;
		if (i == -1)
		{
			argument.type = FILE_NAME;
			argument.name = NULL;
		}
		else
			argument = parser.arguments[i];
		if (!run(parser, argument, &buffer))
		{
			free_parser(&parser);
			return (1);
		}
		printf("%s\n", buffer);
	}

	free_parser(&parser);
	return (0);
}