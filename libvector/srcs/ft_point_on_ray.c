/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_point_on_ray.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 16:04:24 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/18 22:40:09 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libvector.h"

/**
	@brief Calculates the point on the ray that is the specified distance away.
	@param ray Ray.
	@param distance Distance. 
	@return Returns the specific point on the ray.
 */
t_point	ft_point_on_ray(t_ray ray, t_fixed distance)
{
	t_point	pointy;

	pointy.x = dtofx(fxtod(ray.source.x) + (fxtod(distance) * \
		fxtod(ray.direction.n_vec.x)));
	pointy.y = dtofx(fxtod(ray.source.y) + (fxtod(distance) * \
		fxtod(ray.direction.n_vec.y)));
	pointy.z = dtofx(fxtod(ray.source.z) + (fxtod(distance) * \
		fxtod(ray.direction.n_vec.z)));
	return (pointy);
}
