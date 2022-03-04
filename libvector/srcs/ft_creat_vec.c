/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_vec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 22:34:21 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/04 23:00:13 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libvector.h"

t_vec	ft_creat_vec(t_fixed x, t_fixed y, t_fixed z)
{
	double distance;
	t_vec out;

	distance = sqrt(pow(fixed2double(x), 2) + pow(fixed2double(y), 2)+ pow(fixed2double(z), 2));
	out.size = double2fixed(distance);
	out.n_vec.x = double2fixed(fixed2double(x) / distance);
	out.n_vec.y = double2fixed(fixed2double(y) / distance);
	out.n_vec.z = double2fixed(fixed2double(z) / distance);
	return (out);
}
