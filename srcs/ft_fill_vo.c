/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_vo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 22:26:38 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/20 19:08:35 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

/**
	@brief Calls the respective value assignment and frees sub_split.
	@param sub_split Null-terminated array of strings to be converted to
		numbers.
	@param vo Pointer to a structure with view objects (camera, ambient, light). 
	@param mode Indicates the values to be checked for (point or vector).
	@return 0 on success, else number that indicates on the error.
 */
static int	ft_assign_and_free(char	**sub_split, t_view_object *vo, int mode)
{
	int	error;

	error = 0;
	if (mode == FT_ASS_POINT)
	{
		error = ft_value_assignemnt((void *)&(vo->camera.coord), \
			sub_split, FT_ASS_POINT);
		ft_free_split(sub_split);
	}
	else if (mode == FT_ASS_VEC)
	{
		error = ft_value_assignemnt((void *)&(vo->camera.dir_vector), \
			sub_split, FT_ASS_VEC);
		ft_free_split(sub_split);
	}
	return (error);
}

/**
	@brief Fills the camera structure insides the view object structure.
	@param split Null-terminated array of strings to be added.
	@param vo Pointer to a structure with view objects (camera, ambient, light). 
	@return 0 on success, else number that indicates on the error.
*/
static int	ft_fill_vo_camera(char **split, t_view_object *vo)
{
	double	temp;
	char	**sub_split;
	int		error;

	sub_split = ft_split(split[1], ',');
	if (sub_split == NULL)
		return (FT_ERR_C | FT_ERR_BAD_LINE);
	error = ft_assign_and_free(sub_split, vo, FT_ASS_POINT);
	if (error)
		return (FT_ERR_C | error);
	sub_split = ft_split(split[2], ',');
	if (sub_split == NULL)
		return (FT_ERR_C | FT_ERR_BAD_LINE);
	error = ft_assign_and_free(sub_split, vo, FT_ASS_VEC);
	if (error)
		return (FT_ERR_C | error);
	error = ft_atod(split[3], &temp);
	if (error)
		return (FT_ERR_C | error);
	if (temp < 0 || temp > 179.99)
		return (FT_ERR_C | FT_ERR_ANGLE_RANGE);
	temp = temp * M_PI / 180;
	vo->camera.angle = dtofx(temp);
	return (0);
}

/**
	@brief Fills the ambient light structure insides the view object structure.
	@param split Null-terminated array of strings to be added.
	@param vo Pointer to a structure with view objects (camera, ambient, light). 
	@return 0 on success, else number that indicates on the error.
*/
static int	ft_fill_vo_ambient(char **split, t_view_object *vo)
{
	double	temp;
	char	**sub_split;
	int		error;

	error = ft_atod(split[1], &temp);
	if (error)
		return (FT_ERR_A | error);
	if (temp < 0 || temp > 1)
		return (FT_ERR_A | FT_ERR_RATIO_RANGE);
	vo->ambient.light_ratio = dtofx(temp);
	sub_split = ft_split(split[2], ',');
	if (sub_split == NULL)
		return (FT_ERR_A | FT_ERR_BAD_LINE);
	error = ft_value_assignemnt((void *)&(vo->ambient.color), \
		sub_split, FT_ASS_RGB);
	ft_free_split(sub_split);
	if (error)
		return (FT_ERR_A | error);
	return (0);
}

/**
	@brief Fills the light structure insides the view object structure.
	@param split Null-terminated array of strings to be added.
	@param vo Pointer to a structure with view objects (camera, ambient, light). 
	@return 0 on success, else number that indicates on the error.
*/
static int	ft_fill_vo_light(char **split, t_view_object *vo)
{
	double	temp;
	char	**sub_split;
	int		error;

	sub_split = ft_split(split[1], ',');
	if (sub_split == NULL)
		return (FT_ERR_L | FT_ERR_BAD_LINE);
	error = ft_value_assignemnt((void *)&(vo->light.coord), \
		sub_split, FT_ASS_POINT);
	ft_free_split(sub_split);
	if (error)
		return (FT_ERR_L | error);
	error = ft_atod(split[2], &temp);
	if (error)
		return (FT_ERR_L | error);
	if (temp < 0 || temp > 1)
		return (FT_ERR_L | FT_ERR_RATIO_RANGE);
	vo->light.light_ratio = dtofx(temp);
	return (0);
}

/**
	@brief Saves data from split into the view object structure in regards of
		object type.
	@param split Null-terminated array of strings to be added.
	@param vo Pointer to a structure with view objects (camera, ambient, light). 
	@return 0 on success, else number that indicates on the error.
*/
int	ft_fill_vo(char **split, t_view_object *vo)
{
	int	error;

	if (!ft_strcmp(split[0], "C"))
	{
		error = ft_fill_vo_camera(split, vo);
		if (error)
			return (error);
	}
	else if (!ft_strcmp(split[0], "A"))
	{
		error = ft_fill_vo_ambient(split, vo);
		if (error)
			return (error);
	}
	else
	{
		error = ft_fill_vo_light(split, vo);
		if (error)
			return (error);
	}
	return (0);
}
