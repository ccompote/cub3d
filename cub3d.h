/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 15:54:34 by ccompote          #+#    #+#             */
/*   Updated: 2023/04/09 18:35:19 by ccompote         ###   ########.fr       */
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

typedef struct struct_s
{
	int				fd;
	char 			**map;
	int				width;
	int				height;
	mlx_image_t		*south;
	mlx_texture_t	*south_tx;
	mlx_image_t		*north;
	mlx_texture_t	*north_tx;
	mlx_image_t		*east;
	mlx_texture_t	*east_tx;
	mlx_image_t		*west;
	mlx_texture_t	*west_tx;
	mlx_t			*mlx;
}	t_cub;


void	create_map(int fd, t_cub *zop, char **argv);
char	*gn_strchr(char *s, int c);
char	*gn_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);
int		ft_strlen_no_nl(char *s);
int		check_arg(int argc, char **argv);
int		checker_2(t_cub *zop, char **argv);
int		map_lines(int fd, t_cub *zop);

#endif