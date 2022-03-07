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
#include "../libvector/incl/libvector.h"
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

# define FT_MIN_COORD -10000
# define FT_MAX_COORD 10000
# define FT_SP_MAX_DIAMETER 1000
# define FT_CY_MAX_DIAMETER 1000
# define FT_CY_MAX_HEIGHT 1000

# define PRINT_GOL 1
# define PRINT_VO 1

typedef struct s_sphere
{
	t_fixed		coord[3];
	t_fixed		diameter;
}			t_sphere;

typedef struct s_plane
{
	t_fixed		coord[3];
	t_fixed		dir_vector[3];
}			t_plane;

typedef struct s_cylinder
{
	t_fixed		coord[3];
	t_fixed		dir_vector[3];
	t_fixed		diameter;
	t_fixed		height;
}			t_cylinder;

typedef struct s_geo_object
{
	int		type;
	void	*s;
	t_fixed	color[3];
}			t_geo_object;

typedef struct s_camera
{
	t_fixed		coord[3];
	t_fixed		dir_vector[3];
	t_fixed		angle;	////////////////////////////////////////////into radians
}			t_camera;

typedef struct s_light
{
	t_fixed		coord[3];
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


/* ft_utils.c */

int		ft_strcmp(char *s1, char *s2);
void	ft_smart_free(void **ptr);
void	ft_free_split(char **split);

/* ft_utils_num.c */
int		ft_digit_check(char *argv);
int		ft_atoll(const char *str, long long int *out);
int		ft_atod(char *str, double *out);

/* ft_utils_mlx.c */
void ft_mlx(void);

/* ft_arg_check.c */
int line_check(char **line, int last_check);
int argument_check(int argc, char **argv);

/* ft_list_builder.c */
int	ft_list_builder(char *filename, t_list **gol, t_view_object *vo);

/* diagnostics.c */
void print_gol(t_list *gol);
void print_vo(t_view_object vo);

/* ft_exit_free.c */
void ft_exit_free(t_list *gol);


#endif
