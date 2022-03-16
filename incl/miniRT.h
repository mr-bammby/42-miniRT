/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 12:08:08 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/04 12:08:08 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../gnl/incl/get_next_line.h"
# include "../libft/incl/libft.h"
# include "../libvector/incl/libvector.h"
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include "../mlx_linux/mlx.h"
# include "../mlx_mac/include/mlx.h"

# define FT_SP_TYPE 0
# define FT_CY_TYPE 1
# define FT_PL_TYPE 2

# define FT_MAX_COORD 10000
# define FT_MIN_COORD -FT_MAX_COORD
# define FT_BIGGEST_DIST 3 * FT_MAX_COORD
# define FT_SP_MAX_DIAMETER 1000
# define FT_CY_MAX_DIAMETER 1000
# define FT_CY_MAX_HEIGHT 1000

# define FT_MIN_NORM_VEC -1
# define FT_MAX_NORM_VEC 1

# define FT_MIN_RGB 0
# define FT_MAX_RGB 255

# define FT_ASS_VEC 0
# define FT_ASS_RGB 1
# define FT_ASS_POINT 2

# define FT_PX_SIZE 0.001
# define FT_SCREEN_HOR_PX 1000
# define FT_SCREEN_VER_PX 1000

# define PRINT_GOL 1
# define PRINT_VO 1

#define FT_RADIUS_CHECK 1
#define FT_NO_RADIUS_CHECK 0

#define FT_EXIT_ON_ERROR 1

# define FT_ERR_ARG_NUM		"wrong number of arguments\n"
# define FT_ERR_FILE_NAME	"unsupported file name\n"
# define FT_ERR_FILE_ACCESS	"file not accessible\n"
# define FT_ERR_UNKNOWN		"bad line read\n"
# define FT_ERR_UNKNOWN_OBJ	"unknown object\n"
# define FT_ERR_C_LESS		"no camera object\n"
# define FT_ERR_C_MANY		"too many camera objects\n"
# define FT_ERR_C_ARG_CHECK	"wrong camera arguments\n"
# define FT_ERR_A_MANY		"too many ambient light objects\n"
# define FT_ERR_A_ARG_CHECK	"wrong ambient light arguments\n"
# define FT_ERR_L_MANY		"too many light objects\n"
# define FT_ERR_L_ARG_CHECK	"wrong light arguments\n"
# define FT_ERR_SP_ARG_CHECK	"wrong sphere arguments\n"
# define FT_ERR_PL_ARG_CHECK	"wrong plane arguments\n"
# define FT_ERR_CY_ARG_CHECK	"wrong cylinder arguments\n"

typedef struct s_geo_object
{
	int		type;
	void	*s;
	t_fixed	color[3];
}			t_geo_object;

typedef struct s_camera
{
	t_point		coord;
	t_vec		dir_vector;
	t_fixed		angle;	////////////////////////////////////////////in radians max angle is 179.9 degree
}			t_camera;

typedef struct s_light
{
	t_point		coord;
	t_fixed		light_ratio;
}				t_light;

typedef struct s_ambient
{
	t_fixed		light_ratio;
	t_fixed		color[3];
}				t_ambient;

typedef struct s_view_object
{
	t_camera	camera;
	t_light		light;
	t_ambient	ambient;
}				t_view_object;

typedef struct s_screen
{
	t_point	camera;
	t_vec	right;
	t_vec	down;
	t_point	zero;

}				t_screen;

typedef struct	s_canvas {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_canvas;

typedef struct	s_mlx_view {
	void		*mlx;
	void		*mlx_win;
	t_canvas	canvas;
}				t_mlx_view;

typedef t_fixed t_rgb[3];

extern int g_error;

/* ft_utils.c */

int		ft_strcmp(char *s1, char *s2);
void	ft_smart_free(void **ptr);
void	ft_free_split(char **split);

/* ft_utils_num.c */
int		ft_digit_check(char *argv);
int		ft_atoll(const char *str, long long int *out);
int		ft_atod(char *str, double *out);

/* ft_utils_mlx.c */
void ft_mlx(t_screen screen, t_list *gol, t_view_object vo);

/* ft_arg_check.c */
void ft_argument_check(int argc, char **argv);

/* ft_list_builder.c */
void	ft_list_builder(char *filename, t_list **gol, t_view_object *vo);

/* diagnostics.c */
void print_gol(t_list *gol);
void print_vo(t_view_object vo);

/* ft_exit_free.c */
void ft_exit_free(t_list *gol);
void ft_exit_on_arg_error(char *msg, char **split, int fd, char *line);

/* ft_screen_maker.c */
t_screen ft_screen_maker(t_camera camera);
t_ray ft_screen_ray(t_screen screen, int x, int y);

/* ft_sphere_distance.c */
t_fixed ft_sphere_distance(t_sphere sphere, t_ray ray);

/* ft_plane_distance.c */
t_fixed ft_plane_distance(t_plane plane, t_ray ray);

/* ft_cylinder_distance.c */
t_fixed	ft_cylinder_distance(t_cylinder cylinder, t_ray ray);

/* ft_light_stuff.c */
int ft_calc_all_light(t_point point, t_geo_object object, t_view_object vo, t_list *gol);

/* ft_cylinder_utils.c */
t_fixed ft_point_height_loc(t_cylinder cylinder, t_point point);
t_fixed ft_dist2disc(t_cylinder cylinder, t_ray ray, t_fixed scal_prod, int mode);

#endif
