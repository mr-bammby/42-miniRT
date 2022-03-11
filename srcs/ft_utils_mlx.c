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

int ft_get_pixel(int x, int y, t_screen screen, t_list *gol)
{
	t_ray ray;

	ray = ft_screen_ray(screen, x, y);
	while (gol != NULL)
	{
		if (((t_geo_object *)(gol->content))->type == FT_SP_TYPE)
		{
			if (fixed2long(ft_sphere_distance(*(((t_sphere *)(((t_geo_object *)(gol->content))->s))), ray)) > 0)
				return (ft_rgb2int(((t_geo_object *)(gol->content))->color));
			else
				return (0);
		}
		gol = gol->next;
	}
	return (0);
}

void ft_mlx(t_screen screen, t_list *gol)
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
			ft_mlx_display_pixel(&mlx.canvas, x, y, ft_get_pixel(x, y, screen, gol)); // x y can be in array
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, mlx.canvas.img, 0, 0);
	mlx_loop(mlx.mlx);
}