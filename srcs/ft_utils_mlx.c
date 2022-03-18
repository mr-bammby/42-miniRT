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

/**
	@brief Destroys allocated mlx objects before exit and terminates the
		programm.
	@param mlx MLX object.
	@return None. Int return value given due to mlx fct requirements.
 */
static int	ft_exit_mlx(void *mlx)
{
	if (((t_mlx_view *)(mlx))->canvas.img)
		mlx_destroy_image(((t_mlx_view *)(mlx))->mlx, \
			((t_mlx_view *)(mlx))->canvas.img);
	if (((t_mlx_view *)(mlx))->mlx_win)
		mlx_destroy_window(((t_mlx_view *)(mlx))->mlx, \
			((t_mlx_view *)(mlx))->mlx_win);
	if (((t_mlx_view *)(mlx))->mlx)
		mlx_destroy_display(((t_mlx_view *)(mlx))->mlx);
	if (((t_mlx_view *)(mlx))->mlx)
		free(((t_mlx_view *)(mlx))->mlx);
	exit(1);
}

/**
	@brief Reloads the window by image reloading on window manipulations
		linke resize etc.
	@param mlx MLX object.
	@return Retruns 0.
 */
static int	ft_win_manipulation(void *mlx)
{
	mlx_put_image_to_window(((t_mlx_view *)(mlx))->mlx, \
		((t_mlx_view *)(mlx))->mlx_win, \
		((t_mlx_view *)(mlx))->canvas.img, 0, 0);
	return (0);
}

/**
	@brief Terminates the program on "ESC" button.
	@param key_code Key code number.
	@param mlx MLX object.
	@return Retruns 0 on non-ESC button.
 */
static int	ft_esc(int key_code, void *mlx)
{
	if (key_code == 65307)
		ft_exit_mlx(mlx);
	return (0);
}

/**
	@brief Inititalizes MLX objects and necessary tools (hooks, loops) and 
		puts caluculated image to window.
	@param screen Screen object with the respective view field to calculate
		the image for.
	@param gol Pointer to list of objects to be considered.
	@param vo Structure with view objects (camera, ambient, light). 
	@return None.
 */
void	ft_mlx(t_screen screen, t_list *gol, t_view_object vo)
{
	t_mlx_view	mlx;

	mlx.mlx = mlx_init();
	mlx.canvas.img = mlx_new_image(mlx.mlx, FT_SCREEN_HOR_PX, \
		FT_SCREEN_VER_PX);
	mlx.canvas.addr = mlx_get_data_addr(mlx.canvas.img, \
		&mlx.canvas.bits_per_pixel, &mlx.canvas.line_length, \
		&mlx.canvas.endian);
	ft_screen_loop(screen, gol, vo, mlx);
	ft_exit_free(gol);
	mlx.mlx_win = mlx_new_window(mlx.mlx, FT_SCREEN_HOR_PX, \
		FT_SCREEN_VER_PX, "miniRT");
	mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, mlx.canvas.img, 0, 0);
	mlx_key_hook(mlx.mlx_win, ft_esc, &(mlx.mlx));
	mlx_hook(mlx.mlx_win, 33, (1L << 17), ft_exit_mlx, &(mlx.mlx));
	mlx_hook(mlx.mlx_win, 12, (1L << 15), ft_win_manipulation, &mlx);
	mlx_loop(mlx.mlx);
}
