/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_screen_maker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 18:27:42 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/12 02:33:37 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

t_screen ft_screen_maker(t_camera camera)
{
	t_screen screen;
	t_fixed distance;
	t_vec	temp[3];
	t_vec	sum_vec;

	screen.camera = camera.coord;
	screen.right = ft_cross_prod_vec(camera.dir_vector, ft_creat_vec(1, 0, 0));
	if (fixed2double(screen.right.size) < 0.00001)
		screen.right = ft_creat_vec(0, long2fixed(1), 0);
	screen.down = ft_cross_prod_vec(camera.dir_vector, screen.right);
	distance = double2fixed((FT_PX_SIZE * FT_SCREEN_HOR_PX / 2) / tan(fixed2double(camera.angle) / 2));
	temp[0] = camera.dir_vector;
	temp[0].size = distance;
	temp[1] = screen.right;
	temp[1].size = double2fixed((-1) * (FT_PX_SIZE * FT_SCREEN_HOR_PX)/2);
	temp[2] = screen.down;
	temp[2].size = double2fixed((-1) * (FT_PX_SIZE * FT_SCREEN_VER_PX)/2);
	sum_vec = ft_add_vec(ft_add_vec(temp[0], temp[1]), temp[2]);
	screen.zero.x = double2fixed(fixed2double(screen.camera.x) + fixed2double(sum_vec.n_vec.x) * fixed2double(sum_vec.size));
	screen.zero.y = double2fixed(fixed2double(screen.camera.y) + fixed2double(sum_vec.n_vec.y) * fixed2double(sum_vec.size));
	screen.zero.z = double2fixed(fixed2double(screen.camera.z) + fixed2double(sum_vec.n_vec.z) * fixed2double(sum_vec.size));
	return(screen);
}


t_ray ft_screen_ray(t_screen screen, int x, int y)
{
	t_point px_point;

	px_point.x = double2fixed(fixed2double(screen.zero.x) + \
		(fixed2double(screen.right.n_vec.x) * FT_PX_SIZE * (double)x) + \
		(fixed2double(screen.down.n_vec.x) * FT_PX_SIZE * (double)y));
	px_point.y = double2fixed(fixed2double(screen.zero.y) + \
		(fixed2double(screen.right.n_vec.y) * FT_PX_SIZE * (double)x) + \
		(fixed2double(screen.down.n_vec.y) * FT_PX_SIZE * (double)y));
	px_point.z = double2fixed(fixed2double(screen.zero.z) + \
		(fixed2double(screen.right.n_vec.z) * FT_PX_SIZE * (double)x) + \
		(fixed2double(screen.down.n_vec.z) * FT_PX_SIZE * (double)y));
	return(ft_create_ray(screen.camera, px_point));
}
