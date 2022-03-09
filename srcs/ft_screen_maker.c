/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_screen_maker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 18:27:42 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/08 21:40:48 by dbanfi           ###   ########.fr       */
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
		screen.right = ft_creat_vec(0, 1, 0);
	screen.down = ft_cross_prod_vec(camera.dir_vector, screen.right);
	distance = double2fixed((FT_PX_SIZE * FT_SCREEN_HOR_PX / 2) / tan(fixed2double(camera.angle) / 2));
	temp[0] = camera.dir_vector;
	temp[0].size = distance;
	temp[1] = screen.right;
	temp[1].size = double2fixed((-fixed2double(temp[1].size)) * (FT_PX_SIZE * FT_SCREEN_HOR_PX));
	temp[2] = screen.down;
	temp[2].size = double2fixed((-fixed2double(temp[2].size)) * (FT_PX_SIZE * FT_SCREEN_VER_PX));
	sum_vec = ft_add_vec(ft_add_vec(temp[0], temp[1]), temp[2]);
	screen.zero.x = fixed2double(screen.camera.x) + fixed2double(sum_vec.n_vec.x) * fixed2double(sum_vec.size);
	screen.zero.y = fixed2double(screen.camera.y) + fixed2double(sum_vec.n_vec.y) * fixed2double(sum_vec.size);
	screen.zero.z = fixed2double(screen.camera.z) + fixed2double(sum_vec.n_vec.z) * fixed2double(sum_vec.size);
	return(screen);
}

t_ray ft_camera_ray(t_screen screen, int ver_pxint, int hor_px)
{
	t_point zero_corner;

	zero_corner = screen.camera 
}