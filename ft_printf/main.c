/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: song-yejin <song-yejin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 16:37:46 by song-yejin        #+#    #+#             */
/*   Updated: 2021/03/27 00:27:00 by song-yejin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// void test(){
// 	int prec = 3;
// 	char arr[11] = "";
// 	int num = 12345;

// 	while(prec--)
// 	{
// 		arr[prec] = num % 10 + '0';
// 		num /= 10;
// 	}
// 	arr[10] = '\0';
// 	printf("%s\n", arr);
// }

int main()
{
	unsigned int d = 2147483670;
	void *p = 0;
printf("-->|%-15p|<--\n", p);//>-->|0x93b1402710   |<--
printf("--//>|%-16.p|<--\n", p);//>-->|0x93b1402710    |<--
printf("-->|%-16p|<--\n", p);//>-->|0x93b1402710    |<--
printf("--//>|%-16.p|<--\n", p);//>-->|0x              |<--
printf("--//>|%-16.p|<--\n", p);//>-->|                |<--
printf("--//>|%-15.p|<--\n", p);//>-->|               |<--
printf("-->|%-15p|<--\n", p);//>-->|0x0            |<--
printf("--//>|%-16.p|<--\n", p);//>-->|0x              |<--
printf("--//>|%-16.p|<--\n", p);//>-->|                |<--
printf("-->|%-16p|<--\n", p);//>-->|0x0             |<--

puts("==============");
ft_printf("-->|%-15p|<--\n", p);//>-->|0x93b1402710   |<--
ft_printf("--//>|%-16.p|<--\n", p);//>-->|0x93b1402710    |<--
ft_printf("-->|%-16p|<--\n", p);//>-->|0x93b1402710    |<--
ft_printf("--//>|%-16.p|<--\n", p);//>-->|0x              |<--
ft_printf("--//>|%-16.p|<--\n", p);//>-->|                |<--
ft_printf("--//>|%-15.p|<--\n", p);//>-->|               |<--
ft_printf("-->|%-15p|<--\n", p);//>-->|0x0            |<--
ft_printf("--//>|%-16.p|<--\n", p);//>-->|0x              |<--
ft_printf("--//>|%-16.p|<--\n", p);//>-->|                |<--
ft_printf("-->|%-16p|<--\n", p);//>-->|0x0             |<--
	// 숫자의 길이와 precsion이 같을때, -인경우 precsion + 1이 된다.
	// width 보다 precision이 쌔다.
	return (0);
}