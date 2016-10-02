/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 15:29:18 by vroussea          #+#    #+#             */
/*   Updated: 2016/10/02 18:31:54 by vroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	raycaster(t_env *env)
{
	int		x;
	double	crtray;

	x = 0;
	while(x < env->sx)
	{
		currentray = 2 * x / (double)(env->sx) - 1;

		x++;
	}
}

int dda(t_env *env)
{
	int	hit;
	int	side;
	int	x;
	int	y;

	x = (int)env->pos_x;
	y = (int)env->pos_y;
	hit = 0;
	//perform DDA
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				x += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				y += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (worldMap[mapX][mapY] > 0)
				hit = 1;
		}
	return (side);
}
//calculate ray position and direction
double cameraX = 2  x / double(w) - 1; //x-coordinate in camera space
double rayPosX = posX;
double rayPosY = posY;
double rayDirX = dirX + planeX  cameraX;
double rayDirY = dirY + planeY  cameraX;
//which box of the map we're in
int mapX = int(rayPosX);
int mapY = int(rayPosY);

//length of ray from current position to next x or y-side
double sideDistX;
double sideDistY;

//length of ray from one x or y-side to next x or y-side
double deltaDistX = sqrt(1 + (rayDirY  rayDirY) / (rayDirX  rayDirX));
double deltaDistY = sqrt(1 + (rayDirX  rayDirX) / (rayDirY  rayDirY));
double perpWallDist;

//what direction to step in x or y-direction (either +1 or -1)
int stepX;
int stepY;

int hit = 0; //was there a wall hit?
int side; //was a NS or a EW wall hit?
//calculate step and initial sideDist
if (rayDirX < 0)
{
	stepX = -1;
	sideDistX = (rayPosX - mapX)  deltaDistX;
}
else
{
	stepX = 1;
	sideDistX = (mapX + 1.0 - rayPosX)  deltaDistX;
}
if (rayDirY < 0)
{
	stepY = -1;
	sideDistY = (rayPosY - mapY)  deltaDistY;
}
else
{
	stepY = 1;
	sideDistY = (mapY + 1.0 - rayPosY)  deltaDistY;
}
//Calculate distance projected on camera direction (oblique distance will give fisheye effect!)
if (side == 0) perpWallDist = (mapX - rayPosX + (1 - stepX) / 2) / rayDirX;
else           perpWallDist = (mapY - rayPosY + (1 - stepY) / 2) / rayDirY;

//Calculate height of line to draw on screen
int lineHeight = (int)(h / perpWallDist);

//calculate lowest and highest pixel to fill in current stripe
int drawStart = -lineHeight / 2 + h / 2;
if(drawStart < 0)drawStart = 0;
int drawEnd = lineHeight / 2 + h / 2;
if(drawEnd >= h)drawEnd = h - 1;

//choose wall color
ColorRGB color;
switch(worldMap[mapX][mapY])
{
	case 1:  color = RGB_Red;  break; //red
	case 2:  color = RGB_Green;  break; //green
	case 3:  color = RGB_Blue;   break; //blue
	case 4:  color = RGB_White;  break; //white
	default: color = RGB_Yellow; break; //yellow
}

//give x and y sides different brightness
if (side == 1) {color = color / 2;}

//draw the pixels of the stripe as a vertical line
verLine(x, drawStart, drawEnd, color);
//timing for input and FPS counter
oldTime = time;
time = getTicks();
double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
print(1.0 / frameTime); //FPS counter
redraw();
cls();

//speed modifiers
double moveSpeed = frameTime  5.0; //the constant value is in squares/second
double rotSpeed = frameTime  3.0; //the constant value is in radians/second
readKeys();
//move forward if no wall in front of you
if (keyDown(SDLK_UP))
{
	if(worldMap[int(posX + dirX  moveSpeed)][int(posY)] == false) posX += dirX  moveSpeed;
	if(worldMap[int(posX)][int(posY + dirY  moveSpeed)] == false) posY += dirY  moveSpeed;
}
//move backwards if no wall behind you
if (keyDown(SDLK_DOWN))
{
	if(worldMap[int(posX - dirX  moveSpeed)][int(posY)] == false) posX -= dirX  moveSpeed;
	if(worldMap[int(posX)][int(posY - dirY  moveSpeed)] == false) posY -= dirY  moveSpeed;
}
//rotate to the right
if (keyDown(SDLK_RIGHT))
{
	//both camera direction and camera plane must be rotated
	double oldDirX = dirX;
	dirX = dirX  cos(-rotSpeed) - dirY  sin(-rotSpeed);
	dirY = oldDirX  sin(-rotSpeed) + dirY  cos(-rotSpeed);
	double oldPlaneX = planeX;
	planeX = planeX  cos(-rotSpeed) - planeY  sin(-rotSpeed);
	planeY = oldPlaneX  sin(-rotSpeed) + planeY  cos(-rotSpeed);
}
//rotate to the left
if (keyDown(SDLK_LEFT))
{
	//both camera direction and camera plane must be rotated
	double oldDirX = dirX;
	dirX = dirX  cos(rotSpeed) - dirY  sin(rotSpeed);
	dirY = oldDirX  sin(rotSpeed) + dirY  cos(rotSpeed);
	double oldPlaneX = planeX;
	planeX = planeX  cos(rotSpeed) - planeY  sin(rotSpeed);
	planeY = oldPlaneX  sin(rotSpeed) + planeY  cos(rotSpeed);
}
}
