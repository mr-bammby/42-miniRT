/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_point_on_ray.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 16:04:24 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/11 20:14:54 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libvector.h"

t_point	ft_point_on_ray(t_ray ray, t_fixed distance)
{
	t_point pointy;

	pointy.x = double2fixed(fixed2double(ray.source.x) + (fixed2double(distance) * fixed2double(ray.direction.n_vec.x)));
	pointy.y = double2fixed(fixed2double(ray.source.y) + (fixed2double(distance) * fixed2double(ray.direction.n_vec.y)));
	pointy.z = double2fixed(fixed2double(ray.source.z) + (fixed2double(distance) * fixed2double(ray.direction.n_vec.z)));
	return (pointy);
}