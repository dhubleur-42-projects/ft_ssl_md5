/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:33:28 by dhubleur          #+#    #+#             */
/*   Updated: 2023/12/07 12:34:35 by dhubleur         ###   ########.fr       */
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

#define STDIN_BUFFER_SIZE 1024

char *read_stdin()
{
	char *buffer = malloc(sizeof(char) * (STDIN_BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	buffer[0] = '\0';
	int buffer_size = STDIN_BUFFER_SIZE;
	int readed = 0;
	int total_readed = 0;
	char read_buffer[STDIN_BUFFER_SIZE + 1];
	while ((readed = read(0, read_buffer, STDIN_BUFFER_SIZE)) > 0)
	{
		read_buffer[readed] = '\0';
		if (total_readed + readed >= buffer_size)
		{
			buffer_size *= 2;
			char *new_buffer = malloc(sizeof(char) * (buffer_size + 1));
			if (!new_buffer)
			{
				free(buffer);
				return (NULL);
			}
			ft_strcpy(new_buffer, buffer);
			free(buffer);
			buffer = new_buffer;
		}
		ft_strcat(buffer, read_buffer);
		total_readed += readed;
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

	if (!is_valid_command(parser.command))
	{
		ft_putstr_fd("ft_ssl: ", 2);
		ft_putstr_fd(parser.command, 2);
		ft_putstr_fd(": command not found\n", 2);
		free_parser(&parser);
		return (1);
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
			free(stdin_content);
		else
		{
			print(parser, argument, true, buffer);
			free(buffer);
			free(stdin_content);
		}
	}
	for (int i = 0; i < parser.arguments_count; i++)
	{
		char *buffer;
		if (run(parser, parser.arguments[i], &buffer))
		{
			print(parser, parser.arguments[i], false, buffer);
			free(buffer);
		}
	}

	free_parser(&parser);
	return (0);
}