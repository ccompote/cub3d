/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:27:48 by ccompote          #+#    #+#             */
/*   Updated: 2023/04/20 15:43:59 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_arg(char **args)
{
	int	i;

	i = 0;
	if (args)
	{
		while (args[i])
		{
			printf("%s", args[i]);
			i++;
		}
		printf("\n");
	}
	else
		printf("args: (null)\n");
}

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

int	get_color(mlx_texture_t *texture, int x_coord, int y_coord)
{
	int byte;
	uint32_t	color;

	byte = (y_coord * texture->width * 4) + (x_coord * 4);
	color = ft_pixel(texture->pixels[byte], texture->pixels[byte + 1],
		texture->pixels[byte + 2], texture->pixels[byte + 3]);
	return (color);
}

int min(int a, int b)
{
	if (a <= b)
		return a;
	return b;
}
int max(int a, int b)
{
	if (a > b)
		return a;
	return b;
}

void draw_txtr_line(mlx_texture_t *txtr, size_t cl_h, float x1, t_cub3d *s_cub, int i, float y1) // NOT OK
{
	int txt_x;
	int txt_y1;
	int txt_x1;
	int32_t y;

	y = 0;
	while (y < cl_h && y < s_cub->mlx->height )
	{
		txt_x = txtr->width * ((float)x1 - (int)x1);
		if (cl_h > s_cub->mlx->height)
			txt_y1 = ((cl_h - s_cub->mlx->height)/ 2 + y) 
			* txtr->height / (cl_h + 0.00001f);
		else
			txt_y1 = y * txtr->height / (cl_h + 0.00001f);
		txt_x1 = txtr->width * ((float)y1 - (int)y1);
		int clll = min(cl_h, s_cub->mlx->height);
		int yyy = min(max((int)((s_cub->mlx->height - clll)/2+ y), 0), s_cub->mlx->height);
		if 	((txtr == s_cub->c_map->NO) || (txtr == s_cub->c_map->SO))
			mlx_put_pixel(s_cub->image, i, yyy, get_color(txtr, txt_x, (int)txt_y1));
		if 	((txtr == s_cub->c_map->WE) || (txtr == s_cub->c_map->EA))
			mlx_put_pixel(s_cub->image, i, yyy, get_color(txtr, txt_x1, txt_y1));
		++y;
	}
}

typedef struct s_rcast
{
	mlx_texture_t	*wrk_t;
	float x1;
	float y1;
	float ang;
	float dist;
} t_raycst;

void redraw_all(t_cub3d *s_cub) // NOT OK !!!!!!!!!!!!!
{
	mlx_texture_t	*wrk_txt; // replase

	mlx_t* mlx = s_cub->mlx;
	t_player player = *(s_cub->pl_pos);
	float view_angle = s_cub->view_angle;

	// floor ceiling start
	mlx_delete_image(s_cub->mlx, s_cub->image);
	s_cub->image = mlx_new_image(mlx, mlx->width, mlx->height);
	for (int32_t i = 0; i < s_cub->mlx->width; ++i)
	{
		for (int32_t y = 0; y < s_cub->mlx->height; ++y)
		{
			if (y < s_cub->mlx->height/2)
				mlx_put_pixel(s_cub->image, i, y, s_cub->c_map->f_color);
			else
				mlx_put_pixel(s_cub->image, i, y, s_cub->c_map->c_color);
		}
	}
	// end floor ceiling
	
	for (int i = 0; i < mlx->width; i++)
	{
		float ang = player.angle - view_angle/2 + (view_angle * i) / mlx->width;
		for (float dist = 0 ; dist < 20; dist += RTSTEP)
		{
			float x1 = player.x + dist * cosf(ang);
			float y1 = player.y + dist * sinf(ang);
			if (((int)y1 >= 0) && ((int)y1 < s_cub->c_map->rows) && ((int)x1 >= 0) && ((int)x1 < s_cub->c_map->column ) && (s_cub->tmp_map[(int)y1][(int)x1] != '0'))
			{
				size_t column_height = s_cub->mlx->height/(dist*cosf(ang-player.angle));				
				// start
				dist -= RTSTEP;
				x1 = player.x + dist * cosf(ang);
				y1 = player.y + dist * sinf(ang);
				if (fabs(x1 -(int)x1) < fabs(1 - x1 + (int)x1) && fabs(x1 -(int)x1) < fabs(1 - y1 + (int)y1) && fabs(x1 -(int)x1) < fabs(y1 - (int)y1))
					wrk_txt	= s_cub->c_map->WE; // mss
				if (fabs(1 - x1 + (int)x1) < fabs(x1 -(int)x1) && fabs(1 - x1 + (int)x1) < fabs(1 - y1 + (int)y1) && fabs(1 - x1 + (int)x1) < fabs(y1 - (int)y1))
					wrk_txt	= s_cub->c_map->EA; // cls	
				if (fabs(y1 - (int)y1)< fabs(1 - x1 + (int)x1) && fabs(y1 - (int)y1) < fabs(x1 -(int)x1) && fabs(y1 - (int)y1) < fabs(1 - y1 + (int)y1))
					wrk_txt	= s_cub->c_map->NO; // bls
				if (fabs(1 - y1 + (int)y1) < fabs(1 - x1 + (int)x1) && fabs(1 - y1 + (int)y1) < fabs(y1 - (int)y1) && fabs(1 - y1 + (int)y1) < fabs(x1 -(int)x1))
					wrk_txt	= s_cub->c_map->SO; // grs										
				// end
				if (s_cub->mintwo == NULL)
					s_cub->mintwo = wrk_txt;
				else if (s_cub->minone == NULL)
					s_cub->minone = wrk_txt;				
				if (s_cub->mintwo && s_cub->minone)
				{
					if ((s_cub->mintwo != s_cub->minone) && (s_cub->mintwo == wrk_txt) && (i > 1))
					{
						draw_txtr_line(wrk_txt, column_height, x1, s_cub, i-1, y1);
						s_cub->minone = wrk_txt;
					}
					s_cub->mintwo = s_cub->minone;
					s_cub->minone = wrk_txt;
				}
				draw_txtr_line(wrk_txt, column_height, x1, s_cub, i, y1);
				break;
			}
		}
	}
	mlx_image_to_window(mlx, s_cub->image, 0, 0) ;
}



int check_wall(t_cub3d *s_cub, float dispX, float dispY)
{
	int newX;
	int newY;

	newX = (int)(s_cub->pl_pos->x + dispX);
	newY = (int)(s_cub->pl_pos->y + dispY);		
	if (s_cub->tmp_map[newY][newX] == '0')
		return (1);
	else
		return (0);
}

void move_pl(t_cub3d *s_cub, mv_dir dir) // NOT OK
{
	float dx;
	float dy;

	dx = STEP * cosf(s_cub->pl_pos->angle);
	dy = STEP * sinf(s_cub->pl_pos->angle);
	if (dir == rt) 
	{
		if (check_wall(s_cub, -dy, 0))
			s_cub->pl_pos->x -= dy;
		if (check_wall(s_cub, 0, +dx))
			s_cub->pl_pos->y += dx;		
	}
	else if (dir == lf)	
	{
		if (check_wall(s_cub, +dy, 0)) 
			s_cub->pl_pos->x += dy;
		if (check_wall(s_cub, 0, -dx))
			s_cub->pl_pos->y -= dx;		
	}
	else if (dir == up)
	{
		if (check_wall(s_cub, dx, 0))		
			s_cub->pl_pos->x += dx;
		if (check_wall(s_cub, 0, dy))
			s_cub->pl_pos->y += dy;	
	}
	else if (dir == dw)
	{
		if (check_wall(s_cub, -dx, 0))	
			s_cub->pl_pos->x -= dx;
		if (check_wall(s_cub, 0, -dy))			
			s_cub->pl_pos->y -= dy;		
	}
	else if (dir == rot_lf)
		s_cub->pl_pos->angle -= TURN_ANGLE;
	else if (dir == rot_rt)
		s_cub->pl_pos->angle += TURN_ANGLE;
	redraw_all(s_cub);
}

void ft_key_hook(mlx_key_data_t keydata, void *param)
{
	t_cub3d	*s_cub;

	s_cub = (t_cub3d *)param;	
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(s_cub->mlx);
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		move_pl(s_cub, up);
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		move_pl(s_cub, dw);
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		move_pl(s_cub, lf);
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		move_pl(s_cub, rt);
	else if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		move_pl(s_cub, rot_lf);
	else if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		move_pl(s_cub, rot_rt);			
}

void mlx_resize(int32_t width, int32_t height, void* param)
{
	(void)width;
	(void)height;
	t_cub3d	*s_cub;

	s_cub = (t_cub3d *)param;	

// resize happen;

	// redraw_all(s_cub);
	
	// move_pl(s_cub, dw);
	// mlx_resize_image(floor0, width, height);
		// mlx_resize_image(ceiling, width, height);
}

void ft_hook(void* param)
{
	t_cub3d	*s_cub;

	s_cub = (t_cub3d *)param;	
	if (mlx_is_key_down(s_cub->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(s_cub->mlx);
	else if (mlx_is_key_down(s_cub->mlx, MLX_KEY_D))
		move_pl(s_cub, rt);
	else if (mlx_is_key_down(s_cub->mlx, MLX_KEY_A))
		move_pl(s_cub, lf);
	else if (mlx_is_key_down(s_cub->mlx, MLX_KEY_W))
		move_pl(s_cub, up);
	else if (mlx_is_key_down(s_cub->mlx, MLX_KEY_S))
		move_pl(s_cub, dw);
	else if (mlx_is_key_down(s_cub->mlx, MLX_KEY_RIGHT))
		move_pl(s_cub, rot_rt);
	else if (mlx_is_key_down(s_cub->mlx, MLX_KEY_LEFT))
		move_pl(s_cub, rot_lf);
}

// -----------------------------------------------------------------------------

char	**feed_map(char *path) //(t_map *wmap, char *path)
{
	char **hope;
	int rowsize = 13;
	hope = malloc(sizeof(char *) * (rowsize + 1));
	int i = 0;

    char *filename = path;
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error: could not open file %s", filename);
        return 0;
    }
    const unsigned MAX_LENGTH = 256;
    char buffer[MAX_LENGTH];
    while (fgets(buffer, MAX_LENGTH, fp))
	{
		hope[i] = malloc(sizeof(char) * 9);
		strcpy(hope[i++],buffer);
        // printf("%s", buffer);
	}
	hope[i] = 0;
    fclose(fp);
	return (hope);
}

	// system("leaks a.out");
void	checkleaks(void)
{
		system("leaks a.out");
	// system("leaks so_long");
}

void	tdimarr_clear(char	**arrclear)
{
	int	i;

	i = 0;
	while (arrclear[i])
	{
		free(arrclear[i]);
		i++;
	}
	free(arrclear);
}

int32_t main(int32_t argc, char* argv[])	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
{
	// atexit(checkleaks);
	t_cub3d main_cub;

	if (!(main_cub.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}

	read_file(&main_cub, argv);
	main_cub.c_map->EA = mlx_load_png(main_cub.c_map->east_path);
	main_cub.c_map->NO = mlx_load_png(main_cub.c_map->north_path);
	main_cub.c_map->SO = mlx_load_png(main_cub.c_map->south_path);
	main_cub.c_map->WE = mlx_load_png(main_cub.c_map->west_path);
	// loaded_map_st.f_color = ft_pixel(255, 0, 0, 255);
	// loaded_map_st.c_color = ft_pixel(116, 96, 31, 255);
	main_cub.c_map->f_color = ft_pixel(main_cub.c_map->f_color_r,main_cub.c_map->f_color_g, main_cub.c_map->f_color_b, 255);
	main_cub.c_map->c_color = ft_pixel(main_cub.c_map->c_color_r,main_cub.c_map->c_color_g, main_cub.c_map->c_color_b, 255);

	
	t_player player;
	player.x = 2.5f;
	player.y = 5.4f;
	player.angle = 1.5*M_PI;

	main_cub.tmp_map = main_cub.c_map->ar_map;
	main_cub.pl_pos = &player;
	main_cub.view_angle = M_PI/3;
	main_cub.minone = NULL;
	main_cub.mintwo = NULL;
	main_cub.image = mlx_new_image(main_cub.mlx, main_cub.mlx->width, main_cub.mlx->height);

	redraw_all(&main_cub);

	// mlx_loop_hook(mlx, ft_randomize, mlx);
	mlx_loop_hook(main_cub.mlx, ft_hook, &main_cub);
	// mlx_key_hook(main_cub.mlx, ft_key_hook, &main_cub);
	// mlx_resize_hook(main_cub.mlx, mlx_resize, &main_cub);
	mlx_loop(main_cub.mlx);
	mlx_terminate(main_cub.mlx);

mlx_delete_texture(main_cub.c_map->EA);
mlx_delete_texture(main_cub.c_map->NO);
mlx_delete_texture(main_cub.c_map->SO);
mlx_delete_texture(main_cub.c_map->WE);
tdimarr_clear(main_cub.c_map->ar_map);

	return (EXIT_SUCCESS);
}