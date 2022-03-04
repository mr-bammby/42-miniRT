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

void ft_mlx(void)
{
	t_mlx_view	mlx;

	mlx.mlx = mlx_init();
	write(2, "AHAHA1\n", 6);
	mlx.mlx_win = mlx_new_window(mlx.mlx, 500, 500, "miniRT");
	write(2, "AHAHA7\n", 6);
	mlx.canvas.img = mlx_new_image(mlx.mlx, 500, 500);
	write(2, "AHAHA2\n", 6);
	mlx.canvas.addr = mlx_get_data_addr(mlx.canvas.img, &mlx.canvas.bits_per_pixel, &mlx.canvas.line_length, &mlx.canvas.endian);
	mlx_hook(mlx.mlx_win, 33, (1L << 17), ft_exit_mlx, mlx.mlx);
	write(2, "AHAHA3\n", 6);
	ft_mlx_display_pixel(&mlx.canvas, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, mlx.canvas.img, 0, 0);
	write(2, "AHAHA4\n", 6);
	mlx_loop(mlx.mlx);
}