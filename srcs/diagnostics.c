#include "../incl/miniRT.h"

void print_gol(t_list *gol)
{
	int	i;

	while (gol)
	{
		if (((t_geo_object *)(gol->content))->type == FT_SP_TYPE)
		{
			printf("SPHERE\n");
			printf("diameter: %f\n", fixed2double(((t_sphere *)(((t_geo_object *)(gol->content))->s))->diameter));
			for(i = 0; i < 3; i++)
			{
				printf("coord[%i]: %f\n", i, fixed2double(((t_sphere *)(((t_geo_object *)(gol->content))->s))->coord[i]));
			}
		}
		else if (((t_geo_object *)(gol->content))->type == FT_PL_TYPE)
		{
			printf("PLANE\n");
			for(i = 0; i < 3; i++)
				printf("coord[%i]: %f\n", i, fixed2double(((t_plane *)(((t_geo_object *)(gol->content))->s))->coord[i]));
			for(i = 0; i < 3; i++)
				printf("dir_vector[%i]: %f\n", i, fixed2double(((t_plane *)(((t_geo_object *)(gol->content))->s))->dir_vector[i]));
		}
		else
		{
			printf("CYLINDER\n");
			for(i = 0; i < 3; i++)
				printf("coord[%i]: %f\n", i, fixed2double(((t_cylinder *)(((t_geo_object *)(gol->content))->s))->coord[i]));
			for(i = 0; i < 3; i++)
				printf("dir_vector[%i]: %f\n", i, fixed2double(((t_cylinder *)(((t_geo_object *)(gol->content))->s))->dir_vector[i]));
			printf("diameter: %f\n", fixed2double(((t_cylinder *)(((t_geo_object *)(gol->content))->s))->diameter));
			printf("height: %f\n", fixed2double(((t_cylinder *)(((t_geo_object *)(gol->content))->s))->height));
		}
		for(i = 0; i < 3; i++)
			printf("color[%i]: %f\n", i, fixed2double((((t_geo_object *)(gol->content))->color[i])));
		gol = gol->next;
	}
}

void print_vo(t_view_object vo)
{
	int i;
	printf("CAMERA\n");
	for(i = 0; i < 3; i++)
		printf("coord[%i]: %f\n", i, fixed2double(vo.camera.coord[i]));
	for(i = 0; i < 3; i++)
		printf("dir_vector[%i]: %f\n", i, fixed2double(vo.camera.dir_vector[i]));
	printf("angle: %f radians\n", fixed2double(vo.camera.angle));
	printf("LIGHT\n");
	for(i = 0; i < 3; i++)
		printf("coord[%i]: %f\n", i, fixed2double(vo.light.coord[i]));
	printf("light_ratio: %f \n", fixed2double(vo.light.light_ratio));
	printf("AMBIENT\n");
	printf("light_ratio: %f \n", fixed2double(vo.ambient.light_ratio));
	for(i = 0; i < 3; i++)
		printf("color[%i]: %f\n", i, fixed2double(vo.ambient.color[i]));

}