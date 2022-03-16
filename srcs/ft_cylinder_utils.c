/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 23:50:34 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/16 01:25:48 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

t_fixed ft_point_height_loc(t_cylinder cylinder, t_point point)
{
	t_fixed out;

	out = double2fixed((fixed2double(cylinder.dir_vector.n_vec.x) * (fixed2double(point.x) - fixed2double(cylinder.coord.x))) + \
		(fixed2double(cylinder.dir_vector.n_vec.y) * (fixed2double(point.y) - fixed2double(cylinder.coord.y))) + \
		(fixed2double(cylinder.dir_vector.n_vec.z) * (fixed2double(point.z) - fixed2double(cylinder.coord.z))));
	return (out);
}

t_fixed ft_dist2disc(t_cylinder cylinder, t_ray ray, t_fixed scal_prod, int mode)
{
	t_fixed out;
	t_point point;
	t_plane plane;
	t_ray	cy_axis;
	
	cy_axis.source = cylinder.coord;
	if (scal_prod < 0)
		cy_axis.direction = cylinder.dir_vector;
	else
		cy_axis.direction = ft_rev_vec(cylinder.dir_vector);
	point = ft_point_on_ray(cy_axis, double2fixed(fixed2double(cylinder.height)/2));
	plane = ft_create_plane(point, cy_axis.direction.n_vec);
	out = ft_plane_distance(plane, ray);
	if (mode == FT_RADIUS_CHECK)
		if (fixed2double(ft_points_dist(point, ft_point_on_ray(ray, out))) > fixed2double(cylinder.diameter)/2)
			return (long2fixed(-1));
	return (out);
}