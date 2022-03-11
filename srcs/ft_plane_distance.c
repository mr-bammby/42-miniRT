/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plane_distance.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 01:15:54 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/12 20:28:41 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

// ((r - p) . n) / (a . n)
// if parallel_check = 0 then ray and plane are parallel.
// 
t_fixed ft_plane_distance(t_plane plane, t_ray ray)
{
	t_vec vec_ray_point;
	t_fixed intersection_check;
	t_fixed parallel_check;
	t_fixed result;

	vec_ray_point = ft_creat_vec(double2fixed(fixed2double(plane.coord.x) - fixed2double(ray.source.x)), \
		double2fixed(fixed2double(plane.coord.y) - fixed2double(ray.source.y)), double2fixed(fixed2double(plane.coord.z) - fixed2double(ray.source.z)));
	intersection_check = ft_scalar_prod(vec_ray_point, plane.dir_vector);
	parallel_check = ft_scalar_prod(ray.direction, plane.dir_vector);
	if (fixed2double(parallel_check) > 0.00001 || fixed2double(parallel_check) < -0.00001)
		return (double2fixed(fixed2double(intersection_check) / fixed2double(parallel_check)));
	return (long2fixed(-1));
}