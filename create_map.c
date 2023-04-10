/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 16:00:08 by ccompote          #+#    #+#             */
/*   Updated: 2023/04/10 15:36:07 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int	map_lines(int fd, t_cub3d *zop)
// {
// 	int		i;
// 	char	*str;

// 	i = 0;
// 	str = get_next_line(zop->fd);
// 	if (str == NULL)
// 		return (0);
// 	zop->c_map->columns = ft_strlen_no_nl(str);
// 	i++;
// 	while (str)
// 	{
// 		free(str);
// 		str = get_next_line(zop->fd);
// 		if (!str)
// 			break ;
// 		i++;
// 		if (ft_strlen_no_nl(str) != zop->c_map->columns)
// 		{
// 			free(str);
// 			return (0);
// 		}	
// 	}
// 	zop->c_map->rows = i;
// 	return (1);
// }

int	file_lines(int fd, t_cub3d *zop)
{
	int		i;
	char	*str;

	i = 0;
	str = get_next_line(fd);
	if (str == NULL)
		return (0);
	i++;
	while (str)
	{
		free(str);
		str = get_next_line(fd);
		if (!str)
			break ;
		i++;	
	}
	zop->file_rows = i;
	return (1);
}

int	create_images(t_cub3d *zop)
{
	// char	*tmp;
	int		i;

	i = 0;
	printf("%s\n", zop->map_file[i]);
	if (!ft_strncmp(zop->map_file[i], "NO", 2))
	{
		// tmp = ft_calloc((ft_strlen(map_file[i]) - 1 - 3), sizeof(char));
		// map_file[i] += 3;
		// while (i < (ft_strlen(str) - 1))
		// {
		// 	tmp[i] = str[i];
		// 	printf("%i\n", i);
		// 	i++;
		// }
		zop->map_file[i] += 3;
		// printf("%s\n", zop->map_file[i]);
		// zop->north_tx = mlx_load_png(tmp);
		return (1);
	}
	// else if (!ft_strncmp(str, "SO", 2))
	// 	return (1);
	// else if (!ft_strncmp(str, "WE", 2))
	// 	return (1);
	// else if (!ft_strncmp(str, "EA", 2))
	// 	return (1);

	return (0);
}

void	create_file_arr(int fd, t_cub3d *zop)
{
	int i;
	
	zop->map_file = malloc(sizeof(char *) * (zop->file_rows + 1));
	i = 0;
	while (i < zop->file_rows)
	{
		zop->map_file[i] = get_next_line(fd);
		printf("%s", zop->map_file[i]);
		i++;
	}
	zop->map_file[i] = NULL;
	print_arg(zop->map_file);
}

int	read_file(t_cub3d *zop, char **argv)
{
	int fd;
	
	fd = open(argv[1], O_RDONLY);
	file_lines(fd, zop);
	close(fd);
	fd = open(argv[1], O_RDONLY);
	create_file_arr(fd, zop);
	close(fd);
	// create_images(zop);
	// if (checker_2(zop, argv))
	// 	return (0);
	
	return (1);
}