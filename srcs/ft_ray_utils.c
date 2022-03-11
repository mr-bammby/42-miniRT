/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 18:27:42 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/11 02:01:14 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"


//be cearful to not put same point into source and point
t_ray ft_ray(t_point source, t_point point)
{
	t_ray ray;

	if((fabs(fixed2double(point.x) - fixed2double(source.x)) < 0.00001) && (fabs(fixed2double(point.y) - fixed2double(source.y)) < 0.00001) &&(fabs(fixed2double(point.z) - fixed2double(source.z)) < 0.00001))
	{
		g_error = 1;
		ray.direction = ft_creat_vec(0, 0, 0);
		ray.source.x = 0;
		ray.source.y = 0;
		ray.source.z = 0;
		return (ray);
	}
	ray.source = source;
	ray.direction = ft_creat_vec(double2fixed(fixed2double(point.x) - fixed2double(source.x)), double2fixed(fixed2double(point.y) - fixed2double(source.y)), double2fixed(fixed2double(point.z) - fixed2double(source.z)));
	ray.direction.size = long2fixed(1);
	return (ray);
}