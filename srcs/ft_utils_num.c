/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 13:04:50 by dbanfi            #+#    #+#             */
/*   Updated: 2022/02/26 13:04:50 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

/**
	@brief Checks if string is valid number that can be converted.
		Checks for the leading sign.
	@param argv String to be checked.
	@return Retruns 0 on success else 1.
 */
int	ft_digit_check(char *argv)
{
	int	i;
	int num_flag;

	i = 0;
	num_flag = 0;
	while (argv[i])
	{	
		if (ft_isdigit(argv[i]) != 0)
			num_flag = 1;
		else if (argv[i] == '-')
		{
			if	(i != 0)
				return (1);
		}
		else if (argv[i] == '.')
		{
			if (num_flag == 0)
				return (1);
		}
		else
			return (1);
		i++;
	}
	return (0);
}

/**
	@brief Checks leading + and - signs and determines start of numeric chars
		and multiplicator for negative sign.
	@param str String to be coverted.
	@param i Pointer to index in string.
	@param j Pointer to multiplicator for negative sign.
	@return None.
 */
static void	ft_atoll_sign_checker(const char *str, int *i, int *j)
{
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			*j = -1;
		(*i)++;
	}
}

/**
	@brief Converts string int long long integer. Detects overflow.
	@param str String to be converted.
	@param out Pointer to converted number.(output value)
	@param j Pointer of the sign value. 1 for positive and -1 for negative.
	@return Retruns 0 on success else 2.
 */
int	ft_atoll(const char *str, long long int *out, int *j)
{
	int				i;
	long long int	k;
	long long int	old_k;

	i = 0;
	*j = 1;
	k = 0;
	old_k = 0;
	while (str[i] != '\0' && (str[i] == ' ' || (str[i] > 8 && str[i] < 14)))
		i++;
	ft_atoll_sign_checker(str, &i, j);
	while (str[i] != '\0' && (str[i] > 47 && str[i] < 58))
	{
		k = k * 10 + (str[i] - 48);
		if (k < old_k)
			return (FT_ERR_NUM_RANGE);
		old_k = k;
		i++;
	}
	*out = k * *j;
	return (0);
}

static int ft_decimal_engine(char *str, double *out)
{
	int				zero_counter;
	char			*sub_str;
	unsigned int	sub_str_len;
	int				decimal;
	
	zero_counter = 0;
	while (str[zero_counter] == '0')
		zero_counter++;
	if (zero_counter > 8 || str[zero_counter] == 0)
		return (0);
	str = ft_strtrim(str, "0");
	if (str == NULL)
		return (FT_ERR_ALLOC_MEM);
	sub_str_len = 8 - zero_counter;
	if (ft_strlen(str) < sub_str_len)
		sub_str_len = ft_strlen(str);
	sub_str = ft_substr(str, 0, sub_str_len);
	ft_smart_free((void **)&str);
	decimal = ft_atoi(sub_str);
	if (*out < 0)
		*out = *out - ((double) decimal / pow(10, zero_counter + sub_str_len));
	else
		*out = *out + ((double) decimal / pow(10, zero_counter + sub_str_len));
	ft_smart_free((void **)&sub_str);
	return (0);
}

int	ft_atod(char *str, double *out)
{
	char			**split;
	int				error;
	long long int	out_ll;
	int				sign;

	sign = 1;
	split = ft_split(str, '.');
	error = ft_atoll(split[0], &out_ll, &sign);
	if (error)
	{
		ft_free_split(split);
		return (error);
	}
	*out = (double) out_ll;
	if (split[1] != NULL)
		error = ft_decimal_engine((split[1]), out);
	if (error)
	{
		ft_free_split(split);
		return (error);
	}
	ft_free_split(split);
	if (*out > 0)
		*out = *out * sign;
	return (0);


	


}
