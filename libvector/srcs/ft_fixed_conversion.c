/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fixed_conversion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 10:52:15 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/18 21:30:22 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libvector.h"

/**
	@brief Converts a long into a fixed point number.
	@param in Input value as long.
	@return Input value as fixed-point.
 */
t_fixed	ltofx(long in)
{
	t_fixed	temp;

	temp = (t_fixed)in;
	return ((t_fixed)(temp << FT_FIXED_FRAC_BITS));
}

/**
	@brief Converts a double to a fixed point number.
	@param in Input value as double.
	@return Input value as fixed-point.
 */
t_fixed	dtofx(double in)
{
	return ((t_fixed)(roundf(in * (1 << FT_FIXED_FRAC_BITS))));
}

/**
	@brief Converts a fixed point number to a long integer.
	@param in Input value as fixed-point.
	@return Input value as long.
 */
long	fxtol(t_fixed in)
{
	return ((long)(in >> FT_FIXED_FRAC_BITS));
}

/**
	@brief Converts a fixed point number to a double.
	@param in Input value as fixed-point.
	@return Input value as double.
 */
double	fxtod(t_fixed in)
{
	return ((double)in / (1 << FT_FIXED_FRAC_BITS));
}
