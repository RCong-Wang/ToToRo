#include "Item.h"
#include "Playerrole.h"
#include "constants.h"
#include <stdio.h>
#include <math.h>

Item::Item(const char* path, int n, int type, SDL_Renderer* ren) : Role(path, n, ren)
{
	itemType = type;
}

Uint32 Item::ItemTimer(Uint32 interval, void* param)//動圖片抓到的不是這個，是Role的
{
	Item* p = (Item*)param;

	if (p->gettime() != 0 && p->gettime() < 1000)
	{
		p->setframe((p->getframe() + 1) % p->getnum());  // image frame	
		return interval;
	}
	else
	{
		return 0;
	}

}
void Item::draw(int xx, int yy) {
	setPosition(xx, yy);
	SDL_Rect s, d;
	s.x = 0;
	s.y = 0;
	s.w = getWidth();
	s.h = getHeight();
	d.x = xx;
	d.y = yy;
	d.w = getWidth();
	d.h = getHeight();
	setimage(s, d);
}
void Item::draw2(int xx, int yy, int ix, int iy,int zoom,int px,int py, int n) {//xx&yy=絕對座標位置 ix&iy=背景座標位置 zoom=縮放倍率(長寬一致)
	if (um) {
		setPosition(px-15, py - getHeight2() + 25); //物品在人物上方
		um_time += 1;
		actionStatus = fly; //改變人物狀態
		printf("draw2\n");
		if (n == 1) 
		{
			if (um_time == 350) { //雨傘時間修改
				um = false;
				exist = false;
				um_time = 0;
				actionStatus = none; //改變人物狀態
			}
		}
		else 
		{
			if (um_time == 15000000000) { //雨傘時間修改
				um = false;
				exist = false;
				um_time = 0;
				actionStatus = none; //改變人物狀態
			}
		}
	}
	else {
		setPosition(xx - zoom*ix, yy - zoom*iy);
		//setPosition(100 - ix, 1080 - 500 - iy + 540);
		//printf_s("%d\t%d", getX(), getY());
	}

	Role::draw2(); //傳給draw2畫出來

}
void Item::setexist(bool e)
{
	exist = e;
}
bool Item::getexist()
{
	return exist;
}
void Item::setItem(bool e)
{
	item = e;
}
bool Item::getItem()//拿到Item
{
	return item;
}
void Item::touchItem(Playerrole& pl)
{
	if (pl.getX() < getX()) {//玩家位於物體的左側
		if (pl.getY() < getY()) {//玩家位於物體的上方
			if (getX() - pl.getX() < pl.getWidth2()) {
				if (getY() - pl.getY() < pl.getHeight2()) {
					//碰到
					//setexist(false);
					item = true;
					printf_s("item=true");
					itemOption(pl);
					printf_s("goto itemOption");



				}
				else if (getY() - pl.getY() == pl.getHeight2()) {
					//碰到

				}
				else {
					//沒碰到

				}
			}
			else if (getX() - pl.getX() == pl.getWidth2()) {
				if (getY() - pl.getY() < pl.getHeight2()) {
					//沒碰到(先當沒碰到)

				}
				else if (getY() - pl.getY() == pl.getHeight2()) {
					//沒碰到(先當沒碰到)

				}
				else {
					//沒碰到

				}
			}
			else {
				//沒碰到

			}
		}
		else if (pl.getY() == getY()) {
			if (getX() - pl.getX() < pl.getWidth2()) {
				//碰到
				//setexist(false);
				item = true;
				itemOption(pl);
			}
			else if (getX() - pl.getX() == pl.getWidth2()) {
				//沒碰到(先當沒碰到)

			}
			else {
				//沒碰到

			}
		}
		else {
			if (getX() - pl.getX() < pl.getWidth2()) {
				if (pl.getY() - getY() < getHeight()) {
					//碰到
					//setexist(false);
					item = true;
					itemOption(pl);
				}
				else if (pl.getY() - getY() == getHeight2()) {
					//先當沒碰到

				}
				else {
					//沒碰到

				}
			}
			else if (getX() - pl.getX() == pl.getWidth2()) {
				if (pl.getY() - getY() < getHeight()) {
					//先當沒碰到

				}
				else if (pl.getY() - getY() < getHeight()) {
					//先當沒碰到

				}
				else {
					//沒碰到

				}
			}
			else {
				//沒碰到

			}
		}

	}
	else if (pl.getX() == getX()) {
		if (pl.getY() < getY()) {
			if (getY() - pl.getY() < pl.getHeight2()) {
				//碰到
				//setexist(false);
				item = true;
				itemOption(pl);

			}
			else if (getY() - pl.getY() == pl.getHeight2()) {
				//碰到
				//setexist(false);
			}
			else {
				//沒碰到

			}

		}
		else if (pl.getY() == getY()) {
			//碰到
			//setexist(false);
			item = true;
			itemOption(pl);
		}
		else {
			if (pl.getY() - getY() < getHeight2()) {
				//碰到
				//setexist(false);
				item = true;
				itemOption(pl);
			}
			else if (pl.getY() - getY() == getHeight2()) {
				//先當沒碰到

			}
			else {
				//沒碰到

			}
		}
	}
	else {
		if (pl.getY() < getY()) {
			if (pl.getX() - getX() < pl.getWidth2()) {
				if (getY() - pl.getY() < pl.getHeight2()) {
					//碰到
					//setexist(false);
					item = true;
					itemOption(pl);


				}
				else if (getY() - pl.getY() == pl.getHeight2()) {
					//碰到
					//setexist(false);

				}
				else {
					//沒碰到
					printf_s("3");

				}
			}
			else if (pl.getX() - getX() == getWidth2()) {
				if (getY() - pl.getY() < pl.getHeight2()) {
					//先當沒碰到

				}
				else if (getY() - pl.getY() == pl.getHeight2()) {
					//先當沒碰到

				}
				else {
					//沒碰到

				}
			}
			else {
				//沒碰到

			}
		}
		else if (pl.getY() == getY()) {
			if (pl.getX() - getX() < getWidth2()) {
				//碰到
				//setexist(false);
				item = true;
				itemOption(pl);
			}
			else if (pl.getX() - getX() == getWidth2()) {
				//先當沒碰到

			}
			else {
				//沒碰到

			}
		}
		else {
			if (pl.getX() - getX() < pl.getWidth2()) {
				if (pl.getY() - getY() < getHeight2()) {
					//碰到
					//setexist(false);
					printf_s("1");
					item = true;
					itemOption(pl);
				}
				else if (pl.getY() - getY() == getHeight2()) {
					//先當沒碰到
				}
				else {
					//沒碰到
				}
			}
			else if (pl.getX() - getX() == getWidth2()) {
				if (pl.getY() - getY() < getHeight2()) {
					//先當沒碰到
				}
				else if (pl.getY() - getY() == getHeight2()) {
					//先當沒碰到
				}
				else {
					//沒碰到
				}
			}
			else {
				//沒碰到
			}
		}
	}
}
void Item::itemOption(Playerrole& pl)
{
	//printf_s("itemOption");
	if (item = true) {
		switch (itemType)
		case 1:
			um = true;
			//itemPosition = 1; //物品在人物上方
			//itemMove(pl);


	}
	/*
	else
		itemPosition = 0;
		*/

}
/*
void Item::itemMove(Playerrole& pl)
{
	//printf_s("itemMove");
	switch (itemPosition) {
	case 0:
		break;
	case 1:
		um = true;
		//printf_s("%d\t%d",pl.getY(),getY());
		//item跑到人物上面
	}
	itemPosition = 0;
}
*/

/*
void Item::Action(Playerrole& pl)
{
	switch (playerAction) {
	case 1:
		fly = true;
		//設定pl的動作
	}
}*/

Item::~Item() {}