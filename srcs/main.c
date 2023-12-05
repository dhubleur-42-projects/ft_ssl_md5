/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:33:28 by dhubleur          #+#    #+#             */
/*   Updated: 2023/12/05 14:42:08 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithms/md5.h"
#include <stdio.h>


void print(uint8_t *hash){
    for(unsigned int i = 0; i < 16; ++i){
        printf("%02x", hash[i]);
    }
    printf("\n");
}

int	main()
{
	char *string = "Hello World";
	uint8_t result[16];
	md5_string(string, result);
	print(result);

	return (0);
}