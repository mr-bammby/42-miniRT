/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parallel_line_dist.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 10:52:15 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/18 23:45:16 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libvector.h"

/**
	@brief Calculates the distance between two vectors.
		d = |b x (a2 – a1)|
	@param point1 First point to create a vector.
	@param point2 Second point to create a vector.
	@param dir_vec Direction vector.
	@return Returns the length of the calculated vector as fixed-point value.
 */

t_fixed	ft_parallel_line_dist(t_point point1, t_point point2, t_vec dir_vec)
{
	t_vec	dist_vec;

	dist_vec = ft_cross_prod_vec(dir_vec, ft_creat_vec(dtofx(fxtod(point1.x) - \
		fxtod(point2.x)), dtofx(fxtod(point1.y) - \
		fxtod(point2.y)), dtofx(fxtod(point1.z) - fxtod(point2.z))));
	return (dist_vec.size);
}
