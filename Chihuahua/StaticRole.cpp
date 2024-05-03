#include "StaticRole.h"
#include "Image.h"
#include <stdio.h>
#include <iostream>
#include "constants.h"
using namespace std;

StaticRole::StaticRole(const char* path, SDL_Renderer* renderer)
{
	image.set(path, renderer);
}

StaticRole::StaticRole(const char* path, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b)
{
	image.set(path, renderer, r, g, b);
}

void StaticRole::close()
{
	image.close();
}

void StaticRole::setPosition(int xx, int yy)
{
	x = xx;
	y = yy;
	mX = image.getWidth()-400;
	mY = image.getHeight()-200;
}

int StaticRole::getWidth()
{
	return image.getWidth();
}

int StaticRole::getHeight()
{
	return image.getHeight();
}

void StaticRole::draw(SDL_Renderer* renderer)
{
	SDL_Rect d, s;
	d.x = x;
	d.y = y;
	d.w = image.getWidth();
	d.h = image.getHeight();

	image.draw(renderer, d, { mX,mY,150,150});
}

int StaticRole::getX()
{
	cout << mVelX;
	return mVelX;
}

int StaticRole::getY()
{
	return mVelY;
}

void StaticRole::setX(int x1)
{
	mVelX = x1;
}

void StaticRole::setY(int y1)
{
	mVelY = y1;
}

void StaticRole::move() {
	mX += mVelX;
	
	if(mX>= image.getWidth()-150 || mX<=0)
		mX-= mVelX;
}