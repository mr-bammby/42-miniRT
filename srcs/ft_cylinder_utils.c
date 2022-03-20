/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 23:50:34 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/20 13:56:02 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

/**
	@brief
	@param cylinder
	@param point
	@return 
*/
t_fixed	ft_point_height_loc(t_cylinder cylinder, t_point point)
{
	t_fixed	out;

	out = dtofx((fxtod(cylinder.dir_vector.n_vec.x) * (fxtod(point.x) - \
		fxtod(cylinder.coord.x))) + (fxtod(cylinder.dir_vector.n_vec.y) * \
		(fxtod(point.y) - fxtod(cylinder.coord.y))) + \
		(fxtod(cylinder.dir_vector.n_vec.z) * (fxtod(point.z) - \
		fxtod(cylinder.coord.z))));
	return (out);
}

/**
	@brief
	@param cylinder
	@param ray
	@param scal_prod
	@param mode
	@return 
*/
t_fixed	ft_dist2disc(t_cylinder cylinder, t_ray ray, \
	t_fixed scal_prod, int mode)
{
	t_fixed	out;
	t_point	point;
	t_plane	plane;
	t_ray	cy_axis;

	cy_axis.source = cylinder.coord;
	if (scal_prod < 0)
		cy_axis.direction = cylinder.dir_vector;
	else
		cy_axis.direction = ft_rev_vec(cylinder.dir_vector);
	point = ft_point_on_ray(cy_axis, dtofx(fxtod(cylinder.height) / 2));
	plane = ft_create_plane(point, cy_axis.direction.n_vec);
	out = ft_plane_distance(plane, ray);
	if (mode == FT_RADIUS_CHECK)
		if (fxtod(ft_points_dist(point, ft_point_on_ray(ray, out))) > \
			fxtod(cylinder.diameter) / 2)
			return (ltofx(-1));
	return (out);
}

/**
	@brief
	@param cylinder
	@param ray
	@return 
*/
t_fixed	ft_numerical_coefficient_c(t_cylinder cylinder, t_ray ray)
{
	t_fixed	a1;
	t_fixed	b1;
	t_fixed	c1;
	t_fixed	c;

	a1 = dtofx((fxtod(cylinder.dir_vector.n_vec.y) * \
		(fxtod(cylinder.coord.z) - fxtod(ray.source.z))) - \
		(fxtod(cylinder.dir_vector.n_vec.z) * (fxtod(cylinder.coord.y) - \
		fxtod(ray.source.y))));
	b1 = dtofx((fxtod(cylinder.dir_vector.n_vec.z) * \
		(fxtod(cylinder.coord.x) - fxtod(ray.source.x))) - \
		(fxtod(cylinder.dir_vector.n_vec.x) * (fxtod(cylinder.coord.z) - \
		fxtod(ray.source.z))));
	c1 = dtofx((fxtod(cylinder.dir_vector.n_vec.x) * \
		(fxtod(cylinder.coord.y) - fxtod(ray.source.y))) - \
		(fxtod(cylinder.dir_vector.n_vec.y) * (fxtod(cylinder.coord.x) - \
		fxtod(ray.source.x))));
	c = dtofx(pow(fxtod(a1), 2) + pow(fxtod(b1), 2) + pow(fxtod(c1), 2) - \
		pow(fxtod(cylinder.diameter) / 2, 2));
	return (c);
}

/**
	@brief
	@param cylinder
	@param ray
	@return 
*/
t_fixed	ft_numerical_coefficient_b(t_cylinder cylinder, t_ray ray)
{
	t_fixed	fc[3][2];

	fc[0][0] = dtofx((fxtod(cylinder.dir_vector.n_vec.z) * \
		fxtod(ray.direction.n_vec.y)) - (fxtod(cylinder.dir_vector.n_vec.y) * \
		fxtod(ray.direction.n_vec.z)));
	fc[0][1] = dtofx((fxtod(cylinder.dir_vector.n_vec.y) * \
		(fxtod(cylinder.coord.z) - fxtod(ray.source.z))) - \
		(fxtod(cylinder.dir_vector.n_vec.z) * \
		(fxtod(cylinder.coord.y) - fxtod(ray.source.y))));
	fc[1][0] = dtofx((fxtod(cylinder.dir_vector.n_vec.x) * \
		fxtod(ray.direction.n_vec.z)) - (fxtod(cylinder.dir_vector.n_vec.z) * \
		fxtod(ray.direction.n_vec.x)));
	fc[1][1] = dtofx((fxtod(cylinder.dir_vector.n_vec.z) * \
		(fxtod(cylinder.coord.x) - fxtod(ray.source.x))) - \
		(fxtod(cylinder.dir_vector.n_vec.x) * \
		(fxtod(cylinder.coord.z) - fxtod(ray.source.z))));
	fc[2][0] = dtofx((fxtod(cylinder.dir_vector.n_vec.y) * \
		fxtod(ray.direction.n_vec.x)) - (fxtod(cylinder.dir_vector.n_vec.x) * \
		fxtod(ray.direction.n_vec.y)));
	fc[2][1] = dtofx((fxtod(cylinder.dir_vector.n_vec.x) * \
		(fxtod(cylinder.coord.y) - fxtod(ray.source.y))) - \
		(fxtod(cylinder.dir_vector.n_vec.y) * (fxtod(cylinder.coord.x) - \
		fxtod(ray.source.x))));
	return (dtofx(2 * (fxtod(fc[0][0]) * fxtod(fc[0][1]) + fxtod(fc[1][0]) * \
		fxtod(fc[1][1]) + fxtod(fc[2][0]) * fxtod(fc[2][1]))));
}

/**
	@brief
	@param cylinder
	@param ray
	@return 
*/
t_fixed	ft_numerical_coefficient_a(t_cylinder cylinder, t_ray ray)
{
	t_fixed	a0;
	t_fixed	b0;
	t_fixed	c0;
	t_fixed	a;

	a0 = dtofx((fxtod(cylinder.dir_vector.n_vec.z) * \
		fxtod(ray.direction.n_vec.y)) - (fxtod(cylinder.dir_vector.n_vec.y) * \
		fxtod(ray.direction.n_vec.z)));
	b0 = dtofx((fxtod(cylinder.dir_vector.n_vec.x) * \
		fxtod(ray.direction.n_vec.z)) - (fxtod(cylinder.dir_vector.n_vec.z) * \
		fxtod(ray.direction.n_vec.x)));
	c0 = dtofx((fxtod(cylinder.dir_vector.n_vec.y) * \
		fxtod(ray.direction.n_vec.x)) - (fxtod(cylinder.dir_vector.n_vec.x) * \
		fxtod(ray.direction.n_vec.y)));
	a = dtofx(pow(fxtod(a0), 2) + pow(fxtod(b0), 2) + pow(fxtod(c0), 2));
	return (a);
}
