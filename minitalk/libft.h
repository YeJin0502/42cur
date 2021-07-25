/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: song-yejin <song-yejin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 19:03:38 by song-yejin        #+#    #+#             */
/*   Updated: 2021/07/13 18:37:22 by song-yejin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>

# define RET_ERROR -1
# define RET_SUCCESS 1
# define RET_EOF 0

//Libft.c
void	ft_exit(char *s);
void	ft_free(char **line);
void			ft_memset(char *dest, int size);
void			*ft_calloc(size_t number, size_t size);
int				ft_isdigit(char c);
size_t		ft_strlen(char *str);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
long long		ft_atoi(char **s);
size_t		ft_strlcpy(char *dest, const char *src, size_t n);


#endif