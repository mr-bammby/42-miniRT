/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fixed_point.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 10:52:15 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/04 12:10:58 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

void int2fixed(int in, t_fixed *out)
{
	double temp;

	temp = (double)in;
	out->raw_value = temp << FT_FIXED_FRAC_BITS;
}

void float2fixed(float in, t_fixed *out)
{
	out->raw_value = (double)(roundf(in * (1 << FT_FIXED_FRAC_BITS)));
}

void fixed2int(t_fixed in, int *out)
{
	*out = in->raw_value >> FT_FIXED_FRAC_BITS;
}

void fixed2float(t_fixed in, float *out);
{
	*out = (float)in->raw_value / (1 << FT_FIXED_FRAC_BITS);
}