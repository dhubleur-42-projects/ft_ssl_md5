/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_intern.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:37:18 by dhubleur          #+#    #+#             */
/*   Updated: 2023/12/05 15:16:30 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithms/md5.h"

// Initial values for MD5 buffers
#define A 0x67452301
#define B 0xefcdab89
#define C 0x98badcfe
#define D 0x10325476

// Bits to rotate left by in each round
static uint32_t S[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
                       5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
                       4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
                       6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

// Constants used in each round
static uint32_t K[] = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
                       0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
                       0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
                       0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
                       0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
                       0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
                       0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
                       0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
                       0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
                       0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
                       0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
                       0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
                       0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
                       0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
                       0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
                       0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

// Padding to make the input congruent to 448 modulo 512
static uint8_t PADDING_CONTAINER[] = {0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

// MD5 internal functions
#define F(X, Y, Z) ((X & Y) | (~X & Z))
#define G(X, Y, Z) ((X & Z) | (Y & ~Z))
#define H(X, Y, Z) (X ^ Y ^ Z)
#define I(X, Y, Z) (Y ^ (X | ~Z))

// Utility function to apply bitwise rotation left
uint32_t rotateLeft(uint32_t x, uint32_t n){
    return (x << n) | (x >> (32 - n));
}


void _md5_init(_md5_context_t *context)
{
	// Prepare for accumulation
	context->size = 0;

	// Initialize buffers
	context->buffer[0] = A;
	context->buffer[1] = B;
	context->buffer[2] = C;
	context->buffer[3] = D;
}

static void md5_do_a_step(uint32_t *buffer, uint32_t *input)
{
	uint32_t tmp_a = buffer[0];
    uint32_t tmp_b = buffer[1];
    uint32_t tmp_c = buffer[2];
    uint32_t tmp_d = buffer[3];

    uint32_t function_result;

    unsigned int input_part;

    for(unsigned int i = 0; i < 64; ++i)
	{
		if (i < 16)
		{
			function_result = F(tmp_b, tmp_c, tmp_d);
			input_part = i;
		}
		else if (i < 32)
		{
			function_result = G(tmp_b, tmp_c, tmp_d);
			input_part = ((i * 5) + 1) % 16;
		}
		else if (i < 48)
		{
			function_result = H(tmp_b, tmp_c, tmp_d);
			input_part = ((i * 3) + 5) % 16;
		}
		else
		{
			function_result = I(tmp_b, tmp_c, tmp_d);
			input_part = (i * 7) % 16;
		}
        uint32_t temp = tmp_d;
        tmp_d = tmp_c;
        tmp_c = tmp_b;
        tmp_b = tmp_b + rotateLeft(tmp_a + function_result + K[i] + input[input_part], S[i]);
        tmp_a = temp;
    }

    buffer[0] += tmp_a;
    buffer[1] += tmp_b;
    buffer[2] += tmp_c;
    buffer[3] += tmp_d;
}

void _md5_fill_and_run_if_complete(_md5_context_t *context, uint8_t *input, uint64_t input_len)
{
	uint32_t prepared_input[16]; // 512-bit chunk separated into 32-bit words
    unsigned int offset = context->size % 64;
    context->size += (uint64_t)input_len;

    // Copy each byte of input to prepare a complete block
    for(unsigned int i = 0; i < input_len; ++i)
	{
        context->input[offset++] = (uint8_t)*(input + i);
        // If we have a complete block, save it and run the algorithm
        if(offset % 64 == 0)
		{
            for(unsigned int j = 0; j < 16; ++j)
			{
                // Convert to little-endian
				prepared_input[j] = 0;
                prepared_input[j] |= (uint32_t)(context->input[(j * 4) + 3]) << 24;
				prepared_input[j] |= (uint32_t)(context->input[(j * 4) + 2]) << 16;
				prepared_input[j] |= (uint32_t)(context->input[(j * 4) + 1]) <<  8;
				prepared_input[j] |= (uint32_t)(context->input[(j * 4)]);
            }
            md5_do_a_step(context->buffer, prepared_input);
            offset = 0;
        }
    }
}

void _md5_padd_and_finalize(_md5_context_t *context)
{
	uint32_t prepared_input[16]; // 512-bit chunk separated into 32-bit words
    unsigned int offset = context->size % 64;
    unsigned int padding_length = offset < 56 ? 56 - offset : (56 + 64) - offset; // 448 modulo 512, add a block if needed

    // add the padding
    _md5_fill_and_run_if_complete(context, PADDING_CONTAINER, padding_length);
	// dont add the padding_length to context->size because we want to keep the size of the message in bytes
    context->size -= (uint64_t)padding_length;

    for(unsigned int j = 0; j < 14; ++j)
	{
		// Convert to little-endian
		prepared_input[j] = 0;
		prepared_input[j] |= (uint32_t)(context->input[(j * 4) + 3]) << 24;
		prepared_input[j] |= (uint32_t)(context->input[(j * 4) + 2]) << 16;
		prepared_input[j] |= (uint32_t)(context->input[(j * 4) + 1]) <<  8;
		prepared_input[j] |= (uint32_t)(context->input[(j * 4)]);
    }
	// convert the size from bytes to bits
    prepared_input[14] = (uint32_t)(context->size * 8);
    prepared_input[15] = (uint32_t)((context->size * 8) >> 32);

    md5_do_a_step(context->buffer, prepared_input);

    // convert from little-endian
    for(unsigned int i = 0; i < 4; ++i)
	{
        context->digest[(i * 4) + 0] = (uint8_t)((context->buffer[i] & 0x000000FF));
        context->digest[(i * 4) + 1] = (uint8_t)((context->buffer[i] & 0x0000FF00) >>  8);
        context->digest[(i * 4) + 2] = (uint8_t)((context->buffer[i] & 0x00FF0000) >> 16);
        context->digest[(i * 4) + 3] = (uint8_t)((context->buffer[i] & 0xFF000000) >> 24);
    }
}