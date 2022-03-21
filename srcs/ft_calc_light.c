/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 14:58:09 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/21 22:16:40 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

/**
	@brief Calculates the light effect of diffuse light from a light source.
	@param rgb The array that holds the rgb values for color and
		light effects.
	@param vec_arr_lsc Array of helping vectors (light->0, surface->1,camera->2)
	@param object The geometric object.
	@param light Structure of the light view object.
	@return None.
*/
void	ft_calc_diff_light(t_fixed rgb[3], t_vec vec_arr_lsc[3], \
	t_geo_object object, t_light light)
{
	t_fixed	scal_pr;

	scal_pr = ft_scalar_prod(vec_arr_lsc[0], vec_arr_lsc[1]);
	if (object.type != FT_PL_TYPE && fxtod(scal_pr) <= 0)
		return ;
	else
		scal_pr = dtofx(fabs(fxtod(scal_pr)));
	rgb[0] = dtofx(fxtod(rgb[0]) + (fxtod(scal_pr) * fxtod(light.light_ratio)));
	rgb[1] = dtofx(fxtod(rgb[1]) + (fxtod(scal_pr) * fxtod(light.light_ratio)));
	rgb[2] = dtofx(fxtod(rgb[2]) + (fxtod(scal_pr) * fxtod(light.light_ratio)));
}
