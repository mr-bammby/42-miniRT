/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_value_assignemnt.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 20:09:09 by mamuller          #+#    #+#             */
/*   Updated: 2022/03/20 01:27:07 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

/**
	@brief
	@param mode
	@param num
	@param out
	@return 
*/
static t_fixed	*ft_ass_iterator(int mode, int num, void *out)
{
	if (mode == FT_ASS_VEC)
	{
		if (num == 0)
			return (&(((t_vec *)out)->n_vec.x));
		else if (num == 1)
			return (&(((t_vec *)out)->n_vec.y));
		else
			return (&(((t_vec *)out)->n_vec.z));
	}
	else if (mode == FT_ASS_RGB)
		return (&(((t_fixed *)out)[num]));
	else
	{
		if (num == 0)
			return (&(((t_point *)out)->x));
		else if (num == 1)
			return (&(((t_point *)out)->y));
		else
			return (&(((t_point *)out)->z));
	}
}

/**
	@brief
	@param out
	@param mode
	@return 
*/
static int	ft_vector_assigment(void *out, int mode)
{
	if (mode == FT_ASS_VEC)
	{
		*((t_vec *)out) = ft_creat_vec(((t_vec *)out)->n_vec.x, \
			((t_vec *)out)->n_vec.y, ((t_vec *)out)->n_vec.z);
		if (fxtod(((t_vec *)out)->size) < 0.9999 || \
			fxtod(((t_vec *)out)->size) > 1.0001)
			return (FT_ERR_VEC_SIZE);
		((t_vec *)out)->size = ltofx(1);
	}
	return (0);
}

/**
	@brief
	@param out
	@param sub_split
	@param mode
	@return 
*/
int	ft_value_assignemnt(void *out, char **sub_split, int mode)
{
	int		i;
	double	temp;
	int		error;

	i = 0;
	while (i < 3)
	{
		error = ft_atod(sub_split[i], &temp);
		if (error)
			return (FT_ERR_NUM_RANGE);
		if (((temp < FT_MIN_RGB || temp > FT_MAX_RGB) && mode == FT_ASS_RGB))
			return (FT_ERR_RGB_RANGE);
		else if (((temp < FT_MIN_NORM_VEC || temp > FT_MAX_NORM_VEC) && \
			mode == FT_ASS_VEC))
			return (FT_ERR_VEC_RANGE);
		else if (((temp < FT_MIN_COORD || temp > FT_MAX_COORD) && \
			mode == FT_ASS_POINT))
			return (FT_ERR_COORD_RANGE);
		*(ft_ass_iterator(mode, i, out)) = dtofx(temp);
		i++;
	}
	return (ft_vector_assigment(out, mode));
}
