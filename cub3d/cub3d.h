#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include "key_macos.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

# define RET_ERROR -1
# define RET_SUCCESS 1
# define RET_EOF 0
# define MAP_COMPLETE ((1 << 8) - 1)
# define X_EVENT_KEY_PRESS	2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_KEY_EXIT	17

typedef struct		s_info
{
	unsigned char	*cub_info[8];
	char			**map;
	int				win_x; //창 가로= width
	int				win_y; //창 세로= height
	int				height; //map 세로
	int				width; //map 가로
	int				player_x;
	int				player_y;
	int				f_rgb;
	int				c_rgb;
}					t_info;

typedef struct	s_img
{
	void	*img;
	int		*data;

	int		size_l;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}				t_img;

typedef struct		s_key
{
	int			a;
	int			w;
	int			s;
	int			d;
	int			esc;
}					t_key;

typedef struct		s_loca
{
	double	x;
	double	y;
}					t_loca;

typedef struct		s_pair
{
	double	first;
	int		second;
}					t_pair;

typedef struct		s_game
{
	void			*mlx;
	void			*win;
	t_img			img;
	t_key			key;
	t_loca			sz_img[6];
	int				numSprite; //sprite개수
	t_loca			*s;
	char			**map;
	int				win_x; //창 크기
	int				win_y;
	int				height; //map
	int				width;
	int				f_rgb;
	int				c_rgb;
	double			posX;
	double			posY;
	double			dirX;
	double			dirY;
	double			planeX;
	double			planeY;
	int				**buf;
	int				**texture;
	double			*zBuffer; // sprite위해 필요함!
}					t_game;

typedef struct		s_wcasting
{
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int		mapX;
	int		mapY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
	int		stepX;
	int		stepY;
	int		hit;
	int		side;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	int		texNum;
	double	wallX;
	int		texX;
	double	step;
	double	texPos;
}					t_wcasting;

typedef struct	s_scasting
{
	double	spriteX;
	double	spriteY;
	double	invDet;
	double	transformX;
	double	transformY;
	int		spriteScreenX;
	int		spriteH;
	int		drawStartY;
	int		drawEndY;
	int		spriteW;
	int		drawStartX;
	int		drawEndX;
	int		*spriteO;
	double	*spriteD;
}				t_scasting;


//libft.c
char	*ft_strchr(const char *str, int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_atoi(char **s);
void	ft_memset(char *dest, int size, char ch);
void	ft_free(char **line);
void	*ft_calloc(size_t number, size_t size, char ch);
int		ft_max(int x, int y);
int		ft_min(int x, int y);
int		ft_strncmp(char *str1, char *str2, size_t n);
size_t	ft_strlen(char *str);
void	*ft_memcpy(void *dest, void *src, size_t count);

//get_fileinfo.c
int		ft_append(char **line, char ch, char flag);
int		get_a_line(int fd, char **line, int flag);
int		info_parsing(char *line, t_info *info);
int		cub_parsing(int fd, t_info *info);
void	make_map(char *line, t_info *info);

//filevalid.c
int		file_cker(char *filename, char *extension);
int		texture_ck(char *s);
int		ft_valid(t_info *info);
int	map_ck(t_info *info);
int map_closed_ck(t_info *info);
int	dfs(int x, int y, t_info *info, int **visit);
int	contents_ck(t_info *info);
int	win_parsing(char *s, t_info *info, int inf);
int	rgb_parsing(char *s, t_info *info, int inf);
int	rgb2hex(int *tmp);
int	put_num(int *tmp, t_info *info, int inf);

//wall_casting.c
void	wall_casting(t_game *g);
void	wall_init(int x, t_game *g, t_wcasting *tw);
void	dda(t_game *g, t_wcasting *tw);
void	get_height(t_game *g, t_wcasting *tw);
void	draw_one_line(int x, t_game *g, t_wcasting *tw);

//sprites_casting.c
void	sprite_casting(t_game *g);
void	sprite_init(t_game *g, t_scasting *ts);
void	sortSprites(int *order, double *dist, int n);
void	sort_order(t_pair *o, int n);
void	sprite_calc(t_game *g, t_scasting *ts, int i);
void	draw_sprites(t_game *g, t_scasting *ts);

//game_init.c
void	game_init(t_info *info, t_game *g);
void	player_init(t_info *i, t_game *g);
void	copy_map(t_info *info, t_game *g);
void	sprites_location(t_info *info, t_game *g);

//main.c
void	ft_exit(char *s);
void	cub_init(int ac, char *ag[], t_info *info);
void	load_image(t_game *g, char *path, t_img *img, int i);
void	load_texture(t_info *info, t_game *g);
void	floor_color(t_game *g);
void	calc(t_game *g);
void	draw(t_game *g);
void	key_update(t_game *g);
int	key_press(int key, t_game *g);
int	key_release(int key, t_game *g);
int	main_loop(t_game *g);

#endif