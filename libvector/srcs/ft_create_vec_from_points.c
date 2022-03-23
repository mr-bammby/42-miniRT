/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_vec_from_points.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 18:27:42 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/23 19:16:09 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libvector.h"

/**
	@brief Creates a vector from the start to the end point.
	@param start The start point of the vec to be created.
	@param end The end point of the vec to be created.
	@param size The size of created vector. If it is smaller than 0.0001 size
		is determinated from distance between points.
	@return Returns the calculated vec.
	@exception If the end is the same as the start, returns a vec with 
		a vector of 0, 0, 0.
 */
t_vec	ft_create_vec_from_points(t_point start, t_point end, t_fixed size)
{
	t_vec	vec;

	if ((fabs(fxtod(end.x) - fxtod(start.x)) < 0.00001) && \
		(fabs(fxtod(end.y) - fxtod(start.y)) < 0.00001) && \
		(fabs(fxtod(end.z) - fxtod(start.z)) < 0.00001))
		return (ft_creat_vec(0, 0, 0));
	vec = ft_creat_vec(dtofx(fxtod(end.x) - fxtod(start.x)), \
		dtofx(fxtod(end.y) - fxtod(start.y)), \
		dtofx(fxtod(end.z) - fxtod(start.z)));
	if (fxtod(size) > 0.00001)
		vec.size = size;
	return (vec);
}
