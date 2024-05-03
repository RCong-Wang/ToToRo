#include "background.h"
#include "Playerrole.h"
#include <SDL.h>
#include "Image.h"
#include <iostream>
#include <string.h>
#include <iostream>
using namespace std;

Background::Background() 
{

}

Background::Background(const char* pa, SDL_Renderer* ren):Role(pa,ren){

	strncpy_s(path, pa, 21);
	path[22] = '\0';
	sprintf_s(file, 100, "%s%02d.png", path, projection);
	SDL_GetCurrentDisplayMode(0, &DM);
	width = DM.w;
	heigh = DM.h;
}

void Background::draw() {
	SDL_GetCurrentDisplayMode(0, &DM);
	width = DM.w;
	heigh = DM.h;
	SDL_Rect s, d;
	s.x = 0;
	s.y = 0;
	s.w = getWidth();
	s.h = getHeight();
	d.x = 0;
	d.y = 0;
	d.w = DM.w;
	d.h = DM.h;
	setimage(s, d);

}
void Background::draw2(int vx,int vy) {
	
	SDL_GetCurrentDisplayMode(0, &DM);
	width = DM.w;
	heigh = DM.h;
	SDL_Rect s, d;
	//X
	imageX += vx;
	if (imageX < 0) {
		imageX = 0;
	}
	else if (imageX >= getWidth() / 2) {
		imageX = getWidth() / 2;
	}
	//Y
	imageY += vy;

	if (imageY> getHeight() / 2) {
		imageY = getHeight() / 2;
	}
	else if (imageY <0 ) {
		imageY = 0;
	}
	//printf_s("%d\n", imageY);
	s.x = imageX;
	s.y = imageY;
	s.w = getWidth() / 2;
	s.h = getHeight()/2;
	d.x = 0;
	d.y = 0;
	d.w = DM.w;
	d.h = DM.h;
	setimage(s, d);

}
void Background::setprojection(int posi) {
	projection = posi;
	changebackground();
}
void Background::changebackground(){
	sprintf_s(file, 100, "%s%02d.png", path, projection);
	setpath(file);
}

//Ren 4/24
int Background::getscreensize() {
	return width;
}
int Background::getscreenheigh() {
	return heigh;
}
int Background::getimageX() {
	return imageX;
}
int Background::getimageY() {
	return imageY;
}
void Background::setimageX(int xx) {
	imageX = xx;
}
void Background::setimageY(int yy) {
	imageY = yy;
}
Background::~Background(){
}