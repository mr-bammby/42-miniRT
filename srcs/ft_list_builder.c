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
			return(error);
		if (((temp < FT_MIN_RGB || temp > FT_MAX_RGB) && mode == FT_ASS_RGB) \
			|| ((temp < FT_MIN_NORM_VEC || temp > FT_MAX_NORM_VEC) && mode == FT_ASS_VEC) \
			|| ((temp < FT_MIN_COORD || temp > FT_MAX_COORD) && mode == FT_ASS_POINT))
			return (2);
		*(ft_ass_iterator(mode, i, out)) = double2fixed(temp);
		i++;
	}
	if (mode == FT_ASS_VEC)
	{
		*((t_vec *)out) = ft_creat_vec(((t_vec *)out)->n_vec.x, ((t_vec *)out)->n_vec.y, ((t_vec *)out)->n_vec.z);
		if (fixed2double(((t_vec *)out)->size) < 0.9999 || fixed2double(((t_vec *)out)->size) > 1.0001)
			return (1);
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
			return (1);
		error = ft_value_assignemnt((void *)&(vo->camera.coord), sub_split, FT_ASS_POINT);
		ft_free_split(sub_split);
		if (error)
			return(error);
		sub_split = ft_split(split[2], ',');
		if (sub_split == NULL)
			return (1);
		error = ft_value_assignemnt((void *)&(vo->camera.dir_vector), sub_split, FT_ASS_VEC);
		ft_free_split(sub_split);
		if (error)
			return(error);
		error = ft_atod(split[3], &temp); //check for error as return value
		if (error)
			return(error);
		if (temp < 0 || temp > 180)
			return(2);
		temp = temp * M_PI / 180;
		vo->camera.angle = double2fixed(temp);
	}
	else if (!ft_strcmp(split[0], "A"))
	{
		error = ft_atod(split[1], &temp); //check for error as return value
		if (error)
			return(error);
		if (temp < 0 || temp > 1)
			return (2);
		vo->ambient.light_ratio = double2fixed(temp);
		sub_split = ft_split(split[2], ',');
		if (sub_split == NULL)
			return (1);
		error = ft_value_assignemnt((void *)&(vo->ambient.color), sub_split, FT_ASS_RGB);
		ft_free_split(sub_split);
		if (error)
			return(error);
	}
	else
	{
		sub_split = ft_split(split[1], ',');
		if (sub_split == NULL)
			return (1);
		error = ft_value_assignemnt((void *)&(vo->light.coord), sub_split, FT_ASS_POINT);
		ft_free_split(sub_split);
		if (error)
			return(error);
		error = ft_atod(split[2], &temp);
		if (error)
			return(error);
		if (temp < 0 || temp > 1)
			return(2);
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
	{
		ft_smart_free((void **)&sp);
		return(1);
	}
	error = ft_value_assignemnt((void *)&(sp->coord), sub_split, FT_ASS_POINT);
	ft_free_split(sub_split);
	if (error)
	{
		ft_smart_free((void **)&sp);
		return(error);
	}
	error = ft_atod(split[2], &temp);
	if (error)
	{
		ft_smart_free((void **)&sp);
		return(error);
	}
	if (temp < 0 || temp > FT_SP_MAX_DIAMETER)
	{
		ft_smart_free((void **)&sp);
		return(2);
	}
	sp->diameter = double2fixed(temp);
	*s = (void *)sp;
	return (0);
}

static int ft_create_plane(void **s, char **split)
{
	char		**sub_split;
	int			error;
	t_plane		*pl;

	pl = malloc(sizeof(t_plane));
	sub_split = ft_split(split[1], ',');
	if (sub_split == NULL)
	{
		ft_smart_free((void **)&pl);
		return(1);
	}
	error = ft_value_assignemnt((void *)&(pl->coord), sub_split, FT_ASS_POINT);
	ft_free_split(sub_split);
	if (error)
	{
		ft_smart_free((void **)&pl);
		return(error);
	}
	sub_split = ft_split(split[2], ',');
	if (sub_split == NULL)
	{
		ft_smart_free((void **)&pl);
		return(1);
	}
	error = ft_value_assignemnt((void *)&(pl->dir_vector), sub_split, FT_ASS_VEC);
	ft_free_split(sub_split);
	if (error)
	{
		ft_smart_free((void **)&pl);
		return(error);
	}
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
	{
		ft_smart_free((void **)&cy);
		return(1);
	}
	error = ft_value_assignemnt((void *)&(cy->coord), sub_split, FT_ASS_POINT);
	ft_free_split(sub_split);
	if (error)
	{
		ft_smart_free((void **)&cy);
		return(error);
	}
	sub_split = ft_split(split[2], ',');
	if (sub_split == NULL)
	{
		ft_smart_free((void **)&cy);
		return(1);
	}
	error = ft_value_assignemnt((void *)&(cy->dir_vector), sub_split, FT_ASS_VEC);
	ft_free_split(sub_split);
	if (error)
	{
		ft_smart_free((void **)&cy);
		return(error);
	}
	error = ft_atod(split[3], &temp);
	if (error)
	{
		ft_smart_free((void **)&cy);
		return(error);
	}
	if (temp < 0 || temp > FT_CY_MAX_DIAMETER)
	{
		ft_smart_free((void **)&cy);
		return(2);
	}
	cy->diameter = double2fixed(temp);
	error = ft_atod(split[4], &temp);
	if (error)
	{
		ft_smart_free((void **)&cy);
		return(error);
	}
	if (temp < 0 || temp > FT_CY_MAX_HEIGHT)
	{
		ft_smart_free((void **)&cy);
		return(2);
	}
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
		if (go == NULL)
			return (1);
		go->type = FT_SP_TYPE;
		error = ft_create_sphere(&(go->s), split);
		if (error)
		{
			ft_smart_free((void **)&go);
			return (error);
		}
	}
	else if (!ft_strcmp(split[0], "pl"))
	{
		rgb_index = 3;
		go = malloc(sizeof(t_geo_object));
		if (go == NULL)
			return (1);
		go->type = FT_PL_TYPE;
		error = ft_create_plane(&(go->s), split);
		if (error)
		{
			ft_smart_free((void **)&go);
			return (error);
		}
	}
	else
	{
		rgb_index = 5;
		go = malloc(sizeof(t_geo_object));
		if (go == NULL)
			return (1);
		go->type = FT_CY_TYPE;
		error = ft_create_cylinder(&(go->s), split);
		if (error)
		{
			ft_smart_free((void **)&go);
			return (error);
		}
	}
	sub_split = ft_split(split[rgb_index], ',');
	if (sub_split == NULL)
		return (1);
	error = ft_value_assignemnt((void *)&(go->color), sub_split, FT_ASS_RGB);
	ft_free_split(sub_split);
	if (error)
		return(error);
	ft_lstadd_back(gol, ft_lstnew((void *)go));
	return (0);
}

int	ft_list_builder(char *filename, t_list **gol, t_view_object *vo)
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
			return (1);
		if (ft_strcmp(split[0], "\n"))
		{
			if(ft_strlen(split[0]) == 1)
				error = ft_fill_vo(split, vo);
			else
				error = ft_create_gol(split, gol);
			if (error != 0)
				return (error);
		}
		ft_free_split(split);
		ft_smart_free((void **)&line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}