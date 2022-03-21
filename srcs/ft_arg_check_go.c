/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_check_go.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 01:25:28 by mamuller          #+#    #+#             */
/*   Updated: 2022/03/21 01:25:28 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

/**
	@brief Handles the argument check for sphere geometric object 
		(number of arguments, number in argument category, check if 
		the values are numbers). Exits on wrong input.
	@param line_split Array of strings separated by argument categories.
	@param fd Filedescriptor of opened input file.
	@param line Line that was read from input file.
	@return 0 on success.
*/
static int	ft_arg_check_go_sp(char **line_split, int fd, char *line)
{
	int	i;

	i = 1;
	while (line_split[i] != NULL)
	{
		if (i > 3)
			ft_exit_on_arg_error(FT_ERR_SP_ARG_CHECK, line_split, fd, line);
		if (i == 1 || i == 3)
		{
			if (ft_three_num_check(line_split[i]))
				ft_exit_on_arg_error(FT_ERR_SP_ARG_CHECK, line_split, fd, line);
		}
		else
			if (ft_digit_check(line_split[i]) != 0)
				ft_exit_on_arg_error(FT_ERR_SP_ARG_CHECK, line_split, fd, line);
		i++;
	}
	if (i != 4)
		ft_exit_on_arg_error(FT_ERR_SP_ARG_CHECK, line_split, fd, line);
	return (0);
}

/**
	@brief Handles the argument check for plane geometric object 
		(number of arguments, number in argument category, check if 
		the values are numbers). Exits on wrong input.
	@param line_split Array of strings separated by argument categories.
	@param fd Filedescriptor of opened input file.
	@param line Line that was read from input file.
	@return 0 on success.
*/
static int	ft_arg_check_go_pl(char **line_split, int fd, char *line)
{
	int	i;

	i = 1;
	while (line_split[i] != NULL)
	{
		if (i > 3)
			ft_exit_on_arg_error(FT_ERR_PL_ARG_CHECK, line_split, fd, line);
		if (ft_three_num_check(line_split[i]))
			ft_exit_on_arg_error(FT_ERR_PL_ARG_CHECK, line_split, fd, line);
		i++;
	}
	if (i != 4)
		ft_exit_on_arg_error(FT_ERR_PL_ARG_CHECK, line_split, fd, line);
	return (0);
}

/**
	@brief Handles the argument check for cylinder geometric object 
		(number of arguments, number in argument category, check if 
		the values are numbers). Exits on wrong input.
	@param line_split Array of strings separated by argument categories.
	@param fd Filedescriptor of opened input file.
	@param line Line that was read from input file.
	@return 0 on success.
*/
static int	ft_arg_check_go_cy(char **line_split, int fd, char *line)
{
	int	i;

	i = 1;
	while (line_split[i] != NULL)
	{
		if (i > 5)
			ft_exit_on_arg_error(FT_ERR_CY_ARG_CHECK, line_split, fd, line);
		if (i == 1 || i == 2 || i == 5)
		{
			if (ft_three_num_check(line_split[i]))
				ft_exit_on_arg_error(FT_ERR_CY_ARG_CHECK, line_split, fd, line);
		}
		else
			if (ft_digit_check(line_split[i]) != 0)
				ft_exit_on_arg_error(FT_ERR_CY_ARG_CHECK, line_split, fd, line);
		i++;
	}
	if (i != 6)
		ft_exit_on_arg_error(FT_ERR_CY_ARG_CHECK, line_split, fd, line);
	return (0);
}

/**
	@brief Handles the argument check for geometric objects. Exits on wrong input.
	@param line_split Array of strings separated by argument categories.
	objects after inputfile was completely processed.
	@param fd Filedescriptor of opened input file.
	@param line Line that was read from input file.
	@return 0 on success.
*/
int	ft_arg_check_go(char **line_split, int fd, char *line)
{
	if (!ft_strcmp(line_split[0], "sp"))
		return (ft_arg_check_go_sp(line_split, fd, line));
	else if (!ft_strcmp(line_split[0], "pl"))
		return (ft_arg_check_go_pl(line_split, fd, line));
	else if (!ft_strcmp(line_split[0], "cy"))
		return (ft_arg_check_go_cy(line_split, fd, line));
	ft_exit_on_arg_error(FT_ERR_UNKNOWN_OBJ, line_split, fd, line);
	return (0);
}
