/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalev <akovalev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:11:45 by akovalev          #+#    #+#             */
/*   Updated: 2024/07/15 17:19:48 by akovalev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "Libft/libft.h"
# include "Libft/get_next_line_bonus.h"
# include "Libft/ft_printf.h"
# include <fcntl.h>
# include "MLX42/MLX42.h"

typedef struct s_map
{
	int			fd;
	const char	*filename;
	int			name_length;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*f;
	char		*c;
	t_vec		map_copy;
	int			line_count;
	char		**ceiling;
	char		**floor;
	int			start_pos;
}	t_map;

#endif
