/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:19:09 by dhubleur          #+#    #+#             */
/*   Updated: 2023/12/06 16:18:00 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include <stdbool.h>

typedef enum {
	FILE,
	STRING,
}	ARG_TYPE;

typedef struct {
	char *name;
	ARG_TYPE type;
}	t_argument;

typedef struct {
	bool help;
	bool printing;
	bool quiet;
	bool reverse;
	char *command;
	int arguments_count;
	t_argument *arguments;
}	t_parser;

bool	parse(t_parser *parser, int argc, char **argv);
void 	free_parser(t_parser *parser);

#endif