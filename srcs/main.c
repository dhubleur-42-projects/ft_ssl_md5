/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:33:28 by dhubleur          #+#    #+#             */
/*   Updated: 2023/12/06 18:11:02 by dhubleur         ###   ########.fr       */
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

char *read_stdin()
{
	//leak
	char *buffer = get_next_line(0);
	if (!buffer)
	{
		ft_putstr_fd("A malloc failed\n", 2);
		return (NULL);
	}
	return (buffer);
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

	if (parser.arguments_count == 0 || parser.printing)
	{
		char *stdin_content = read_stdin();
		if (!stdin_content)
		{
			ft_putstr_fd("A malloc failed\n", 2);
			free_parser(&parser);
			return (1);
		}
		t_argument argument = { .type = STRING, .name = stdin_content };
		char *buffer;
		if (!run(parser, argument, &buffer))
		{
			free(stdin_content);
			free_parser(&parser);
			return (1);
		}
		print(parser, argument, true, buffer);
		free(buffer);
		free(stdin_content);
	}
	for (int i = 0; i < parser.arguments_count; i++)
	{
		char *buffer;
		if (!run(parser, parser.arguments[i], &buffer))
		{
			free_parser(&parser);
			return (1);
		}
		print(parser, parser.arguments[i], false, buffer);
		free(buffer);
	}

	free_parser(&parser);
	return (0);
}