/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 13:20:12 by dbanfi            #+#    #+#             */
/*   Updated: 2022/02/26 13:20:12 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/miniRT.h"

int file_extension_check(char *file_name)
{
	int cnt;
	int len;

	cnt = 0;
	len = ft_strlen(file_name);
	if (len < 4)
	{
		write(2, "Error: unsupported file\n", 24);
		return (1);
	}
	while (cnt < len - 3)
	{
		if (file_name[cnt] == '.' && cnt != 0)
		{
			write(2, "Error: unsupported file\n", 24);
			return(1);
		}
		cnt++;
	}
	if (file_name[cnt] == '.' && file_name[cnt + 1] == 'r' /
		&& file_name[cnt + 2] == 't')
		return(0);
	write(2, "Error: unsupported file\n", 24);
	return(1);
}

int access_check(char *file_name)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if(fd == -1)
	{
		perror("Error")
		return(-1);
	}
	return (fd);
}

int rgb_check(char* str)///////////////////////////////////////////////////////////////FIX THIS
{
	char **split;
	int i;
	int j;

	split = ft_split(str, ',');
	if (split == NULL)
		return (1);
	i = 0;
	while(split[i] != NULL)
	(
		if (i > 2)
			break;
		if (ft_digit_check(split[i]) != 0)
		{
			ft_free_split(split);
			return (1);
		}
		if (split[i][0] > '2' || split[i][0] < '0')
		{
			ft_free_split(split);
			return (1);
		}
		else if (split[i][0] == '2')
			if (split[i][1] > '5' || split[i][1] < '0')
			{
				ft_free_split(split);
				return (1);
			}
			else if (split[i][1] == '5')
				if (split[i][1] > '5' || split[i][1] < '0')
				{
					ft_free_split(split);
					return (1);
				}
				else if (split[i][1] == '5')

		i++;
	)
	ft_free_split(split);
	if (i != 2)
		return (1);
	return (0);
}

int main_line_check(char **line_split, int last_check)
{
	static int	a_cnt = 0;
	static int	l_cnt = 0; 									//remove for bonus part
	static int	c_cnt = 0;
	int			i;

	if (last_check)
		return (!c_cnt);
	i = 1;
	if (!(strcmp(line_split[0], "C"))
	{
		while(line_split != NULL)
		(
			if (i > 3)
				break;
			if (i == 1)
			{
				if()
			}
		)
	}

}

int line_check(char *line, int last_check)
{
	char		**line_split;
	char		**arg_split;

	line_split = ft_split(line. ' ');
	if (line_split == NULL)
		return (1);
	if (!(strcmp(line_split[0], "A") || !(strcmp(line_split[0], "L") || !(strcmp(line_split[0], "C")))

}

int argument_check(int argc, char **argv, int *fd)
{
	if (argc != 2)
	{
		write(2, "Error: wrong number of arguments\n", 33);
		return (1);
	}
	if (file_extension_check(argv[1]) != 0)
		return (2);
	*fd = access_check(argv[1]);
	if (*fd)
		return (3);
	line = get_next_line(*fd);
	while (line != NULL)
	{
		if (line_check(line) != 0)
		{
			close(*fd);
			ft_smart_free((void **)&line);
			write(2, "Error: unknown line format\n", 27);
			return(4);
		}
		ft_smart_free((void **)&line);
		line = get_next_line(*fd);
	}
	return (0);
}





int	main(int argc, char **argv)
{
	argument_check(argc, argv);
	//object list builder
}
