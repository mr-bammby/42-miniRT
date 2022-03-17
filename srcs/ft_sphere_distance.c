/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sphere_distance.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 01:15:54 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/18 18:01:01 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

// (x - A)^2 + (y - B)^2 + (z - C)^2 = R^2
// (a^2 + b^2 + c^2)t^2 + 2((x0 - A)a + (y0 - B)b + (z0 - C)c)t +
// (x0 - A)^2 + (y0 - B)^2 + (z0 - C)^2 - R^2 = 0
t_fixed ft_sphere_distance(t_sphere sphere, t_ray ray)
{
	t_fixed a;
	t_fixed b;
	t_fixed c;
	t_fixed result[2];
	int		result_num;

	a = dtofx(pow(fxtod(ray.direction.n_vec.x), 2) + \
		pow(fxtod(ray.direction.n_vec.y), 2) + \
		pow(fxtod(ray.direction.n_vec.z), 2));
	b = dtofx(2 * (((fxtod(ray.source.x) - \
		fxtod(sphere.coord.x)) * fxtod(ray.direction.n_vec.x)) + \
		((fxtod(ray.source.y) - fxtod(sphere.coord.y)) * \
		fxtod(ray.direction.n_vec.y)) + ((fxtod(ray.source.z) - \
		fxtod(sphere.coord.z)) * fxtod(ray.direction.n_vec.z))));
	c = dtofx(pow(fxtod(ray.source.x) - \
		fxtod(sphere.coord.x) , 2) + pow(fxtod(ray.source.y) - \
		fxtod(sphere.coord.y), 2) + pow(fxtod(ray.source.z) - \
		fxtod(sphere.coord.z), 2) - pow(fxtod(sphere.diameter)/2, 2));
	result_num = ft_quadratic_solver(a, b, c, result);
	if (result_num == 0)
		return (ltofx(-1));
	else if (result_num == 1)
		return (result[0]);
	if (result[0] > result[1])
		return (result[1]);
	return (result[0]);
}