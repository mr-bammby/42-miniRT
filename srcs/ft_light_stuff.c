/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_light_stuff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 14:58:09 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/18 18:01:01 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

int ft_apply_light(t_geo_object obj, t_fixed light_norm_rgb[3])
{
	int out;
	int temp;
	temp = ((int)(255 * ((fxtod(obj.color[0]) / 255.0) * fxtod(light_norm_rgb[0]))));
	if (temp > 255)
		temp = 255;
	out = temp << 16;
	temp = ((int)(255 * ((fxtod(obj.color[1]) / 255.0) * fxtod(light_norm_rgb[1]))));
	if (temp > 255)
		temp = 255;
	out = out + (temp << 8);
	temp = ((int)(255 * ((fxtod(obj.color[2]) / 255.0) * fxtod(light_norm_rgb[2]))));
	if (temp > 255)
		temp = 255;
	out = out + temp;
	return (out);
}

void	ft_calc_ambient(t_fixed rgb[3], t_ambient ambient)
{
	rgb[0] = dtofx((fxtod(ambient.color[0])) * fxtod(ambient.light_ratio) / 255);
	rgb[1] = dtofx((fxtod(ambient.color[1])) * fxtod(ambient.light_ratio) / 255);
	rgb[2] = dtofx((fxtod(ambient.color[2])) * fxtod(ambient.light_ratio) / 255);
}

t_point ft_closest_point_on_axis(t_cylinder cylinder, t_point point)
{
	t_fixed t;
	t_point out;

	t = ft_point_height_loc(cylinder, point);
	out.x = dtofx(fxtod(cylinder.coord.x) + (fxtod(t) * fxtod(cylinder.dir_vector.n_vec.x)));
	out.y = dtofx(fxtod(cylinder.coord.y) + (fxtod(t) * fxtod(cylinder.dir_vector.n_vec.y)));
	out.z = dtofx(fxtod(cylinder.coord.z) + (fxtod(t) * fxtod(cylinder.dir_vector.n_vec.z)));
	return (out);
	
}

void ft_calc_diff_light(t_fixed rgb[3], t_light light, t_point point, t_geo_object object)
{
	t_vec light_vec_inv;
	t_vec surface_vec;
	t_fixed scal_prod;
	t_point cylinder_helper;
	t_fixed cy_height;

	light_vec_inv = ft_creat_vec(dtofx(fxtod(light.coord.x) - fxtod(point.x)), \
		dtofx(fxtod(light.coord.y) - fxtod(point.y)), dtofx(fxtod(light.coord.z) - fxtod(point.z)));
	if (object.type == FT_SP_TYPE)
		surface_vec = ft_creat_vec(dtofx(fxtod(point.x) - fxtod(((t_sphere *)(object.s))->coord.x)), \
		dtofx(fxtod(point.y) - fxtod(((t_sphere *)(object.s))->coord.y)), dtofx(fxtod(point.z) - fxtod(((t_sphere *)(object.s))->coord.z)));
	else if (object.type == FT_PL_TYPE)
		surface_vec = ((t_plane *)(object.s))->dir_vector;
	else if (object.type == FT_CY_TYPE)
	{
		cy_height = ft_point_height_loc(*((t_cylinder *)(object.s)), point);
		if (fabs(fxtod(cy_height) - fxtod(((t_cylinder *)(object.s))->height) / 2) < 0.0001)
			surface_vec = ((t_cylinder *)(object.s))->dir_vector;
		else if (fabs(fxtod(cy_height) + fxtod(((t_cylinder *)(object.s))->height) / 2) < 0.0001)
			surface_vec = ft_rev_vec(((t_cylinder *)(object.s))->dir_vector);
		else
		{
			cylinder_helper = ft_closest_point_on_axis(*((t_cylinder *)(object.s)), point);
			surface_vec = ft_creat_vec(dtofx(fxtod(point.x) - fxtod(cylinder_helper.x)), dtofx(fxtod(point.y) - fxtod(cylinder_helper.y)), dtofx(fxtod(point.z) - fxtod(cylinder_helper.z)));
		}
	}
	else
		surface_vec = ft_creat_vec(0, 0, 0);
	surface_vec.size = ltofx(1);
	light_vec_inv.size = ltofx(1);
	scal_prod = ft_scalar_prod(light_vec_inv, surface_vec);
	if (object.type != FT_PL_TYPE && fxtod(scal_prod) <= 0)
		return ;
	else
		scal_prod = dtofx(fabs(fxtod(scal_prod)));
	rgb[0] = dtofx(fxtod(rgb[0]) + (fxtod(scal_prod) * fxtod(light.light_ratio)));
	rgb[1] = dtofx(fxtod(rgb[1]) + (fxtod(scal_prod) * fxtod(light.light_ratio)));
	rgb[2] = dtofx(fxtod(rgb[2]) + (fxtod(scal_prod) * fxtod(light.light_ratio)));
}

int ft_calc_all_light(t_point point, t_geo_object object, t_view_object vo, t_list *gol)
{
	t_fixed out_norm_rgb[3];
	t_ray ray;
	t_fixed view_point_dist;
	t_fixed dist;

	ft_calc_ambient(out_norm_rgb, vo.ambient);
	ray = ft_create_ray(vo.light.coord, point);
	view_point_dist = ft_points_dist(vo.light.coord, point);
	while (gol != NULL)
	{
		if (((t_geo_object *)(gol->content))->type == FT_SP_TYPE)
			dist = ft_sphere_distance(*(((t_sphere *)(((t_geo_object *)(gol->content))->s))), ray);
		else if (((t_geo_object *)(gol->content))->type == FT_PL_TYPE)
			dist = ft_plane_distance(*(((t_plane *)(((t_geo_object *)(gol->content))->s))), ray);
		else if (((t_geo_object *)(gol->content))->type == FT_CY_TYPE)
			dist = ft_cylinder_distance(*(((t_cylinder *)(((t_geo_object *)(gol->content))->s))), ray);
		if (fxtod(dist) > 0 && (fxtod(dist) - fxtod(view_point_dist)) < -0.001)
			return (ft_apply_light(object, out_norm_rgb));
		gol = gol->next;
	}
	ft_calc_diff_light(out_norm_rgb, vo.light, point, object);
	return (ft_apply_light(object, out_norm_rgb));
}
