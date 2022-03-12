/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quadratic_solver.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 00:30:15 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/10 00:52:11 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libvector.h"

//returns number of real solutions. Solutions inside result.
int ft_quadratic_solver(t_fixed a, t_fixed b, t_fixed c, t_fixed result[2])
{
	double det;

	det = pow(fixed2double(b), 2) - (4 * fixed2double(a) * fixed2double(c));
	if (det < 0)
		return (0);
	result[0] = double2fixed((-fixed2double(b) + sqrt(det)) / (2 * fixed2double(a)));
	result[1] = double2fixed((-fixed2double(b) - sqrt(det)) / (2 * fixed2double(a)));
	if (result[0] == result[1])
		return (1);
	return (2);
}