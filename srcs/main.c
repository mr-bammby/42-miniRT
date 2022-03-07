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
	int				error;
	t_list			*gol;
	t_view_object	vo;

	gol = NULL;
	error = argument_check(argc, argv);
	if(error)
		return (error);
	ft_list_builder(argv[1], &gol, &vo);
	//error = list_builder
/* 	t_vec vec1;
	t_vec vec2;
	t_vec vec3;

	vec1 = ft_creat_vec(long2fixed(1), long2fixed(0), long2fixed(0));
	vec2 = ft_creat_vec(long2fixed(0), long2fixed(0), long2fixed(1));
	vec3 = ft_cross_prod_vec(vec1, vec2);
	printf("vector size: %f, norm vect: %f, %f, %f \n", fixed2double(vec3.size), fixed2double(vec3.n_vec.x), fixed2double(vec3.n_vec.y), fixed2double(vec3.n_vec.z));
	printf("scalar product: %f\n", fixed2double(vec3)); */
	if (PRINT_GOL)
		print_gol(gol);
	if (PRINT_VO)
		print_vo(vo);
	//ft_mlx();
	ft_exit_free(gol);
}





//export DISPLAY=$(cat /etc/resolv.conf | grep nameserver | awk '{print $2}'):0.0