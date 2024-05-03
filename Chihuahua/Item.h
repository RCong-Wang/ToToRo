#pragma once
#include "Playerrole.h"
#include "Image.h"
#include <SDL.h>
#include "floor.h"

class Item :
	public Role
{
public:
	Item(const char* path, int n, int type, SDL_Renderer* ren);
	void touchItem(Playerrole& pl); //判斷有沒有碰到
	void setexist(bool);//數時間十秒Item會消失
	bool getexist();
	void itemOption(Playerrole& pl);
	void setItem(bool);
	bool getItem();
	//void setFly(bool);
	//bool getFly();
	void draw(int xx, int yy);
	void draw2(int xx, int yy, int ix, int iy, int zoom,int px, int py, int n); //xx=人物X軸 yy=人物Y軸 ix = 背景的X軸 iy = 背景的Y軸





	//void startTimer(Uint32 t);
	~Item();
private:
	int playerAction;
	int itemType; //道具種類
	int itemPosition;
	int item = false;
	//bool fly = false;
	bool exist = true;
	bool um = false;
	int um_time = 0;
	static Uint32 ItemTimer(Uint32 interval, void* param); // Timer callback
};
#pragma once
