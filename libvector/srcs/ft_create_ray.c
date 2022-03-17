/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_ray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 18:27:42 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/18 21:22:59 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libvector.h"

/**
	@brief Creates a vector (ray) from the source to the point.
	@param source The source point of the ray to be created.
	@param point The point towards the ray goes from the source.
	@return Returns the calculated ray.
	@exception If the point is the same as the source, returns a ray with 
		a direction of 0, 0, 0 and a source of 0, 0, 0.
 */

t_ray	ft_create_ray(t_point source, t_point point)
{
	t_ray	ray;

	if ((fabs(fxtod(point.x) - fxtod(source.x)) < 0.00001) && \
		(fabs(fxtod(point.y) - fxtod(source.y)) < 0.00001) && \
		(fabs(fxtod(point.z) - fxtod(source.z)) < 0.00001))
	{
		ray.direction = ft_creat_vec(0, 0, 0);
		ray.source.x = 0;
		ray.source.y = 0;
		ray.source.z = 0;
		return (ray);
	}
	ray.source = source;
	ray.direction = ft_creat_vec(dtofx(fxtod(point.x) - fxtod(source.x)), \
		dtofx(fxtod(point.y) - fxtod(source.y)), \
		dtofx(fxtod(point.z) - fxtod(source.z)));
	ray.direction.size = ltofx(1);
	return (ray);
}
