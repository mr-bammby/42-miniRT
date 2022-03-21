/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 16:04:24 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/18 21:15:39 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libvector.h"

/**
	@brief Creates a plane from the point and the vector.
	@param point A point on the plane.
	@param n_vec A normal vector to the plane.
	@return Returns the plane.
 */

t_plane	ft_create_plane(t_point point, t_norm_vector n_vec)
{
	t_plane	out;

	out.coord = point;
	out.dir_vector = ft_creat_vec(n_vec.x, n_vec.y, n_vec.z);
	return (out);
}
