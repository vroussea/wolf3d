/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 16:21:57 by vroussea          #+#    #+#             */
/*   Updated: 2016/09/20 15:59:31 by vroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "wolf.h"

static int	test_file(char *file)
{
	int		fd;
	int		ret;
	int		i;
	char	*line;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (0);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		i = 0;
		if (ret < 0 || line[i] == '\0')
			return (0);
		while (line[i] != '\0')
		{
			if (!ft_isdigit(line[i]) && line[i] != ' ' && line[i] != '-')
				return (0);
			if (line[i] == '-' && line[i + 1] == '-')
				return (0);
			i++;
		}
		ft_strdel(&line);
	}
	close(fd);
	return ((ret == -1 ? 0 : 1));
}

static int	test_size(int ***map)
{
	int	i;
	int	size;

	i = 1;
	size = *map[0][0];
	while ((*map)[i])
	{
		if (size != (*map)[i][0])
		{
			ft_tabdel((void ***)&(*map));
			return (0);
		}
		i++;
	}
	return (1);
}

static int	init_map(int ***map, char *file)
{
	int		size_y;
	char	*line;
	int		fd;
	int		ret;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (0);
	size_y = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		ft_strdel(&line);
		size_y++;
	}
	if (ret == -1 || size_y == 0)
		return (0);
	close(fd);
	if (!(*map = (int **)ft_memalloc(sizeof(int *) * (size_y + 1))))
		return (0);
	(*map)[size_y] = NULL;
	return (1);
}

static int	*line_filler(char *line, int *mapline)
{
	char	**tab;
	int		i;
	int		nb_int;

	if (!(tab = ft_strsplit(line, ' ')))
		return (NULL);
	nb_int = 0;
	while (tab[nb_int] != NULL)
		nb_int++;
	if (!(mapline = (int *)ft_memalloc(sizeof(int) * (nb_int + 1))))
	{
		ft_tabdel((void ***)&tab);
		return (NULL);
	}
	mapline[0] = nb_int;
	i = 0;
	while (tab[i])
	{
		mapline[i + 1] = ft_atoi(tab[i]);
		i++;
	}
	ft_tabdel((void ***)&tab);
	return (mapline);
}

int			file_reader(char *file, int ***map)
{
	int		fd;
	int		ret;
	char	*line;
	int		i;

	if ((init_map(map, file)) == 0)
		return (0);
	if (!test_file(file))
		return (0);
	i = 0;
	if ((fd = open(file, O_RDONLY)) == -1)
		return (0);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (!((*map)[i] = line_filler(line, (*map)[i])))
			return (0);
		ft_strdel(&line);
		i++;
	}
	if (!test_size(map))
		return (0);
	close(fd);
	return ((ret < 0) ? 0 : 1);
}
