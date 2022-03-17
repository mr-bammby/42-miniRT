/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 23:50:34 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/18 18:01:01 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

t_fixed ft_point_height_loc(t_cylinder cylinder, t_point point)
{
	t_fixed out;

	out = dtofx((fxtod(cylinder.dir_vector.n_vec.x) * (fxtod(point.x) - fxtod(cylinder.coord.x))) + \
		(fxtod(cylinder.dir_vector.n_vec.y) * (fxtod(point.y) - fxtod(cylinder.coord.y))) + \
		(fxtod(cylinder.dir_vector.n_vec.z) * (fxtod(point.z) - fxtod(cylinder.coord.z))));
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
	point = ft_point_on_ray(cy_axis, dtofx(fxtod(cylinder.height)/2));
	plane = ft_create_plane(point, cy_axis.direction.n_vec);
	out = ft_plane_distance(plane, ray);
	if (mode == FT_RADIUS_CHECK)
		if (fxtod(ft_points_dist(point, ft_point_on_ray(ray, out))) > fxtod(cylinder.diameter)/2)
			return (ltofx(-1));
	return (out);
}