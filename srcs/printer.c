/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:39:28 by dhubleur          #+#    #+#             */
/*   Updated: 2023/12/07 12:23:27 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runner.h"

static void print_without_newline(char *str)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			ft_putstr_fd("\\n", 1);
		else
			ft_putchar_fd(str[i], 1);
		i++;
	}
}

static void print_to_upper(char *str)
{
	int i = 0;
	while (str[i])
	{
		ft_putchar_fd(ft_toupper(str[i]), 1);
		i++;
	}

}

static void print_info(t_parser parser, t_argument argument, bool is_stdin, char *algorithm)
{
	print_to_upper(algorithm);
	ft_putstr_fd("(", 1);
	if (is_stdin)
	{
		if (parser.printing)
		{
			ft_putstr_fd("\"", 1);
			print_without_newline(argument.name);
			ft_putstr_fd("\"", 1);
		}
		else
		{
			ft_putstr_fd("stdin", 1);
		}
	}
	else
	{
		if (argument.type == STRING)
		{
			ft_putstr_fd("\"", 1);
			print_without_newline(argument.name);
			ft_putstr_fd("\"", 1);
		}
		else
		{
			ft_putstr_fd(argument.name, 1);
		}
	}
	ft_putstr_fd(")", 1);
}

void print(t_parser parser, t_argument argument, bool is_stdin, char *hash)
{
	if (!parser.quiet && !parser.reverse)
	{
		print_info(parser, argument, is_stdin, parser.command);
		ft_putstr_fd(" = ", 1);
	}
	ft_putstr_fd(hash, 1);
	if (!parser.quiet && parser.reverse)
	{
		ft_putstr_fd(" = ", 1);
		print_info(parser, argument, is_stdin, parser.command);
	}
	ft_putstr_fd("\n", 1);
}