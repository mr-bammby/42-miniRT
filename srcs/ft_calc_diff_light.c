/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc_diff_light.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 14:58:09 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/23 19:17:07 by dbanfi           ###   ########.fr       */
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
	@brief Calculates the light effect of diffuse light from a light source.
	@param rgb The array that holds the rgb values for color and
		light effects.
	@param vo Structure with view objects (camera, ambient, light).
	@param point Point on the screen for which the light effect needs to be 
		calculated.
	@param object The geometric object.
	@return None.
*/
void	ft_calc_diff_light(t_fixed rgb[3], t_view_object vo, t_point point, \
	t_geo_object object)
{
	t_vec	surface_vec;
	t_fixed	scal;

	if (object.type == FT_SP_TYPE)
		surface_vec = ft_sp_surface_vec(*((t_sphere *)(object.s)), point);
	else if (object.type == FT_PL_TYPE)
		surface_vec = ((t_plane *)(object.s))->dir_vector;
	else if (object.type == FT_CY_TYPE)
		surface_vec = ft_cy_surface_vec(*((t_cylinder *)(object.s)), point);
	else
		surface_vec = ft_creat_vec(0, 0, 0);
	surface_vec.size = ltofx(1);
	scal = ft_scalar_prod(ft_create_vec_from_points(point, \
		vo.light.coord, ltofx(1)), surface_vec);
	if (object.type == FT_PL_TYPE && \
		((fxtod(ft_scalar_prod(ft_create_vec_from_points(point, \
		vo.camera.coord, ltofx(1)), surface_vec)) * fxtod(scal)) > 0))
		scal = dtofx(fabs(fxtod(scal)));
	else if (object.type == FT_PL_TYPE)
		return ;
	if (fxtod(scal) <= 0)
		return ;
	rgb[0] = dtofx(fxtod(rgb[0]) + (fxtod(scal) * fxtod(vo.light.light_ratio)));
	rgb[1] = dtofx(fxtod(rgb[1]) + (fxtod(scal) * fxtod(vo.light.light_ratio)));
	rgb[2] = dtofx(fxtod(rgb[2]) + (fxtod(scal) * fxtod(vo.light.light_ratio)));
}
