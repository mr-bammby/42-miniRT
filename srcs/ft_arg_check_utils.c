/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_check_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 02:24:32 by mamuller          #+#    #+#             */
/*   Updated: 2022/03/21 02:24:32 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

/**
	@brief Checks whether the file has the required file extension.
	@param file_name The file to be checked.
	@return None.
*/
void	ft_file_extension_check(char *file_name)
{
	int	cnt;
	int	len;

	cnt = 0;
	len = ft_strlen(file_name);
	if (len < 4)
		ft_exit_on_arg_error(FT_ERR_FILE_NAME, NULL, -1, NULL);
	while (cnt < len - 3)
	{
		if (file_name[cnt] == '.' && cnt != 0)
			ft_exit_on_arg_error(FT_ERR_FILE_NAME, NULL, -1, NULL);
		cnt++;
	}
	if (file_name[cnt] == '.' && file_name[cnt + 1] == 'r' \
		&& file_name[cnt + 2] == 't')
		return ;
	ft_exit_on_arg_error(FT_ERR_FILE_NAME, NULL, -1, NULL);
}

/**
	@brief Checks whether the file can be read.
	@param file_name The file to be checked.
	@return Returns the file desriptor of the opened file.
*/
int	ft_access_check(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		ft_exit_on_arg_error(FT_ERR_FILE_ACCESS, NULL, -1, NULL);
	return (fd);
}
