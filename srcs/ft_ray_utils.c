/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 18:27:42 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/08 20:47:20 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"


//be cearful to not put same point into source and point
t_ray ft_ray(t_point source, t_point point)
{
	t_ray ray;

	if((fabs(double2fixed(point.x) - double2fixed(source.x)) < 0.00001) && (fabs(double2fixed(point.y) - double2fixed(source.y)) < 0.00001) &&(fabs(double2fixed(point.z) - double2fixed(source.z)) < 0.00001))
	{
		g_error = 1;
		return (0);
	}
	ray.source = source;
	ray.direction = ft_creat_vec(double2fixed(point.x) - double2fixed(source.x), double2fixed(point.y) - double2fixed(source.y), double2fixed(point.z) - double2fixed(source.z));
	ray.direction.size = long2fixed(1);
	return (ray);
}