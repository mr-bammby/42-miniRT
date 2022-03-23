/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_screen_maker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 18:27:42 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/23 19:09:57 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

/**
	@brief Inititalizes screen values for further calculation.
	@param cam Structure of camera view object.
	@param distance Distance to the screen.
	@param screen Structure of view screen.
	@return Returns the vector from camera to the most left up point of
		the screen.
 */
static t_vec	ft_init_screen(t_camera cam, t_fixed distance, t_screen screen)
{
	t_vec	sum_vec;
	t_vec	temp[3];

	temp[0] = cam.dir_vector;
	temp[0].size = distance;
	temp[1] = screen.right;
	temp[1].size = dtofx((-1) * (FT_PX_SIZE * FT_SCREEN_HOR_PX) / 2);
	temp[2] = screen.down;
	temp[2].size = dtofx((-1) * (FT_PX_SIZE * FT_SCREEN_VER_PX) / 2);
	sum_vec = ft_add_vec(ft_add_vec(temp[0], temp[1]), temp[2]);
	return (sum_vec);
}

/**
	@brief Creates the screen.
	@param camera Structure of camera view object.
	@return Returns the created screen object.
 */
t_screen	ft_screen_maker(t_camera camera)
{
	t_screen	screen;
	t_fixed		distance;
	t_vec		sum_vec;

	screen.camera = camera.coord;
	screen.right = ft_cross_prod_vec(camera.dir_vector, \
		ft_creat_vec(ltofx(1), 0, 0));
	if (fxtod(screen.right.size) < 0.00001)
		screen.right = ft_creat_vec(0, ltofx(1), 0);
	screen.right.size = ltofx(1);
	screen.down = ft_cross_prod_vec(camera.dir_vector, screen.right);
	screen.down.size = ltofx(1);
	distance = dtofx((FT_PX_SIZE * FT_SCREEN_HOR_PX / 2) / \
		tan(fxtod(camera.angle) / 2));
	sum_vec = ft_init_screen(camera, distance, screen);
	screen.zero.x = dtofx(fxtod(screen.camera.x) + fxtod(sum_vec.n_vec.x) * \
		fxtod(sum_vec.size));
	screen.zero.y = dtofx(fxtod(screen.camera.y) + fxtod(sum_vec.n_vec.y) * \
		fxtod(sum_vec.size));
	screen.zero.z = dtofx(fxtod(screen.camera.z) + fxtod(sum_vec.n_vec.z) * \
		fxtod(sum_vec.size));
	return (screen);
}

/**
	@brief Creates a ray from the camera source to a specific pixel point on the
		view screen.
	@param screen Structure of view screen.
	@param x X value of the pixel point.
	@param y Y value of the pixel point.
	@return Returns the calculated ray.
 */
t_ray	ft_screen_ray(t_screen screen, int x, int y)
{
	t_point	px_point;

	px_point.x = dtofx(fxtod(screen.zero.x) + \
		(fxtod(screen.right.n_vec.x) * FT_PX_SIZE * (double)x) + \
		(fxtod(screen.down.n_vec.x) * FT_PX_SIZE * (double)y));
	px_point.y = dtofx(fxtod(screen.zero.y) + \
		(fxtod(screen.right.n_vec.y) * FT_PX_SIZE * (double)x) + \
		(fxtod(screen.down.n_vec.y) * FT_PX_SIZE * (double)y));
	px_point.z = dtofx(fxtod(screen.zero.z) + \
		(fxtod(screen.right.n_vec.z) * FT_PX_SIZE * (double)x) + \
		(fxtod(screen.down.n_vec.z) * FT_PX_SIZE * (double)y));
	return (ft_create_ray(screen.camera, px_point));
}
