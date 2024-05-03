#include "Playerrole.h"
#include "background.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h> // Using SDL
#include "constants.h"
#include "Text.h"
#include "SDL_ttf.h"
#include <time.h>   /* 時間相關函數 */


int sysStatus;
int actionStatus = none;

Playerrole::Playerrole() 
{

}

Playerrole::Playerrole(const char* path, int n, int hhn, int wwn, SDL_Renderer* ren,int map) : Role(path, n, hhn, wwn, ren) {
	SDL_GetCurrentDisplayMode(0, &DM);
	randonmode = 0;
	mapsize = map;
	sysStatus = stop;
}
Playerrole::Playerrole(const char* path, int n, SDL_Renderer* ren, int map, Uint8 r, Uint8 g, Uint8 b) : Role(path, n, ren, r, g, b) {
	SDL_GetCurrentDisplayMode(0, &DM);
	randonmode = 0;
	mapsize = map;
	sysStatus = stop;
}
Playerrole::Playerrole(const char* path, int n, SDL_Renderer* ren, int map, Uint8 r, Uint8 g, Uint8 b,int seed) : Role(path, n, ren, r, g, b) {
	randonmode = seed % 2+1;
	mapsize = map;
	srand(seed);
	//shit = new flor("../images/floor/smallstone.png", ren, 1, false, 2);
	thro = false;
	setPosition(rand() % 3840 + 600, rand() % 1500);
}

//ren 4/23
bool Playerrole::handlevent(SDL_Event& e, RenderWindow& win) {
	{
		/* The method for "Debunce" */

		// If a key was pressed
		// repeat: non-zero if this is a key repeat
		// https://wiki.libsdl.org/SDL_KeyboardEvent
		//if (e.type == SDL_KEYDOWN)
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_d:
				sysStatus = right;
				break;

			case SDLK_a:
				sysStatus = left;
				break;

			case SDLK_SPACE:
				if (actionStatus != jump && actionStatus != fly) {
					//actionStatus = force;
				}
				break;
			case SDLK_LSHIFT:
				if (sysStatus == left) {
					if (phy == 1) {
						speed = -10;
					}
				}
				else if (sysStatus == right) {
					if (phy == 1) {
						speed = 10;
					}
				}
				break;
			case SDLK_ESCAPE:
				if (list == 0) {
					bool list = true;
					Role rtotoro("../images/03.png", renderer);
					rtotoro.setAlpha(155);
					rtotoro.draw3(DM.w / 4, DM.h / 4, DM.w / 2, DM.h / 2);
					Text continu("Contiune", "../fonts/lazy.ttf", 60, TTF_STYLE_UNDERLINE | TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, renderer, { (DM.w / 3) ,(DM.h / 3) }, { NULL, NULL }, NULL, SDL_FLIP_NONE, 100);
					Text quit("Quit", "../fonts/lazy.ttf", 60, TTF_STYLE_UNDERLINE | TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, renderer, { (DM.w / 3),2*(DM.h/2)-(DM.h / 3) }, { NULL, NULL }, NULL, SDL_FLIP_NONE, 100);
					const int n = 4;
					Sint16 vx[n] = {DM.w/4,DM.w*0.75,DM.w*0.75,DM.w/4};
					Sint16 vy[n] = {DM.h/4,DM.h/4,DM.h*0.75,DM.h*0.75};
					polygonRGBA(renderer, vx, vy, n, 0xCC, 0xCC, 0x00, 0xAA);
					const int n2 = 2;
					Sint16 vx2[n2] = { DM.w / 4,DM.w * 0.75 };
					Sint16 vy2[n2] = { DM.h / 2,DM.h / 2 };
					polygonRGBA(renderer, vx2, vy2, n2, 0xCC, 0xCC, 0x00, 0xAA);
					continu.draw();
					quit.draw();
					win.display();
					while (list) {
						while (SDL_PollEvent(&e) != 0)
						{
							//User requests quit
							if (e.type == SDL_QUIT)
							{
								list = false;
							}
							mouseHandleEvent(&e);
						}

						switch (m.state)
						{
						case NONE:
							break;
						case IN_LB_SC:  // Inside, Left Button, Single Click
							if (m.x >= DM.w / 4 && m.x <= DM.w * 0.75 && m.y >= DM.h / 4 && m.y <= DM.h / 2) {
								list = false;
								m.state = NONE;
								continu.close();
								quit.close();
								rtotoro.close();
							}
							else if (m.x >= DM.w / 4 && m.x <= DM.w * 0.75 && m.y >= DM.h / 2 && m.y <= DM.h * 0.75) {
								list = false;
								m.state = NONE;
								continu.close();
								quit.close();
								rtotoro.close();
								return false;
							}
							break;
						}
					}
				}
			case SDLK_w:
				printf("press w");
				if (actionStatus == fly) {
					v = 0 - VELOCITY;
				}
				break;
			}
			statusAction();
		}
		//If a key was released
		//else if (e.type == SDL_KEYUP)
		else if (e.type == SDL_KEYUP && e.key.repeat == 0)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_d:
				if(sysStatus == right)
					sysStatus = stop;
				break;

			case SDLK_a:
				if(sysStatus == left)
					sysStatus = stop;
				break;

			case SDLK_SPACE:
				if (phy == 1) {
					actionStatus = jump;
				}
				else {
					fo = 0;
				}
				break;
			case SDLK_LSHIFT:
				speed = 0;
				break;
			case SDLK_w:
				v = 0;
				break;
			}
			statusAction();
		}
	}
	return true;
}
int Playerrole::getprojection() {
	return p;
}
void Playerrole::mouseHandleEvent(SDL_Event* e) {
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP || e->type == SDL_MOUSEWHEEL) {
		SDL_GetMouseState(&(m.x), &(m.y));//取得滑鼠位置
		static int lasttime = SDL_GetTicks64();
		static int curtime = SDL_GetTicks64();
		int timediv;

		lasttime = curtime;
		curtime = SDL_GetTicks64();
		timediv = curtime - lasttime;

		switch (e->type)
		{
		case SDL_MOUSEBUTTONDOWN:
			break;

		case SDL_MOUSEBUTTONUP:
			if (e->button.button == SDL_BUTTON_LEFT && e->button.clicks == 2 && timediv < 150)
			{
				m.state = IN_LB_DC;
			}
			else if (e->button.button == SDL_BUTTON_RIGHT && e->button.clicks == 2 && timediv < 150)
			{
				m.state = IN_RB_DC;
			}
			else if (e->button.button == SDL_BUTTON_LEFT && e->button.clicks == 1 && timediv < 800 && timediv > 100)
			{
				m.state = IN_LB_SC;
			}
			else if (e->button.button == SDL_BUTTON_RIGHT && e->button.clicks == 1 && timediv < 800 && timediv > 100)
			{
				m.state = IN_RB_SC;
			}

			break;

		case SDL_MOUSEWHEEL:
			if (e->wheel.y > 0) // scroll up
			{
				// Put code for handling "scroll up" here!
				m.y = e->wheel.y;
				m.state = IN_WU;
			}
			else if (e->wheel.y < 0) // scroll down
			{
				// Put code for handling "scroll down" here!
				m.y = e->wheel.y;
				m.state = IN_WD;
			}
			break;

		case SDL_MOUSEMOTION:
			m.state = HOVER;
			if (e->button.button == SDL_BUTTON_LEFT)
			{
				m.state = IN_LB_PR_HOVER;
			}
			break;
		}
	}

}



// Lan and Lin 4/24
bool Playerrole::getflag() {
	return flag;
}
void Playerrole::setflag(bool b) {
	flag = b;
}
int Playerrole::getStatus() {
	return status;
}
void Playerrole::setcharturn(bool charturn)
{
	characterturn = charturn;
}
int Playerrole::getVX()
{
	return speedX;
}
void Playerrole::setVX(int xx)
{
	speedX = xx;
}
int Playerrole::getVY()
{
	return speedY;
}
void Playerrole::setVY(int yy)
{
	speedY = yy;
}
void Playerrole::move(int imageX,int imageY,int yy){
	imageVX = 0;
	imageVY = 0;
	setX(getX() + speedX * friction + silp);
	setY(getY() + speedY);
	
	 
	 
	 //X
	if ((getX()< 810)) {
		if (imageX != 0) {
			imageVX = 0.5 * (speedX * friction + silp);
			setX(810);
		}
		else {
			if (getX() - getWidth2() <= 0) {
				setX(getWidth2());
			}
		}
		
	}
	else if(getX() + getWidth2() > 1110) {
		if (imageX != 960) {
			imageVX = 0.5 * (speedX * friction + silp);
			setX(1110- getWidth2());
		}
		else {
			if (getX() + getWidth2() >= 1920) {
				setX(1920-getWidth2());
			}
		}
	}
	//Y
	if ((getY()< 390)) {
		if (imageY != 0) {
			if (speedY < 0) {
				imageVY = 0.5 * (speedY);
				setY(390);
			}
			
		}
	}
	else if (getY() + getHeight2() > 690) {
		if (imageY != 540) {
			imageVY = 0.5 * (speedY);
			setY(690 - getHeight2());
		}
	}
}
Uint32 Playerrole::changeRole(Uint32 interval, void* param)
{
	Playerrole* p = (Playerrole*)param;

	if (p->gettime() != 0) // p.time != 0 // p.gettime() != 0 
	{
		switch (sysStatus)
		{
		case stop:
			if (p->getframe() > 23) {
				if (p->getframe() == 40) {
					p->wait++;
					if (p->wait > 3)
					{
						p->setframe((p->getframe() - p->getframe() + 28));
						p->wait = 0;
					}
				}
				else if (p->getframe() == 28) {
					p->wait++;
					if (p->wait > 3)
					{
						p->setframe((p->getframe() - p->getframe() + 40));
						p->wait = 0;
					}
				}	
				else
					p->setframe((p->getframe() - p->getframe() + 28));
			}
			else {
				if (p->getframe() == 17) {
					p->wait++;
					if (p->wait > 3)
					{
						p->setframe((p->getframe() - p->getframe() + 5));
						p->wait = 0;
					}
				}
				else if (p->getframe() == 5) {
					p->wait++;
					if (p->wait > 3)
					{
						p->setframe((p->getframe() - p->getframe() + 17));
						p->wait = 0;
					}
				}
				else
					p->setframe((p->getframe() - p->getframe() + 5));

			}
			break;

		case right: //右走
			p->setframe((p->getframe() + 1) % p->getnum());// 面向右向右走
			p->setframe((p->getframe() % 23));

			break;

		case left:
			p->setframe((p->getframe() + 1) % p->getnum());
			p->setframe((p->getframe() % 23 + 23));
			break;

		case up:

			break;
		}

		return interval;
	}
	else
	{
		return 0;
	}

}
void Playerrole::statusAction(void)
{

	switch (sysStatus)
	{
	case stop: //不動
		// tremble
		// y = 0 && x != move
		setVX(0);
		break;

	case right: //右走
		if (speed < 0)
			speed = 10;
		setVX(VELOCITY + speed);
		break;

	case left: //左走
		if (speed > 0)
			speed = -10;
		setVX(0 - VELOCITY + speed);
		break;
	}
}
void Playerrole::Action(Background& bg)
{
	//控制起跳以及速度
	if (getY() >= DM.h) {
		setPosition(oriX, oriY);
		bg.setimageX(oribgX);
		bg.setimageY(oribgY);

	}
	if (stay == 0) {
		if (phy >= 60 || actionStatus == fly) {
			if (speed != 0) {
				speed = 0;
				if (speedX > 0 && actionStatus != fly) {
					speedX -= 10;
				}
				else if (speedX < 0 && actionStatus != fly) {
					speedX += 10;
				}
			}
		}
	}
	switch (actionStatus) {
	case force:
		fo += 1;
		break;
	case jump: //左轉
		if (fo > 19) {//設置限制
			fo = 19;
		}
		if (fo != 0) {
			fo -= 1;
			phy += 1;
		}
		else {
			fo = 0;
			actionStatus = none;
		}
		break;
	case fly:
		//printf("fly");
		fo = 0;
		phy = 2;
		break;
		//不能跳
		//設定速度
		//不能加速
		//按鍵按w

	case none:
		break;
	}
	if (stay == 0) {
		phy += 1;
		//printf_s("v%d  ", phy);
	}
	else {
		phy = 1;
	}
	if (actionStatus == force) {
		v = (VELOCITY * phy * 0.1) + stay * 0.1;
		//printf_s("v%d  ",v);
	}
	else if (actionStatus == fly) {
		if (v == 0) {
			v = (VELOCITY)+stay;
		}
		else if (v != 0 - VELOCITY) {
			v = 0;
		}
	}
	else {
		v = (-2 * fo) + (VELOCITY * phy * 0.1) + stay * 0.1;
		
	}
	//printf_s("%d  ", fo);
	speedY = v;
	stay = 0;
	//控制滑鼠動作
	switch (m.state)
	{
	case NONE:
		break;

	case OUT: // Mouse out
		break;

	case IN_LB_SC:  // Inside, Left Button, Single Click
		//printf("Inside, Left Button, Single Click: (%d, %d)\n", m.x, m.y);
		if(vx.size()==0){
			arrow_ID = SDL_AddTimer(60,arrow,this);
			m.state = NONE;
		}
		break;

	case IN_RB_SC:  // Inside, RIGHT Button, Single Click
		//printf("Inside, Right Button, Single Click: (%d, %d)\n", m.x, m.y);
		if (ar) {
			setPosition(vx[vx.size() - 1], vy[vy.size() - 1] - 150);
			arr = true;
			ar = false;
			vx.clear();
			vy.clear();
			m.state = NONE;
		}
		break;
	}
}
bool Playerrole::randomwalk() {
	if (randonmode == 1) {
		//printf_s("good");
		if (getX() >= 0 && getX() <= 3840 && getY() >= 0 && getY() <= 2160) {
			int walk = rand() % 25;
			int bf = rand() % 10;
			if (walk % 2 == 0) {
				if (bf > 3) {
					setX(getX() + walk);
				}
			}
			else {
				if (bf > 3) {
					setY(getY() + walk);
				}
				else {
					setY(getY() - walk);
				}
			}
		}
		else {
			setPosition(rand() % 3840 + 600, rand() % 1500);
		}		
	}
	else if (randonmode == 2) {
		if (getX() >= 0 && getX() <= 3840) {
			int walk = rand() % 25;
			int bf = rand() % 10;
			if (walk % 2 == 0) {
				if (bf > 3) {
					setX(getX() + walk);
				}

			}
			else {
				if (bf > 3) {
					setY(getY() - walk);
					return true;
				}
				else {
					setY(getY() + walk);
				}
			}
		}
		else {
			setPosition(rand() % 3840+600, rand() % 1500);
		}
	}
	return false;
}

void Playerrole::startTimer(Uint32 t)
{
	settime(t);
	settimeID(SDL_AddTimer(gettime(), changeRole, this)); // Set Timer callback
}
//Ren
int Playerrole::getspeedY() {
	return speedY;
}
int Playerrole::getspeedX() {
	return speedX;
}
void Playerrole::setnowpos(int posi) {
	nowpos = posi;
}
int Playerrole::getmas() {
	return mas;
}
int Playerrole::getstay() {
	return stay;
}
void Playerrole::setstay(int v) {
	stay = v;
}
int Playerrole::getfo() {
	return fo;
}
void Playerrole::setfo(int f) {
	fo = f;
}
//Ren
int Playerrole::getphy() {
	return phy;
}
void Playerrole::setphy(int ph) {
	phy = ph;
}
Uint32 Playerrole::arrow(Uint32 interval, void* param) {
	//依照設定方向射出箭
	Playerrole* p = (Playerrole*)param;
	//判斷方向
	int num = p->vx.size();
	if (p->getX() > p->m.x && num==0) {
		if (p->getframe() <= 23) {
			return 0;
		}
	}
	else {
		if (p->getframe() > 23 && num == 0) {
			return 0;
		}
	}
	if (num == 0) {
		if (p -> arr) {
			p->arr = false;
			return 0;
		}
		//依照滑鼠點的位置作為初始速度大小
		int xx = p->m.x - p->getX();
		if (xx > 60) {
			xx = 60;
		}//給死上限值
		else if (xx < -60) {
			xx = -60;
		}
		int yy = p->m.y - p->getY();
		if (yy > 60) {
			yy = 60;
		}//給死上限值
		else if (yy<-60) {
			yy = -60;
		}
		//printf_s("xx = %d\tyy = %d",xx,yy);
		if (p->getX() + xx >= 0) {
			p->vx.push_back(p->getX()+(p->getWidth2()/2));
			p->vx.push_back(p->getX() + (p->getWidth2() / 2) + xx);
		}
		if (p->getY() + yy >= 0) {
			p->vy.push_back(p->getY() + (p->getHeight2() / 2));
			p->vy.push_back(p->getY() + (p->getHeight2() / 2) + yy);
		}
	}
	else if (p->ar) {
		p->vx.erase(p->vx.begin());
		p->vy.erase(p->vy.begin());
		if (p->vx.size() == 0) {
			p->vx.clear();
			p->vy.clear();
			p->ar = false;
			p->arr = true;
		}
	}
	else if(num < 30) {
		p->vx.push_back((2*p->vx[num - 1]) - p->vx[num - 2]);
		p->vy.push_back((2*p->vy[num - 1]) - p->vy[num - 2] + VELOCITY*(num-1));
		if ((int)(2 * p->vx[num - 1]) - (int)p->vx[num - 2] <= 0 || (2 * p->vx[num - 1]) - p->vx[num - 2] > p->DM.w) {
			p->vx.clear();
			p->vy.clear();
			//printf_s("good3");
			return 0;
		}
		else if ((int)(2 * p->vy[num - 1]) - (int)p->vy[num - 2] <= 0 || (2 * p->vy[num - 1]) - p->vy[num - 2] > p->DM.h) {
			p->vx.clear();
			p->vy.clear();
			//printf_s("good4");
			return 0;
		}

	}
	
	return interval;
}

void Playerrole::draw2() {
	if (vx.size() != 0) {
		Sint16 za[30];
		Sint16 zb[30];
		for (int x = 0; x < vx.size(); x++) {
			za[x] = vx[x];
			zb[x] = vy[x];
			
		}

		bezierColor(renderer, za, zb, vx.size(), 5, 0xFF0000FF);
	}
	Role::draw2();
}
void Playerrole::draw(int ix, int iy, int zoom) {//xx&yy=絕對座標位置 ix&iy=背景座標位置 zoom=縮放倍率(長寬一致)
	//相對座標= 絕對座標-縮放倍率*背景座標
	if (getX() - zoom * ix > 0 && getX() - zoom * ix < 1920) {
		if (getY() - zoom * iy > 0 && getY() - zoom * iy < 1080) {
			//setPosition(xx - zoom * ix, yy - zoom * iy);
			Role::draw4(ix, iy,zoom);
		}
	}
	
}
vector<Sint16> Playerrole::getvx() {
	return vx;
}
vector<Sint16> Playerrole::getvy() {
	return vy;
}
void Playerrole::setvector(int xx,int yy) {
	vx[vx.size() - 1] = xx;
	vy[vy.size() - 1] = yy;
}
int Playerrole::getvxsize() {
	return vx.size();
}
void Playerrole::setar(bool t) {
	ar = t;
}
void Playerrole::setfriction(double fr) {
	friction = fr;
}
void Playerrole::setsilp(int s) {
	silp = s;
}
int Playerrole::getsilp() {
	return silp;
}
int Playerrole::getimageVX() {
	return imageVX;
}
void Playerrole::setimageVX(int vvx) {
	imageVX = vvx;
}
int Playerrole::getimageVY() {
	return imageVY;
}
void Playerrole::setimageVY(int vvy) {
	imageVY = vvy;
}
void Playerrole::setoriposi(int xx, int yy,int bgx,int bgy) {
	oriX = xx;
	oriY = yy;
	oribgX = bgx;
	oribgY = bgy;
}
void Playerrole::setprojection(int pp) {
	p = pp;
}

//0605
void Playerrole::setspeed(int a)
{
	speed = a;
}

int Playerrole::getlist()
{
	return list;
}

void Playerrole::getv(int a) 
{
	v = a;
}

Playerrole::~Playerrole()
{
	if (randonmode != 0) {
		//delete shit;
	}
}