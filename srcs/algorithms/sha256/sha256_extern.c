/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_extern.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 21:59:40 by dhubleur          #+#    #+#             */
/*   Updated: 2023/12/07 12:36:11 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithms/sha256.h"

void sha256_string(char *string, uint8_t *result)
{
	_sha256_context_t context;

	_sha256_init(&context);
	_sha256_fill_and_run_if_complete(&context, (uint8_t *)string, ft_strlen(string));
	_sha256_padd_and_finalize(&context);

	ft_memcpy(result, context.digest, 32);	
}

bool sha256_file(int fd, uint8_t *result)
{
	char buffer[1024];
	int read_size;
	_sha256_context_t context;

	_sha256_init(&context);
	while ((read_size = read(fd, buffer, 1024)) > 0)
		_sha256_fill_and_run_if_complete(&context, (uint8_t *)buffer, read_size);

	if (read_size == -1)
	{
		ft_putstr_fd("ft_ssl: Impossible to read a file\n", 2);
		return (false);
	}

	_sha256_padd_and_finalize(&context);

	ft_memcpy(result, context.digest, 32);
	return (true);
}