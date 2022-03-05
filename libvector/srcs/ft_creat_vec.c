/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_vec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 22:34:21 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/05 01:59:49 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libvector.h"

t_vec	ft_creat_vec(t_fixed x, t_fixed y, t_fixed z)
{
	double distance;
	t_vec out;

	distance = sqrt(pow(fixed2double(x), 2) + pow(fixed2double(y), 2)+ pow(fixed2double(z), 2));
	printf("distance %f\n", fixed2double(distance));
	out.size = double2fixed(distance);
	if(distance < 0.0000001)
	{
		out.n_vec.x = double2fixed(0);
		out.n_vec.y = double2fixed(0);
		out.n_vec.z = double2fixed(0);
	}
	else
	{	
		out.n_vec.x = double2fixed(fixed2double(x) / distance);
		out.n_vec.y = double2fixed(fixed2double(y) / distance);
		out.n_vec.z = double2fixed(fixed2double(z) / distance);
	}
	return (out);
}
