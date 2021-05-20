/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: song-yejin <song-yejin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 17:43:51 by song-yejin        #+#    #+#             */
/*   Updated: 2021/05/20 20:02:12 by song-yejin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_exit(char *s)
{
	const int len = ft_strlen(s);

	write(1, s, len);
	write(1, "\n", 1);
	exit(0);
}

t_info	cub_init(int ac, char *ag[])
{
	t_info		info;
	const int	fd = open(ag[1], O_RDONLY); //ag[1]
	int n = ac;
	
	ft_memset((char *)&info, sizeof(t_info), 0);
	if (fd < 0)
		ft_exit("ERROR: FILE CANNOT BE FOUND");
	ft_memset((char*)&info, sizeof(t_info), 0);
	if (cub_parsing(fd, &info) != (1 << 9) - 1)
		ft_exit("ERROR: CHECK FILE CONTENTS");
	ft_valid(&info);
	close(fd);
	n = n / 1;
	return (info);
}

void	load_image(t_game *g, char *path, t_img *img, int i)
{
	int	y;
	int	x;
	img->img = mlx_xpm_file_to_image(g->mlx, path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
	g->texture[i] = (int *)ft_calloc(img->img_width * img->img_height, sizeof(int), 0);
	g->sz_img[i].x = img->img_width;
	g->sz_img[i].y = img->img_height;
	y = -1;
	while (++y < img->img_height)
	{
		x = -1;
		while (++x < img->img_width)
			g->texture[i][img->img_width * y + x] = img->data[img->img_width * y + x];
	}
	mlx_destroy_image(g->mlx, img->img);
}

void	load_texture(t_info *info, t_game *g)
{
	t_img	img;
	int		i;

	i = -1;
	g->texture = (int **)ft_calloc(sizeof(int *), 6, 0); //sprite까지
	while (++i < 5) //바닥이랑 위 텍스쳐 필요하면 개수 올리기
		load_image(g, (char *)info->cub_info[i], &img, i);
}

void	floor_color(t_game *g)
{
	int	y;
	int	x;
	int	color;

	y = g->win_y / 2;
	while (++y < g->win_y)
	{
		x = -1;
		while (++x < g->win_x)
		{
			color = g->c_rgb;
			//color = (color >> 1) & 8355711;
			g->buf[y][x] = color;
			color = g->f_rgb;
			//color = (color >> 1) & 8355711;
			g->buf[g->win_y - y - 1][x] = color;
		}
	}
}


void	calc(t_game *g)
{
	floor_color(g);
	wall_casting(g);
	sprite_casting(g);
}

void	draw(t_game *g)
{
	int	x;
	int	y;

	y = -1;
	while (++y < g->win_y)
	{
		x = -1;
		while (++x < g->win_x)
		{
			g->img.data[y * g->win_x + x] = g->buf[y][x];
		}
	}
	mlx_put_image_to_window(g->mlx, g->win, g->img.img, 0, 0);
}

void	key_update(t_game *g)
{
	double	oldDirX;
	double	oldPlaneX;

	if (g->key.w)
	{
		if (!g->map[(int)(g->posX + g->dirX * 0.05)][(int)(g->posY)])
			g->posX += g->dirX * 0.05;
		if (!g->map[(int)(g->posX)][(int)(g->posY + g->dirY * 0.05)])
			g->posY += g->dirY * 0.05;
	}
	if (g->key.s)
	{
		if (!g->map[(int)(g->posX - g->dirX * 0.05)][(int)(g->posY)])
			g->posX -= g->dirX * 0.05;
		if (!g->map[(int)(g->posX)][(int)(g->posY - g->dirY * 0.05)])
			g->posY -= g->dirY * 0.05;
	}
	if (g->key.d)
	{
		oldDirX = g->dirX;
		g->dirX = g->dirX * cos(-0.05) - g->dirY * sin(-0.05);
		g->dirY = oldDirX * sin(-0.05) + g->dirY * cos(-0.05);
		oldPlaneX = g->planeX;
		g->planeX = g->planeX * cos(-0.05) - g->planeY * sin(-0.05);
		g->planeY = oldPlaneX * sin(-0.05) + g->planeY * cos(-0.05);
	}
	if (g->key.a)
	{
		oldDirX = g->dirX;
		g->dirX = g->dirX * cos(0.05) - g->dirY * sin(0.05);
		g->dirY = oldDirX * sin(0.05) + g->dirY * cos(0.05);
		oldPlaneX = g->planeX;
		g->planeX = g->planeX * cos(0.05) - g->planeY * sin(0.05);
		g->planeY = oldPlaneX * sin(0.05) + g->planeY * cos(0.05);
	}
	if (g->key.esc)
		exit(0);
}

int	key_press(int key, t_game *g)
{
	if(key == K_ESC)
		exit(0);
	else if (key == K_W)
		g->key.w = 1;
	else if (key == K_A)
		g->key.a = 1;
	else if (key == K_S)
		g->key.s = 1;
	else if (key == K_D)
		g->key.d = 1;
	return (0);
}

int	key_release(int key, t_game *g)
{
	if(key == K_ESC)
		exit(0);
	else if (key == K_W)
		g->key.w = 0;
	else if (key == K_A)
		g->key.a = 0;
	else if (key == K_S)
		g->key.s = 0;
	else if (key == K_D)
		g->key.d = 0;
	return (0);
}

int	main_loop(t_game *g)
{
	calc(g);
	draw(g);
	key_update(g);
	return (0);
}

int		main()
{
	t_info	info;
	t_game	g;

	int ac = 3;
	char *ag[3] = {"", "map.cub", "--save"}; //상수로 넣기때문
	//원소를 바꾸려고 하면 안바뀜!!~ 상수(=고정된 숫자라고 표현)! 이기 떄문 변수 ㄴㄴㄴ
	//되도록 초기화를 하면서 선언하세욤.
	if (ac > 1 && ac < 4 && !ft_strncmp(ag[2], "--save", 6))
	{
		ft_memset((char *)&info, sizeof(t_info), 0);
		ft_memset((char *)&g, sizeof(t_game), 0);
		g.mlx = mlx_init();
		mlx_get_screen_size(g.mlx, &info.win_x, &info.win_y);
		info = cub_init(ac, ag);
		game_init(&info, &g);
		g.win = mlx_new_window(g.mlx, info.win_x, info.win_y, "mlx");
		g.img.img = mlx_new_image(g.mlx, info.win_x, info.win_y);
		g.img.data = (int *)mlx_get_data_addr(g.img.img, &g.img.bpp, &g.img.size_l, &g.img.endian);
		mlx_loop_hook(g.mlx, &main_loop, &g);
		mlx_hook(g.win, X_EVENT_KEY_PRESS, 0, &key_press, &g);
		mlx_hook(g.win, X_EVENT_KEY_RELEASE, 0, &key_release, &g);
		mlx_loop(g.mlx);
	}//나중에 main에 있는 valid도 빼서 함수로 만들자.
	else
		ft_exit("ERROR: CHECK PARAMETER");
	return (0);
}