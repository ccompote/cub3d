/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 15:54:34 by ccompote          #+#    #+#             */
/*   Updated: 2023/04/10 15:35:54 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif
# define STEP 32
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

#include <stdbool.h>
#include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"

typedef struct s_player
{
    float x;
    float y;
    float angle;
} t_player;

typedef struct s_map
{
    int     rows;
    int     columns;
    char    **ar_map;
} t_map;

typedef struct s_cub3D
{
    mlx_t       *mlx;
    t_map       *c_map;
    t_player    *pl_pos;
    mlx_image_t *cur_img;
    mlx_image_t *old_img;
	char		**map_file;
	int			file_rows;

	int				fd;
	mlx_image_t		*south;
	mlx_texture_t	*south_tx;
	mlx_image_t		*north;
	mlx_texture_t	*north_tx;
	mlx_image_t		*east;
	mlx_texture_t	*east_tx;
	mlx_image_t		*west;
	mlx_texture_t	*west_tx;

} t_cub3d;

int	read_file(t_cub3d *zop, char **argv);
char	*gn_strchr(char *s, int c);
char	*gn_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);
int		ft_strlen_no_nl(char *s);
int		check_arg(int argc, char **argv);
int		checker_2(t_cub3d *zop, char **argv);
int		map_lines(int fd, t_cub3d *zop);


void	print_arg(char **args);

#endif