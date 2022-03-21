/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_value_assignemnt.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 20:09:09 by mamuller          #+#    #+#             */
/*   Updated: 2022/03/20 19:29:23 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

/**
	@brief Creates vector in case the mode indicates for it and checks for the
		validity.
	@param out Respective view object structure part that needs to be filled with
		converted and checked values.
	@param mode Indicates the values to be checked for (point or vector).
	@return 0 on success, else number that indicates on the error.
*/
static int	ft_vector_assigment(void *out, int mode)
{
	if (mode == FT_ASS_VEC)
	{
		*((t_vec *)out) = ft_creat_vec(((t_vec *)out)->n_vec.x, \
			((t_vec *)out)->n_vec.y, ((t_vec *)out)->n_vec.z);
		if (fxtod(((t_vec *)out)->size) < (1 - FT_PR) || \
			fxtod(((t_vec *)out)->size) > (1 + FT_PR))
			return (FT_ERR_VEC_SIZE);
		((t_vec *)out)->size = ltofx(1);
	}
	return (0);
}

/**
	@brief Fills the repective structure parts in regards of the type
		(point/vector).
	@param mode Indicates the values to be checked for (point or vector).
	@param num Index of the number in sub_split.
	@param out Respective view object structure part that needs to be filled with
		converted and checked values.
	@return 0 on success, else number that indicates on the error.
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
	@brief Casts string values to number and checks for the respective
		range values.
	@param out Respective view object structure part that needs to be filled with
		converted and checked values.
	@param sub_split Null-terminated array of strings to be converted to
		numbers.
	@param mode Indicates the values to be checked for (point or vector).
	@return 0 on success, else number that indicates on the error.
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
