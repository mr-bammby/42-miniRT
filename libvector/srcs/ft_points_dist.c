/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_points_dist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 16:04:24 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/18 23:45:21 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libvector.h"

/**
	@brief Caculates the distance between two points
	@param a First point.
	@param b Second point.
	@return Returns the distance betweens two points als fixed-point value.
 */
t_fixed	ft_points_dist(t_point a, t_point b)
{
	double	dist;

	dist = sqrt(pow(fxtod(a.x - b.x), 2) + pow(fxtod(a.y - b.y), 2) + \
		pow(fxtod(a.z - b.z), 2));
	return (dtofx(dist));
}
