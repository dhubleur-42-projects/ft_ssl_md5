/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 21:58:19 by dhubleur          #+#    #+#             */
/*   Updated: 2023/12/06 23:02:18 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA256_H
# define SHA256_H

# include "libft.h"
# include <stdint.h>
# include <stdbool.h>

// Extern
bool sha256_file(int fd, uint8_t *result);
void sha256_string(char *string, uint8_t *result);


// Intern
typedef struct {
    uint8_t input[64];
	uint32_t datalen;
	unsigned long long bitlen;
	uint32_t buffer[8];
	uint8_t digest[32];
}	_sha256_context_t;

void _sha256_init(_sha256_context_t *context);
void _sha256_fill_and_run_if_complete(_sha256_context_t *context, uint8_t *input, uint64_t input_len);
void _sha256_padd_and_finalize(_sha256_context_t *context);

#endif