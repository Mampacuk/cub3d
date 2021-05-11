/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisraely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 18:50:21 by aisraely          #+#    #+#             */
/*   Updated: 2021/05/11 18:50:24 by aisraely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define FIELD_OF_VIEW 0.90
# define BUFFER_SIZE 1

# include "./mlx/mlx.h"
# include "./libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct	s_keys
{
	int			movefor;
	int			moveback;
	int			moveleft;
	int			moveright;
	int			turnleft;
	int			turnright;
}				t_keys;

typedef struct	s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			linelen;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct	s_screen
{
	void		*mlx;
	void		*win;
	t_img		img;
}				t_screen;

typedef struct	s_map
{
	int			w;
	int			h;
	int			**m;
}				t_map;

typedef struct	s_ray
{
	double		dirx;
	double		diry;
	double		camx;
	double		deltax;
	double		deltay;
	double		walldist;
	int			mapx;
	int			mapy;
	double		sidedistx;
	double		sidedisty;
	int			stepx;
	int			stepy;
	int			hit;
	int			side;
	int			lineheight;
	int			drawstart;
	int			drawend;
	int			drawstartx;
	int			drawendx;
	int			drawstarty;
	int			drawendy;
	double		wallx;
	int			texx;
	int			texy;
	double		texpos;
	double		texstep;
	double		spritex;
	double		spritey;
	double		invdet;
	double		transx;
	double		transy;
	int			sprx;
	int			sprheight;
	int			sprwidth;
}				t_ray;

typedef struct	s_player
{
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		olddirx;
	double		planex;
	double		planey;
	double		oldplanex;
	double		time;
	double		oldtime;
	double		frametime;
	double		movespeed;
	double		rotspeed;
}				t_player;

typedef struct	s_sprite
{
	double		posx;
	double		posy;
	double		dist;
}				t_sprite;

typedef struct	s_parsed
{
	int			i;
	int			j;
	int			d;
	int			y;
	int			w;
	int			h;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*spr;
	int			sprnum;
	int			fcolor;
	int			ccolor;
	int			bmp;
	t_ray		ray;
	t_map		map;
	t_sprite	**sprites;
	t_player	player;
	t_screen	scr;
	t_keys		keys;
	t_img		texno;
	t_img		texso;
	t_img		texwe;
	t_img		texea;
	t_img		texspr;
	double		*zbuffer;
}				t_parsed;

void			ft_mlx_pixel_put(t_screen *data, int x, int y, int color);
void			ft_mlx_stripe_put(t_parsed *res, int stripe, int drawstart,
								int drawend);
int				ft_raycast(t_parsed *res);
int				get_next_line(int fd, char **line);
int				ft_strlen(char *str);
char			*ft_fetchdigit(char *str);
t_parsed		ft_parser(char *mappath);
char			*ft_strchr(char *s, int c);
char			*ft_getpath(char *str);
int				ft_trgb(int t, int r, int g, int b);
int				ft_gettrgb(char *str);
void			ft_getworldmap(char *mappath, t_parsed *res);
int				ft_ismaprow(char *str);
int				ft_getmapheight(char *mappath);
int				ft_getmapwidth(char *mappath);
void			ft_writerow(char *line, t_parsed *res, int x);
void			ft_checkwalls(int **map, int height, int width);
int				ft_mlx_pressed(int keycode, t_keys *keys);
int				ft_mlx_released(int keycode, t_keys *keys);
void			ft_renderframe(t_parsed *res);
unsigned int	ft_mlx_get_color(t_img *imgstruct, int x, int y);
int				ft_getsprnum(char *mappath);
void			ft_quicksort(t_sprite **arr, int p, int r);
double			ft_squared(double num);
void			ft_createbmp(t_parsed *res);
void			ft_exit(char *error);
int				ft_check_extension(char *path, char *ext);
int				ft_check_resources(t_parsed *res);
void			ft_setup_map(t_parsed *res, char *mappath);
void			ft_initplayer(t_parsed *res, char startdir, int posx, int posy);
void			ft_initparser(t_parsed *res);
void			ft_getresolution(t_parsed *res, char *line);
void			ft_gettexture1(t_parsed *res, char *line);
void			ft_gettexture2(t_parsed *res, char *line);
void			ft_getcolors(t_parsed *res, char *line);
void			ft_setdirvector(t_parsed *res, char d);
void			ft_setcamplane(t_parsed *res, char d);
void			ft_checkdimensions(t_parsed *res);
void			ft_loadtextures1(t_parsed *res);
void			ft_loadtextures2(t_parsed *res);
void			ft_setray(t_parsed *res);
void			ft_setstep(t_parsed *res);
void			ft_performdda(t_parsed *res);
void			ft_domath1(t_parsed *res);
void			ft_domath2(t_parsed *res);
void			ft_putspritestripe(t_parsed *res);
void			ft_drawsprite(t_parsed *res);
void			ft_drawwall(t_parsed *res, int stripe, int y);
void			ft_receiveinput1(t_parsed *res);
void			ft_receiveinput2(t_parsed *res);
void			ft_receiveinput3(t_parsed *res);
void			ft_receiveinput4(t_parsed *res);

#endif
