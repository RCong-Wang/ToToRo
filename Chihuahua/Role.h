#pragma once
#include <SDL.h> // Using SDL
#include "Image.h"

class Role
{
public:
	Role();
	Role(const char* path, SDL_Renderer* ren);
	Role(const char* path, int n, SDL_Renderer* ren);
	Role(const char* path, int n, int hhn, int wwn, SDL_Renderer* ren);
	Role(const char* path, int n, int hhn, int wwn, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b);
	Role(const char* path, int n, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b);
	void close();
	void setPosition(int xx, int yy);
	int getWidth();
	int getHeight();

	void setCenterAngle(SDL_Point c, double a);
	void setFlip(SDL_RendererFlip f);
	void setAlpha(int a);
	double getAngle();
	int getAlpha();
	virtual void startTimer(Uint32 t);
	void stopTimer();


	//Ren 4/23
	virtual int getX();
	virtual int getY();
	void setimage(SDL_Rect s, SDL_Rect d);
	void setpath(char* pa);
	/* New in this example*/
	virtual void draw();  // change into virtual function
	virtual void draw2();
	virtual ~Role();
	// Ren 4/24
	Uint32 gettime();
	void settime(Uint32 t);
	void settimeID(SDL_TimerID t);
	int getframe();
	void setframe(int f);
	int getnum();
	virtual void setX(int xx);
	virtual void setY(int yy);
	int getWidth2();
	int getHeight2();
	void draw3(int xx,int yy, int ww, int hh);
	void draw4(int ix, int iy,int zoom);
	/* New in this example*/
protected:
	SDL_Renderer* renderer; // change into protected data member
	/*********************/
	Image image;
private:
	int num;
	int wn; // image number in width
	int hn; // image number in height
	int w, h;
	
	Image* image2;
	int frame;
	int x;
	int y;
	SDL_TimerID timerID;
	Uint32 time;
	static Uint32 changeData(Uint32 interval, void* param); // Timer callback 
};
