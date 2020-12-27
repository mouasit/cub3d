/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drawing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 09:53:48 by mouassit          #+#    #+#             */
/*   Updated: 2020/12/19 09:53:52 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	deal_key_release()
{
	turn_direction = 0;
	walk_direction = 0;
	return(0);
}

int deal_key(int key)
{
	if(key == 126)
		walk_direction = 1;
	if(key == 125)
		walk_direction = -1;
	if(key == 124)
		turn_direction = 1;
	if(key == 123)
		turn_direction = -1;
	ft_drawing();
	return(0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void	ft_draw_rays(int rays_angle)
{
	int i;
	int m;

	i = 0;

	while(i != rays_angle / 2)
	{
		m = 0;
		while(m != 30)
		{
			loop_x = x + 1 + cos(retation_angle + i * (M_PI / 180)) * m;
			loop_y = y + 1 + sin(retation_angle	+ i * (M_PI / 180)) * m;
			my_mlx_pixel_put(&img,loop_x,loop_y,0xFF0000);
			m++;
		}
		i++;
	}
	i = 0;
	while(i != rays_angle / 2)
	{
		m = 0;
		while(m != 30)
		{
			loop_x = x + 1 + cos(retation_angle - i * (M_PI / 180)) * m;
			loop_y = y + 1 + sin(retation_angle	- i * (M_PI / 180)) * m;
			my_mlx_pixel_put(&img,loop_x,loop_y,0xFF0000);
			m++;
		}
		i++;
	}
}

int	ft_normalaize_angle(int angle)
{
	int fo_v;
	fo_v = 2 * M_PI;
	angle = angle % fo_v;
	if(angle < 0)
		angle = fo_v + angle;
	return(angle);
}

void	ft_cast()
{
	 closet_one_y = (y / tile_size) * tile_size;
	 if(is_ray_facing_down == 1)
		 closet_one_y = closet_one_y + tile_size;
	 else
	 	closet_one_y = closet_one_y + 0;
	 closet_one_x = x + ((y - closet_one_x) / tan(ray_angle));
	 y_step = tile_size;
	 x_step = tile_size / tan(ray_angle);
}

void	ft_check_ray_face()
{
	if((ray_angle > 0) && (ray_angle < M_PI))
	{
		is_ray_facing_down = 1;
		is_ray_facing_up = 0;
	}
	else
	{
		is_ray_facing_down = 0;
		is_ray_facing_up = 1;
	}
	if((ray_angle < (0.5 * M_PI)) || (ray_angle > (1.5 * M_PI)))
	{
		is_ray_facing_right = 1;
		is_ray_facing_left = 0;
	}
	else
	{
		is_ray_facing_right = 0;
		is_ray_facing_left = 1;
	}
}

void	ft_draw_line()
{
	int m;

	m = 0;
	while(m != 30)
	{
		loop_x = x + 1 + cos(retation_angle) * m;
		loop_y = y + 1 + sin(retation_angle) * m;
		my_mlx_pixel_put(&img,loop_x,loop_y,0xFF0000);
		m++;
	}
	ray_angle = ft_normalaize_angle(ray_angle);
	ft_check_ray_face();
	ft_cast();
	//ft_draw_rays(60);
}

int     ft_has_wallat(float i, float j)
{
    int wallat;
    int position_x;
    int position_y;

    wallat = 0;
    position_x = (i / tile_size);
    position_y = (j / tile_size);
    if(map[position_y][position_x] == '1')
        wallat = 1;
    else
        wallat = 0;
    return(wallat);
}

void	ft_draw_player()
{
	new_playerx = x + cos(retation_angle) * move_step * walk_direction;
	new_playery = y + sin(retation_angle) * move_step * walk_direction;
    if(ft_has_wallat(new_playerx, new_playery) == 0)
    {
        x = new_playerx;
        y = new_playery;
        my_mlx_pixel_put(&img, x, y, 0x008000);
    }
}

void	ft_draw_map()
{
	int i;
	int j;
	int t;
	int r;
	int color;

	i = 0;
	j = 0;
	color = 0;
	while(map[j])
	{
		i = 0;
		while(map[j][i])
		{
			if(map[j][i] == '1')
				color = 0x808080;
			else
			{
				if(map[j][i] == '0')
					color = 0xFFFFFF;
				else
				{
					if(map[j][i] == '2')
						color = 0xFFFFFF;
					else
						color = 0;
				}
			}
			r = 0;
			while(r != tile_size)
			{
				t = 0;
				while(t != tile_size)
				{
					my_mlx_pixel_put(&img, (tile_size * i) + t, (tile_size * j) + r, color);
					t++;
				}
				r++;
			}
			if(map[j][i] == '2' && x == 0)
			{
				x = (tile_size * i) + tile_size / 2;
				y = (tile_size * j) + tile_size / 2;
			}
			i++;
		}
		j++;
	}
}

void	ft_drawing()
{
	retation_angle = M_PI / 2 + (turn_direction + stock_direction)  * 10 * (M_PI / 180);
	ray_angle = retation_angle - ((60 * M_PI / 180) / 2);
	move_step = 5;
	stock_direction = turn_direction + stock_direction;
	stock_walk = walk_direction + stock_walk;
	ft_draw_map();
	ft_draw_player();
	ft_draw_line();
	move_step = 0;
	mlx_put_image_to_window(mlx_ptr, win_ptr, img.img, 0, 0);
	mlx_hook(win_ptr,2,0,&deal_key,&img);
	mlx_hook(win_ptr,3,0,&deal_key_release,&img);
}

void	ft_window(char **resolution)
{
	x = 0;
	y = 0;
	width_window = ft_atoi(resolution[0]);
	height_window = ft_atoi(resolution[1]);
	mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, width_window, height_window, "cub3d");
	img.img = mlx_new_image(mlx_ptr, width_window, height_window);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,&img.endian);
	ft_drawing();
	mlx_loop(mlx_ptr);
}