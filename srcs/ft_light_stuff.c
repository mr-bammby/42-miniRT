/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_light_stuff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 14:58:09 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/14 21:33:52 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

int ft_apply_light(t_geo_object obj, t_fixed light_norm_rgb[3])
{
	int out;
	int temp;
	temp = ((int)(255 * ((fixed2double(obj.color[0]) / 255.0) * fixed2double(light_norm_rgb[0]))));
	if (temp > 255)
		temp = 255;
	out = temp << 16;
	temp = ((int)(255 * ((fixed2double(obj.color[1]) / 255.0) * fixed2double(light_norm_rgb[1]))));
	if (temp > 255)
		temp = 255;
	out = out + (temp << 8);
	temp = ((int)(255 * ((fixed2double(obj.color[2]) / 255.0) * fixed2double(light_norm_rgb[2]))));
	if (temp > 255)
		temp = 255;
	out = out + temp;
	return (out);
}

void	ft_calc_ambient(t_fixed rgb[3], t_ambient ambient)
{
	rgb[0] = double2fixed((fixed2double(ambient.color[0])) * fixed2double(ambient.light_ratio) / 255);
	rgb[1] = double2fixed((fixed2double(ambient.color[1])) * fixed2double(ambient.light_ratio) / 255);
	rgb[2] = double2fixed((fixed2double(ambient.color[2])) * fixed2double(ambient.light_ratio) / 255);
}

t_point ft_closest_point_on_axis(t_cylinder cylinder, t_point point)
{
	t_fixed t;
	t_point out;

	t = double2fixed((fixed2double(cylinder.dir_vector.n_vec.x) * (fixed2double(point.x) - fixed2double(cylinder.coord.x))) + \
		(fixed2double(cylinder.dir_vector.n_vec.y) * (fixed2double(point.y) - fixed2double(cylinder.coord.y))) + \
		(fixed2double(cylinder.dir_vector.n_vec.z) * (fixed2double(point.z) - fixed2double(cylinder.coord.z))));
	out.x = double2fixed(fixed2double(cylinder.coord.x) + (fixed2double(t) * fixed2double(cylinder.dir_vector.n_vec.x)));
	out.y = double2fixed(fixed2double(cylinder.coord.y) + (fixed2double(t) * fixed2double(cylinder.dir_vector.n_vec.y)));
	out.z = double2fixed(fixed2double(cylinder.coord.z) + (fixed2double(t) * fixed2double(cylinder.dir_vector.n_vec.z)));
	printf("point on axis %f, %f, %f\n", fixed2double(out.x), fixed2double(out.y), fixed2double(out.z));
	return (out);
	
}

void ft_calc_diff_light(t_fixed rgb[3], t_light light, t_point point, t_geo_object object)
{
	t_vec light_vec_inv;
	t_vec surface_vec;
	t_fixed scal_prod;
	t_point cylinder_helper;

	light_vec_inv = ft_creat_vec(double2fixed(fixed2double(light.coord.x) - fixed2double(point.x)), \
		double2fixed(fixed2double(light.coord.y) - fixed2double(point.y)), double2fixed(fixed2double(light.coord.z) - fixed2double(point.z)));
	if (object.type == FT_SP_TYPE)
		surface_vec = ft_creat_vec(double2fixed(fixed2double(point.x) - fixed2double(((t_sphere *)(object.s))->coord.x)), \
		double2fixed(fixed2double(point.y) - fixed2double(((t_sphere *)(object.s))->coord.y)), double2fixed(fixed2double(point.z) - fixed2double(((t_sphere *)(object.s))->coord.z)));
	else if (object.type == FT_PL_TYPE)
		surface_vec = ((t_plane *)(object.s))->dir_vector;
	else if (object.type == FT_CY_TYPE)
	{
		cylinder_helper = ft_closest_point_on_axis(*((t_cylinder *)(object.s)), point);
		surface_vec = ft_creat_vec(double2fixed(fixed2double(point.x) - fixed2double(cylinder_helper.x)), double2fixed(fixed2double(point.y) - fixed2double(cylinder_helper.y)), double2fixed(fixed2double(point.z) - fixed2double(cylinder_helper.z)));
	}
	else
		surface_vec = ft_creat_vec(0, 0, 0);
	surface_vec.size = long2fixed(1);
	light_vec_inv.size = long2fixed(1);
	scal_prod = ft_scalar_prod(light_vec_inv, surface_vec);
	if (object.type != FT_PL_TYPE && fixed2double(scal_prod) <= 0)
		return ;
	else
		scal_prod = double2fixed(fabs(fixed2double(scal_prod)));
	rgb[0] = double2fixed(fixed2double(rgb[0]) + (fixed2double(scal_prod) * fixed2double(light.light_ratio)));
	rgb[1] = double2fixed(fixed2double(rgb[1]) + (fixed2double(scal_prod) * fixed2double(light.light_ratio)));
	rgb[2] = double2fixed(fixed2double(rgb[2]) + (fixed2double(scal_prod) * fixed2double(light.light_ratio)));
}

int ft_calc_all_light(t_point point, t_geo_object object, t_view_object vo, t_list *gol)
{
	t_fixed out_norm_rgb[3];
	t_ray ray;
	t_fixed view_point_dist;
	t_fixed dist;
	int temp;

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
		if (fixed2double(dist) > 0 && (fixed2double(dist) - fixed2double(view_point_dist)) < -0.001)
			return (ft_apply_light(object, out_norm_rgb));
		gol = gol->next;
	}
	ft_calc_diff_light(out_norm_rgb, vo.light, point, object);
	return (ft_apply_light(object, out_norm_rgb));
}
