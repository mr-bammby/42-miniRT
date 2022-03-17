/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder_distance.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 01:15:54 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/18 18:01:01 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

static t_fixed	ft_numerical_coefficient_c(t_cylinder cylinder, t_ray ray)
{
	t_fixed	a1;
	t_fixed	b1;
	t_fixed	c1;
	t_fixed	c;

	a1 = dtofx((fxtod(cylinder.dir_vector.n_vec.y) * (fxtod(cylinder.coord.z) - fxtod(ray.source.z))) - (fxtod(cylinder.dir_vector.n_vec.z) * (fxtod(cylinder.coord.y) - fxtod(ray.source.y))));
	b1 = dtofx((fxtod(cylinder.dir_vector.n_vec.z) * (fxtod(cylinder.coord.x) - fxtod(ray.source.x))) - (fxtod(cylinder.dir_vector.n_vec.x) * (fxtod(cylinder.coord.z) - fxtod(ray.source.z))));
	c1 = dtofx((fxtod(cylinder.dir_vector.n_vec.x) * (fxtod(cylinder.coord.y) - fxtod(ray.source.y))) - (fxtod(cylinder.dir_vector.n_vec.y) * (fxtod(cylinder.coord.x) - fxtod(ray.source.x))));
	c = dtofx(pow(fxtod(a1), 2) + pow(fxtod(b1), 2) + pow(fxtod(c1), 2) - pow(fxtod(cylinder.diameter) / 2, 2));
	return (c);
}

static t_fixed	ft_numerical_coefficient_b(t_cylinder cylinder, t_ray ray)
{
	t_fixed	a_arr[2];
	t_fixed	b_arr[2];
	t_fixed	c_arr[2];
	t_fixed	b;

	a_arr[0] = dtofx((fxtod(cylinder.dir_vector.n_vec.z) * fxtod(ray.direction.n_vec.y)) - (fxtod(cylinder.dir_vector.n_vec.y) * fxtod(ray.direction.n_vec.z)));
	a_arr[1] = dtofx((fxtod(cylinder.dir_vector.n_vec.y) * (fxtod(cylinder.coord.z) - fxtod(ray.source.z))) - (fxtod(cylinder.dir_vector.n_vec.z) * (fxtod(cylinder.coord.y) - fxtod(ray.source.y))));
	b_arr[0] = dtofx((fxtod(cylinder.dir_vector.n_vec.x) * fxtod(ray.direction.n_vec.z)) - (fxtod(cylinder.dir_vector.n_vec.z) * fxtod(ray.direction.n_vec.x)));
	b_arr[1] = dtofx((fxtod(cylinder.dir_vector.n_vec.z) * (fxtod(cylinder.coord.x) - fxtod(ray.source.x))) - (fxtod(cylinder.dir_vector.n_vec.x) * (fxtod(cylinder.coord.z) - fxtod(ray.source.z))));
	c_arr[0] = dtofx((fxtod(cylinder.dir_vector.n_vec.y) * fxtod(ray.direction.n_vec.x)) - (fxtod(cylinder.dir_vector.n_vec.x) * fxtod(ray.direction.n_vec.y)));
	c_arr[1] = dtofx((fxtod(cylinder.dir_vector.n_vec.x) * (fxtod(cylinder.coord.y) - fxtod(ray.source.y))) - (fxtod(cylinder.dir_vector.n_vec.y) * (fxtod(cylinder.coord.x) - fxtod(ray.source.x))));
	b = dtofx(2 * (fxtod(a_arr[0]) * fxtod(a_arr[1]) + fxtod(b_arr[0]) * fxtod(b_arr[1]) + fxtod(c_arr[0]) * fxtod(c_arr[1])));
	return (b);
}

static t_fixed	ft_numerical_coefficient_a(t_cylinder cylinder, t_ray ray)
{
	t_fixed	a0;
	t_fixed	b0;
	t_fixed	c0;
	t_fixed	a;

	a0 = dtofx((fxtod(cylinder.dir_vector.n_vec.z) * fxtod(ray.direction.n_vec.y)) - (fxtod(cylinder.dir_vector.n_vec.y) * fxtod(ray.direction.n_vec.z)));
	b0 = dtofx((fxtod(cylinder.dir_vector.n_vec.x) * fxtod(ray.direction.n_vec.z)) - (fxtod(cylinder.dir_vector.n_vec.z) * fxtod(ray.direction.n_vec.x)));
	c0 = dtofx((fxtod(cylinder.dir_vector.n_vec.y) * fxtod(ray.direction.n_vec.x)) - (fxtod(cylinder.dir_vector.n_vec.x) * fxtod(ray.direction.n_vec.y)));
	a = dtofx(pow(fxtod(a0), 2) + pow(fxtod(b0), 2) + pow(fxtod(c0), 2));
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
		return (ltofx(-1));
	t[0] = ft_point_height_loc(cylinder, ft_point_on_ray(ray, result[0]));
	if (result_num == 1)
	{
		if ((fxtod(t[0]) <= (fxtod(cylinder.height)/2)) && (fxtod(t[0]) >= (-fxtod(cylinder.height)/2)))
			return (result[0]);
		return (ltofx(-1));
	}
	t[1] = ft_point_height_loc(cylinder, ft_point_on_ray(ray, result[1]));
	scalar = ft_scalar_prod(ray.direction, cylinder.dir_vector);
	if (((fabs(fxtod(scalar)) - 1.0) < 0.000001) && ((fabs(fxtod(scalar)) - 1.0) > -0.000001)) //case 1
	{
		return(ft_dist2disc(cylinder,ray, scalar, FT_RADIUS_CHECK));;
	}
	else if(((fxtod(t[0]) > fxtod(cylinder.height)/2) && (fxtod(t[1]) < -fxtod(cylinder.height)/2)) || ((fxtod(t[1]) > fxtod(cylinder.height)/2) && (fxtod(t[0]) < -fxtod(cylinder.height)/2))) //case 4
		return(ft_dist2disc(cylinder,ray, scalar, FT_NO_RADIUS_CHECK));
	else if(((fxtod(t[0]) > fxtod(cylinder.height)/2) && (fxtod(t[1]) > fxtod(cylinder.height)/2)) || ((fxtod(t[0]) < -fxtod(cylinder.height)/2) && (fxtod(t[1]) < -fxtod(cylinder.height)/2))) //case 2
		return (ltofx(-1));
	else if(((fxtod(t[0]) <= fxtod(cylinder.height)/2) && (fxtod(t[0]) >= -fxtod(cylinder.height)/2)) && ((fxtod(t[1]) <= fxtod(cylinder.height)/2) && (fxtod(t[1]) >= -fxtod(cylinder.height)/2))) //case 3
	{
		if (fxtod(result[0]) > fxtod(result[1]))
			return (result[1]);
		return (result[0]);
	}
	else
	{
		if ((fxtod(t[0]) <= fxtod(cylinder.height)/2) && (fxtod(t[0]) >= -fxtod(cylinder.height)/2))
			result[1] = ft_dist2disc(cylinder,ray , scalar, FT_RADIUS_CHECK);
		else
			result[0] = ft_dist2disc(cylinder,ray, scalar, FT_RADIUS_CHECK);
		if(fxtod(result[0]) < 0)
			return (result[1]);
		else if(fxtod(result[1]) < 0)
			return (result[0]);
		if (fxtod(result[0]) > fxtod(result[1]))
			return (result[1]);
		return (result[0]);
	}
}