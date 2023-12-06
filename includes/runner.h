/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:34:57 by dhubleur          #+#    #+#             */
/*   Updated: 2023/12/06 16:54:07 by dhubleur         ###   ########.fr       */
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

bool run(t_parser parser, t_argument argument, char *res[2]);

#endif