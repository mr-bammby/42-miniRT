/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_check_vo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 00:57:13 by mamuller          #+#    #+#             */
/*   Updated: 2022/03/21 00:57:13 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

/**
	@brief Handles the argument check for light view object 
		(number of arguments, number in argument category, check if 
		the values are numbers). Exits on wrong input.
	@param line_split Array of strings separated by argument categories.
	@param l_cnt Pointer to light counter.
	@param fd Filedescriptor of opened input file.
	@param line Line that was read from input file.
	@return 0 on success.
*/
static int	ft_arg_check_vo_l(char **line_split, int *l_cnt, int fd, char *line)
{
	int	i;

	i = 1;
	while (line_split[i] != NULL)
	{
		if (i > 2)
			ft_exit_on_arg_error(FT_ERR_L_ARG_CHECK, line_split, fd, line);
		if (i == 1)
		{
			if (ft_three_num_check(line_split[i]))
				ft_exit_on_arg_error(FT_ERR_L_ARG_CHECK, line_split, fd, line);
		}
		else
			if (ft_digit_check(line_split[i]) != 0)
				ft_exit_on_arg_error(FT_ERR_L_ARG_CHECK, line_split, fd, line);
		i++;
	}
	if (i != 3)
		ft_exit_on_arg_error(FT_ERR_L_ARG_CHECK, line_split, fd, line);
	(*l_cnt)++;
	if (*l_cnt > 1)
		ft_exit_on_arg_error(FT_ERR_L_MANY, line_split, fd, line);
	return (0);
}

/**
	@brief Handles the argument check for ambient light view object 
		(number of arguments, number in argument category, check if 
		the values are numbers). Exits on wrong input.
	@param line_split Array of strings separated by argument categories.
	@param a_cnt Pointer to ambient light counter.
	@param fd Filedescriptor of opened input file.
	@param line Line that was read from input file.
	@return 0 on success.
*/
static int	ft_arg_check_vo_a(char **line_split, int *a_cnt, int fd, char *line)
{
	int	i;

	i = 1;
	while (line_split[i] != NULL)
	{
		if (i > 2)
			ft_exit_on_arg_error(FT_ERR_A_ARG_CHECK, line_split, fd, line);
		if (i == 2)
		{
			if (ft_three_num_check(line_split[i]))
				ft_exit_on_arg_error(FT_ERR_A_ARG_CHECK, line_split, fd, line);
		}
		else
			if (ft_digit_check(line_split[i]) != 0)
				ft_exit_on_arg_error(FT_ERR_A_ARG_CHECK, line_split, fd, line);
		i++;
	}
	if (i != 3)
		ft_exit_on_arg_error(FT_ERR_A_ARG_CHECK, line_split, fd, line);
	(*a_cnt)++;
	if (*a_cnt > 1)
		ft_exit_on_arg_error(FT_ERR_A_MANY, line_split, fd, line);
	return (0);
}

/**
	@brief Handles the argument check for camera view objects (number of arguments,
		number in argument category, check if the values are numbers).
		Exits on wrong input.
	@param line_split Array of strings separated by argument categories.
	@param c_cnt Pointer to camera counter.
	@param fd Filedescriptor of opened input file.
	@param line Line that was read from input file.
	@return 0 on success.
*/
static int	ft_arg_check_vo_c(char **line_split, int *c_cnt, int fd, char *line)
{
	int	i;

	i = 1;
	while (line_split[i] != NULL)
	{
		if (i > 3)
			ft_exit_on_arg_error(FT_ERR_C_ARG_CHECK, line_split, fd, line);
		else if (i == 1 || i == 2)
		{
			if (ft_three_num_check(line_split[i]))
				ft_exit_on_arg_error(FT_ERR_C_ARG_CHECK, line_split, fd, line);
		}
		else
			if (ft_digit_check(line_split[i]) != 0)
				ft_exit_on_arg_error(FT_ERR_C_ARG_CHECK, line_split, fd, line);
		i++;
	}
	if (i != 4)
		ft_exit_on_arg_error(FT_ERR_C_ARG_CHECK, line_split, fd, line);
	(*c_cnt)++;
	if (*c_cnt > 1)
		ft_exit_on_arg_error(FT_ERR_C_MANY, line_split, fd, line);
	return (0);
}

/**
	@brief Handles the argument check for view objects. Exits on wrong input.
	@param line_split Array of strings separated by argument categories.
	objects after inputfile was completely processed.
	@param last_check Indicator for checking the correct amount of mandatory
		objects after inputfile was completely processed.
	@param fd Filedescriptor of opened input file.
	@param line Line that was read from input file.
	@return 0 on success.
*/
int	ft_arg_check_vo(char **line_split, int last_check, int fd, char *line)
{
	static int	a_cnt = 0;
	static int	l_cnt = 0;
	static int	c_cnt = 0;

	if (last_check)
	{
		if (c_cnt == 0)
			ft_exit_on_arg_error(FT_ERR_C_LESS, NULL, fd, line);
		else
			return (0);
	}
	if (!ft_strcmp(line_split[0], "C"))
		return (ft_arg_check_vo_c(line_split, &c_cnt, fd, line));
	else if (!ft_strcmp(line_split[0], "A"))
		return (ft_arg_check_vo_a(line_split, &a_cnt, fd, line));
	else if (!ft_strcmp(line_split[0], "L"))
		return (ft_arg_check_vo_l(line_split, &l_cnt, fd, line));
	ft_exit_on_arg_error(FT_ERR_UNKNOWN_OBJ, line_split, fd, line);
	return (0);
}
