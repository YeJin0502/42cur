/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: song-yejin <song-yejin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 16:37:46 by song-yejin        #+#    #+#             */
/*   Updated: 2021/03/29 16:49:39 by song-yejin       ###   ########.fr       */
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
	int	ret;
ret = printf("%p", p);//>-->|0x0 |<--
	printf("\n%d\n", ret);
ret = printf("-->|%-4p|<--\n", p);//>-->|0x0 |<--
	printf("%d\n", ret);
ret = printf("-->|%-3.p|<--\n", p);//>-->|0x |<--
	printf("%d\n", ret);
ret = printf("-->|%-3p|<--\n", p);//>-->|0x0|<--
	printf("%d\n", ret);
ret = printf("--//>|%-2.p|<--\n", p);//>-->|0x|<--
	printf("//%d\n", ret);
ret = printf("--//>|%-2.p|<--\n", p);//>-->|0x |<--
	printf("//%d\n", ret);
ret = printf("--//>|%-2.p|<--\n", p);//>-->|0x|<--
	printf("//%d\n", ret);
ret = printf("--//>|%-2.p|<--\n", p);//>-->|0x |<--
	printf("//%d\n", ret);
ret = printf("-->|%-2p|<--\n", p);//>-->|0x0|<--
	printf("%d\n", ret);
ret = printf("-->|%-3.p|<--\n", p);//>-->|0x |<--
	printf("%d\n", ret);
ret = printf("-->|%-3p|<--\n", p);//>-->|0x0|<--
	printf("%d\n", ret);

puts("==============");
ret = ft_printf("-->|%-4p|<--\n", p);//>-->|0x0 |<--
	printf("%d\n", ret);
ret = ft_printf("-->|%-3.p|<--\n", p);//>-->|0x |<--
	printf("%d\n", ret);
ret = ft_printf("-->|%-3p|<--\n", p);//>-->|0x0|<--
	printf("%d\n", ret);
ret = ft_printf("--//>|%-2.p|<--\n", p);//>-->|0x|<--
	printf("//%d\n", ret);
ret = ft_printf("--//>|%-2.p|<--\n", p);//>-->|0x |<--
	printf("//%d\n", ret);
ret = ft_printf("--//>|%-2.p|<--\n", p);//>-->|0x|<--
	printf("//%d\n", ret);
ret = ft_printf("--//>|%-2.p|<--\n", p);//>-->|0x |<--
	printf("//%d\n", ret);
ret = ft_printf("-->|%-2p|<--\n", p);//>-->|0x0|<--
	printf("%d\n", ret);
ret = ft_printf("-->|%-3.p|<--\n", p);//>-->|0x |<--
	printf("%d\n", ret);
ret = ft_printf("-->|%-3p|<--\n", p);//>-->|0x0|<--
	printf("%d\n", ret);
	// width 보다 precision이 쌔다.
	return (0);
}