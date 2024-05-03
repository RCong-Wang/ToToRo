
#include "Role.h"
#include "Image.h"
#include <stdio.h>
#include "constants.h"
#include <iostream>
using namespace std;
Role::Role(){

}
Role::Role(const char* path, SDL_Renderer* ren)
{
	image.setPath(path);
	image.setRenderer(ren);
	image.setColorKey(NO_TRANSPARENT_BG);
	image.setCenterAngle({ 0,0 }, 0);
	image.setFlip(SDL_FLIP_NONE);
	image.setAlpha(255);

	image.generateTexture();

	renderer = ren;
	num = 1;
	frame = 0;
	hn = 1;
	wn = 1;
}

Role::Role(const char* path, int n, int hhn, int wwn, SDL_Renderer* ren)
{
	image.setPath(path);
	image.setRenderer(ren);
	image.setColorKey(NO_TRANSPARENT_BG);
	image.setCenterAngle({ 0,0 }, 0);
	image.setFlip(SDL_FLIP_NONE);
	image.setAlpha(255);

	image.generateTexture();

	renderer = ren;
	num = n;
	frame = 0;
	hn = hhn;
	wn = wwn;
}

Role::Role(const char* path, int n, int hhn, int wwn, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b)
{
	image.setPath(path);
	image.setRenderer(ren);
	image.setColorKey({ r, g, b });
	image.setCenterAngle({ 0,0 }, 0);
	image.setFlip(SDL_FLIP_NONE);
	image.setAlpha(255);

	image.generateTexture();

	renderer = ren;
	num = n;
	frame = 0;
	hn = hhn;
	wn = wwn;
}
Role::Role(const char* path, int n, SDL_Renderer* ren)
{
	num = n;
	image2 = new Image[num];

	for (int i = 0; i < num; i++)
	{
		char file[100];
		sprintf_s(file, 100, "%s%02d.png", path, i + 1);
		image2[i].setPath(file);
		image2[i].setRenderer(ren);
		image2[i].setColorKey(NO_TRANSPARENT_BG);
		image2[i].setCenterAngle({ 0,0 }, 0);
		image2[i].setFlip(SDL_FLIP_NONE);
		image2[i].setAlpha(255);

		image2[i].generateTexture();
	}
	w = image2[0].getWidth();
	h = image2[0].getHeight();
	renderer = ren;
	frame = 0;
	hn = 1;
	wn = 1;

}
Role::Role(const char* path, int n, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b)
{
	num = n;
	image2 = new Image[num];

	for (int i = 0; i < num; i++)
	{
		char file[100];
		sprintf_s(file, 100, "%s%02d.png", path, i + 1);
		image2[i].setPath(file);
		image2[i].setRenderer(ren);
		image2[i].setColorKey({ 255,255,255 });
		image2[i].setCenterAngle({ 0,0 }, 0);
		image2[i].setFlip(SDL_FLIP_NONE);
		image2[i].setAlpha(255);

		image2[i].generateTexture();
	}
	w = image2[0].getWidth();
	h = image2[0].getHeight();
	renderer = ren;
	frame = 0;
	hn = 1;
	wn = 1;
}
void Role::close()
{
	// Free loaded image	
	if (image2 == NULL) {
		image.close();
	}
	else {
		for (int i = 0; i < num; i++)
		{
			image2[i].close();
		}
	}

	// Remove timer in case the call back was not called
	SDL_RemoveTimer(timerID);
}

void Role::setPosition(int xx, int yy)
{
	x = xx;
	y = yy;
}

int Role::getWidth()
{
	return image.getWidth() / wn;
}
int Role::getWidth2()
{
	return w;
}
int Role::getHeight()
{
	return image.getHeight() / hn;
}
int Role::getHeight2()
{
	return h;
}
void Role::draw()
{
	int wc = frame % wn;
	int hc = frame / wn;

	SDL_Rect s, d;
	s.x = getWidth() * wc;
	s.y = getHeight() * hc;
	s.w = getWidth();
	s.h = getHeight();
	d.x = x;
	d.y = y;
	d.w = s.w;
	d.h = s.h;

	image.setSrcRegion(s);
	image.setDstRegion(d);

	image.draw();
}
void Role::draw2(){
	SDL_Rect d;
	d.x = x;
	d.y = y;
	d.w = image2[frame].getWidth();
	d.h = image2[frame].getHeight();

	image2[frame].setSrcRegion({ ALLREGION });
	image2[frame].setDstRegion(d);

	image2[frame].draw();
}

void Role::draw3(int xx,int yy,int ww,int hh)
{
	int wc = frame % wn;
	int hc = frame / wn;
	setX(xx);
	setY(yy);
	SDL_Rect s, d;
	s.x = getWidth() * wc;
	s.y = getHeight() * hc;
	s.w = getWidth();
	s.h = getHeight();
	d.x = xx;
	d.y = yy;
	d.w = ww;
	d.h = hh;

	image.setSrcRegion(s);
	image.setDstRegion(d);

	image.draw();
}
void Role::draw4(int ix,int iy,int zoom) {
	SDL_Rect d;
	d.x = x-(2*ix);
	d.y = y-(2*iy);
	d.w = image2[frame].getWidth();
	d.h = image2[frame].getHeight();

	image2[frame].setSrcRegion({ ALLREGION });
	image2[frame].setDstRegion(d);

	image2[frame].draw();
}
Uint32 Role::changeData(Uint32 interval, void* param)
{
	Role* p = (Role*)param;

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

void Role::startTimer(Uint32 t)
{
	time = t;
	timerID = SDL_AddTimer(time, changeData, this); // Set Timer callback
}

void Role::stopTimer()
{
	time = 0;
}

void Role::setCenterAngle(SDL_Point c, double a)
{
	image.setCenterAngle(c, a);
}

void Role::setFlip(SDL_RendererFlip f)
{
	image.setFlip(f);
}

void Role::setAlpha(int a)
{
	image.setAlpha(a);
}

double Role::getAngle()
{
	return image.getAngle();
}

int Role::getAlpha()
{
	return image.getAlpha();
}


//Ren 4/23
int Role::getX() {
	return x;
}
int Role::getY() {
	return y;
}
void Role::setimage(SDL_Rect s, SDL_Rect d) {
	image.setSrcRegion(s);
	image.setDstRegion(d);

	image.draw();
}
void Role::setpath(char* pa){
	image.close();
	image.setPath(pa);
	image.generateTexture();
}
// Ren 4/24
Uint32 Role::gettime() {
	return time;
}
void Role::settime(Uint32 t) {
	time = t;
}
void Role::settimeID(SDL_TimerID t) {
	timerID = t;
}
int Role::getframe() {
	return frame;
}
void Role::setframe(int f) {
	frame = f;
}
int Role::getnum() {
	return num;
}
void Role::setX(int xx) {
	x = xx;
}
void Role::setY(int yy) {
	y = yy;
}


Role::~Role()
{
	close();
}