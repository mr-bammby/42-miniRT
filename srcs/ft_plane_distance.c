/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plane_distance.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 01:15:54 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/20 22:00:36 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

/**
	@brief Calculated the distance from the source of a ray and a plane.
	@param plane Plane structure
	@param ray The ray towards the plane.
	@return Returns the disctance on success, else -1.
 */
t_fixed	ft_plane_distance(t_plane plane, t_ray ray)
{
	t_vec	vec_ray_point;
	t_fixed	intersection_check;
	t_fixed	parallel_check;

	vec_ray_point = ft_creat_vec(dtofx(fxtod(plane.coord.x) - \
		fxtod(ray.source.x)), dtofx(fxtod(plane.coord.y) - \
		fxtod(ray.source.y)), dtofx(fxtod(plane.coord.z) - \
		fxtod(ray.source.z)));
	intersection_check = ft_scalar_prod(vec_ray_point, plane.dir_vector);
	parallel_check = ft_scalar_prod(ray.direction, plane.dir_vector);
	if (fxtod(parallel_check) > FT_PR || fxtod(parallel_check) < -FT_PR)
		return (dtofx(fxtod(intersection_check) / fxtod(parallel_check)));
	return (ltofx(-1));
}
