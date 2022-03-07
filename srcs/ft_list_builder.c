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

static int	ft_value_assignemnt(t_fixed out[3], char **sub_split, long long int min_v, long long int max_v)
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
		if (temp < min_v || temp > max_v)
			return (2);
		out[i] = double2fixed(temp);
		i++;
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
		error = ft_value_assignemnt(vo->camera.coord, sub_split, FT_MIN_COORD, FT_MAX_COORD);
		ft_free_split(sub_split);
		if (error)
			return(error);
		sub_split = ft_split(split[2], ',');
		if (sub_split == NULL)
			return (1);
		error = ft_value_assignemnt(vo->camera.dir_vector, sub_split, -1, 1);
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
		
		error = ft_value_assignemnt(vo->ambient.color, sub_split, 0, 255);
		ft_free_split(sub_split);
		if (error)
			return(error);
	}
	else
	{
		sub_split = ft_split(split[1], ',');
		if (sub_split == NULL)
			return (1);
		error = ft_value_assignemnt(vo->light.coord, sub_split, FT_MIN_COORD, FT_MAX_COORD);
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
	error = ft_value_assignemnt(sp->coord, sub_split, FT_MIN_COORD, FT_MAX_COORD);
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
	error = ft_value_assignemnt(pl->coord, sub_split, FT_MIN_COORD, FT_MAX_COORD);
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
	error = ft_value_assignemnt(pl->dir_vector, sub_split, -1, 1);
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
	error = ft_value_assignemnt(cy->coord, sub_split, FT_MIN_COORD, FT_MAX_COORD);
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
	error = ft_value_assignemnt(cy->dir_vector, sub_split, -1, 1);
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
	error = ft_value_assignemnt(go->color, sub_split, 0, 255);
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