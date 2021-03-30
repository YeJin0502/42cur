/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejsong <yjsong0502@daum.net>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 04:33:28 by yejsong           #+#    #+#             */
/*   Updated: 2021/03/07 04:33:28 by yejsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h> //printf 를 위해

typedef struct		t_list
{
	char			*str;
	char			*buf;
	char			*start;
	int				flag;
	int				width;
	int				prec;
	int				size;
	char			base;
	int				numeral;
	struct t_list	*pNext;
}					t_list;

#define ZERO 1
#define LEFT 2
#define PLUS 4
#define SPACE 8
#define SPECIAL 16
#define FLAG "0-"
#define BASE "cspdiuxX%%"
#define DIGIT "0123456789abcdef0123456789ABCDEF"
#define RET_ERROR -1
#define RET_SUCCESS 1

//utils.c
int					ft_isdigit(char c);
int					ft_atoi(char **s);
void				ft_memset(char *dest, int sz, char ch);
int					ft_calloc(size_t number, size_t size, void **ret, char ch);
int					ft_strlen(char *str);
int					ft_numlen(long long num, t_list *cur);
int					ft_max(int a, int b);

//valid_utils.c
int					ft_isbase(char c);
int					ft_get_flag(char **str);
int					ft_get_width(t_list **cur, char **str, va_list ap);
int					ft_get_prec(char **str, va_list ap);
int					ft_conversion(t_list *cur, va_list ap);

//string_utils.c
void				ft_memcpy(char *dest, char *src, size_t count);
int					ft_addline(char *fmt, char *iter, t_list **lst, int ck);
int					ft_parsing(char *fmt, t_list **lst);
void				make_num(char *dest, int sz, long long num, t_list *cur);

//put_utils.c
int					ft_putstring(char *str, int size);
int					ft_putchar(t_list *cur, va_list ap);
int					ft_putstr(t_list *cur, va_list ap);
char				ft_ped(t_list *cur, long long num);
int					ft_put_num(t_list *cur, void *p);

//ft_printf.c
int					ft_free(t_list *lst, int ret);
int					ft_print(t_list **lst, va_list ap);
int					ft_printf(const char *fmt, ...);


int	ft_excep(t_list *cur);
#endif