/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:19:31 by dhubleur          #+#    #+#             */
/*   Updated: 2023/12/06 16:25:38 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	count_arguments(int argc, char **argv)
{
	int count = 0;
	for (int i = 1; i < argc; i++)
	{
		if (argv[i][0] != '-')
			count++;
	}
	return (count);
}

static bool parse_option_string(t_parser *parser, char *str, bool *is_next_arg_a_string)
{
	for (int i = 1; str[i]; i++)
	{
		if (str[i] == 'h')
			parser->help = true;
		else if (str[i] == 'p')
			parser->printing = true;
		else if (str[i] == 'q')
			parser->quiet = true;
		else if (str[i] == 'r')
			parser->reverse = true;
		else if (str[i] == 's')
			*is_next_arg_a_string = true;
		else
		{
			ft_putstr_fd("Unknown option: ", 2);
			ft_putchar_fd(str[i], 2);
			ft_putchar_fd('\n', 2);
			return (false);
		}
	}
	return (true);
}


bool	parse(t_parser *parser, int argc, char **argv)
{
	parser->help = false;
	parser->printing = false;
	parser->quiet = false;
	parser->reverse = false;
	parser->command = NULL;
	parser->arguments = NULL;
	parser->arguments_count = count_arguments(argc, argv);
	parser->arguments_count--;
	if (parser->arguments_count <= 0)
		parser->arguments = NULL;
	else
	{
		parser->arguments = malloc(sizeof(t_argument) * parser->arguments_count);
		if (!parser->arguments)
		{
			ft_putstr_fd("A malloc failed during parsing\n", 2);
			return (false);
		}
	}
	int arg_index = 0;
	bool is_next_arg_a_string = false;
	for (int i = 1; i < argc; i++)
	{
		if (argv[i][0] == '-')
		{
			if (parser->command == NULL && argv[i][1] != 'h')
			{
				ft_putstr_fd("Options cannot precede the command\n", 2);
				return (false);
			}
			if (is_next_arg_a_string)
			{
				ft_putstr_fd("After an '-s' option, there must be a string\n", 2);
				return (false);
			}
			if (!parse_option_string(parser, argv[i], &is_next_arg_a_string))
				return (false);
		}
		else
		{
			if (parser->command == NULL)
				parser->command = argv[i];
			else
			{
				parser->arguments[arg_index++] = (t_argument){argv[i], is_next_arg_a_string ? STRING : FILE};
				is_next_arg_a_string = false;
			}
		}
	}
	if (is_next_arg_a_string)
	{
		ft_putstr_fd("After an '-s' option, there must be a string\n", 2);
		return (false);
	}
	if (parser->command == NULL && !parser->help)
	{
		ft_putstr_fd("Usage: ./ft_ssl COMMAND [OPTIONS] [ARGUMENTS]\n", 2);
		return (false);
	}
	return (true);
}

void free_parser(t_parser *parser)
{
	if (parser->arguments)
		free(parser->arguments);
}