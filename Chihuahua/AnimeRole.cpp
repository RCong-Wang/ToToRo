#include "AnimeRole.h"
#include "Image.h"
#include <stdio.h>
#include "constants.h"


#include "AnimeRole.h"
#include "Image.h"
#include <stdio.h>
#include "constants.h"


AnimeRole::AnimeRole(const char* path, int n, SDL_Renderer* renderer)
{
	num = n;
	image = new Image[num];

	for (int i = 0; i < num; i++)
	{
		char file[100];
		sprintf_s(file, 100, "%s%02d.png", path, i + 1);

		image[i].set(file, renderer);
	}

	frame = 0;
}

AnimeRole::AnimeRole(const char* path, int n, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b)
{
	num = n;
	image = new Image[num];

	for (int i = 0; i < num; i++)
	{
		char file[100];
		sprintf_s(file, 100, "%s%02d.png", path, i + 1);

		image[i].set(file, renderer, r, g, b);
	}

	frame = 0;
}

void AnimeRole::close()
{
	// Free loaded image	
	for (int i = 0; i < num; i++)
	{
		image[i].close();
	}

	// Remove timer in case the call back was not called	
	SDL_RemoveTimer(timerID);
}

void AnimeRole::setPosition(int xx, int yy)
{
	x = xx;
	y = yy;
}

int AnimeRole::getWidth()
{
	return image[frame].getWidth();
}

int AnimeRole::getHeight()
{
	return image[frame].getHeight();
}

void AnimeRole::draw(SDL_Renderer* renderer)
{
	SDL_Rect d, s;
	d.x = x;
	d.y = y;
	d.w = image[frame].getWidth();
	d.h = image[frame].getHeight();

	image[frame].draw(renderer, d, { ALLREGION });
}

Uint32 AnimeRole::changeData(Uint32 interval, void* param)
{
	AnimeRole* p = (AnimeRole*)param;

	if (p->time != 0)
	{
		p->frame = (p->frame + 1) % p->num;  // image frame	

		return interval;
	}
	else
	{
		return 0;
	}

}

void AnimeRole::startTimer(Uint32 t)
{
	time = t;
	timerID = SDL_AddTimer(time, changeData, this); // Set Timer callback
}

void AnimeRole::stopTimer()
{
	time = 0;
}

void AnimeRole::move()
{
	//Move the dot left or right
	x += mVelX;

	if (x >= 750 || x <= 0)
		x -= mVelX;
	
}
int AnimeRole::getVX()
{
	return mVelX;

}

int AnimeRole::getVY()
{
	return mVelY;
}

int AnimeRole::getY()
{
	return y;
}


void AnimeRole::setVX(int x)
{
	mVelX = x;
}

void AnimeRole::setVY(int y)
{
	mVelY = y;
}
void AnimeRole::jump() {
	if (y == 480)
		y -= 100;
}
void AnimeRole::down() {
	y += 5;
}