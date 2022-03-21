#include "../incl/miniRT.h"

void print_gol(t_list *gol)
{
	int	i;

	while (gol)
	{
		if (((t_geo_object *)(gol->content))->type == FT_SP_TYPE)
		{
			printf("SPHERE\n");
			printf("diameter: %f\n", fxtod(((t_sphere *)(((t_geo_object *)(gol->content))->s))->diameter));
			printf("coord[x]: %f\n", fxtod(((t_sphere *)(((t_geo_object *)(gol->content))->s))->coord.x));
			printf("coord[y]: %f\n", fxtod(((t_sphere *)(((t_geo_object *)(gol->content))->s))->coord.y));
			printf("coord[z]: %f\n", fxtod(((t_sphere *)(((t_geo_object *)(gol->content))->s))->coord.z));
			
		}
		else if (((t_geo_object *)(gol->content))->type == FT_PL_TYPE)
		{
			printf("PLANE\n");
			printf("coord[x]: %f\n",fxtod(((t_plane *)(((t_geo_object *)(gol->content))->s))->coord.x));
			printf("coord[y]: %f\n",fxtod(((t_plane *)(((t_geo_object *)(gol->content))->s))->coord.y));
			printf("coord[z]: %f\n",fxtod(((t_plane *)(((t_geo_object *)(gol->content))->s))->coord.z));
			printf("dir_vector[x]: %f\n", fxtod(((t_plane *)(((t_geo_object *)(gol->content))->s))->dir_vector.n_vec.x));
			printf("dir_vector[y]: %f\n", fxtod(((t_plane *)(((t_geo_object *)(gol->content))->s))->dir_vector.n_vec.y));
			printf("dir_vector[z]: %f\n", fxtod(((t_plane *)(((t_geo_object *)(gol->content))->s))->dir_vector.n_vec.z));
			printf("dir_vector size: %f\n", fxtod(((t_plane *)(((t_geo_object *)(gol->content))->s))->dir_vector.size));
		}
		else
		{
			printf("CYLINDER\n");
			printf("coord[x]: %f\n",fxtod(((t_cylinder *)(((t_geo_object *)(gol->content))->s))->coord.x));
			printf("coord[y]: %f\n",fxtod(((t_cylinder *)(((t_geo_object *)(gol->content))->s))->coord.y));
			printf("coord[z]: %f\n",fxtod(((t_cylinder *)(((t_geo_object *)(gol->content))->s))->coord.z));
			printf("dir_vector[x]: %f\n", fxtod(((t_cylinder *)(((t_geo_object *)(gol->content))->s))->dir_vector.n_vec.x));
			printf("dir_vector[y]: %f\n", fxtod(((t_cylinder *)(((t_geo_object *)(gol->content))->s))->dir_vector.n_vec.y));
			printf("dir_vector[z]: %f\n", fxtod(((t_cylinder *)(((t_geo_object *)(gol->content))->s))->dir_vector.n_vec.z));
			printf("dir_vector size: %f\n", fxtod(((t_cylinder *)(((t_geo_object *)(gol->content))->s))->dir_vector.size));
			printf("diameter: %f\n", fxtod(((t_cylinder *)(((t_geo_object *)(gol->content))->s))->diameter));
			printf("height: %f\n", fxtod(((t_cylinder *)(((t_geo_object *)(gol->content))->s))->height));
		}
		for(i = 0; i < 3; i++)
			printf("color[%i]: %f\n", i, fxtod((((t_geo_object *)(gol->content))->color[i])));
		gol = gol->next;
	}
}

void print_vo(t_view_object vo)
{
	int i;
	printf("CAMERA\n");
	printf("coord[x]: %f\n",fxtod(vo.camera.coord.x));
	printf("coord[y]: %f\n",fxtod(vo.camera.coord.y));
	printf("coord[z]: %f\n",fxtod(vo.camera.coord.z));
	printf("dir_vector[x]: %f\n", fxtod(vo.camera.dir_vector.n_vec.x));
	printf("dir_vector[y]: %f\n", fxtod(vo.camera.dir_vector.n_vec.y));
	printf("dir_vector[z]: %f\n", fxtod(vo.camera.dir_vector.n_vec.z));
	printf("dir_vector size: %f\n", fxtod(vo.camera.dir_vector.size));
	printf("angle: %f radians\n", fxtod(vo.camera.angle));
	printf("LIGHT\n");
	printf("coord[x]: %f\n",fxtod(vo.light.coord.x));
	printf("coord[y]: %f\n",fxtod(vo.light.coord.y));
	printf("coord[z]: %f\n",fxtod(vo.light.coord.z));
	printf("light_ratio: %f \n", fxtod(vo.light.light_ratio));
	printf("AMBIENT\n");
	printf("light_ratio: %f \n", fxtod(vo.ambient.light_ratio));
	for(i = 0; i < 3; i++)
		printf("color[%i]: %f\n", i, fxtod(vo.ambient.color[i]));

}