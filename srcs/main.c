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

int	main(int argc, char **argv)
{
	t_list			*gol;
	t_view_object	vo;
	t_screen		screen;

	gol = NULL;
	ft_argument_check(argc, argv);
	ft_list_builder(argv[1], &gol, &vo);
	screen = ft_screen_maker(vo.camera);
	ft_mlx(screen, gol, vo);
	ft_exit_free(gol);
	return (0);
}
