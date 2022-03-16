/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder_distance.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 01:15:54 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/16 01:19:41 by dbanfi           ###   ########.fr       */
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
	t_fixed	t[2];
	t_fixed scalar;
	t_fixed	result[2];
	int		result_num;

	a = ft_numerical_coefficient_a(cylinder, ray);
	b = ft_numerical_coefficient_b(cylinder, ray);
	c = ft_numerical_coefficient_c(cylinder, ray);
	result_num = ft_quadratic_solver(a, b, c, result);
	if (result_num == 0)
		return (long2fixed(-1));
	t[0] = ft_point_height_loc(cylinder, ft_point_on_ray(ray, result[0]));
	if (result_num == 1)
	{
		if ((fixed2double(t[0]) <= (fixed2double(cylinder.height)/2)) && (fixed2double(t[0]) >= (-fixed2double(cylinder.height)/2)))
			return (result[0]);
		return (long2fixed(-1));
	}
	t[1] = ft_point_height_loc(cylinder, ft_point_on_ray(ray, result[1]));
	scalar = ft_scalar_prod(ray.direction, cylinder.dir_vector);
	if (((fabs(fixed2double(scalar)) - 1.0) < 0.000001) && ((fabs(fixed2double(scalar)) - 1.0) > -0.000001)) //case 1
	{
		return(ft_dist2disc(cylinder,ray, scalar, FT_RADIUS_CHECK));;
	}
	else if(((fixed2double(t[0]) > fixed2double(cylinder.height)/2) && (fixed2double(t[1]) < -fixed2double(cylinder.height)/2)) || ((fixed2double(t[1]) > fixed2double(cylinder.height)/2) && (fixed2double(t[0]) < -fixed2double(cylinder.height)/2))) //case 4
		return(ft_dist2disc(cylinder,ray, scalar, FT_NO_RADIUS_CHECK));
	else if(((fixed2double(t[0]) > fixed2double(cylinder.height)/2) && (fixed2double(t[1]) > fixed2double(cylinder.height)/2)) || ((fixed2double(t[0]) < -fixed2double(cylinder.height)/2) && (fixed2double(t[1]) < -fixed2double(cylinder.height)/2))) //case 2
		return (long2fixed(-1));
	else if(((fixed2double(t[0]) <= fixed2double(cylinder.height)/2) && (fixed2double(t[0]) >= -fixed2double(cylinder.height)/2)) && ((fixed2double(t[1]) <= fixed2double(cylinder.height)/2) && (fixed2double(t[1]) >= -fixed2double(cylinder.height)/2))) //case 3
	{
		if (fixed2double(result[0]) > fixed2double(result[1]))
			return (result[1]);
		return (result[0]);
	}
	else
	{
		if ((fixed2double(t[0]) <= fixed2double(cylinder.height)/2) && (fixed2double(t[0]) >= -fixed2double(cylinder.height)/2))
			result[1] = ft_dist2disc(cylinder,ray , scalar, FT_RADIUS_CHECK);
		else
			result[0] = ft_dist2disc(cylinder,ray, scalar, FT_RADIUS_CHECK);
		if(fixed2double(result[0]) < 0)
			return (result[1]);
		else if(fixed2double(result[1]) < 0)
			return (result[0]);
		if (fixed2double(result[0]) > fixed2double(result[1]))
			return (result[1]);
		return (result[0]);
	}
}