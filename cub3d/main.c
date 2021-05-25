/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: song-yejin <song-yejin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 17:43:51 by song-yejin        #+#    #+#             */
/*   Updated: 2021/05/25 01:57:00 by song-yejin       ###   ########.fr       */
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

void	cub_init(int ac, char *ag[], t_info *info)
{
	const int	fd = open(ag[1], O_RDONLY);

	if (fd < 0)
		ft_exit("ERROR: FILE CANNOT BE FOUND");
	if (cub_parsing(fd, info) != (1 << 9) - 1)
		ft_exit("ERROR: CHECK FILE CONTENTS");
	ft_valid(info);
	close(fd);
	if (ac == 3 && !ft_strncmp(ag[2], "--save", ft_strlen(ag[2])))
		info->save = 1;
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
	g->texture = (int **)ft_calloc(sizeof(int *), 6, 0);
	while (++i < 5)
		load_image(g, (char *)info->cub_info[i], &img, i);
}

int		ag_ck(int ac, char *ag[])
{
	if ((ac == 2 || ac == 3) && file_cker(ag[1], ".cub") == RET_SUCCESS)
	{
		if (ac == 2 || (ac == 3 && !ft_strncmp(ag[2], "--save", ft_strlen(ag[2]))))
			return (RET_SUCCESS);
		else
			return (RET_ERROR);
	}
	else
		return (RET_ERROR);
}

int		main()
{
	t_info	info;
	t_game	g;

	int ac = 3; //[수정]
	char *ag[3] = {"", "map.cub", "--save"}; //[수정]
	if (ag_ck(ac, ag) == RET_ERROR)
		ft_exit ("ERROR: CHECK PARAMETER");
	ft_memset((char *)&info, sizeof(t_info), 0);
	ft_memset((char *)&g, sizeof(t_game), 0);
	g.mlx = mlx_init();
	mlx_get_screen_size(g.mlx, &info.win_x, &info.win_y);
	cub_init(ac, ag, &info);
	game_init(&info, &g);
	g.win = mlx_new_window(g.mlx, info.win_x, info.win_y, "mlx");
	g.img.img = mlx_new_image(g.mlx, info.win_x, info.win_y);
	g.img.data = (int *)mlx_get_data_addr(g.img.img, &g.img.bpp, &g.img.size_l, &g.img.endian);
	save_bmp(&g);
	mlx_loop_hook(g.mlx, &main_loop, &g);
	mlx_hook(g.win, X_EVENT_KEY_PRESS, 0, &key_press, &g);
	mlx_hook(g.win, X_EVENT_KEY_RELEASE, 0, &key_release, &g);
	mlx_hook(g.win, X_EVENT_EXIT, 0, &close_mouse, &g);
	mlx_loop(g.mlx);
	return (0);
}