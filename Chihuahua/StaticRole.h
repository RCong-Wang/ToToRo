#pragma once

#include <SDL.h> // Using SDL
#include<iostream>
#include "Image.h"

class StaticRole
{
public:
	StaticRole(const char* path, SDL_Renderer* renderer);
	StaticRole(const char* path, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b);
	void close();
	void setPosition(int xx, int yy);
	int getWidth();
	int getHeight();
	void draw(SDL_Renderer* renderer);

	int getX();
	int getY();
	void setX(int);
	void setY(int);
	void move();

private:
	char path[100];
	Image image;
	int x;
	int y;
	int mVelX=0;
	int mVelY=0;
	int mX;
	int mY;
};


