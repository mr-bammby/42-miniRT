/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parallel_line_dist.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 10:52:15 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/15 00:18:11 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libvector.h"

/* d = |b x (a2 – a1)| */
t_fixed ft_parallel_line_dist(t_point point1, t_point point2, t_vec dir_vec)
{
	t_vec dist_vec;

	dist_vec = ft_cross_prod_vec(dir_vec, ft_creat_vec(double2fixed(fixed2double(point1.x) - fixed2double(point2.x)), double2fixed(fixed2double(point1.y) - fixed2double(point2.y)), double2fixed(fixed2double(point1.z) - fixed2double(point2.z))));
	return(dist_vec.size);
}