/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder_distance.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 01:15:54 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/20 14:00:05 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

/**
	@brief
	@param result
	@return 
*/
static t_fixed	ft_result_chooser(t_fixed result[2])
{
	if (fxtod(result[0]) < 0)
		return (result[1]);
	else if (fxtod(result[1]) < 0)
		return (result[0]);
	if (fxtod(result[0]) > fxtod(result[1]))
		return (result[1]);
	return (result[0]);
}

/**
	@brief
	@param cy
	@param ray
	@param result
	@param t
	@return 
*/
static t_fixed	ft_cylinder_distance_two_inter_hnd(t_cylinder cy, t_ray ray, \
	t_fixed result[2], t_fixed t[2])
{
	t_fixed	sc;
	t_fixed	hg;

	sc = ft_scalar_prod(ray.direction, cy.dir_vector);
	hg = cy.height;
	if (((fabs(fxtod(sc)) - 1.0) < FT_PR) && ((fabs(fxtod(sc)) - 1.0) > -FT_PR))
		return (ft_dist2disc(cy, ray, sc, FT_RADIUS_CHECK));
	else if (((fxtod(t[0]) > fxtod(hg) / 2) && (fxtod(t[1]) < -fxtod(hg) / 2)) \
		|| ((fxtod(t[1]) > fxtod(hg) / 2) && (fxtod(t[0]) < -fxtod(hg) / 2)))
		return (ft_dist2disc(cy, ray, sc, FT_NO_RADIUS_CHECK));
	else if (((fxtod(t[0]) > fxtod(hg) / 2) && (fxtod(t[1]) > fxtod(hg) / 2)) \
		|| ((fxtod(t[0]) < -fxtod(hg) / 2) && (fxtod(t[1]) < -fxtod(hg) / 2)))
		return (ltofx(-1));
	else if ((((fxtod(t[0]) <= fxtod(hg) / 2) && fxtod(t[0]) >= \
		-fxtod(hg) / 2)) && ((fxtod(t[1]) <= fxtod(hg) / 2) && \
		(fxtod(t[1]) >= -fxtod(hg) / 2)))
		return (ft_result_chooser(result));
	else
	{
		if ((fxtod(t[0]) <= fxtod(hg) / 2) && (fxtod(t[0]) >= -fxtod(hg) / 2))
			result[1] = ft_dist2disc(cy, ray, sc, FT_RADIUS_CHECK);
		else
			result[0] = ft_dist2disc(cy, ray, sc, FT_RADIUS_CHECK);
		return (ft_result_chooser(result));
	}
}

/**
	@brief
	@param cylinder
	@param ray
	@param result
	@return 
*/
static int	quad_equat_hnd(t_cylinder cylinder, t_ray ray, t_fixed result[2])
{
	t_fixed	a;
	t_fixed	b;
	t_fixed	c;
	int		result_num;

	a = ft_numerical_coefficient_a(cylinder, ray);
	b = ft_numerical_coefficient_b(cylinder, ray);
	c = ft_numerical_coefficient_c(cylinder, ray);
	result_num = ft_quadratic_solver(a, b, c, result);
	return (result_num);
}

/**
	@brief
	@param cylinder
	@param ray
	@return 
*/
t_fixed	ft_cylinder_distance(t_cylinder cylinder, t_ray ray)
{
	t_fixed	t[2];
	t_fixed	result[2];
	int		result_num;

	result_num = quad_equat_hnd(cylinder, ray, result);
	if (result_num == 0)
		return (ltofx(-1));
	t[0] = ft_point_height_loc(cylinder, ft_point_on_ray(ray, result[0]));
	if (result_num == 1)
	{
		if ((fxtod(t[0]) <= (fxtod(cylinder.height) / 2)) && \
			(fxtod(t[0]) >= (-fxtod(cylinder.height) / 2)))
			return (result[0]);
		return (ltofx(-1));
	}
	t[1] = ft_point_height_loc(cylinder, ft_point_on_ray(ray, result[1]));
	return (ft_cylinder_distance_two_inter_hnd(cylinder, ray, result, t));
}
