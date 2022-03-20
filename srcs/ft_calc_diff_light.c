/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc_diff_light.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 14:58:09 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/20 11:56:34 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

/**
	@brief
	@param sphere
	@param point
	@return 
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
	@brief
	@param cylinder
	@param point
	@return 
*/
static t_vec	ft_cy_surface_vec(t_cylinder cylinder, t_point point)
{
	t_fixed	t;
	t_point	top_point;
	t_fixed	cy_height;
	t_vec	surface_vec;

	cy_height = ft_point_height_loc(cylinder, point);
	if (fabs(fxtod(cy_height) - fxtod(cylinder.height) / 2) < 0.0001)
		surface_vec = cylinder.dir_vector;
	else if (fabs(fxtod(cy_height) + fxtod(cylinder.height) / 2) < 0.0001)
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
	@brief
	@param rgb
	@param light
	@param point
	@param object
	@return 
*/
void	ft_calc_diff_light(t_fixed rgb[3], t_light light, t_point point, \
	t_geo_object object)
{
	t_vec	light_vec_inv;
	t_vec	surface_vec;
	t_fixed	scal_pr;

	light_vec_inv = ft_creat_vec(dtofx(fxtod(light.coord.x) - fxtod(point.x)), \
		dtofx(fxtod(light.coord.y) - fxtod(point.y)), \
		dtofx(fxtod(light.coord.z) - fxtod(point.z)));
	if (object.type == FT_SP_TYPE)
		surface_vec = ft_sp_surface_vec(*((t_sphere *)(object.s)), point);
	else if (object.type == FT_PL_TYPE)
		surface_vec = ((t_plane *)(object.s))->dir_vector;
	else if (object.type == FT_CY_TYPE)
		surface_vec = ft_cy_surface_vec(*((t_cylinder *)(object.s)), point);
	else
		surface_vec = ft_creat_vec(0, 0, 0);
	surface_vec.size = ltofx(1);
	light_vec_inv.size = ltofx(1);
	scal_pr = ft_scalar_prod(light_vec_inv, surface_vec);
	if (object.type != FT_PL_TYPE && fxtod(scal_pr) <= 0)
		return ;
	else
		scal_pr = dtofx(fabs(fxtod(scal_pr)));
	rgb[0] = dtofx(fxtod(rgb[0]) + (fxtod(scal_pr) * fxtod(light.light_ratio)));
	rgb[1] = dtofx(fxtod(rgb[1]) + (fxtod(scal_pr) * fxtod(light.light_ratio)));
	rgb[2] = dtofx(fxtod(rgb[2]) + (fxtod(scal_pr) * fxtod(light.light_ratio)));
}
