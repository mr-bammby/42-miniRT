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

int g_error;

int	main(int argc, char **argv)
{
	int				error;
	t_list			*gol;
	t_view_object	vo;
	t_screen		screen;

	g_error = 0;
	gol = NULL;
	error = argument_check(argc, argv);
	if(error)
		return (error);
	error = ft_list_builder(argv[1], &gol, &vo);
	//error = list_builder
	if (PRINT_GOL)
		print_gol(gol);
	if (PRINT_VO)
		print_vo(vo);
	screen = ft_screen_maker(vo.camera);
	ft_mlx(screen, gol, vo);
	ft_exit_free(gol);

	
	if (error)
	{
		printf ("Builder ERROR\n");
		return (error);
	}
	
}





//export DISPLAY=$(cat /etc/resolv.conf | grep nameserver | awk '{print $2}'):0.0