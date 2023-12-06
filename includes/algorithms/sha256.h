/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 21:58:19 by dhubleur          #+#    #+#             */
/*   Updated: 2023/12/06 22:16:37 by dhubleur         ###   ########.fr       */
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
    uint64_t size;        // Use to accumulate the size of the message (in bytes)
    uint32_t buffer[8];   // A/B/C/D/E/F/G/H buffers for current accumulation
    uint8_t input[64];    // Next input message block
    uint8_t digest[32];   // Hash result
}	_sha256_context_t;

void _sha256_init(_sha256_context_t *context);
void _sha256_fill_and_run_if_complete(_sha256_context_t *context, uint8_t *input, uint64_t input_len);
void _sha256_padd_and_finalize(_sha256_context_t *context);

#endif