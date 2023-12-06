/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_intern.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 22:01:27 by dhubleur          #+#    #+#             */
/*   Updated: 2023/12/06 22:37:04 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithms/sha256.h"

#define A 0x6a09e667
#define B 0xbb67ae85
#define C 0x3c6ef372
#define D 0xa54ff53a
#define E 0x510e527f
#define F 0x9b05688c
#define G 0x1f83d9ab
#define H 0x5be0cd19

#define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define EP0(x) (rotateRight(x,2) ^ rotateRight(x,13) ^ rotateRight(x,22))
#define EP1(x) (rotateRight(x,6) ^ rotateRight(x,11) ^ rotateRight(x,25))
#define SIG0(x) (rotateRight(x,7) ^ rotateRight(x,18) ^ ((x) >> 3))
#define SIG1(x) (rotateRight(x,17) ^ rotateRight(x,19) ^ ((x) >> 10))

static const uint32_t k[64] = {
	0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
	0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
	0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
	0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
	0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
	0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
	0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
	0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
};

static uint32_t rotateRight(uint32_t x, uint32_t n){
	return (x >> n) | (x << (32 - n));
}

void _sha256_init(_sha256_context_t *context)
{
	context->size = 0;

	context->buffer[0] = A;
	context->buffer[1] = B;
	context->buffer[2] = C;
	context->buffer[3] = D;
	context->buffer[4] = E;
	context->buffer[5] = F;
	context->buffer[6] = G;
	context->buffer[7] = H;
}

static void sha256_do_a_round(uint32_t *buffer, uint8_t *input)
{
	uint32_t tmp_a = buffer[0];
	uint32_t tmp_b = buffer[1];
	uint32_t tmp_c = buffer[2];
	uint32_t tmp_d = buffer[3];
	uint32_t tmp_e = buffer[4];
	uint32_t tmp_f = buffer[5];
	uint32_t tmp_g = buffer[6];
	uint32_t tmp_h = buffer[7];

	uint32_t m[64];

	int i, j;
	for (i = 0, j = 0; i < 16; ++i, j += 4)
		m[i] = (input[j] << 24) | (input[j + 1] << 16) | (input[j + 2] << 8) | (input[j + 3]);
	for ( ; i < 64; ++i)
		m[i] = SIG1(m[i - 2]) + m[i - 7] + SIG0(m[i - 15]) + m[i - 16];

	uint32_t t1, t2;
	for (i = 0; i < 64; ++i) {
		t1 = tmp_h + EP1(tmp_e) + CH(tmp_e,tmp_f,tmp_g) + k[i] + m[i];
		t2 = EP0(tmp_a) + MAJ(tmp_a,tmp_b,tmp_c);
		tmp_h = tmp_g;
		tmp_g = tmp_f;
		tmp_f = tmp_e;
		tmp_e = tmp_d + t1;
		tmp_d = tmp_c;
		tmp_c = tmp_b;
		tmp_b = tmp_a;
		tmp_a = t1 + t2;
	}

	buffer[0] += tmp_a;
	buffer[1] += tmp_b;
	buffer[2] += tmp_c;
	buffer[3] += tmp_d;
	buffer[4] += tmp_e;
	buffer[5] += tmp_f;
	buffer[6] += tmp_g;
	buffer[7] += tmp_h;
}

void _sha256_fill_and_run_if_complete(_sha256_context_t *context, uint8_t *input, uint64_t input_len)
{
	uint8_t prepared_input[64];

	unsigned int offset = context->size % 64;
    context->size += (uint64_t)input_len;

    for(unsigned int i = 0; i < input_len; ++i)
	{
        context->input[offset++] = (uint8_t)*(input + i);
        if(offset % 64 == 0)
		{
			for(unsigned int j = 0; j < 64; ++j)
			{
				prepared_input[j] = 0;
				prepared_input[j] |= (uint32_t)(context->input[(j * 4) + 3]) << 24;
				prepared_input[j] |= (uint32_t)(context->input[(j * 4) + 2]) << 16;
				prepared_input[j] |= (uint32_t)(context->input[(j * 4) + 1]) <<  8;
				prepared_input[j] |= (uint32_t)(context->input[(j * 4) + 0]) <<  0;
			}
            sha256_do_a_round(context->buffer, prepared_input);
            offset = 0;
		}
	}
}

void _sha256_padd_and_finalize(_sha256_context_t *context)
{
	uint32_t i = context->size % 64;

	if (context->size < 56) {
		context->input[i++] = 0x80;
		while (i < 56)
			context->input[i++] = 0x00;
	}
	else {
		context->input[i++] = 0x80;
		while (i < 64)
			context->input[i++] = 0x00;
		sha256_do_a_round(context->buffer, context->input);
		ft_memset(context->input, 0, 56);
	}

	context->size *= 8;
	context->input[63] = context->size;
	context->input[62] = context->size >> 8;
	context->input[61] = context->size >> 16;
	context->input[60] = context->size >> 24;
	context->input[59] = context->size >> 32;
	context->input[58] = context->size >> 40;
	context->input[57] = context->size >> 48;
	context->input[56] = context->size >> 56;

	sha256_do_a_round(context->buffer, context->input);

	for (int i = 0; i < 4; ++i) {
		context->digest[i] = context->buffer[0] >> (24 - i * 8);
		context->digest[i + 4] = context->buffer[1] >> (24 - i * 8);
		context->digest[i + 8] = context->buffer[2] >> (24 - i * 8);
		context->digest[i + 12] = context->buffer[3] >> (24 - i * 8);
		context->digest[i + 16] = context->buffer[4] >> (24 - i * 8);
		context->digest[i + 20] = context->buffer[5] >> (24 - i * 8);
		context->digest[i + 24] = context->buffer[6] >> (24 - i * 8);
		context->digest[i + 28] = context->buffer[7] >> (24 - i * 8);
	}

}