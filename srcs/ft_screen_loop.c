/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_screen_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 14:34:10 by mamuller          #+#    #+#             */
/*   Updated: 2022/03/19 14:34:10 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

/**
	@brief Calculates the respective endianness with given color for
		given pixel.
	@param canvas Structure with necessary information on coloring.
	@param pix Pixel x and y values on screen.
	@param color The color to be put into a specific pixel.
	@return None.
 */
static void	ft_mlx_display_pixel(t_canvas *canvas, int pix[2], int color)
{
	char	*dst;

	dst = canvas->addr + (pix[1] * canvas->line_length + pix[0] * \
		(canvas->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

/**
	@brief Find the nearest object from the camera source and measures the distance
		to that object.
	@param gol Pointer to list of objects to be considered.
	@param ray Ray from the camera source to pixel.
	@param distance Pointer to distance value of nearest object.
	@return Returns the nearest object.
 */
static t_geo_object	ft_find_nearest_object(t_list *gol, t_ray ray, \
	t_fixed *distance)
{
	t_geo_object	object;
	t_fixed			temp;

	while (gol != NULL)
	{
		if (((t_geo_object *)(gol->content))->type == FT_SP_TYPE)
			temp = ft_sphere_distance(*(((t_sphere *)(((t_geo_object *) \
				(gol->content))->s))), ray);
		else if (((t_geo_object *)(gol->content))->type == FT_PL_TYPE)
			temp = ft_plane_distance(*(((t_plane *)(((t_geo_object *) \
				(gol->content))->s))), ray);
		else if (((t_geo_object *)(gol->content))->type == FT_CY_TYPE)
			temp = ft_cylinder_distance(*(((t_cylinder *)(((t_geo_object *) \
				(gol->content))->s))), ray);
		if (fxtod(temp) > 0 && fxtod(temp) < fxtod(*distance))
		{
			*distance = temp;
			object = *((t_geo_object *)(gol->content));
		}
		gol = gol->next;
	}
	return (object);
}

/**
	@brief Gets the nearest visible object for every pixel and calls for proper
		light and color calculation.
	@param pix Pixel x and y values on screen.
	@param screen Screen object with the respective view field to calculate
		the image for.
	@param gol Pointer to list of objects to be considered.
	@param vo Structure with view objects (camera, ambient, light).
	@return Returns the calculated color as integer value if object was hit by ray,
		else 0.
 */
static int	ft_get_pixel(int pix[2], t_screen screen, t_list *gol, \
	t_view_object vo)
{
	t_ray			ray;
	t_fixed			distance;
	t_geo_object	object;
	t_list			*temp_l;

	temp_l = gol;
	ray = ft_screen_ray(screen, pix[0], pix[1]);
	distance = ltofx(FT_BIGGEST_DIST);
	object = ft_find_nearest_object(gol, ray, &distance);
	if (fxtol(distance) != FT_BIGGEST_DIST)
		return (ft_calc_all_light(ft_point_on_ray(ray, distance), \
			object, vo, temp_l));
	return (0);
}

/**
	@brief Loops through every pixel of the screen view and calls for 
		calculating the necessary color to be put on screen.
	@param screen Screen object with the respective view field to calculate
		the image for.
	@param gol Pointer to list of objects to be considered.
	@param vo Structure with view objects (camera, ambient, light).
	@param mlx MLX object.
	@return None.
 */
void	ft_screen_loop(t_screen screen, t_list *gol, t_view_object vo, \
	t_mlx_view mlx)
{
	int	pix[2];

	pix[1] = 0;
	while (pix[1] < FT_SCREEN_VER_PX)
	{
		pix[0] = 0;
		while (pix[0] < FT_SCREEN_HOR_PX)
		{
			ft_mlx_display_pixel(&mlx.canvas, pix, \
				ft_get_pixel(pix, screen, gol, vo));
			(pix[0])++;
		}
		(pix[1])++;
	}
}
