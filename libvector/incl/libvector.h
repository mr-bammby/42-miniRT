/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libvector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:53:13 by dbanfi            #+#    #+#             */
/*   Updated: 2022/03/07 12:02:17 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBVECTOR_H
# define LIBVECTOR_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

# define FT_FIXED_FRAC_BITS 20

typedef long long	t_fixed;

typedef struct s_norm_vector
{
	t_fixed x;
	t_fixed y;
	t_fixed z;
}			t_norm_vector;

typedef struct s_vec
{
	t_norm_vector n_vec;
	t_fixed	size;
}			t_vec;

t_fixed	long2fixed(long in);
t_fixed	double2fixed(double in);
long	fixed2long(t_fixed in); ///////////////////loses everything after decimal point
double	fixed2double(t_fixed in);

t_vec	ft_creat_vec(t_fixed x, t_fixed y, t_fixed z);
t_vec	ft_add_vec(t_vec vec1, t_vec vec2);
t_vec	ft_sub_vec(t_vec vec1, t_vec vec2);
t_fixed	ft_scalar_prod(t_vec vec1, t_vec vec2);
t_vec	ft_cross_prod_vec(t_vec vec1, t_vec vec2);

#endif