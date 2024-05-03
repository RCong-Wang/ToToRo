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
void Flor::draw2(int xx, int yy, int ix, int iy, int zoom) {//xx&yy=����y�Ц�m ix&iy=�I���y�Ц�m zoom=�Y�񭿲v(���e�@�P)
	//�۹�y��= ����y��-�Y�񭿲v*�I���y��
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
	//xx&yy=����y�Ц�m ix&iy=�I���y�Ц�m zoom=�Y�񭿲v(���e�@�P) disX=���ʶZ�� speed=���ʳt�� XY(true)=���k���� back(true)=�|�^�u reverse(true)=�ϦV����(�U��Wor�k�쥪)
	//�۹�y��= ����y��-�Y�񭿲v*�I���y��
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
	if (pl.getX() < getX()) {//���a����骺����
		if (pl.getY() < getY()) {//���a����骺�W��
			if (getX() - pl.getX() < pl.getWidth2()) {
				if (getY() - pl.getY() < pl.getHeight2()) {
					//�I��
					itemStatus = 1;
				}
				else if (getY() - pl.getY() == pl.getHeight2()) {
					//�I��
					itemStatus = 2;
				}
				else {
					//�S�I��
					itemStatus = 3;
				}
			}
			else if (getX() - pl.getX() == pl.getWidth2()) {
				if (getY() - pl.getY() < pl.getHeight2()) {
					//�S�I��(����S�I��)
					itemStatus = 3;
				}
				else if (getY() - pl.getY() == pl.getHeight2()) {
					//�S�I��(����S�I��)
					itemStatus = 3;
				}
				else {
					//�S�I��
					itemStatus = 3;
				}
			}
			else {
				//�S�I��
				itemStatus = 3;
			}
		}
		else if (pl.getY() == getY()) {
			if (getX() - pl.getX() < pl.getWidth2()) {
				//�I��
				itemStatus = 1;
			}
			else if (getX() - pl.getX() == pl.getWidth2()) {
				//�S�I��(����S�I��)
				itemStatus = 3;
			}
			else {
				//�S�I��
				itemStatus = 3;
			}
		}
		else {
			if (getX() - pl.getX() < pl.getWidth2()) {
				if (pl.getY() - getY() < getHeight()) {
					//�I��
					itemStatus = 1;
				}
				else if (pl.getY() - getY() == getHeight()) {
					//����S�I��
					itemStatus = 3;
				}
				else {
					//�S�I��
					itemStatus = 3;
				}
			}
			else if (getX() - pl.getX() == pl.getWidth2()) {
				if (pl.getY() - getY() < getHeight()) {
					//����S�I��
					itemStatus = 3;
				}
				else if (pl.getY() - getY() < getHeight()) {
					//����S�I��
					itemStatus = 3;
				}
				else {
					//�S�I��
					itemStatus = 3;
				}
			}
			else {
				//�S�I��
				itemStatus = 3;
			}
		}

	}
	else if (pl.getX() == getX()) {
		if (pl.getY() < getY()) {
			if (getY() - pl.getY() < pl.getHeight2()) {
				//�I��
				itemStatus = 1;
			}
			else if (getY() - pl.getY() == pl.getHeight2()) {
				//�I��
				itemStatus = 2;
			}
			else {
				//�S�I��
				itemStatus = 3;
			}

		}
		else if (pl.getY() == getY()) {
			//�I��
			itemStatus = 1;
		}
		else {
			if (pl.getY() - getY() < getHeight()) {
				//�I��
				itemStatus = 1;
			}
			else if (pl.getY() - getY() == getHeight()) {
				//����S�I��
				itemStatus = 3;
			}
			else {
				//�S�I��
				itemStatus = 3;
			}
		}
	}
	else {
		if (pl.getY() < getY()) {
			if (pl.getX() - getX() < getWidth()) {
				if (getY() - pl.getY() < pl.getHeight2()) {
					//�I��
					itemStatus = 1;
				}
				else if (getY() - pl.getY() == pl.getHeight2()) {
					//�I��
					itemStatus = 2;
				}
				else {
					//�S�I��
					itemStatus = 3;
				}
			}
			else if (pl.getX() - getX() == getWidth()) {
				if (getY() - pl.getY() < pl.getHeight2()) {
					//����S�I��
					itemStatus = 3;
				}
				else if (getY() - pl.getY() == pl.getHeight2()) {
					//����S�I��
					itemStatus = 3;
				}
				else {
					//�S�I��
					itemStatus = 3;
				}
			}
			else {
				//�S�I��
				itemStatus = 3;
			}
		}
		else if (pl.getY() == getY()) {
			if (pl.getX() - getX() < getWidth()) {
				//�I��
				itemStatus = 1;
			}
			else if (pl.getX() - getX() == getWidth()) {
				//����S�I��
				itemStatus = 3;
			}
			else {
				//�S�I��
				itemStatus = 3;
			}
		}
		else {
			if (pl.getX() - getX() < getWidth()) {
				if (pl.getY() - getY() < getHeight()) {
					//�I��
					itemStatus = 1;
				}
				else if (pl.getY() - getY() == getHeight()) {
					//����S�I��
					itemStatus = 3;
				}
				else {
					//�S�I��
					itemStatus = 3;
				}
			}
			else if (pl.getX() - getX() == getWidth()) {
				if (pl.getY() - getY() < getHeight()) {
					//����S�I��
					itemStatus = 3;
				}
				else if (pl.getY() - getY() == getHeight()) {
					//����S�I��
					itemStatus = 3;
				}
				else {
					//�S�I��
					itemStatus = 3;
				}
			}
			else {
				//�S�I��
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
void Flor::touch2(Playerrole& pl) {//�I���˴�
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
		if (pl.getspeedX() != 0) {//�e�i��h
			if (pl.getspeedY() != 0) { //�W�U
				if (pl.getspeedX() > 0) {//�e�i����V
					if (pl.getspeedY() < 0) {//���W����V
						pl.setPosition(pl.getX() - pl.getspeedX(), pl.getY() - pl.getspeedY());
						pl.setVX(0);
						pl.setVY(0);
					}
					else {//���U����V
						//���e�i�M���U�ɸI��
						if (pl.getY() + pl.getHeight2() < getY() + (getHeight() * 6 / 7)) {//���a��������m�����骺2/3��m��
							//�Ϫ��a�i�H�ݦb������W
							pl.setY(getY() - pl.getHeight2());//�N���aX���ʨ쪫�~��Y-�������פW
							pl.setstay(0 - VELOCITY);//�����V�W���O
							//printf_s("a1\t");
						}
						else {
							//�Ϫ��a�|���U�h
							//pl.setY(getY() + getHeight());
							//printf_s("a2\t");
						}
					}
				}
				else {//��h����V
					if (pl.getspeedY() < 0) {//���W����V
						printf_s("good1");
						pl.setPosition(pl.getX() - pl.getspeedX(), pl.getY() - pl.getspeedY());
						pl.setVX(0);
						pl.setVY(0);
						//����h�M�V�W�ɸI��
					}
					else {//���U����V
						//����h�M���U�ɸI��
						if (pl.getY() + pl.getHeight2() < getY() + (getHeight() * 6 / 7)) {//���a��������m�����骺2/3��m��
							//�Ϫ��a�i�H�ݦb������W
							pl.setY(getY() - pl.getHeight2());//�N���aX���ʨ쪫�~��Y-�������פW
							pl.setstay(0 - VELOCITY);//�����V�W���O
						}
						else {
							//�Ϫ��a�|���U�h
							pl.setY(getY() + getHeight());
							//pl.setX(getX() + getWidth());//�N���aX���ʨ쪫�~��X-�����e�פW
							//printf_s("a3\t");
						}
					}
				}

			}
			else {//������V�S�����R
				if (pl.getY() + pl.getHeight2() > getY() + (getHeight() / 2)) {
					if (pl.getspeedX() > 0) {//�e�i����V
					//�u�����e��
						pl.setX(getX() - pl.getWidth2());//�N��m���쪫�骺X+���饻�����e�פW
					}
					else {//��h����V
						//�u����h��
						pl.setX(getX() + getWidth());//�N��m���쪫�骺X+���饻�����e�פW
					}
				}
			}
		}
		else {//�e���V�S�����R
			if (pl.getspeedY() != 0) {
				if (pl.getspeedY() < 0) {//���W����V
					pl.setPosition(pl.getX() - pl.getspeedX(), pl.getY() - pl.getspeedY());
				}
				else {//���U����V
					if (pl.getY() - pl.getspeedY() < getY()) {
						pl.setY(getY() - pl.getHeight2());//�N���aY���ʨ쪫�~��Y-�������פW
					}
					pl.setstay(0 - VELOCITY);//�����V�W���O
					//printf_s("a1");
				}
			}
			else {
				//�������ʮ�
			}
		}
		break;
	case 3:
		//printf_s("nothing occuse!!");
		break;
	case 2:
		pl.setstay(0 - VELOCITY);//�����@�ӦV�W���O
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
	case 1://�P�_�O���I�쪺
		if (pl.getspeedX() != 0) {//�e�i��h
			if (pl.getspeedY() != 0) { //�W�U
				if (pl.getspeedX() > 0) {//�e�i����V
					if (pl.getspeedY() < 0) {//���W����V
						//���e�i�M�V�W�ɸI��
						pl.setfo(0);//�N�V�W���O����
						if (pl.getX() < getX() + getWidth() && pl.getX() > getX()) {
							//pl.setY(getY() + getHeight());
						}
						else if (pl.getX() + pl.getWidth2() > getX() && pl.getX() + pl.getWidth2() < getX() + getWidth()) {
							//pl.setY(getY() + getHeight());
						}
						else {
							pl.setY(getY() + getHeight());
							printf_s("a1\t");
							//pl.setX(getX() - pl.getWidth2());//�N��m���쪫�骺X�W
						}
					}
					else {//���U����V
						//���e�i�M���U�ɸI��
						if (pl.getY() + pl.getHeight2() < getY() + (getHeight() * 6 / 7)) {//���a��������m�����骺2/3��m��
							//�Ϫ��a�i�H�ݦb������W
							pl.setY(getY() - pl.getHeight2());//�N���aX���ʨ쪫�~��Y-�������פW
							pl.setstay(0 - VELOCITY);//�����V�W���O
							//printf_s("a1\t");
						}
						else {
							//�Ϫ��a�|���U�h
							//pl.setY(getY() + getHeight());
							//printf_s("a2\t");
						}
					}
				}
				else {//��h����V
					if (pl.getspeedY() < 0) {//���W����V
						//����h�M�V�W�ɸI��
						pl.setfo(0);//�N�V�W���O����
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
							//pl.setX(getX() + getWidth());//�N��m���쪫�骺X+���饻�����e�פW
						}
					}
					else {//���U����V
						//����h�M���U�ɸI��
						if (pl.getY() + pl.getHeight2() < getY() + (getHeight() * 6 / 7)) {//���a��������m�����骺2/3��m��
							//�Ϫ��a�i�H�ݦb������W
							pl.setY(getY() - pl.getHeight2());//�N���aX���ʨ쪫�~��Y-�������פW
							pl.setstay(0 - VELOCITY);//�����V�W���O
						}
						else {
							//�Ϫ��a�|���U�h
							pl.setY(getY() + getHeight());
							//pl.setX(getX() + getWidth());//�N���aX���ʨ쪫�~��X-�����e�פW
							printf_s("a3\t");
						}
					}
				}

			}
			else {//������V�S�����R
				if (pl.getY() + pl.getHeight2() > getY() + (getHeight() / 2)) {
					if (pl.getspeedX() > 0) {//�e�i����V
					//�u�����e��
						pl.setX(getX() - pl.getWidth2());//�N��m���쪫�骺X+���饻�����e�פW
					}
					else {//��h����V
						//�u����h��
						pl.setX(getX() + getWidth());//�N��m���쪫�骺X+���饻�����e�פW
					}
				}
			}
		}
		else {//�e���V�S�����R
			if (pl.getspeedY() != 0) {
				if (pl.getspeedY() < 0) {//���W����V
					pl.setfo(0);//�N�V�W���O����
					pl.setY(getY() + getHeight());//�N��m���쪫�骺X+���饻�����e�פW
				}
				else {//���U����V
					if (pl.getY() - pl.getspeedY() < getY()) {
						pl.setY(getY() - pl.getHeight2());//�N���aY���ʨ쪫�~��Y-�������פW
					}
					pl.setstay(0 - VELOCITY);//�����V�W���O
					//printf_s("a1");
				}
			}
			else {
				//�������ʮ�
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
	if (!p->appear) { //��I���appear = false
		p->tt += 1; //�ɶ�+1
		if (p->tt >= 7) { //��ɶ�>7��
			p->appear = true; //appear = true
			p->tt = 0; //�ɶ��k�s
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