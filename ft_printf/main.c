/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: song-yejin <song-yejin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 16:37:46 by song-yejin        #+#    #+#             */
/*   Updated: 2021/03/26 19:44:19 by song-yejin       ###   ########.fr       */
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
	printf("%u\n", d);
	ft_printf("%u", d);
	// 숫자의 길이와 precsion이 같을때, -인경우 precsion + 1이 된다.
	// width 보다 precision이 쌔다.
	return (0);
}