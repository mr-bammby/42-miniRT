/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_gol.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 23:19:39 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/20 13:57:46 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

/**
	@brief
	@param split
	@param go
	@param rgb_index
	@return 
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
	@brief
	@param type
	@param go
	@param split
	@return 
*/
static int	ft_geo_obj_shp_setup(int type, t_geo_object **go, char **split)
{
	int	error;

	*go = ft_calloc(1, sizeof(t_geo_object));
	if (*go == NULL)
		return ((FT_ERR_SP << type) | FT_ERR_ALLOC_MEM);
	(*go)->type = type;
	if (type == FT_SP_TYPE)
	{
		error = ft_create_sphere(&((*go)->s), split);
		if (error)
			return (ft_list_creation_arg_error(error, *go, (void *)((*go)->s)));
	}
	else if (type == FT_PL_TYPE)
	{
		error = ft_create_plane_builder(&((*go)->s), split);
		if (error)
			return (ft_list_creation_arg_error(error, *go, (void *)((*go)->s)));
	}
	else
	{
		error = ft_create_cylinder(&((*go)->s), split);
		if (error)
			return (ft_list_creation_arg_error(error, *go, (void *)((*go)->s)));
	}
	return (0);
}

/**
	@brief
	@param split
	@param gol
	@param rgb_index
	@return 
*/
static int	ft_geo_obj_shp_hnd(char **split, t_geo_object **go, int *rgb_index)
{
	int	error;

	if (!ft_strcmp(split[0], "sp"))
	{
		*rgb_index = 3;
		error = ft_geo_obj_shp_setup(FT_SP_TYPE, go, split);
		if (error)
			return (error);
	}
	else if (!ft_strcmp(split[0], "pl"))
	{
		*rgb_index = 3;
		error = ft_geo_obj_shp_setup(FT_PL_TYPE, go, split);
		if (error)
			return (error);
	}
	else
	{
		*rgb_index = 5;
		error = ft_geo_obj_shp_setup(FT_CY_TYPE, go, split);
		if (error)
			return (error);
	}
	return (0);
}

/**
	@brief
	@param split
	@param gol
	@return 
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
