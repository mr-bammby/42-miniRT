/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sphere_distance.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 01:15:54 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/11 02:14:59 by dbanfi           ###   ########.fr       */
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

	a = double2fixed(pow(fixed2double(ray.direction.n_vec.x), 2) + \
		pow(fixed2double(ray.direction.n_vec.y), 2) + \
		pow(fixed2double(ray.direction.n_vec.z), 2));
	b = double2fixed(2 * (((fixed2double(ray.source.x) - \
		fixed2double(sphere.coord.x)) * fixed2double(ray.direction.n_vec.x)) + \
		((fixed2double(ray.source.y) - fixed2double(sphere.coord.y)) * \
		fixed2double(ray.direction.n_vec.y)) + ((fixed2double(ray.source.z) - \
		fixed2double(sphere.coord.z)) * fixed2double(ray.direction.n_vec.z))));
	c = double2fixed(pow(fixed2double(ray.source.x) - \
		fixed2double(sphere.coord.x) , 2) + pow(fixed2double(ray.source.y) - \
		fixed2double(sphere.coord.y), 2) + pow(fixed2double(ray.source.z) - \
		fixed2double(sphere.coord.z), 2) - pow(fixed2double(sphere.diameter)/2, 2));
	result_num = ft_quadratic_solver(a, b, c, result);
	
	if (result_num != 0)
	{
		printf("ray x %f, y %f, z %f\n", fixed2double(ray.direction.n_vec.x), fixed2double(ray.direction.n_vec.y) , fixed2double(ray.direction.n_vec.z));
		printf("a %f, b %f, c %f result %f\n", fixed2double(a), fixed2double(b) , fixed2double(c), fixed2double(result[0]));
		printf("result: %f %f\n", fixed2double(result[0]), fixed2double(result[1]));
	}
	if (result_num == 0)
		return (long2fixed(-1));
	else if (result_num == 1)
		return (result[0]);
	if (result[0] > result[1])
		return (result[1]);
	return (result[0]);
}