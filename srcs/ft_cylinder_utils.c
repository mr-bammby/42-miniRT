/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 23:50:34 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/21 00:40:29 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

/**
	@brief Calculates the distance of a point on a cylinder in regards to the
		center part of the cylinder and its direction vector.
	@param cylinder Structure of a cylinder object.
	@param point Intersection point with a cylinder.
	@return Returns the distance from the center of a cylinder to the
		given point.
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
	@brief Calculates the distance to an intersection point on a ray on the
		top/bottom part of a cylinder.
	@param cylinder Structure of a cylinder object.
	@param ray Structure of the ray to intersect with the cylinder.
	@param scal_prod Scalar product between the direction vector of the cylinder
		and the ray.
	@param mode Indicates if the return value needs to be checked for
		the cylinder.
	@return Returns the distance from ray source to the intersection point 
		on top/bottom part of cylinder. -1 if distance value isn't in 
			radius range.
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
	@brief Calculates the numerical coefficiant "c" for solving quadratic equations.
	@param cylinder Structure of a cylinder object.
	@param ray Structure of the ray to intersect with the cylinder.
	@return Returns the numerical coefficiant "c" for further calculations.
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
	@brief Calculates the numerical coefficiant "b" for solving quadratic equations.
	@param cylinder Structure of a cylinder object.
	@param ray Structure of the ray to intersect with the cylinder.
	@return Returns the numerical coefficiant "b" for further calculations.
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
	@brief Calculates the numerical coefficiant "a" for solving quadratic equations.
	@param cylinder Structure of a cylinder object.
	@param ray Structure of the ray to intersect with the cylinder.
	@return Returns the numerical coefficiant "a" for further calculations.
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
