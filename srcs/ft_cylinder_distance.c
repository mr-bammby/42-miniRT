/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder_distance.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 01:15:54 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/13 20:52:42 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

static t_fixed	ft_numerical_coefficient_c(t_cylinder cylinder, t_ray ray)
{
	t_fixed	a1;
	t_fixed	b1;
	t_fixed	c1;
	t_fixed	c;

	a1 = double2fixed((fixed2double(cylinder.dir_vector.n_vec.y) * (fixed2double(cylinder.coord.z) - fixed2double(ray.source.z))) - (fixed2double(cylinder.dir_vector.n_vec.z) * (fixed2double(cylinder.coord.y) - fixed2double(ray.source.y))));
	b1 = double2fixed((fixed2double(cylinder.dir_vector.n_vec.z) * (fixed2double(cylinder.coord.x) - fixed2double(ray.source.x))) - (fixed2double(cylinder.dir_vector.n_vec.x) * (fixed2double(cylinder.coord.z) - fixed2double(ray.source.z))));
	c1 = double2fixed((fixed2double(cylinder.dir_vector.n_vec.x) * (fixed2double(cylinder.coord.y) - fixed2double(ray.source.y))) - (fixed2double(cylinder.dir_vector.n_vec.y) * (fixed2double(cylinder.coord.x) - fixed2double(ray.source.x))));
	c = double2fixed(pow(fixed2double(a1), 2) + pow(fixed2double(b1), 2) + pow(fixed2double(c1), 2) - pow(fixed2double(cylinder.diameter) / 2, 2));
	return (c);
}

static t_fixed	ft_numerical_coefficient_b(t_cylinder cylinder, t_ray ray)
{
	t_fixed	a_arr[2];
	t_fixed	b_arr[2];
	t_fixed	c_arr[2];
	t_fixed	b;

	a_arr[0] = double2fixed((fixed2double(cylinder.dir_vector.n_vec.z) * fixed2double(ray.direction.n_vec.y)) - (fixed2double(cylinder.dir_vector.n_vec.y) * fixed2double(ray.direction.n_vec.z)));
	a_arr[1] = double2fixed((fixed2double(cylinder.dir_vector.n_vec.y) * (fixed2double(cylinder.coord.z) - fixed2double(ray.source.z))) - (fixed2double(cylinder.dir_vector.n_vec.z) * (fixed2double(cylinder.coord.y) - fixed2double(ray.source.y))));
	b_arr[0] = double2fixed((fixed2double(cylinder.dir_vector.n_vec.x) * fixed2double(ray.direction.n_vec.z)) - (fixed2double(cylinder.dir_vector.n_vec.z) * fixed2double(ray.direction.n_vec.x)));
	b_arr[1] = double2fixed((fixed2double(cylinder.dir_vector.n_vec.z) * (fixed2double(cylinder.coord.x) - fixed2double(ray.source.x))) - (fixed2double(cylinder.dir_vector.n_vec.x) * (fixed2double(cylinder.coord.z) - fixed2double(ray.source.z))));
	c_arr[0] = double2fixed((fixed2double(cylinder.dir_vector.n_vec.y) * fixed2double(ray.direction.n_vec.x)) - (fixed2double(cylinder.dir_vector.n_vec.x) * fixed2double(ray.direction.n_vec.y)));
	c_arr[1] = double2fixed((fixed2double(cylinder.dir_vector.n_vec.x) * (fixed2double(cylinder.coord.y) - fixed2double(ray.source.y))) - (fixed2double(cylinder.dir_vector.n_vec.y) * (fixed2double(cylinder.coord.x) - fixed2double(ray.source.x))));
	b = double2fixed(2 * (fixed2double(a_arr[0]) * fixed2double(a_arr[1]) + fixed2double(b_arr[0]) * fixed2double(b_arr[1]) + fixed2double(c_arr[0]) * fixed2double(c_arr[1])));
	return (b);
}

static t_fixed	ft_numerical_coefficient_a(t_cylinder cylinder, t_ray ray)
{
	t_fixed	a0;
	t_fixed	b0;
	t_fixed	c0;
	t_fixed	a;

	a0 = double2fixed((fixed2double(cylinder.dir_vector.n_vec.z) * fixed2double(ray.direction.n_vec.y)) - (fixed2double(cylinder.dir_vector.n_vec.y) * fixed2double(ray.direction.n_vec.z)));
	b0 = double2fixed((fixed2double(cylinder.dir_vector.n_vec.x) * fixed2double(ray.direction.n_vec.z)) - (fixed2double(cylinder.dir_vector.n_vec.z) * fixed2double(ray.direction.n_vec.x)));
	c0 = double2fixed((fixed2double(cylinder.dir_vector.n_vec.y) * fixed2double(ray.direction.n_vec.x)) - (fixed2double(cylinder.dir_vector.n_vec.x) * fixed2double(ray.direction.n_vec.y)));
	a = double2fixed(pow(fixed2double(a0), 2) + pow(fixed2double(b0), 2) + pow(fixed2double(c0), 2));
	return (a);
}


t_fixed	ft_cylinder_distance(t_cylinder cylinder, t_ray ray)
{
	t_fixed	a;
	t_fixed	b;
	t_fixed	c;
	t_fixed	result[2];
	int		result_num;

	a = ft_numerical_coefficient_a(cylinder, ray);
	b = ft_numerical_coefficient_b(cylinder, ray);
	c = ft_numerical_coefficient_c(cylinder, ray);
	result_num = ft_quadratic_solver(a, b, c, result);
	if (result_num == 0)
		return (long2fixed(-1));
	else if (result_num == 1)
		return (result[0]);
	if (result[0] > result[1])
		return (result[1]);
	return (result[0]);
}