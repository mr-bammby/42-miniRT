/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quadratic_solver.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 00:30:15 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/18 23:07:16 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libvector.h"

/**
	@brief Solves quadratic equations with the quadtratic formula
		t_0 = -b + sqrt(b^2 - 4(ac)) / 2a
		t_1 = -b - sqrt(b^2 - 4(ac)) / 2a
	@param a First constant.
	@param b Second constant.
	@param c Third constant
	@param result Array for fixed-point values where the solution(s) is/are
		stored in.
	@return Returns number of real solutions. Solutions inside result.
 */
int	ft_quadratic_solver(t_fixed a, t_fixed b, t_fixed c, t_fixed result[2])
{
	double	det;

	det = pow(fxtod(b), 2) - (4 * fxtod(a) * fxtod(c));
	if (det < 0)
		return (0);
	result[0] = dtofx((-fxtod(b) + sqrt(det)) / (2 * fxtod(a)));
	result[1] = dtofx((-fxtod(b) - sqrt(det)) / (2 * fxtod(a)));
	if (result[0] == result[1])
		return (1);
	return (2);
}
