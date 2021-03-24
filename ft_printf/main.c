/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: song-yejin <song-yejin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 16:37:46 by song-yejin        #+#    #+#             */
/*   Updated: 2021/03/24 16:09:39 by song-yejin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int main()
{
    // int num1;
    // void *ptr = &num1;
    // printf("%p\n", ptr);
    // puts("");
	// //ft_printf("%9.4s", "aaaggggg");
	// //ft_printf("%+55 .*d_aaa_%-*.7d%1235", 1, 2, 3, 4);
	// // ft_printf("aaa_bbb_%abd_cc");
    // printf("%u", 20);
	// //printf("%s","aaaggggg");
    // //printf("%9.4s","aaaggggg");
    // ==>"     aaag" 로 출력된다.
    char *s = "adkfjglkadjsflj";
	printf("-->|%-2.*s|<--\n", 1, s);
    printf("-->|%-9.*s|<--\n", 4, s);
	printf("-->|%-10s|<--\n", s);
    printf("-->|%-3.7s|<--\n", s);
    printf("-->|%-6.8s|<--\n", s);
    puts("============================");
	ft_printf("-->|%-2.*s|<--\n", 1, s);
    ft_printf("-->|%-9.*s|<--\n", 4, s);
	ft_printf("-->|%-10s|<--\n", s);
    ft_printf("-->|%-3.7s|<--\n", s);
    ft_printf("-->|%-6.8s|<--\n", s);
    return (0);
}