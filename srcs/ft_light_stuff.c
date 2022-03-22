/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_light_stuff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 14:58:09 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/21 22:29:43 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

/**
	@brief Calculates the color value as integer out of given rgb values.
	@param obj The structure of the geometric object.
	@param light_norm_rgb The array that holds the rgb values for color and
		light effects.
	@return Returns the color value as integer.
*/
static int	ft_apply_light(t_geo_object obj, t_fixed light_norm_rgb[3])
{
	int	out;
	int	temp;

	temp = ((int)(255 * ((fxtod(obj.color[0]) / 255.0) * \
		fxtod(light_norm_rgb[0]))));
	if (temp > 255)
		temp = 255;
	out = temp << 16;
	temp = ((int)(255 * ((fxtod(obj.color[1]) / 255.0) * \
		fxtod(light_norm_rgb[1]))));
	if (temp > 255)
		temp = 255;
	out = out + (temp << 8);
	temp = ((int)(255 * ((fxtod(obj.color[2]) / 255.0) * \
		fxtod(light_norm_rgb[2]))));
	if (temp > 255)
		temp = 255;
	out = out + temp;
	return (out);
}

/**
	@brief Calculates the ambient light effect.
	@param rgb The array that holds the rgb values for color and
		light effects.
	@param ambient Structure of the ambient light view object.
	@return None.
*/
static void	ft_calc_ambient(t_fixed rgb[3], t_ambient ambient)
{
	rgb[0] = dtofx((fxtod(ambient.color[0])) * \
		fxtod(ambient.light_ratio) / 255);
	rgb[1] = dtofx((fxtod(ambient.color[1])) * \
		fxtod(ambient.light_ratio) / 255);
	rgb[2] = dtofx((fxtod(ambient.color[2])) * \
		fxtod(ambient.light_ratio) / 255);
}

static int	ft_shadow_hunter(t_view_object vo, t_list *gol, t_point point)
{
	t_ray	ray;
	t_fixed	view_point_dist;
	t_fixed	dist;

	ray = ft_create_ray(vo.light.coord, point);
	view_point_dist = ft_points_dist(vo.light.coord, point);
	while (gol != NULL)
	{
		if (((t_geo_object *)(gol->content))->type == FT_SP_TYPE)
			dist = ft_sphere_distance(*(((t_sphere *)(((t_geo_object *) \
				(gol->content))->s))), ray);
		else if (((t_geo_object *)(gol->content))->type == FT_PL_TYPE)
			dist = ft_plane_distance(*(((t_plane *)(((t_geo_object *) \
				(gol->content))->s))), ray);
		else if (((t_geo_object *)(gol->content))->type == FT_CY_TYPE)
			dist = ft_cylinder_distance(*(((t_cylinder *)(((t_geo_object *) \
				(gol->content))->s))), ray);
		if (fxtod(dist) > 0 && (fxtod(dist) - fxtod(view_point_dist)) < -0.001)
			return (1);
		gol = gol->next;
	}
	return (0);
}

/**
	@brief Calculates all the light effects and their colors (ambient light,
		diffuse light)
	@param point Point on the view screen.
	@param object The geometric object.
	@param vo Structure with view objects (camera, ambient, light).
	@param gol List of objects to be considered.
	@return Returns the color value as integer.
*/
int	ft_calc_all_light(t_point point, t_geo_object object, \
	t_view_object vo, t_list *gol)
{
	t_fixed	out_norm_rgb[3];
	t_vec	vec_arr_lsc[3];

	ft_calc_ambient(out_norm_rgb, vo.ambient);
	if (ft_shadow_hunter(vo, gol, point))
		return (ft_apply_light(object, out_norm_rgb));
	vec_arr_lsc[0] = ft_create_light_vec(vo.light, point);
	vec_arr_lsc[1] = ft_create_surface_vec(point, object);
	vec_arr_lsc[2] = ft_create_cam_vec(vo.camera, point);
	ft_calc_diff_light(out_norm_rgb, vec_arr_lsc, object, vo.light);
	return (ft_apply_light(object, out_norm_rgb));
}
