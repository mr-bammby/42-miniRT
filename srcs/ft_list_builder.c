/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_builder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 20:09:09 by mamuller          #+#    #+#             */
/*   Updated: 2022/03/06 20:09:09 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

static t_fixed *ft_ass_iterator(int mode, int num, void *out)
{
	t_vec *vec;
	t_point *point;
	t_fixed *rgb;

	if(mode == FT_ASS_VEC)
	{
		vec = (t_vec *)out;
		if (num == 0)
			return (&(vec->n_vec.x));
		else if (num == 1)
			return (&(vec->n_vec.y));
		else
			return (&(vec->n_vec.z));
	}
	else if(mode == FT_ASS_RGB)
	{
		rgb = (t_fixed *)out;
		return (&(rgb[num]));
	}
	else
	{
		point = (t_point *)out;
		if (num == 0)
			return (&(point->x));
		else if (num == 1)
			return (&(point->y));
		else
			return (&(point->z));
	}
}

static int	ft_value_assignemnt(void *out, char **sub_split, int mode)
{
	int		i;
	double	temp;
	int 	error;

	i = 0;
	while (i < 3)
	{
		error = ft_atod(sub_split[i], &temp);
		if (error)
			return(FT_ERR_NUM_RANGE);
		if (((temp < FT_MIN_RGB || temp > FT_MAX_RGB) && mode == FT_ASS_RGB))
			return (FT_ERR_RGB_RANGE);
		else if (((temp < FT_MIN_NORM_VEC || temp > FT_MAX_NORM_VEC) && mode == FT_ASS_VEC))
			return (FT_ERR_VEC_RANGE);
		else if (((temp < FT_MIN_COORD || temp > FT_MAX_COORD) && mode == FT_ASS_POINT))
			return (FT_ERR_COORD_RANGE);
		*(ft_ass_iterator(mode, i, out)) = double2fixed(temp);
		i++;
	}
	if (mode == FT_ASS_VEC)
	{
		*((t_vec *)out) = ft_creat_vec(((t_vec *)out)->n_vec.x, ((t_vec *)out)->n_vec.y, ((t_vec *)out)->n_vec.z);
		if (fixed2double(((t_vec *)out)->size) < 0.9999 || fixed2double(((t_vec *)out)->size) > 1.0001)
			return (FT_ERR_VEC_SIZE);
		((t_vec *)out)->size = long2fixed(1);
	}
	return (0);
}


static int	ft_fill_vo(char **split, t_view_object *vo)
{
	double	temp;
	char	**sub_split;
	int 	error;

	if (!ft_strcmp(split[0], "C"))
	{
		sub_split = ft_split(split[1], ',');
		if (sub_split == NULL)
			return (FT_ERR_C | FT_ERR_BAD_LINE);
		error = ft_value_assignemnt((void *)&(vo->camera.coord), sub_split, FT_ASS_POINT);
		ft_free_split(sub_split);
		if (error)
			return(FT_ERR_C | error);
		sub_split = ft_split(split[2], ',');
		if (sub_split == NULL)
			return (FT_ERR_C | FT_ERR_BAD_LINE);
		error = ft_value_assignemnt((void *)&(vo->camera.dir_vector), sub_split, FT_ASS_VEC);
		ft_free_split(sub_split);
		if (error)
			return(FT_ERR_C | error);
		error = ft_atod(split[3], &temp); //check for error as return value
		if (error)
			return(FT_ERR_C | error);
		if (temp < 0 || temp > 180)
			return(FT_ERR_C | FT_ERR_ANGLE_RANGE);
		temp = temp * M_PI / 180;
		vo->camera.angle = double2fixed(temp);
	}
	else if (!ft_strcmp(split[0], "A"))
	{
		error = ft_atod(split[1], &temp); //check for error as return value
		if (error)
			return(FT_ERR_A | error);
		if (temp < 0 || temp > 1)
			return (FT_ERR_A | FT_ERR_RATIO_RANGE);
		vo->ambient.light_ratio = double2fixed(temp);
		sub_split = ft_split(split[2], ',');
		if (sub_split == NULL)
			return (FT_ERR_A | FT_ERR_BAD_LINE);
		error = ft_value_assignemnt((void *)&(vo->ambient.color), sub_split, FT_ASS_RGB);
		ft_free_split(sub_split);
		if (error)
			return(FT_ERR_A | error);
	}
	else
	{
		sub_split = ft_split(split[1], ',');
		if (sub_split == NULL)
			return (FT_ERR_L | FT_ERR_BAD_LINE);
		error = ft_value_assignemnt((void *)&(vo->light.coord), sub_split, FT_ASS_POINT);
		ft_free_split(sub_split);
		if (error)
			return(FT_ERR_L | error);
		error = ft_atod(split[2], &temp);
		if (error)
			return(FT_ERR_L | error);
		if (temp < 0 || temp > 1)
			return(FT_ERR_L | FT_ERR_RATIO_RANGE);
		vo->light.light_ratio = double2fixed(temp);
	}
	return (0);
}

static int ft_create_sphere(void **s, char **split)
{
	char		**sub_split;
	int			error;
	t_sphere	*sp;
	double		temp;

	sp = malloc(sizeof(t_sphere));
	sub_split = ft_split(split[1], ',');
	if (sub_split == NULL)
		return(ft_list_creation_arg_error(FT_ERR_SP | FT_ERR_BAD_LINE, NULL, sp));
	error = ft_value_assignemnt((void *)&(sp->coord), sub_split, FT_ASS_POINT);
	ft_free_split(sub_split);
	if (error)
		return(ft_list_creation_arg_error(FT_ERR_SP | error, NULL, sp));
	error = ft_atod(split[2], &temp);
	if (error)
		return(ft_list_creation_arg_error(FT_ERR_SP | error, NULL, sp));
	if (temp < 0 || temp > FT_SP_MAX_DIAMETER)
		return(ft_list_creation_arg_error(FT_ERR_SP | FT_ERR_DIAMETER_RANGE, NULL, sp));
	sp->diameter = double2fixed(temp);
	*s = (void *)sp;
	return (0);
}

static int ft_create_plane_builder(void **s, char **split)
{
	char		**sub_split;
	int			error;
	t_plane		*pl;

	pl = malloc(sizeof(t_plane));
	sub_split = ft_split(split[1], ',');
	if (sub_split == NULL)
		return(ft_list_creation_arg_error(FT_ERR_PL | FT_ERR_BAD_LINE, NULL, pl));
	error = ft_value_assignemnt((void *)&(pl->coord), sub_split, FT_ASS_POINT);
	ft_free_split(sub_split);
	if (error)
		return(ft_list_creation_arg_error(FT_ERR_PL | error, NULL, pl));
	sub_split = ft_split(split[2], ',');
	if (sub_split == NULL)
		return(ft_list_creation_arg_error(FT_ERR_PL | FT_ERR_BAD_LINE, NULL, pl));
	error = ft_value_assignemnt((void *)&(pl->dir_vector), sub_split, FT_ASS_VEC);
	ft_free_split(sub_split);
	if (error)
		return(ft_list_creation_arg_error(FT_ERR_PL | error, NULL, pl));
	*s = (void *)pl;
	return (0);
}

static int ft_create_cylinder(void **s, char **split)
{
	char			**sub_split;
	int				error;
	t_cylinder		*cy;
	double			temp;

	cy = malloc(sizeof(t_cylinder));
	sub_split = ft_split(split[1], ',');
	if (sub_split == NULL)
		return(ft_list_creation_arg_error(FT_ERR_CY | FT_ERR_BAD_LINE, NULL, cy));
	error = ft_value_assignemnt((void *)&(cy->coord), sub_split, FT_ASS_POINT);
	ft_free_split(sub_split);
	if (error)
		return(ft_list_creation_arg_error(FT_ERR_CY | error, NULL, cy));
	sub_split = ft_split(split[2], ',');
	if (sub_split == NULL)
		return(ft_list_creation_arg_error(FT_ERR_CY | FT_ERR_BAD_LINE, NULL, cy));
	error = ft_value_assignemnt((void *)&(cy->dir_vector), sub_split, FT_ASS_VEC);
	ft_free_split(sub_split);
	if (error)
		return(ft_list_creation_arg_error(FT_ERR_CY | error, NULL, cy));
	error = ft_atod(split[3], &temp);
	if (error)
		return(ft_list_creation_arg_error(FT_ERR_CY | error, NULL, cy));
	if (temp < 0 || temp > FT_CY_MAX_DIAMETER)
		return(ft_list_creation_arg_error(FT_ERR_CY | FT_ERR_DIAMETER_RANGE, NULL, cy));
	cy->diameter = double2fixed(temp);
	error = ft_atod(split[4], &temp);
	if (error)
		return(ft_list_creation_arg_error(FT_ERR_CY | error, NULL, cy));
	if (temp < 0 || temp > FT_CY_MAX_HEIGHT)
		return(ft_list_creation_arg_error(FT_ERR_CY | FT_ERR_HEIGHT_RANGE, NULL, cy));
	cy->height = double2fixed(temp);
	*s = (void *)cy;
	return (0);
}

static int	ft_create_gol(char **split, t_list **gol)
{
	char			**sub_split;
	int 			error;
	t_geo_object	*go;
	int				rgb_index;

	if (!ft_strcmp(split[0], "sp"))
	{
		rgb_index = 3;
		go = malloc(sizeof(t_geo_object));
		go->s = NULL;
		if (go == NULL)
			return (FT_ERR_SP | FT_ERR_ALLOC_MEM);
		go->type = FT_SP_TYPE;
		error = ft_create_sphere(&(go->s), split);
		if (error)
			return(ft_list_creation_arg_error(error, go, (void *)(go->s)));
	}
	else if (!ft_strcmp(split[0], "pl"))
	{
		rgb_index = 3;
		go = malloc(sizeof(t_geo_object));
		go->s = NULL;
		if (go == NULL)
			return (FT_ERR_PL | FT_ERR_ALLOC_MEM);
		go->type = FT_PL_TYPE;
		error = ft_create_plane_builder(&(go->s), split);
		if (error)
			return(ft_list_creation_arg_error(error, go, (void *)(go->s)));
	}
	else
	{
		rgb_index = 5;
		go = malloc(sizeof(t_geo_object));
		go->s = NULL;
		if (go == NULL)
			return (FT_ERR_CY | FT_ERR_ALLOC_MEM);
		go->type = FT_CY_TYPE;
		error = ft_create_cylinder(&(go->s), split);
		if (error)
			return(ft_list_creation_arg_error(error, go, (void *)(go->s)));
	}
	sub_split = ft_split(split[rgb_index], ',');
	if (sub_split == NULL)
		return (1);
	error = ft_value_assignemnt((void *)&(go->color), sub_split, FT_ASS_RGB);
	ft_free_split(sub_split);
	if (error)
	{
		if (!ft_strcmp(split[0], "sp"))
			error = FT_ERR_SP | error ;
		else if (!ft_strcmp(split[0], "pl"))
			error = FT_ERR_PL | error ;
		else
			error = FT_ERR_CY | error ;
		return(ft_list_creation_arg_error(error, go, (void *)(go->s)));
	}
	ft_lstadd_back(gol, ft_lstnew((void *)go));
	return (0);
}

void	ft_list_builder(char *filename, t_list **gol, t_view_object *vo)
{
	int		fd;
	char	*line;
	char	**split;
	int		error;
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		split = ft_split(line, ' ');
		if (split == NULL)
		{
			ft_exit_free(*gol);
			ft_exit_on_arg_error(FT_ERR_UNKNOWN, split, fd, line);
		}
		if (ft_strcmp(split[0], "\n"))
		{
			if (ft_strlen(split[0]) == 1)
				error = ft_fill_vo(split, vo);
			else
				error = ft_create_gol(split, gol);
			if (error != 0)
			{
				ft_perror(error);
				ft_exit_free(*gol);
				ft_exit_on_arg_error(NULL, split, fd, line);
			}
		}
		ft_free_split(split);
		ft_smart_free((void **)&line);
		line = get_next_line(fd);
	}
	close(fd);
}