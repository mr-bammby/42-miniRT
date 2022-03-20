/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_gol_geo_obj.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 23:19:39 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/20 01:33:32 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

/**
	@brief
	@param s
	@param split
	@return 
*/
int	ft_create_sphere(void **s, char **split)
{
	char		**sub_split;
	int			error;
	t_sphere	*sp;
	double		temp;

	sp = malloc(sizeof(t_sphere));
	sub_split = ft_split(split[1], ',');
	if (sub_split == NULL)
		return (ft_list_creation_arg_error(FT_ERR_SP | FT_ERR_BAD_LINE, \
			NULL, sp));
	error = ft_value_assignemnt((void *)&(sp->coord), sub_split, FT_ASS_POINT);
	ft_free_split(sub_split);
	if (error)
		return (ft_list_creation_arg_error(FT_ERR_SP | error, NULL, sp));
	error = ft_atod(split[2], &temp);
	if (error)
		return (ft_list_creation_arg_error(FT_ERR_SP | error, NULL, sp));
	if (temp < 0 || temp > FT_SP_MAX_DIAMETER)
		return (ft_list_creation_arg_error(FT_ERR_SP | FT_ERR_DIAMETER_RANGE, \
		NULL, sp));
	sp->diameter = dtofx(temp);
	*s = (void *)sp;
	return (0);
}

/**
	@brief
	@param s
	@param split
	@return 
*/
int	ft_create_plane_builder(void **s, char **split)
{
	char		**sub_split;
	int			error;
	t_plane		*pl;

	pl = malloc(sizeof(t_plane));
	sub_split = ft_split(split[1], ',');
	if (sub_split == NULL)
		return (ft_list_creation_arg_error(FT_ERR_PL | FT_ERR_BAD_LINE, \
			NULL, pl));
	error = ft_value_assignemnt((void *)&(pl->coord), sub_split, FT_ASS_POINT);
	ft_free_split(sub_split);
	if (error)
		return (ft_list_creation_arg_error(FT_ERR_PL | error, NULL, pl));
	sub_split = ft_split(split[2], ',');
	if (sub_split == NULL)
		return (ft_list_creation_arg_error(FT_ERR_PL | FT_ERR_BAD_LINE, \
		NULL, pl));
	error = ft_value_assignemnt((void *)&(pl->dir_vector), sub_split, \
		FT_ASS_VEC);
	ft_free_split(sub_split);
	if (error)
		return (ft_list_creation_arg_error(FT_ERR_PL | error, NULL, pl));
	*s = (void *)pl;
	return (0);
}

/**
	@brief
	@param split
	@param cy
	@return 
*/
static int	ft_create_cylinder_coord_and_vec_hlp(char **split, t_cylinder *cy)
{
	int				error;
	char			**sub_split;

	sub_split = ft_split(split[1], ',');
	if (sub_split == NULL)
		return (ft_list_creation_arg_error(FT_ERR_CY | FT_ERR_BAD_LINE, \
			NULL, cy));
	error = ft_value_assignemnt((void *)&(cy->coord), sub_split, FT_ASS_POINT);
	ft_free_split(sub_split);
	if (error)
		return (ft_list_creation_arg_error(FT_ERR_CY | error, NULL, cy));
	sub_split = ft_split(split[2], ',');
	if (sub_split == NULL)
		return (ft_list_creation_arg_error(FT_ERR_CY | FT_ERR_BAD_LINE, \
			NULL, cy));
	error = ft_value_assignemnt((void *)&(cy->dir_vector), sub_split, \
		FT_ASS_VEC);
	ft_free_split(sub_split);
	if (error)
		return (ft_list_creation_arg_error(FT_ERR_CY | error, NULL, cy));
	return (0);
}

/**
	@brief
	@param split
	@param cy
	@return 
*/
static int	ft_create_cylinder_diameter_height_hlp(char **split, t_cylinder *cy)
{
	int				error;
	double			temp;

	error = ft_atod(split[3], &temp);
	if (error)
		return (ft_list_creation_arg_error(FT_ERR_CY | error, NULL, cy));
	if (temp < 0 || temp > FT_CY_MAX_DIAMETER)
		return (ft_list_creation_arg_error(FT_ERR_CY | FT_ERR_DIAMETER_RANGE, \
			NULL, cy));
	cy->diameter = dtofx(temp);
	error = ft_atod(split[4], &temp);
	if (error)
		return (ft_list_creation_arg_error(FT_ERR_CY | error, NULL, cy));
	if (temp < 0 || temp > FT_CY_MAX_HEIGHT)
		return (ft_list_creation_arg_error(FT_ERR_CY | FT_ERR_HEIGHT_RANGE, \
			NULL, cy));
	cy->height = dtofx(temp);
	return (0);
}

/**
	@brief
	@param s
	@param split
	@return 
*/
int	ft_create_cylinder(void **s, char **split)
{
	int				error;
	t_cylinder		*cy;

	cy = malloc(sizeof(t_cylinder));
	error = ft_create_cylinder_coord_and_vec_hlp(split, cy);
	if (error)
		return (error);
	error = ft_create_cylinder_diameter_height_hlp(split, cy);
	if (error)
		return (error);
	*s = (void *)cy;
	return (0);
}
