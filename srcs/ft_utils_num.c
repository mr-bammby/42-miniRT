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
		else if (argv[i] == '-' && i != 0)
			return (1);
		else if (argv[i] == '.' && num_flag == 0)
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
	@return Retruns 0 on success else 1.
 */
int	ft_atoll(const char *str, long long int *out)
{
	int				i;
	int				j;
	long long int	k;
	long long int	old_k;

	i = 0;
	j = 1;
	k = 0;
	old_k = 0;
	while (str[i] != '\0' && (str[i] == ' ' || (str[i] > 8 && str[i] < 14)))
		i++;
	ft_atoll_sign_checker(str, &i, &j);
	while (str[i] != '\0' && (str[i] > 47 && str[i] < 58))
	{
		k = k * 10 + (str[i] - 48);
		if (k < old_k)
			return (1);
		old_k = k;
		i++;
	}
	*out = k * j;
	return (0);
}
