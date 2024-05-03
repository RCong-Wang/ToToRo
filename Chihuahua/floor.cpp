#include "floor.h"
#include "constants.h"
#include "Playerrole.h"
#include "Star.h"
#include <stdio.h>
#include <math.h>

Flor::Flor() {
	//printf_s("good");
}
Flor::Flor(const char* path, SDL_Renderer* ren, double fr, bool si,int num) :Role(path, ren) {
	number = num;
	dist = 0;
	tt = 0;
	friction = fr;
	silp = si;
	appear = true;
	thro = false;
	turn = 0;
	reverse = false;
}

void Flor::draw(int xx, int yy, int dis) {
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
void Flor::draw2(int xx, int yy, int ix, int iy, int zoom) {//xx&yy=絕對座標位置 ix&iy=背景座標位置 zoom=縮放倍率(長寬一致)
	//相對座標= 絕對座標-縮放倍率*背景座標
	if (appear) {
		if (xx - zoom * ix > 0 || xx - zoom * ix < 1920) {
			if (yy - zoom * iy > 0 || yy - zoom * iy < 1080) {
				setPosition(xx - zoom * ix, yy - zoom * iy);
				SDL_Rect s, d;
				s.x = 0;
				s.y = 0;
				s.w = getWidth();
				s.h = getHeight();
				d.x = getX();
				d.y = getY();
				d.w = getWidth();
				d.h = getHeight();
				setimage(s, d);
			}
		}
	}
}
void Flor::draw3(int xx, int yy, int ix, int iy, int zoom, int dis, int speed, bool XY, bool back, bool reverse) {
	//xx&yy=絕對座標位置 ix&iy=背景座標位置 zoom=縮放倍率(長寬一致) disX=移動距離 speed=移動速度 XY(true)=左右移動 back(true)=會回彈 reverse(true)=反向移動(下到上or右到左)
	//相對座標= 絕對座標-縮放倍率*背景座標
	int dx = 0, dy = 0;
	if (XY) {
		dx = dist % dis;
	}
	else {
		dy = dist % dis;
		//printf_s("%d\n",dy);
	}
	//printf_s("%d\t%d\t%d\t%d\n", dist, dis, dist % dis, dy);
	if (back) {
		//printf_s("%d\t%d\n",(dist / dis), (dist / dis) / 2);
		if ((dist / dis) % 2 == 1) {
			if (XY) {
				dx = dis - dx;
			}
			else {
				dy = dis - dy;
			}
		}
	}
	if (appear) {
		if (xx + dx - zoom * ix >= 0 && xx + dx - zoom * ix < 1920) {
			if (yy + dy - zoom*  iy >= 0 && yy + dy - zoom * iy < 1080) {
				if (reverse) {
					if (xx - dx - zoom * ix >= 0 && xx - dx - zoom * ix < 1920) {
						if (yy - dy - zoom * iy >= 0 && yy - dy - zoom * iy < 1080) {
							setPosition(xx - dx - zoom * ix, yy - dy - zoom * iy);
							SDL_Rect s, d;
							s.x = 0;
							s.y = 0;
							s.w = getWidth();
							s.h = getHeight();
							d.x = getX();
							d.y = getY();
							d.w = getWidth();
							d.h = getHeight();
							setimage(s, d);
						}
					}
				}
				else {
					setPosition(xx + dx - zoom * ix, yy + dy - zoom * iy);
					SDL_Rect s, d;
					s.x = 0;
					s.y = 0;
					s.w = getWidth();
					s.h = getHeight();
					d.x = getX();
					d.y = getY();
					d.w = getWidth();
					d.h = getHeight();
					setimage(s, d);
				}
			}
		}
	}

	dist += speed;
}




void Flor::draw4(int ix, int iy, int zoom, int dis, int speed) {
	if (thro) {
		if (dist > dis) {
			thro = false;
			dist = 0;
			return;
		}
		if (throX - zoom * ix > 0 || throX - zoom * ix < 1920) {
			if (throY + dist - zoom * iy > 0 || throY + dist - zoom * iy < 1080) {
				setPosition(throX - zoom * ix, throY + dist - zoom * iy);
				SDL_Rect s, d;
				s.x = 0;
				s.y = 0;
				s.w = getWidth();
				s.h = getHeight();
				d.x = getX();
				d.y = getY();
				d.w = getWidth();
				d.h = getHeight();
				setimage(s, d);
			}
		}
		dist += speed;
	}
}
void Flor::touch(Playerrole& pl, Star& st) {
	if (pl.getX() < getX()) {//玩家位於物體的左側
		if (pl.getY() < getY()) {//玩家位於物體的上方
			if (getX() - pl.getX() < pl.getWidth2()) {
				if (getY() - pl.getY() < pl.getHeight2()) {
					//碰到
					itemStatus = 1;
				}
				else if (getY() - pl.getY() == pl.getHeight2()) {
					//碰到
					itemStatus = 2;
				}
				else {
					//沒碰到
					itemStatus = 3;
				}
			}
			else if (getX() - pl.getX() == pl.getWidth2()) {
				if (getY() - pl.getY() < pl.getHeight2()) {
					//沒碰到(先當沒碰到)
					itemStatus = 3;
				}
				else if (getY() - pl.getY() == pl.getHeight2()) {
					//沒碰到(先當沒碰到)
					itemStatus = 3;
				}
				else {
					//沒碰到
					itemStatus = 3;
				}
			}
			else {
				//沒碰到
				itemStatus = 3;
			}
		}
		else if (pl.getY() == getY()) {
			if (getX() - pl.getX() < pl.getWidth2()) {
				//碰到
				itemStatus = 1;
			}
			else if (getX() - pl.getX() == pl.getWidth2()) {
				//沒碰到(先當沒碰到)
				itemStatus = 3;
			}
			else {
				//沒碰到
				itemStatus = 3;
			}
		}
		else {
			if (getX() - pl.getX() < pl.getWidth2()) {
				if (pl.getY() - getY() < getHeight()) {
					//碰到
					itemStatus = 1;
				}
				else if (pl.getY() - getY() == getHeight()) {
					//先當沒碰到
					itemStatus = 3;
				}
				else {
					//沒碰到
					itemStatus = 3;
				}
			}
			else if (getX() - pl.getX() == pl.getWidth2()) {
				if (pl.getY() - getY() < getHeight()) {
					//先當沒碰到
					itemStatus = 3;
				}
				else if (pl.getY() - getY() < getHeight()) {
					//先當沒碰到
					itemStatus = 3;
				}
				else {
					//沒碰到
					itemStatus = 3;
				}
			}
			else {
				//沒碰到
				itemStatus = 3;
			}
		}

	}
	else if (pl.getX() == getX()) {
		if (pl.getY() < getY()) {
			if (getY() - pl.getY() < pl.getHeight2()) {
				//碰到
				itemStatus = 1;
			}
			else if (getY() - pl.getY() == pl.getHeight2()) {
				//碰到
				itemStatus = 2;
			}
			else {
				//沒碰到
				itemStatus = 3;
			}

		}
		else if (pl.getY() == getY()) {
			//碰到
			itemStatus = 1;
		}
		else {
			if (pl.getY() - getY() < getHeight()) {
				//碰到
				itemStatus = 1;
			}
			else if (pl.getY() - getY() == getHeight()) {
				//先當沒碰到
				itemStatus = 3;
			}
			else {
				//沒碰到
				itemStatus = 3;
			}
		}
	}
	else {
		if (pl.getY() < getY()) {
			if (pl.getX() - getX() < getWidth()) {
				if (getY() - pl.getY() < pl.getHeight2()) {
					//碰到
					itemStatus = 1;
				}
				else if (getY() - pl.getY() == pl.getHeight2()) {
					//碰到
					itemStatus = 2;
				}
				else {
					//沒碰到
					itemStatus = 3;
				}
			}
			else if (pl.getX() - getX() == getWidth()) {
				if (getY() - pl.getY() < pl.getHeight2()) {
					//先當沒碰到
					itemStatus = 3;
				}
				else if (getY() - pl.getY() == pl.getHeight2()) {
					//先當沒碰到
					itemStatus = 3;
				}
				else {
					//沒碰到
					itemStatus = 3;
				}
			}
			else {
				//沒碰到
				itemStatus = 3;
			}
		}
		else if (pl.getY() == getY()) {
			if (pl.getX() - getX() < getWidth()) {
				//碰到
				itemStatus = 1;
			}
			else if (pl.getX() - getX() == getWidth()) {
				//先當沒碰到
				itemStatus = 3;
			}
			else {
				//沒碰到
				itemStatus = 3;
			}
		}
		else {
			if (pl.getX() - getX() < getWidth()) {
				if (pl.getY() - getY() < getHeight()) {
					//碰到
					itemStatus = 1;
				}
				else if (pl.getY() - getY() == getHeight()) {
					//先當沒碰到
					itemStatus = 3;
				}
				else {
					//沒碰到
					itemStatus = 3;
				}
			}
			else if (pl.getX() - getX() == getWidth()) {
				if (pl.getY() - getY() < getHeight()) {
					//先當沒碰到
					itemStatus = 3;
				}
				else if (pl.getY() - getY() == getHeight()) {
					//先當沒碰到
					itemStatus = 3;
				}
				else {
					//沒碰到
					itemStatus = 3;
				}
			}
			else {
				//沒碰到
				itemStatus = 3;
			}
		}
	}
	if (number==1) {
		if (actionStatus == fly && itemStatus == 1) {
			itemStatus = 4;
		}
		Action(pl);
	}
	else if (number == 2) {
		if (itemStatus == 1) {
			if (st.geteated() == 0) {
				st = st - 1;
			}
			else {
				if (st.geteated() >= 1 && st.geteated()<=20) {
					st.seteated(st.geteated() + 1);
				}
				else {
					st.seteated(0);
				}
			}
		}
	}
	else if (number == 3) {
		if (itemStatus == 2 && tt == 0) {
			disID = SDL_AddTimer(1500, disapp, this);//disID = SDL_AddTimer(750, disapp, this);
			tt += 1;
		}
		else if (!appear) {
			itemStatus = 3;
		}
		if (actionStatus == fly && itemStatus == 1) {
			itemStatus = 4;
		}
		Action(pl);
	}
	else if (number == 4) {
		if(itemStatus == 1){
			pl.setprojection(turn);
			pl.setY(1921);
		}
	}
}
void Flor::touch2(Playerrole& pl) {//碰撞檢測
	if (!appear) {
		return;
	}
	int size = pl.getvxsize();
	if (size != 0) {
		int vx = pl.getvx()[size - 1];
		int vy = pl.getvy()[size - 1];
		if (vx > getX() && vx < getX() + getWidth()) {
			if (vy > getY() && vy < getY() + getHeight()) {
				props = 1;
			}
			else {
				props = 0;
			}
		}
		else {
			props = 0;
		}
	}
	switch (props) {
	case 0:
		break;
	case 1:
		pl.setar(true);
		props = 0;
		break;
	}
}
void Flor::Action(Playerrole& pl) {
	switch (itemStatus) {
	case 4:
		if (pl.getspeedX() != 0) {//前進後退
			if (pl.getspeedY() != 0) { //上下
				if (pl.getspeedX() > 0) {//前進的方向
					if (pl.getspeedY() < 0) {//往上的方向
						pl.setPosition(pl.getX() - pl.getspeedX(), pl.getY() - pl.getspeedY());
						pl.setVX(0);
						pl.setVY(0);
					}
					else {//往下的方向
						//有前進和往下時碰撞
						if (pl.getY() + pl.getHeight2() < getY() + (getHeight() * 6 / 7)) {//當玩家的底部位置高於物體的2/3位置時
							//使玩家可以待在此物體上
							pl.setY(getY() - pl.getHeight2());//將玩家X移動到物品的Y-本身長度上
							pl.setstay(0 - VELOCITY);//給予向上的力
							//printf_s("a1\t");
						}
						else {
							//使玩家會掉下去
							//pl.setY(getY() + getHeight());
							//printf_s("a2\t");
						}
					}
				}
				else {//後退的方向
					if (pl.getspeedY() < 0) {//往上的方向
						printf_s("good1");
						pl.setPosition(pl.getX() - pl.getspeedX(), pl.getY() - pl.getspeedY());
						pl.setVX(0);
						pl.setVY(0);
						//有後退和向上時碰撞
					}
					else {//往下的方向
						//有後退和往下時碰撞
						if (pl.getY() + pl.getHeight2() < getY() + (getHeight() * 6 / 7)) {//當玩家的底部位置高於物體的2/3位置時
							//使玩家可以待在此物體上
							pl.setY(getY() - pl.getHeight2());//將玩家X移動到物品的Y-本身長度上
							pl.setstay(0 - VELOCITY);//給予向上的力
						}
						else {
							//使玩家會掉下去
							pl.setY(getY() + getHeight());
							//pl.setX(getX() + getWidth());//將玩家X移動到物品的X-本身寬度上
							//printf_s("a3\t");
						}
					}
				}

			}
			else {//垂直方向沒有動靜
				if (pl.getY() + pl.getHeight2() > getY() + (getHeight() / 2)) {
					if (pl.getspeedX() > 0) {//前進的方向
					//只有往前時
						pl.setX(getX() - pl.getWidth2());//將位置移到物體的X+物體本身的寬度上
					}
					else {//後退的方向
						//只有後退時
						pl.setX(getX() + getWidth());//將位置移到物體的X+物體本身的寬度上
					}
				}
			}
		}
		else {//前後方向沒有動靜
			if (pl.getspeedY() != 0) {
				if (pl.getspeedY() < 0) {//往上的方向
					pl.setPosition(pl.getX() - pl.getspeedX(), pl.getY() - pl.getspeedY());
				}
				else {//往下的方向
					if (pl.getY() - pl.getspeedY() < getY()) {
						pl.setY(getY() - pl.getHeight2());//將玩家Y移動到物品的Y-本身長度上
					}
					pl.setstay(0 - VELOCITY);//給予向上的力
					//printf_s("a1");
				}
			}
			else {
				//完全不動時
			}
		}
		break;
	case 3:
		//printf_s("nothing occuse!!");
		break;
	case 2:
		pl.setstay(0 - VELOCITY);//給予一個向上的力
		pl.setfriction(friction);
		if (silp) {
			if (pl.getspeedX() == 0 && pl.getsilp() != 0) {
				pl.setsilp(pl.getsilp() * 0.995);
				//printf("%d\t", pl.getsilp());
			}
			else if (pl.getspeedX() == 0 && pl.getsilp() == 0 && havesilp) {
				if (pl.getframe() <= 23) {
					pl.setsilp(10);
					havesilp = false;
				}
				else if (pl.getframe() > 23) {
					pl.setsilp(-10);
					havesilp = false;
				}
			}
			else if (pl.getspeedX() != 0) {
				pl.setsilp(0);
				havesilp = true;
			}
		}
		else {
			pl.setsilp(0);
		}
		break;
	case 1://判斷是怎麼碰到的
		if (pl.getspeedX() != 0) {//前進後退
			if (pl.getspeedY() != 0) { //上下
				if (pl.getspeedX() > 0) {//前進的方向
					if (pl.getspeedY() < 0) {//往上的方向
						//有前進和向上時碰撞
						pl.setfo(0);//將向上的力取消
						if (pl.getX() < getX() + getWidth() && pl.getX() > getX()) {
							//pl.setY(getY() + getHeight());
						}
						else if (pl.getX() + pl.getWidth2() > getX() && pl.getX() + pl.getWidth2() < getX() + getWidth()) {
							//pl.setY(getY() + getHeight());
						}
						else {
							pl.setY(getY() + getHeight());
							printf_s("a1\t");
							//pl.setX(getX() - pl.getWidth2());//將位置移到物體的X上
						}
					}
					else {//往下的方向
						//有前進和往下時碰撞
						if (pl.getY() + pl.getHeight2() < getY() + (getHeight() * 6 / 7)) {//當玩家的底部位置高於物體的2/3位置時
							//使玩家可以待在此物體上
							pl.setY(getY() - pl.getHeight2());//將玩家X移動到物品的Y-本身長度上
							pl.setstay(0 - VELOCITY);//給予向上的力
							//printf_s("a1\t");
						}
						else {
							//使玩家會掉下去
							//pl.setY(getY() + getHeight());
							//printf_s("a2\t");
						}
					}
				}
				else {//後退的方向
					if (pl.getspeedY() < 0) {//往上的方向
						//有後退和向上時碰撞
						pl.setfo(0);//將向上的力取消
						if (pl.getX() + ((pl.getWidth2() * 4) / 5) > getX() && pl.getX() + ((pl.getWidth2() * 4) / 5) < getX() + getWidth()) {
							printf_s("a5\t");
							//pl.setY(getY() + getHeight());
						}
						else if (pl.getX() > getX() && pl.getX() < getX() + getWidth()) {
							printf_s("a4\t");
							//printf_s("a2\t");
							//pl.setY(getY() + getHeight());
						}
						else {
							pl.setY(getY() + getHeight());
							printf_s("a6\t");
							//printf_s("a2\t");
							//pl.setX(getX() + getWidth());//將位置移到物體的X+物體本身的寬度上
						}
					}
					else {//往下的方向
						//有後退和往下時碰撞
						if (pl.getY() + pl.getHeight2() < getY() + (getHeight() * 6 / 7)) {//當玩家的底部位置高於物體的2/3位置時
							//使玩家可以待在此物體上
							pl.setY(getY() - pl.getHeight2());//將玩家X移動到物品的Y-本身長度上
							pl.setstay(0 - VELOCITY);//給予向上的力
						}
						else {
							//使玩家會掉下去
							pl.setY(getY() + getHeight());
							//pl.setX(getX() + getWidth());//將玩家X移動到物品的X-本身寬度上
							printf_s("a3\t");
						}
					}
				}

			}
			else {//垂直方向沒有動靜
				if (pl.getY() + pl.getHeight2() > getY() + (getHeight() / 2)) {
					if (pl.getspeedX() > 0) {//前進的方向
					//只有往前時
						pl.setX(getX() - pl.getWidth2());//將位置移到物體的X+物體本身的寬度上
					}
					else {//後退的方向
						//只有後退時
						pl.setX(getX() + getWidth());//將位置移到物體的X+物體本身的寬度上
					}
				}
			}
		}
		else {//前後方向沒有動靜
			if (pl.getspeedY() != 0) {
				if (pl.getspeedY() < 0) {//往上的方向
					pl.setfo(0);//將向上的力取消
					pl.setY(getY() + getHeight());//將位置移到物體的X+物體本身的寬度上
				}
				else {//往下的方向
					if (pl.getY() - pl.getspeedY() < getY()) {
						pl.setY(getY() - pl.getHeight2());//將玩家Y移動到物品的Y-本身長度上
					}
					pl.setstay(0 - VELOCITY);//給予向上的力
					//printf_s("a1");
				}
			}
			else {
				//完全不動時
			}
		}
		break;
	}
	itemStatus = 3;
}

int Flor::getXlen() {
	return getX() + getWidth();
}
int Flor::getYlen() {
	return getY() + getHeight();
}
Uint32 Flor::disapp(Uint32 interval, void* param) {
	Flor* p = (Flor*)param;
	if (!p->appear) { //當碰到時appear = false
		p->tt += 1; //時間+1
		if (p->tt >= 7) { //當時間>7時
			p->appear = true; //appear = true
			p->tt = 0; //時間歸零
			return 0;
		}


	}
	else if (p->tt == 1) {
		p->tt += 1;
	}
	else {
		p->appear = false;
		p->tt += 1;
	}

	return interval;

}
// for star
int Flor::getfloorx()
{
	return (getX() + getWidth() / 2);
}
int Flor::getfloory()
{
	return getY();
}
void Flor::print() {
	printf_s("%s", image.path);
}
void Flor::setturn(int pp) {
	turn = pp;
}
void Flor::setthro(bool t) {
	thro = t;
}
bool Flor::getthro() {
	return thro;
}
void Flor::setthroposi(int xx, int yy) {
	throX = xx;
	throY = yy;
}
Flor::~Flor() {}