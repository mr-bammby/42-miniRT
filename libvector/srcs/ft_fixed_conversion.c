/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fixed_conversion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 10:52:15 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/04 22:54:11 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libvector.h"

t_fixed long2fixed(long in)
{
	t_fixed temp;

	temp = (t_fixed)in;
	return((t_fixed)(temp << FT_FIXED_FRAC_BITS));
}

t_fixed float2fixed(double in)
{
	return((t_fixed)(roundf(in * (1 << FT_FIXED_FRAC_BITS))));
}

long fixed2int(t_fixed in)
{
	return((long)(in >> FT_FIXED_FRAC_BITS));
}

double fixed2float(t_fixed in)
{
	return((double)in / (1 << FT_FIXED_FRAC_BITS));
}