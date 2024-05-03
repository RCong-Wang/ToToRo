#include "Item.h"
#include "Playerrole.h"
#include "constants.h"
#include <stdio.h>
#include <math.h>

Item::Item(const char* path, int n, int type, SDL_Renderer* ren) : Role(path, n, ren)
{
	itemType = type;
}

Uint32 Item::ItemTimer(Uint32 interval, void* param)//�ʹϤ���쪺���O�o�ӡA�ORole��
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
void Item::draw2(int xx, int yy, int ix, int iy,int zoom,int px,int py, int n) {//xx&yy=����y�Ц�m ix&iy=�I���y�Ц�m zoom=�Y�񭿲v(���e�@�P)
	if (um) {
		setPosition(px-15, py - getHeight2() + 25); //���~�b�H���W��
		um_time += 1;
		actionStatus = fly; //���ܤH�����A
		printf("draw2\n");
		if (n == 1) 
		{
			if (um_time == 350) { //�B�ʮɶ��ק�
				um = false;
				exist = false;
				um_time = 0;
				actionStatus = none; //���ܤH�����A
			}
		}
		else 
		{
			if (um_time == 15000000000) { //�B�ʮɶ��ק�
				um = false;
				exist = false;
				um_time = 0;
				actionStatus = none; //���ܤH�����A
			}
		}
	}
	else {
		setPosition(xx - zoom*ix, yy - zoom*iy);
		//setPosition(100 - ix, 1080 - 500 - iy + 540);
		//printf_s("%d\t%d", getX(), getY());
	}

	Role::draw2(); //�ǵ�draw2�e�X��

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
bool Item::getItem()//����Item
{
	return item;
}
void Item::touchItem(Playerrole& pl)
{
	if (pl.getX() < getX()) {//���a����骺����
		if (pl.getY() < getY()) {//���a����骺�W��
			if (getX() - pl.getX() < pl.getWidth2()) {
				if (getY() - pl.getY() < pl.getHeight2()) {
					//�I��
					//setexist(false);
					item = true;
					printf_s("item=true");
					itemOption(pl);
					printf_s("goto itemOption");



				}
				else if (getY() - pl.getY() == pl.getHeight2()) {
					//�I��

				}
				else {
					//�S�I��

				}
			}
			else if (getX() - pl.getX() == pl.getWidth2()) {
				if (getY() - pl.getY() < pl.getHeight2()) {
					//�S�I��(����S�I��)

				}
				else if (getY() - pl.getY() == pl.getHeight2()) {
					//�S�I��(����S�I��)

				}
				else {
					//�S�I��

				}
			}
			else {
				//�S�I��

			}
		}
		else if (pl.getY() == getY()) {
			if (getX() - pl.getX() < pl.getWidth2()) {
				//�I��
				//setexist(false);
				item = true;
				itemOption(pl);
			}
			else if (getX() - pl.getX() == pl.getWidth2()) {
				//�S�I��(����S�I��)

			}
			else {
				//�S�I��

			}
		}
		else {
			if (getX() - pl.getX() < pl.getWidth2()) {
				if (pl.getY() - getY() < getHeight()) {
					//�I��
					//setexist(false);
					item = true;
					itemOption(pl);
				}
				else if (pl.getY() - getY() == getHeight2()) {
					//����S�I��

				}
				else {
					//�S�I��

				}
			}
			else if (getX() - pl.getX() == pl.getWidth2()) {
				if (pl.getY() - getY() < getHeight()) {
					//����S�I��

				}
				else if (pl.getY() - getY() < getHeight()) {
					//����S�I��

				}
				else {
					//�S�I��

				}
			}
			else {
				//�S�I��

			}
		}

	}
	else if (pl.getX() == getX()) {
		if (pl.getY() < getY()) {
			if (getY() - pl.getY() < pl.getHeight2()) {
				//�I��
				//setexist(false);
				item = true;
				itemOption(pl);

			}
			else if (getY() - pl.getY() == pl.getHeight2()) {
				//�I��
				//setexist(false);
			}
			else {
				//�S�I��

			}

		}
		else if (pl.getY() == getY()) {
			//�I��
			//setexist(false);
			item = true;
			itemOption(pl);
		}
		else {
			if (pl.getY() - getY() < getHeight2()) {
				//�I��
				//setexist(false);
				item = true;
				itemOption(pl);
			}
			else if (pl.getY() - getY() == getHeight2()) {
				//����S�I��

			}
			else {
				//�S�I��

			}
		}
	}
	else {
		if (pl.getY() < getY()) {
			if (pl.getX() - getX() < pl.getWidth2()) {
				if (getY() - pl.getY() < pl.getHeight2()) {
					//�I��
					//setexist(false);
					item = true;
					itemOption(pl);


				}
				else if (getY() - pl.getY() == pl.getHeight2()) {
					//�I��
					//setexist(false);

				}
				else {
					//�S�I��
					printf_s("3");

				}
			}
			else if (pl.getX() - getX() == getWidth2()) {
				if (getY() - pl.getY() < pl.getHeight2()) {
					//����S�I��

				}
				else if (getY() - pl.getY() == pl.getHeight2()) {
					//����S�I��

				}
				else {
					//�S�I��

				}
			}
			else {
				//�S�I��

			}
		}
		else if (pl.getY() == getY()) {
			if (pl.getX() - getX() < getWidth2()) {
				//�I��
				//setexist(false);
				item = true;
				itemOption(pl);
			}
			else if (pl.getX() - getX() == getWidth2()) {
				//����S�I��

			}
			else {
				//�S�I��

			}
		}
		else {
			if (pl.getX() - getX() < pl.getWidth2()) {
				if (pl.getY() - getY() < getHeight2()) {
					//�I��
					//setexist(false);
					printf_s("1");
					item = true;
					itemOption(pl);
				}
				else if (pl.getY() - getY() == getHeight2()) {
					//����S�I��
				}
				else {
					//�S�I��
				}
			}
			else if (pl.getX() - getX() == getWidth2()) {
				if (pl.getY() - getY() < getHeight2()) {
					//����S�I��
				}
				else if (pl.getY() - getY() == getHeight2()) {
					//����S�I��
				}
				else {
					//�S�I��
				}
			}
			else {
				//�S�I��
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
			//itemPosition = 1; //���~�b�H���W��
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
		//item�]��H���W��
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
		//�]�wpl���ʧ@
	}
}*/

Item::~Item() {}