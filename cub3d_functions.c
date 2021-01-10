/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 19:13:43 by mouassit          #+#    #+#             */
/*   Updated: 2020/12/16 10:24:35 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_line_map(const char *str)
{
	size_t i;
	int error;

	i = 0;
	if ((ft_strlen(str) == 0) && (check == 0))
		error = 1;
	while (i != ft_strlen(str))
	{
		if ((str[i] != ' ') && (str[i] != '0')
				&& (str[i] != '1') && (str[i] != '2'))
		{
			check = 0;
			error = 0;
			break ;
		}
		else
		{
			check = 1;
			error = 1;
		}
		i++;
	}
	if (check == 1)
		error = ft_continue_check(str, error);
	return (error);
}

int		ft_same(char *str)
{
	int j;

	j = 1;
	if(ft_strlen(str) == 1)
		if((str[0] == 'R') || (str[0] == 'S') || (str[0] == 'F') || str[0] == 'C')
			j = 0;
		if(ft_strlen(str) == 2)
			if(((str[0] == 'N') && (str[1] == 'O')) || ((str[0] == 'S') && (str[1] == 'O'))
			|| ((str[0] == 'W') && (str[1] == 'E')) || ((str[0] == 'E') && (str[1] == 'A')))
				j = 0;
	return (j);
}

int		ft_check_errors(const char *str)
{
	char	**no_space;
	char	**no_vrg;
	size_t	i;
	int		error;

	no_space = ft_split(str, ' ');
	no_vrg = ft_split(str, ',');
	i = 0;
	error = 0;
		if (((str[0] == 'R') || (str[0] == 'F') || (str[0] == 'C') || (str[0] == 'S') || (str[0] == 'E')) && (ft_same(no_space[0]) == 0))
		{
			if(str[0] == 'R')
			{
				while (i != ft_strlen(str))
				{
					if (!(no_space[i]))
					{
						i = i - 1;
						break ;
					}
					i++;
				}
				error = ft_check_letter(no_space, i);
			}
			if(str[0] == 'F')
			{
				i = 0;
				while (i != ft_strlen(str))
				{
					if (!(no_vrg[i]))
					{
						i = i - 1;
						break ;
					}
					i++;
				}
				error =	ft_continue_vrg_f(no_vrg,i,str);
				if(error == 1)
					check_f = 1;
			}
			if(str[0] == 'C')
			{
				i = 0;
				while (i != ft_strlen(str))
				{
					if (!(no_vrg[i]))
					{
						i = i - 1;
						break ;
					}
					i++;
				}
				error =	ft_continue_vrg_c(no_vrg,i,str);
				if(error == 1)
					check_c = 1;
			}
			if(str[0] == 'S')
			{
				i = 0;
				while (no_space[i] != '\0')
					i++;
				if((ft_strlen(no_space[0]) == 1) && (i > 1) && ((no_space[1][0] == '.') && ((no_space[1][1] == '/'))))
				{
					if((no_space[i - 1][ft_strlen(no_space[i - 1]) - 1] == 'm') && (no_space[i - 1][ft_strlen(no_space[i - 1]) - 2] == 'p')
						&& (no_space[i - 1][ft_strlen(no_space[i - 1]) - 3] == 'x') && (no_space[i - 1][ft_strlen(no_space[i - 1]) - 4] == '.'))
						{
							error = 1;
							textur_sprite = no_space[i - 1];
						}
					else
					{
						error = 0;
						text_error = "type file xpm in S";
					}
					if(error == 1)
						check_s = 1;
				}
				else
					text_error = "Info invalid in S";
			}
			if((str[0] == 'E') && (str[1] == 'A'))
			{
				i = 0;
				while (no_space[i] != '\0')
					i++;
				if((ft_strlen(no_space[0]) == 2) && (i > 1) && ((no_space[1][0] == '.') && ((no_space[1][1] == '/'))))
				{
					if((no_space[i - 1][ft_strlen(no_space[i - 1]) - 1] == 'm') && (no_space[i - 1][ft_strlen(no_space[i - 1]) - 2] == 'p')
						&& (no_space[i - 1][ft_strlen(no_space[i - 1]) - 3] == 'x') && (no_space[i - 1][ft_strlen(no_space[i - 1]) - 4] == '.'))
						{
							error = 1;
							textur_ea = no_space[i - 1];
						}
					else
					{
						error = 0;
						text_error = "type file xpm in EA";
					}
					if(error == 1)
						check_ea = 1;
				}
				else
					text_error = "Info invalid in EA";
			}
		}
		else
		{
			text_error = "lack the identifier";
			error = ft_check_line_map(str, info);
		}
	return (error);
}

int		ft_check_one_on_line(char *firstr, char *endstr)
{
	int error;
	size_t i;

	error = 0;
	i = 0;
	while (i != ft_strlen(firstr))
	{
		if ((firstr[i] != '1') && (firstr[i] != ' '))
		{
			error = 1;
			break ;
		}
		i++;
	}
	if (error == 0)
		error = ft_endstr(endstr);
	return (error);
}

int	ft_check_all_errors(const char *str)
{
	char	**separ_lines;
	int		error;

	error = 0;
	if (ft_check_errors(str) == 1)
	{
		separ_lines = ft_split_n(get, 'c');
		if (get_y > 1)
		{
			if (ft_check_one_on_line(separ_lines[0],
						separ_lines[get_y - 1]) == 0)
				error = ft_continue_line(separ_lines);
			else
				error = 1;
			if (error == 1)
				write(1, "Error\n", 7);
		}
		else
			write(1, "Error\n", 6);
	}
	else
	{
		write(1, "Error\n", 6);
		error = 1;
	}
	return(error) ;
}
