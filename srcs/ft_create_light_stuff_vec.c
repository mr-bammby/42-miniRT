/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_light_stuff_vec.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 14:58:09 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/21 22:37:15 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

/**
	@brief Calculates the surface vector for a sphere.
	@param sphere Structure of a sphere object.
	@param point he point on the sphere the surface vector needs to be
		calculated for.
	@return Returns the surface vector.
*/
static t_vec	ft_sp_surface_vec(t_sphere sphere, t_point point)
{
	t_vec	surface_vec;

	surface_vec = ft_creat_vec(dtofx(fxtod(point.x) - fxtod(sphere.coord.x)), \
		dtofx(fxtod(point.y) - fxtod(sphere.coord.y)), dtofx(fxtod(point.z) - \
		fxtod(sphere.coord.z)));
	return (surface_vec);
}

/**
	@brief Calculates the surface vector for a cylinder.
	@param cylinder Structure of a cylinder object.
	@param point The point on the cylinder the surface vector needs to be
		calculated for.
	@return Returns the surface vector.
*/
static t_vec	ft_cy_surface_vec(t_cylinder cylinder, t_point point)
{
	t_fixed	t;
	t_point	top_point;
	t_fixed	cy_height;
	t_vec	surface_vec;

	cy_height = ft_point_height_loc(cylinder, point);
	if (fabs(fxtod(cy_height) - fxtod(cylinder.height) / 2) < FT_PR)
		surface_vec = cylinder.dir_vector;
	else if (fabs(fxtod(cy_height) + fxtod(cylinder.height) / 2) < FT_PR)
		surface_vec = ft_rev_vec(cylinder.dir_vector);
	else
	{
		t = ft_point_height_loc(cylinder, point);
		top_point.x = dtofx(fxtod(cylinder.coord.x) + \
			(fxtod(t) * fxtod(cylinder.dir_vector.n_vec.x)));
		top_point.y = dtofx(fxtod(cylinder.coord.y) + (fxtod(t) * \
			fxtod(cylinder.dir_vector.n_vec.y)));
		top_point.z = dtofx(fxtod(cylinder.coord.z) + (fxtod(t) * \
			fxtod(cylinder.dir_vector.n_vec.z)));
		surface_vec = ft_creat_vec(dtofx(fxtod(point.x) - fxtod(top_point.x)), \
			dtofx(fxtod(point.y) - fxtod(top_point.y)), \
			dtofx(fxtod(point.z) - fxtod(top_point.z)));
	}
	return (surface_vec);
}

/**
	@brief Calculates unit vector of surface(norm).
	@param point Point on the surface of thee object.
	@param object The geometric object.
	@return Calculated vector.
*/
t_vec	ft_create_surface_vec(t_point point, t_geo_object object)
{
	t_vec	surface_vec;

	if (object.type == FT_SP_TYPE)
		surface_vec = ft_sp_surface_vec(*((t_sphere *)(object.s)), point);
	else if (object.type == FT_PL_TYPE)
		surface_vec = ((t_plane *)(object.s))->dir_vector;
	else if (object.type == FT_CY_TYPE)
		surface_vec = ft_cy_surface_vec(*((t_cylinder *)(object.s)), point);
	else
		surface_vec = ft_creat_vec(0, 0, 0);
	surface_vec.size = ltofx(1);
	return (surface_vec);
}

/**
	@brief Calculates unit vector from the point to light.
	@param light Structure of the light view object.
	@param point Point in space.
	@return Calculated vector.
*/
t_vec	ft_create_light_vec(t_light light, t_point point)
{
	t_vec	light_vec_inv;

	light_vec_inv = ft_creat_vec(dtofx(fxtod(light.coord.x) - fxtod(point.x)), \
		dtofx(fxtod(light.coord.y) - fxtod(point.y)), \
		dtofx(fxtod(light.coord.z) - fxtod(point.z)));
	light_vec_inv.size = ltofx(1);
	return (light_vec_inv);
}

/**
	@brief Calculates unit vector from the point to camera.
	@param camera Structure of the camera view object.
	@param point Point in space.
	@return Calculated vector.
*/
t_vec	ft_create_cam_vec(t_camera camera, t_point point)
{
	t_vec	camera_vec_inv;

	camera_vec_inv = ft_creat_vec(dtofx(fxtod(camera.coord.x) - \
		fxtod(point.x)), dtofx(fxtod(camera.coord.y) - fxtod(point.y)), \
		dtofx(fxtod(camera.coord.z) - fxtod(point.z)));
	camera_vec_inv.size = ltofx(1);
	return (camera_vec_inv);
}
