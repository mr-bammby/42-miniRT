/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_gol.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 23:19:39 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/20 20:55:21 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

/**
	@brief Assigns the rgb values to the structure of the geometric object.
	@param split Null-terminated array of strings to be added.
	@param go Structure of an geometric object to be filled with values of the 
		respective type.
	@param rgb_index Value with the position of the rgb values in given array 
		of strings.
	@return 0 on success, else number that indicates on the error.
*/
static int	ft_geo_obj_color_hnd(char **split, t_geo_object *go, int rgb_index)
{
	char			**sub_split;
	int				error;

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
		return (ft_list_creation_arg_error(error, go, (void *)(go->s)));
	}
	return (0);
}

/**
	@brief	Assigns structure memory depending on the geometric object type and calls
		respective create function.
	@param type Type of the geometric object.
	@param go Structure of an geometric object to be filled with values of the 
		respective type.
	@param split Null-terminated array of strings to be added.
	@return 0 on success, else number that indicates on the error.
*/
static int	ft_geo_obj_shp_setup(int type, t_geo_object **go, char **split)
{
	int	error;

	*go = ft_calloc(1, sizeof(t_geo_object));
	if (*go == NULL)
		return ((FT_ERR_SP << type) | FT_ERR_ALLOC_MEM);
	(*go)->type = type;
	if (type == FT_SP_TYPE)
		error = ft_create_sphere(&((*go)->s), split);
	else if (type == FT_PL_TYPE)
		error = ft_create_plane_builder(&((*go)->s), split);
	else
		error = ft_create_cylinder(&((*go)->s), split);
	if (error)
		return (ft_list_creation_arg_error(error, *go, (void *)((*go)->s)));
	return (0);
}

/**
	@brief Determines the corresponding geometric type and calls 
		structure setup function.
	@param split Null-terminated array of strings to be added.
	@param gol Pointer to list of objects (sphere, plane, cylinder).
	@param rgb_index Pointer to value that saves the position of the 
		rgb values in given array of strings.
	@return 0 on success, else number that indicates on the error.
*/
static int	ft_geo_obj_shp_hnd(char **split, t_geo_object **go, int *rgb_index)
{
	int	error;

	*rgb_index = 3;
	if (!ft_strcmp(split[0], "sp"))
		error = ft_geo_obj_shp_setup(FT_SP_TYPE, go, split);
	else if (!ft_strcmp(split[0], "pl"))
		error = ft_geo_obj_shp_setup(FT_PL_TYPE, go, split);
	else
	{
		*rgb_index = 5;
		error = ft_geo_obj_shp_setup(FT_CY_TYPE, go, split);
	}
	if (error)
		return (error);
	return (0);
}

/**
	@brief Saves data from split into the geometric object structure in regards of
		object type.
	@param split Null-terminated array of strings to be added.
	@param gol Pointer to list of objects (sphere, plane, cylinder).
	@return 0 on success, else number that indicates on the error.
*/
int	ft_create_gol(char **split, t_list **gol)
{
	int				error;
	t_geo_object	*go;
	int				rgb_index;

	error = ft_geo_obj_shp_hnd(split, &go, &rgb_index);
	if (error)
		return (error);
	error = ft_geo_obj_color_hnd(split, go, rgb_index);
	if (error)
		return (error);
	ft_lstadd_back(gol, ft_lstnew((void *)go));
	return (0);
}
