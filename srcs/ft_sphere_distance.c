/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sphere_distance.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 01:15:54 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/19 21:43:24 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

/**
	@brief Calculates a, b, c factors of quadratic equation 
		for sphere ray intersections.
	@param abc Array of t_fixed numbers of calculated factors.
	@param sphere Sphere for calculation.
	@param ray Ray for calculation.
	@return None.
 */
static void	ft_sphere_abc_calc(t_fixed abc[3], t_sphere sphere, t_ray ray)
{
	abc[0] = dtofx(pow(fxtod(ray.direction.n_vec.x), 2) + \
		pow(fxtod(ray.direction.n_vec.y), 2) + \
		pow(fxtod(ray.direction.n_vec.z), 2));
	abc[1] = dtofx(2 * (((fxtod(ray.source.x) - \
		fxtod(sphere.coord.x)) * fxtod(ray.direction.n_vec.x)) + \
		((fxtod(ray.source.y) - fxtod(sphere.coord.y)) * \
		fxtod(ray.direction.n_vec.y)) + ((fxtod(ray.source.z) - \
		fxtod(sphere.coord.z)) * fxtod(ray.direction.n_vec.z))));
	abc[2] = dtofx(pow(fxtod(ray.source.x) - \
		fxtod(sphere.coord.x), 2) + pow(fxtod(ray.source.y) - \
		fxtod(sphere.coord.y), 2) + pow(fxtod(ray.source.z) - \
		fxtod(sphere.coord.z), 2) - pow(fxtod(sphere.diameter) / 2, 2));
}

/**
	@brief Calculates the distence between source of ray and
		the closest intersection between sphere and ray.
	@param abc Array of t_fixed numbers of calculated factors.
	@param sphere Sphere for calculation.
	@param ray Ray for calculation.
	@return Distance to the closest intersection or
		-1 of there is no intersection.
 */
t_fixed	ft_sphere_distance(t_sphere sphere, t_ray ray)
{
	t_fixed	abc[3];
	t_fixed	result[2];
	int		result_num;

	ft_sphere_abc_calc(abc, sphere, ray);
	result_num = ft_quadratic_solver(abc[0], abc[1], abc[2], result);
	if (result_num == 0)
		return (ltofx(-1));
	else if (result_num == 1)
		return (result[0]);
	if (result[0] > result[1])
		return (result[1]);
	return (result[0]);
}
