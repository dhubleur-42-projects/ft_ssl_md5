/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:34:57 by dhubleur          #+#    #+#             */
/*   Updated: 2023/12/06 22:01:14 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUNNER_H
# define RUNNER_H

# include <fcntl.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>

# include "libft.h"
# include "parser.h"
# include "algorithms/md5.h"
# include "algorithms/sha256.h"

typedef void (*t_string_runner)(char *, uint8_t *);
typedef bool (*t_file_runner)(int, uint8_t *);

typedef struct {
	char *name;
	t_string_runner string_runner;
	t_file_runner file_runner;
	int hash_length;
} t_runner;

bool run(t_parser parser, t_argument argument, char *res[2]);
void print(t_parser parser, t_argument argument, bool is_stdin, char *hash);

#endif