/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_points_dist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 16:04:24 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/11 16:17:34 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libvector.h"

t_fixed ft_points_dist(t_point a, t_point b)
{
	double dist;
	
	dist = sqrt(pow(fixed2double(a.x - b.x), 2) + pow(fixed2double(a.y - b.y), 2)+ pow(fixed2double(a.z - b.z), 2));
	return(double2fixed(dist));
}