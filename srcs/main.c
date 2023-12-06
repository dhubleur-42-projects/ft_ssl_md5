/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:33:28 by dhubleur          #+#    #+#             */
/*   Updated: 2023/12/06 16:23:44 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithms/md5.h"
#include "parser.h"

// void print(uint8_t *hash){
//     for(unsigned int i = 0; i < 16; ++i){
//         printf("%02x", hash[i]);
//     }
//     printf("\n");
// }

void print_help()
{
	ft_putstr_fd("Usage: ./ft_ssl COMMAND [OPTIONS] [ARGUMENTS]\n\n", 1);
	ft_putstr_fd("Hash stdin/file/string using a specifed algorithm\n\n", 1);
	ft_putstr_fd("The COMMAND argument must be one of:\n", 1);
	ft_putstr_fd("\tmd5\n", 1);
	ft_putstr_fd("\tsha256\n", 1);
	ft_putstr_fd("\nOPTIONS:\n", 1);
	ft_putstr_fd("\t-h\tPrint this help\n", 1);
	ft_putstr_fd("\t-p\tPrint content of stdin to stdout\n", 1);
	ft_putstr_fd("\t-q\tQuiet mode. Print just the hash\n", 1);
	ft_putstr_fd("\t-r\tReverse the format of the output\n", 1);
	ft_putstr_fd("\t-s\tPrint the sum of the given string\n", 1);
}

int	main(int argc, char **argv)
{
	t_parser parser;
	if (!parse(&parser, argc, argv))
	{
		free_parser(&parser);
		return (1);
	}

	if (parser.help)
	{
		print_help();
		free_parser(&parser);
		return (0);
	}



	free_parser(&parser);
	return (0);
}