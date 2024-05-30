/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalev <akovalev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:08:41 by akovalev          #+#    #+#             */
/*   Updated: 2024/05/30 20:50:56 by akovalev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map_info(t_map *map)
{
	free(map->no);
	free(map->ea);
	free(map->we);
	free(map->so);
	free(map->f);
	free(map->c);
	while (map->line_count--)
		free(*(char **)(vec_get(&map->map_copy, map->line_count)));
	vec_free(&map->map_copy);
}

int	check_arguments(int argc, char **argv, t_map *map)
{
	if (argc < 2)
	{
		ft_putstr_fd("Error:\nPlease provide a map file\n", 2);
		return (1);
	}
	else if (argc > 2)
	{
		ft_putstr_fd("Error:\nPlease provide only one map file\n", 2);
		return (1);
	}
	map->filename = argv[1];
	map->name_length = ft_strlen(map->filename);
	if (ft_strncmp(&map->filename[map->name_length - 4], ".cub", 4))
	{
		ft_putstr_fd("Error:\nIncorrect map format\n", 2);
		return (1);
	}
	map->fd = open(map->filename, O_RDONLY);
	if (map->fd == -1)
	{
		perror("Error\n");
		close(map->fd);
		return (1);
	}
	return (0);
}

int	check_lines(t_map *map)
{
	size_t	y;
	size_t	x;
	char	*str;
	char	*pr_str;
	char	*nxt_str;
	int		start_pos;

	y = 0;
	start_pos = 0;
	printf("\nabout to check lines\n");
	while (y < map->map_copy.len)
	{
		str = *(char **)vec_get(&map->map_copy, y);
		//printf("%s", *(char **)(vec_get(&map->map_copy, n)));
		x = 0;
		if (str[x] == ' ')
			x++;
		//printf("we are now at %s", *(char **)(vec_get(&map->map_copy, y)));
		while (str[x])
		{
			//printf("%c", *str);
			if (str[x] != 'N' && str[x] != 'S' && str[x] != 'E' && str[x] != 'W' && str[x] != '1' && str[x] != ' ' && str[x] != '0' && str[x] != '\n')
				printf("Disallowed characters in the map\n");
			if (str[x] == ' ')
			{
				if ((str[x - 1] != '1' && str[x - 1] != ' ') || (str[x + 1] != '1' && str[x + 1] != ' ' && str[x + 1] != '\0' && str[x + 1] != '\n'))
					printf("Wrong character at %s\n", &str[x]);
			}
			else if (str[x] == 'N' || str[x] == 'S' || str[x] == 'E' || str[x] == 'W')
			{
				start_pos++;
				if (start_pos > 1)
				{
					printf("Only one starting position marker allowed\n");
					return (1);
				}
			}
			if (str[x] == '0' || str[x] == 'N' || str[x] == 'S' || str[x] == 'E' || str[x] == 'W')
			{
				if (y)
					pr_str = *(char **)vec_get(&map->map_copy, y - 1);
				if (y < map->map_copy.len - 1)
					nxt_str = *(char **)vec_get(&map->map_copy, y + 1);
				if (str[x + 1] == ' ' || str[x + 1] == '\n')
				{
					printf("Wrong character after %s\n", &str[x]);
					return (1);
				}
				if ((y && (pr_str[x] == ' ' || pr_str[x] == '\n')) || y == 0)
				{
					printf("Wrong character above %s\n", &str[x]);
					return (1);
				}
				if ((x && str[x - 1] == ' ') || x == 0)
				{
					printf("Wrong character before %s\n", &str[x]);
					return (1);
				}
				if ((y < map->map_copy.len - 1 && (nxt_str [x] == ' ' || nxt_str [x] == '\n'|| nxt_str [x] == '\0')) || y == map->map_copy.len - 1)
				{
					printf("Wrong character below %s\n", &str[x]);
					return (1);
				}
			}
			x++;
		}
		//printf("\n");
		y++;
	}
	return (0);
}

int	validate_map(t_map *map)
{
	char	*line;
	char	*line_copy;
	char	*ptr;
	int		n;
	int		count;

	n = 0;
	count = 0;
	line = ft_strdup("");
	while (line != NULL)
	{
		free(line);
		line = get_next_line(map->fd);
		if (!line)
			break ;
		ptr = line;
		if (!strncmp(line, "NO", 2))
		{
			if (map->no)
			{
				ft_putstr_fd("Error\nMultiple lines referring to one texture\n", 2);
				free (line);
				return (1);
			}
			ptr++;
			ptr++;
			while (*ptr == ' ')
				ptr++;
			map->no = ft_strdup(ptr);
			count++;
		}
		else if (!strncmp(line, "SO", 2))
		{
			if (map->so)
			{
				ft_putstr_fd("Error\nMultiple lines referring to one texture\n", 2);
				free (line);
				return (1);
			}
			ptr++;
			ptr++;
			while (*ptr == ' ')
				ptr++;
			map->so = ft_strdup(ptr);
			count++;
		}
		else if (!strncmp(line, "WE", 2))
		{
			if (map->we)
			{
				ft_putstr_fd("Error\nMultiple lines referring to one texture\n", 2);
				free (line);
				return (1);
			}
			ptr++;
			ptr++;
			while (*ptr == ' ')
				ptr++;
			map->we = ft_strdup(ptr);
			count++;
		}
		else if (!strncmp(line, "EA", 2))
		{
			if (map->ea)
			{
				ft_putstr_fd("Error\nMultiple lines referring to one texture\n", 2);
				free (line);
				return (1);
			}
			ptr++;
			ptr++;
			while (*ptr == ' ')
				ptr++;
			map->ea = ft_strdup(ptr);
			count++;
		}
		else if (!strncmp(line, "F", 1))
		{
			if (map->f)
			{
				ft_putstr_fd("Error\nMultiple lines referring to one texture\n", 2);
				free (line);
				return (1);
			}
			ptr++;
			while (*ptr == ' ')
				ptr++;
			map->f = ft_strdup(ptr);
			count++;
		}
		else if (!strncmp(line, "C", 1))
		{
			if (map->c)
			{
				ft_putstr_fd("Error\nMultiple lines referring to one texture\n", 2);
				free (line);
				return (1);
			}
			ptr++;
			while (*ptr == ' ')
				ptr++;
			map->c = ft_strdup(ptr);
			count++;
		}
		else if (strncmp(line, "\n", 1) && count != 6)
		{
			ft_putstr_fd("Error\nIncorrect or missing map lines\n", 2);
			free (line);
			return (1);
		}
		if (count == 6)
		{
			free(line);
			break ;
		}
		//ft_putstr_fd("line %d read successfully and is %s\n", n, line);	
		n++;
	}
	// if (!map->no || !map->so ||!map->we ||!map->ea || !map->f || !map->c)
	// {
	// 	ft_putstr_fd("Error\nMap file missing necessary data\n", 2);
	// 	return (1);
	// }
	printf("Path to NO texture is %s", map->no);
	printf("Path to SO texture is %s", map->so);
	printf("Path to WE texture is %s", map->we);
	printf("Path to EA texture is %s", map->ea);
	printf("Floor color is %s", map->f);
	printf("Ceiling color is %s", map->c);
	line = get_next_line(map->fd);
	while (!ft_strncmp(line, "\n", 1))
	{
		free(line);
		line = get_next_line(map->fd);
	}
	while (line)
	{
		line_copy = ft_strdup(line);
		printf("copied line is %s", line_copy);
		vec_push(&map->map_copy, &line_copy);
		free(line);
		line = get_next_line(map->fd);
		map->line_count++;
	}
	//printf("\nLine 0 is\n%s\n", *(char **)(vec_get(&map->map_copy, 0)))
	if (check_lines(map))
		return (1);
	printf("\nMap size is %d lines\n", map->line_count);
	printf("\nDone reading file\n");
	return (0);
}

void	initialize_map_values(t_map *map)
{
	map->no = NULL;
	map->so = NULL;
	map->ea = NULL;
	map->we = NULL;
	map->f = NULL;
	map->c = NULL;
	vec_new(&map->map_copy, 0, sizeof(char *));
	map->line_count = 0;
}

int	main(int argc, char **argv)
{
	t_map	map;

	if (check_arguments (argc, argv, &map))
		exit (EXIT_FAILURE);
	initialize_map_values(&map);
	if (validate_map(&map))
		exit(EXIT_FAILURE);
	printf("Map validated successfully\n");
	free_map_info(&map);
	return (0);
	//exit(EXIT_SUCCESS);
}
