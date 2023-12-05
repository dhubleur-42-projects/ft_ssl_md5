/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:36:18 by dhubleur          #+#    #+#             */
/*   Updated: 2023/12/05 15:20:06 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H

# include "libft.h"
# include <stdint.h>
# include <stdbool.h>

// Extern
bool md5_file(int fd, uint8_t *result);
void md5_string(char *string, uint8_t *result);


// Intern
typedef struct {
    uint64_t size;        // Use to accumulate the size of the message (in bytes)
    uint32_t buffer[4];   // A/B/C/D buffers for current accumulation
    uint8_t input[64];    // Next input message block
    uint8_t digest[16];   // Hash result
}	_md5_context_t;

void _md5_init(_md5_context_t *context);
void _md5_fill_and_run_if_complete(_md5_context_t *context, uint8_t *input, uint64_t input_len);
void _md5_padd_and_finalize(_md5_context_t *context);

#endif