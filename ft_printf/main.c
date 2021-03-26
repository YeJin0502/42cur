/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: song-yejin <song-yejin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 16:37:46 by song-yejin        #+#    #+#             */
/*   Updated: 2021/03/26 17:02:05 by song-yejin       ###   ########.fr       */
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
	// 숫자의 길이와 precsion이 같을때, -인경우 precsion + 1이 된다.
	// width 보다 precision이 쌔다.
	int d = -1;
printf("--//>|%0*.*d|<--\n", 4, -4, d);//>-->|-012|<--
printf("--//>|%0*.*d|<--\n", 4, -3, d);//>-->|-012|<--
printf("--//>|%04d|<--\n", d);//>-->|0198|<--
printf("--//>|%04d|<--\n", d);//>-->| 198|<--
printf("-->|%0*.d|<--\n", -4, d);//>-->|-12 |<--
printf("-->|%0*.d|<--\n", -4, d);//>-->|-120|<--
printf("-->|%04.0d|<--\n", d);//>-->| 198|<--
printf("-->|%04.0d|<--\n", d);//>-->|0198|<--
puts("=======s========");
ft_printf("--//>|%0*.*d|<--\n", 4, -4, d);//>-->|-012|<--
ft_printf("--//>|%0*.*d|<--\n", 4, -3, d);//>-->|-012|<--
ft_printf("--//>|%04d|<--\n", d);//>-->|0198|<--
ft_printf("--//>|%04d|<--\n", d);//>-->| 198|<--
ft_printf("-->|%0*.d|<--\n", -4, d);//>-->|-12 |<--
ft_printf("-->|%0*.d|<--\n", -4, d);//>-->|-120|<--
ft_printf("-->|%04.0d|<--\n", d);//>-->| 198|<--
ft_printf("-->|%04.0d|<--\n", d);//>-->|0198|<--
	return (0);
}