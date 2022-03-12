/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 21:10:51 by mamuller          #+#    #+#             */
/*   Updated: 2022/03/04 21:10:51 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

static int	ft_exit_mlx(void *mlx)
{
	if (mlx)			//insert proper mlx free functions
		free(mlx);
	exit(1);
}

static void	ft_mlx_display_pixel(t_canvas *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int ft_get_pixel(int x, int y, t_screen screen, t_list *gol, t_view_object vo)
{
	t_ray ray;
	t_fixed distance;
	t_geo_object object;
	t_fixed temp;
	t_list *temp_l;
	
	temp_l = gol;
	ray = ft_screen_ray(screen, x, y);
	distance = long2fixed(FT_BIGGEST_DIST);
	while (gol != NULL)
	{
		if (((t_geo_object *)(gol->content))->type == FT_SP_TYPE)
			temp = ft_sphere_distance(*(((t_sphere *)(((t_geo_object *)(gol->content))->s))), ray);
		if (fixed2double(temp) > 0 && fixed2double(temp) < fixed2double(distance))
		{
			distance = temp;
			object = *((t_geo_object *)(gol->content));
		}
		gol = gol->next;
	}
	if (fixed2long(distance) != FT_BIGGEST_DIST)
		return(ft_calc_all_light(ft_point_on_ray(ray, distance), object, vo, temp_l));

	return (0); 
}

void ft_mlx(t_screen screen, t_list *gol, t_view_object vo)
{
	t_mlx_view	mlx;
	int x;
	int y;

	mlx.mlx = mlx_init();
	mlx.mlx_win = mlx_new_window(mlx.mlx, FT_SCREEN_HOR_PX, FT_SCREEN_VER_PX, "miniRT");
	mlx.canvas.img = mlx_new_image(mlx.mlx, FT_SCREEN_HOR_PX, FT_SCREEN_VER_PX);
	mlx.canvas.addr = mlx_get_data_addr(mlx.canvas.img, &mlx.canvas.bits_per_pixel, &mlx.canvas.line_length, &mlx.canvas.endian);
	mlx_hook(mlx.mlx_win, 33, (1L << 17), ft_exit_mlx, mlx.mlx);
	y = 0;
	while (y < FT_SCREEN_VER_PX)
	{
		x = 0;
		while (x < FT_SCREEN_HOR_PX)
		{
			ft_mlx_display_pixel(&mlx.canvas, x, y, ft_get_pixel(x, y, screen, gol, vo)); // x y can be in array
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, mlx.canvas.img, 0, 0);
	mlx_loop(mlx.mlx);
}