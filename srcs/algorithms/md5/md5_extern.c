/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_extern.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:36:59 by dhubleur          #+#    #+#             */
/*   Updated: 2023/12/05 15:15:28 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithms/md5.h"

void md5_string(char *string, uint8_t *result)
{
	_md5_context_t context;

	_md5_init(&context);
	_md5_fill_and_run_if_complete(&context, (uint8_t *)string, ft_strlen(string));
	_md5_padd_and_finalize(&context);

	ft_memcpy(result, context.digest, 16);
}

void md5_file(int fd, uint8_t *result)
{
	(void)fd;
	(void)result;
}