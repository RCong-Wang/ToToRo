/* Alphar: 2022.04.17 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h> // Using SDL
#include <SDL2_gfxPrimitives.h> // Using SDL2_gfx
#include <SDL_image.h>
//#include <SDL_ttf.h>  // Using truetype font
#include "constants.h"
#include "RenderWindow.h"
#include "System.h"
#include <iostream>
#include "Star.h"
#include "Item.h"
#include "Score.h"
using namespace std;
//#include "Text.h"


/************************/
/* New in this example */
#include "Role.h"
#include "Playerrole.h"
#include "background.h"
#include "floor.h"
#include "Text.h"
#include <vector>
#include "SDL_ttf.h"
#include "Mixer.h"
// use seed
#include <time.h>
//use strcpy_s
#include<cstring>
/***********************/
void mouseHandleEvent(SDL_Event* e, Mouse* m);
void mouseHandleEvent(SDL_Event* e, Mouse* m)
{
	// If mouse event happened
	// https://wiki.libsdl.org/SDL_Event
	// https://wiki.libsdl.org/SDL_MouseMotionEvent
	// https://wiki.libsdl.org/SDL_MouseButtonEvent
	// https://wiki.libsdl.org/SDL_MouseWheelEvent
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP || e->type == SDL_MOUSEWHEEL)
	{
		// Get mouse position
		// https://wiki.libsdl.org/SDL_GetMouseState		
		SDL_GetMouseState(&(m->x), &(m->y));
		//printf("(%d, %d)\n", *x, *y);

		// Mouse is at left/right/above/below of the button. Mouse is outside the button
		switch (e->type)
		{
		case SDL_MOUSEBUTTONDOWN:
			break;

		case SDL_MOUSEBUTTONUP:
			if (e->button.button == SDL_BUTTON_LEFT && e->button.clicks == 1)
			{
				m->state = IN_LB_SC;
			}
			else if (e->button.button == SDL_BUTTON_RIGHT && e->button.clicks == 1)
			{
				m->state = IN_RB_SC;
			}

			break;
		case SDL_MOUSEMOTION:
			m->state = HOVER;
			if (e->button.button == SDL_BUTTON_LEFT)
			{
				m->state = IN_LB_PR_HOVER;
			}
			break;
		}
	}
}
bool handlevent(Playerrole* p, SDL_Event* e, RenderWindow* win, Mouse* m, Score* sco, Star* Sta);
bool handlevent(Playerrole* p, SDL_Event* e, RenderWindow* win, Mouse* m, Score* sco, Star* Sta) {
	{
		/* The method for "Debunce"*/

		// If a key was pressed
		// repeat: non-zero if this is a key repeat
		// https://wiki.libsdl.org/SDL_KeyboardEvent
		//if (e.type == SDL_KEYDOWN)

		if (e->type == SDL_KEYDOWN && e->key.repeat == 0)
		{
			switch (e->key.keysym.sym)
			{
			case SDLK_d:
				sysStatus = 1;
				break;

			case SDLK_a:
				sysStatus = 2;
				break;

			case SDLK_SPACE:
				if (actionStatus != jump && actionStatus != fly)
					actionStatus = force;
				break;
			case SDLK_LSHIFT:
				if (sysStatus == 2) {
					if (p->getphy() == 1) {
						p->setspeed(-10);
					}
				}
				else if (sysStatus == 1) {
					if (p->getphy() == 1) {
						p->setspeed(-10);
					}
				}
				break;
			case SDLK_ESCAPE:
				if (p->getlist() == 0) {
					sco->startTimer(0);
					Sta->startTimer(0);
					bool list = true;
					Role rtotoro("../images/03.png", win->getRenderer());
					rtotoro.setAlpha(155);
					rtotoro.draw3(1920 / 4, 1080 / 4, 1920 / 2, 1080 / 2);
					Text continu("Contiune", "../fonts/lazy.ttf", 60, TTF_STYLE_UNDERLINE | TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, win->getRenderer(), { (1920 / 3) ,(1080 / 3) }, { NULL, NULL }, NULL, SDL_FLIP_NONE, 100);
					Text quit("Quit", "../fonts/lazy.ttf", 60, TTF_STYLE_UNDERLINE | TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, win->getRenderer(), { (1920 / 3),2 * (1080 / 2) - (1080 / 3) }, { NULL, NULL }, NULL, SDL_FLIP_NONE, 100);
					const int n = 4;
					Sint16 vx[n] = { 1920 / 4, 1920 * 0.75, 1920 * 0.75, 1920 / 4 };
					Sint16 vy[n] = { 1080 / 4, 1080 / 4, 1080 * 0.75, 1080 * 0.75 };
					polygonRGBA(win->getRenderer(), vx, vy, n, 0xCC, 0xCC, 0x00, 0xAA);
					const int n2 = 2;
					Sint16 vx2[n2] = { 1920 / 4, 1920 * 0.75 };
					Sint16 vy2[n2] = { 1080 / 2, 1080 / 2 };
					polygonRGBA(win->getRenderer(), vx2, vy2, n2, 0xCC, 0xCC, 0x00, 0xAA);
					continu.draw();
					quit.draw();
					win->display();
					while (list) {
						while (SDL_PollEvent(e) != 0)
						{
							//User requests quit
							if (e->type == SDL_QUIT)
							{
								list = false;
							}

							if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP || e->type == SDL_MOUSEWHEEL) {
								SDL_GetMouseState(&(m->x), &(m->y));//取得滑鼠位置
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
										m->state = IN_LB_DC;
									}
									else if (e->button.button == SDL_BUTTON_RIGHT && e->button.clicks == 2 && timediv < 150)
									{
										m->state = IN_RB_DC;
									}
									else if (e->button.button == SDL_BUTTON_LEFT && e->button.clicks == 1 && timediv < 800 && timediv > 100)
									{
										m->state = IN_LB_SC;
									}
									else if (e->button.button == SDL_BUTTON_RIGHT && e->button.clicks == 1 && timediv < 800 && timediv > 100)
									{
										m->state = IN_RB_SC;
									}

									break;

								case SDL_MOUSEWHEEL:
									if (e->wheel.y > 0) // scroll up
									{
										// Put code for handling "scroll up" here!
										m->y = e->wheel.y;
										m->state = IN_WU;
									}
									else if (e->wheel.y < 0) // scroll down
									{
										// Put code for handling "scroll down" here!
										m->y = e->wheel.y;
										m->state = IN_WD;
									}
									break;

								case SDL_MOUSEMOTION:
									m->state = HOVER;
									if (e->button.button == SDL_BUTTON_LEFT)
									{
										m->state = IN_LB_PR_HOVER;
									}
									break;
								}
							}
						}
						switch (m->state)
						{
						case NONE:
							break;
						case IN_LB_SC:  // Inside, Left Button, Single Click
							if (m->x >= 1920 / 4 && m->x <= 1920 * 0.75 && m->y >= 1080 / 4 && m->y <= 1080 / 2) {
								list = false;
								m->state = NONE;
								continu.close();
								quit.close();
								rtotoro.close();
								sco->startTimer(100);
								Sta->startTimer(4000);
							}
							else if (m->x >= 1920 / 4 && m->x <= 1920 * 0.75 && m->y >= 1080 / 2 && m->y <= 1080 * 0.75) {
								list = false;
								m->state = NONE;
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
					p->getv(0 - VELOCITY);
				}
				break;
			}
			p->statusAction();
		}
		//If a key was released
		//else if (e.type == SDL_KEYUP)
		else if (e->type == SDL_KEYUP && e->key.repeat == 0)
		{
			switch (e->key.keysym.sym)
			{
			case SDLK_d:
				if (sysStatus == 1)
					sysStatus = stop;
				break;

			case SDLK_a:
				if (sysStatus == 2)
					sysStatus = stop;
				break;

			case SDLK_SPACE:
				if (p->getphy() == 1) {
					actionStatus = jump;
				}
				else {
					p->setfo(0);
				}
				break;
			case SDLK_LSHIFT:
				p->setspeed(0);
				break;
			case SDLK_w:
				p->getv(0);
				break;
			}
			p->statusAction();
		}
		return true;
	}
}

int getenergy(Star* st) {
	return st->eated;
}
void setenergy(Star* st) {
	st->eated += 1;
}
void move(Playerrole &pl) {
	printf_s("%d\n", pl.speedX);
	pl.speedX = pl.speedX * 2;
	printf_s("%d\n", pl.speedX);
}
void reducemove(Playerrole& pl) {
	pl.speedX = pl.speedX / 2;
}
void acc(Playerrole& pl, Star* st) {
	int e = getenergy(st);
	if (e > 1 && e<=20) {
		reducemove(pl);
		move(pl);
		setenergy(st);
	}
	else if (e == 1) {
		move(pl);
		setenergy(st);
		
	}
}
//0614
void rsort(char** v, int num)
{
	char temp[1000][12];
	for (int x = 0; x < num - 1; x++)
	{
		for (int y = 0; y < (num - 1 - x); y++)
		{
			if (strcmp(v[y], v[y + 1]) < 0)
			{
				strcpy_s(temp[y], 12, v[y]);
				strcpy_s(v[y], 12, v[y+1]);
				strcpy_s(v[y+1], 12, temp[y]);
			}
		}
	}
}
// When using SDL, you have to use "int main(int argc, char* args[])"
// int main() and void main() are not allowed
int main(int argc, char* args[])
{
	unsigned seed;
	seed = (unsigned)time(NULL); // 取得時間序列
	srand(seed); // 以時間序列當亂數種子

	System sdl;

	// Start up SDL and create window
	if (!sdl.init())
	{
		printf("Failed to initialize SDL system!\n");
		return -1;
	}
	RenderWindow window("OOP SDL Tutorial", 20, 20, WIDTH, HEIGHT);
	SDL_RendererFlip no = SDL_FLIP_NONE;
	SDL_RendererFlip ho = SDL_FLIP_HORIZONTAL;
	SDL_RendererFlip ve = SDL_FLIP_VERTICAL;
	SDL_RendererFlip hove = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);

	Background peko("../images/01.png", window.getRenderer());
	Background rbtotoro1("../images/04.png", window.getRenderer());
	Background rbtotoro2("../images/04.png", window.getRenderer());
	Background rbtotoro3("../images/04.png", window.getRenderer());
	rbtotoro1.setAlpha(155);
	rbtotoro2.setAlpha(155);
	rbtotoro3.setAlpha(155);
	//0612
	Background rbtotoro4("../images/04.png", window.getRenderer());
	rbtotoro4.setAlpha(155);

	peko.setPosition(0, 0);
	SDL_Event e;
	bool list = true;
	int li = 0;
	Mouse ms;
	Text start("Start", "../fonts/lazy.ttf", 60, TTF_STYLE_UNDERLINE | TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 250, 250 }, { NULL, NULL }, NULL, no, 100);
	Text leave("Leave", "../fonts/lazy.ttf", 60, TTF_STYLE_UNDERLINE | TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 1450, 250 }, { NULL, NULL }, NULL, no, 100);
	Text story("Story", "../fonts/lazy.ttf", 60, TTF_STYLE_UNDERLINE | TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 850, 250 }, { NULL, NULL }, NULL, no, 100);
	//0612
	Text Rank("Rank", "../fonts/lazy.ttf", 60, TTF_STYLE_UNDERLINE | TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 1450, 750 }, { NULL, NULL }, NULL, no, 100);

	Mixer m1("../audio/lookocean.mp3", MUSIC);
	m1.play(FOREVER);

	//0612
	
	FILE *rf, *wf, *wb;
	errno_t erf, ewf, ewb;
	ewf = fopen_s(&wf, "../Score.txt", "a");
	int n1;
	bool fo = false;

	int ttf = 1;
	//fscanf_s(wf, "%d", &n1);
	//printf("%d", n1);
	//fclose(wf);

	//While application is running
	while (list) {
		//0612
		if (fo == true) 
		{
			erf = fopen_s(&wf, "../Score.txt", "a");
			fo = false;
		}

		window.clear();
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				list = false;
			}
			mouseHandleEvent(&e, &ms);
		}
		peko.draw();
		rbtotoro1.draw3(200, 150, 400, 200);
		rbtotoro2.draw3(800, 150, 400, 200);
		rbtotoro3.draw3(1400, 150, 400, 200);

		//0612
		rbtotoro4.draw3(1400, 650, 400, 200);

		const int n = 4;
		Sint16 vx[n] = { 200,200,600,600 };
		Sint16 vy[n] = { 150,350,350,150 };
		polygonRGBA(window.getRenderer(), vx, vy, n, 0xCC, 0xCC, 0x00, 0xAA);
		Sint16 vx2[n] = { 800,800,1200,1200 };
		Sint16 vy2[n] = { 150,350,350,150 };
		polygonRGBA(window.getRenderer(), vx2, vy2, n, 0xCC, 0xCC, 0x00, 0xAA);
		Sint16 vx3[n] = { 1400,1400,1800,1800 };
		Sint16 vy3[n] = { 150,350,350,150 };
		polygonRGBA(window.getRenderer(), vx3, vy3, n, 0xCC, 0xCC, 0x00, 0xAA);
		//0612
		Sint16 vx4[n] = { 1400,1400,1800,1800 };
		Sint16 vy4[n] = { 650,850,850,650 };
		polygonRGBA(window.getRenderer(), vx4, vy4, n, 0xCC, 0xCC, 0x00, 0xAA);



		start.draw();
		leave.draw();
		story.draw();
		//0612
		Rank.draw();

		switch (ms.state)
		{
		case NONE:
			break;
		case IN_LB_SC:  // Inside, Left Button, Single Click
			if (ms.x >= 200 && ms.x <= 600 && ms.y >= 150 && ms.y <= 350) {
				m1.stop();
				li = 1;
			}
			else if (ms.x >= 800 && ms.x <= 1200 && ms.y >= 150 && ms.y <= 350) {
				m1.stop();
				li = 2;
			}
			else if (ms.x >= 1400 && ms.x <= 1800 && ms.y >= 650 && ms.y <= 850) {
				m1.stop();
				li = 3;
			}
			else if (ms.x >= 1400 && ms.x <= 1800 && ms.y >= 150 && ms.y <= 350) {
				list = false;
			}
			ms.state = NONE;
			break;
		case IN_RB_SC:  // Inside, RIGHT Button, Single Click
			//printf("Inside, Right Button, Single Click: (%d, %d)\n", ms.x, ms.y);
			break;
		case HOVER: // Mouse hover
			//printf("Inside, Hover: (%d, %d)\n", ms.x, ms.y);
			break;
		case IN_LB_PR_HOVER: // Mouse hover
			//printf("Inside, Left Button, Press, Hover: (%d, %d)\n", ms.x, ms.y);
			break;
		case IN_RB_PR_HOVER: // Mouse hover
			//printf("Inside, Right Button, Press, Hover: (%d, %d)\n", ms.x, ms.y);
			break;
		}
		window.display();
		if (li == 1) {
			m1.play(FOREVER);
			bool quit = false;
			bool quit2 = true;
			//Playerrole sb("../images/sb.png",12,3,4, window.getRenderer(),3);
			Background rob("../images/background/01.png", window.getRenderer());

			Playerrole sb("../images/46/", 46, window.getRenderer(),2, 255, 255, 255);
			int startY = rob.getscreenheigh();
			
			//1st background floor
			//flor f1("../images/floor/stone.png", window.getRenderer(), 1, false, false);
			//flor f6("../images/floor/Icestone.png", window.getRenderer(), 1, true, false);
			//flor f7("../images/floor/box.png", window.getRenderer(), 1, false, true);
			//flor f10("../images/floor/sand.png", window.getRenderer(), 0.5, false, false);
			//flor f30("../images/floor/wall.png", window.getRenderer(), 1, false, false);
			vector<Flor*> ff;
			for (int x = 0; x < 20; x++) {
				if (x < 5) {
					ff.push_back(new Flor("../images/floor/Icestone.png", window.getRenderer(), 1, true,1));
				}
				else if (x >= 5 && x < 10) {
					ff.push_back(new Flor("../images/floor/sand.png", window.getRenderer(), 0.5, false,1));
				}
				else {
					ff.push_back(new Flor("../images/floor/stone.png", window.getRenderer(), 1, false,1));
				}
			}	
			for (int x = 0; x < 20; x++) {
				ff.push_back(new Flor("../images/floor/smallstone.png", window.getRenderer(), 1,false,2));
			}
			ff.push_back(new Flor("../images/floor/box.png", window.getRenderer(), 1,false, 3));
			ff.push_back(new Flor("../images/floor/door.png", window.getRenderer(), 1, false, 4));
			ff[41]->setturn(2);
			//0~4為冰塊 5~9為沙子 10~19為石頭 20~39為小石頭 40消失箱子 41傳送門

			vector<Flor*> f1;
			//0傳送門 1~9為冰塊 10~20為沙子 21~50箱子 51~80牆壁 81~150為小石頭 150~石頭
			for (int x = 0; x < 300; x++) {
				if (x == 0) {
					
					f1.push_back(new Flor("../images/floor/door.png", window.getRenderer(), 1, false, 4));
				}
				else if (x >= 1 && x < 10) {
					f1.push_back(new Flor("../images/floor/Icestone.png", window.getRenderer(), 1, true, 1));
				}
				else if (x >= 10 && x < 21) {
					f1.push_back(new Flor("../images/floor/sand.png", window.getRenderer(), 0.5, false, 1));
				}
				else if (x >= 21 && x < 51) {
					f1.push_back(new Flor("../images/floor/box.png", window.getRenderer(), 1, false, 3));
				}
				else if (x >= 51 && x < 81) {
					f1.push_back(new Flor("../images/floor/wall.png", window.getRenderer(), 1, false, 1));
				}
				else if (x >= 81 && x < 150) {
					f1.push_back(new Flor("../images/floor/smallstone.png", window.getRenderer(), 1, false, 2));
				}
				else {
					f1.push_back(new Flor("../images/floor/stone.png", window.getRenderer(), 1, false, 1));
				}
			}
			f1[0]->setturn(2);
			
			vector<Flor*> f2;
			for (int x = 0; x < 300; x++) {
				if (x == 0) {

					f2.push_back(new Flor("../images/floor/door.png", window.getRenderer(), 1, false, 4));
				}
				else if (x >= 1 && x < 10) {
					f2.push_back(new Flor("../images/floor/Icestone.png", window.getRenderer(), 1, true, 1));
				}
				else if (x >= 10 && x < 21) {
					f2.push_back(new Flor("../images/floor/sand.png", window.getRenderer(), 0.5, false, 1));
				}
				else if (x >= 21 && x < 51) {
					f2.push_back(new Flor("../images/floor/box.png", window.getRenderer(), 1, false, 3));
				}
				else if (x >= 51 && x < 81) {
					f2.push_back(new Flor("../images/floor/wall.png", window.getRenderer(), 1, false, 1));
				}
				else if (x >= 81 && x < 150) {
					f2.push_back(new Flor("../images/floor/smallstone.png", window.getRenderer(), 1, false, 2));
				}
				else {
					f2.push_back(new Flor("../images/floor/stone.png", window.getRenderer(), 1, false, 1));
				}
			}
			f2[0]->setturn(3);
			
			vector<Playerrole*> bird;
			for (int x = 0; x < 20; x++) {
				bird.push_back(new Playerrole("../images/bird/", 4, window.getRenderer(),2, 255, 255, 255,rand()));
				bird[x]->setPosition(rand()%1920, rand()%1080);
				bird[x]->Role::startTimer(100);
				f1.push_back(new Flor("../images/floor/smallstone.png", window.getRenderer(), 1, false, 2));
			}
			//Item
			Item umbrella("../images/umbrella_2/", 3, 1, window.getRenderer());
			//umbrella.setPosition(600 , 2060);
			umbrella.startTimer(200);
			//star
			vector<Star*> st;
			for (int x = 0; x < 6; x++) {
				st.push_back(new Star("../images/S/", 15, window.getRenderer()));
			}
			
			//energy
			Star energy("../images/E/", 20, window.getRenderer());
			Star energytime("../images/E/", 20, window.getRenderer());
			//star
			int setstar = 0;
			int oncestar = 0;
			//energy
			energy.setPosition(0, 0);
			energy.startTimer(10);
			energytime.startTimer(8000);//時間修改
			sb.setPosition(100, 780);
			sb.startTimer(100);
			// background origin setting
			rob.setPosition(0, 0);
			rob.setimageX(0);
			rob.setimageY(540);
			//min : second : ms
			Score survival;
			survival.startTimer(10);
			for (int x = 0; x < 6; x++)
				st[x]->startTimer(150);
			//radom star

			int s, s1 = 0, s2 = 0, s3 = 0;
			s = rand() % 3 + 11;//隨機0~9
			s1 = 13;
			do
				s = rand() % 6 + 24;
			while (s1 == s);
			s2 = s;
			do
				s = rand() % 4 + 159;
			while (s == s1 || s == s2);
			s3 = s;


			int s4, s5 = 0, s6 = 0, s7 = 0;
			s4 = rand() % 4 + 152;//隨機0~9
			s5 = s4;
			do
				s4 = rand() % 3 + 180;
			while (s5 == s4);
			s6 = s4;
			do
				s4 = rand() % 2 + 177;
			while (s4 == s5 || s4 == s6);
			s7 = s4;


			while (!quit && quit2)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					//quit2 = sb.handlevent(e, window);
					quit2 = handlevent(&sb, &e, &window, &ms, &survival, &energytime);
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					sb.mouseHandleEvent(&e);
				}
				// Clear screen
				window.clear();
			
				if (sb.getprojection() == 1) {
					sb.setoriposi(100, 780, 0, 540);
				}
				else if (sb.getprojection() == 2) {
					sb.setoriposi(0, 300, 0, 0);
				}
				sb.Action(rob);
				for (int x = 0; x < 3; x++) {
					acc(sb, st[x]);
				}
				sb.move(rob.getimageX(), rob.getimageY(), startY);
				//backage and floor
				rob.draw2(sb.getimageVX(), sb.getimageVY());
				//min : second : ms
				char tt1[2] = { 0 }, tt2[2] = { 0 }, tt4[2] = { 0 }, tt5[2] = { 0 }, tt7[2] = { 0 }, tt8[2] = { 0 }; // min : second : ms
				//ms
				tt8[0] = ((survival.getscore() % 10) + 48);
				//printf("%c ", tt8[0]);
				tt7[0] = (((survival.getscore() / 10) % 10) + 48);
				//printf("%c ", tt7[0]);
				//secind
				tt5[0] = (((survival.getscore() / 100) % 10) + 48);
				tt4[0] = (((survival.getscore() / 1000) % 6) + 48);
				//min
				tt2[0] = ((((survival.getscore() / 100) / 60) % 10) + 48);
				tt1[0] = (((((survival.getscore() / 100) / 60) / 10) % 6) + 48);
				Text t1(tt1, "../fonts/lazy.ttf", 40, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 255, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 910,50 }, { NULL, NULL }, NULL, no, 100);
				Text t2(tt2, "../fonts/lazy.ttf", 40, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 255, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 930,50 }, { NULL, NULL }, NULL, no, 100);
				Text t3(":", "../fonts/lazy.ttf", 40, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 255, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 950,50 }, { NULL, NULL }, NULL, no, 100);
				Text t4(tt4, "../fonts/lazy.ttf", 40, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 255, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 970,50 }, { NULL, NULL }, NULL, no, 100);
				Text t5(tt5, "../fonts/lazy.ttf", 40, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 255, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 990,50 }, { NULL, NULL }, NULL, no, 100);
				Text t6(":", "../fonts/lazy.ttf", 40, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 255, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 1010,50 }, { NULL, NULL }, NULL, no, 100);
				Text t7(tt7, "../fonts/lazy.ttf", 40, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 255, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 1030,50 }, { NULL, NULL }, NULL, no, 100);
				Text t8(tt8, "../fonts/lazy.ttf", 40, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 255, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 1050,50 }, { NULL, NULL }, NULL, no, 100);
				//backage and floor
				rob.draw2(sb.getimageVX(), sb.getimageVY());

				if (sb.getprojection() == 1) 
				{
					//sb.setoriposi(100, 780, 0, 540);
					if (umbrella.getexist())
						umbrella.draw2(1500, 1960,  rob.getimageX(), rob.getimageY(),2,sb.getX(),sb.getY(), 1);
					//0傳送門 1~9為冰塊 10~20為沙子 21~40箱子 41~50牆壁 51~100為小石頭 100~石頭
					//0傳送門 1~9為冰塊 10~20為沙子 21~50箱子 51~80牆壁 81~150為小石頭 150~石頭
					//door
					f1[0]->draw2(3270, 1805, rob.getimageX(), rob.getimageY(), 2);
					//f1[0]->draw2(100, 1500, rob.getimageX(), rob.getimageY(), 2);

					//ice
					//f1[1]->draw3(200, 1960, rob.getimageX(), rob.getimageY(), 2, 400, 3, true, true, false);
					f1[1]->draw3(600, 1960, rob.getimageX(), rob.getimageY(), 2, 400, 3, true, true, true);
					f1[2]->draw3(1650, 2060, rob.getimageX(), rob.getimageY(), 2, 650, 4, true, true, false);
					f1[3]->draw3(2450, 1910, rob.getimageX(), rob.getimageY(), 2, 650, 4, false, true, true);
					f1[4]->draw3(2150, 760, rob.getimageX(), rob.getimageY(), 2, 750, 4, false, true, false);
					f1[5]->draw3(2450, 510, rob.getimageX(), rob.getimageY(), 2, 650, 4, false, true, false);
					f1[6]->draw3(3400, 660, rob.getimageX(), rob.getimageY(), 2, 400, 4, false, true, false);

					
					//sand
					//f1[10]->draw2(1450, 560, rob.getimageX(), rob.getimageY(), 2);
					//f1[11]->draw2(1850, 560, rob.getimageX(), rob.getimageY(), 2);
					for (int x = 11; x <= 13; x++) {
						f1[x]->draw2(0 + (x - 11) * 400, 1660, rob.getimageX(), rob.getimageY(), 2);
					}
					f1[14]->draw2(3740, 1560, rob.getimageX(), rob.getimageY(), 2);

					//box
					f1[21]->draw2(1100, 1810, rob.getimageX(), rob.getimageY(), 2);
					f1[22]->draw2(650, 1510, rob.getimageX(), rob.getimageY(), 2);
					f1[23]->draw2(450, 1360, rob.getimageX(), rob.getimageY(), 2);
					f1[24]->draw2(250, 1210, rob.getimageX(), rob.getimageY(), 2);
					f1[25]->draw2(450, 1060, rob.getimageX(), rob.getimageY(), 2);
					f1[26]->draw2(650, 910, rob.getimageX(), rob.getimageY(), 2);
					f1[27]->draw2(400, 760, rob.getimageX(), rob.getimageY(), 2);
					//f1[28]->draw2(1650, 560, rob.getimageX(), rob.getimageY(), 2);
					for (int x = 29; x <= 30; x++) {
						f1[x]->draw2(1450 + (x - 29) * 100, 860, rob.getimageX(), rob.getimageY(), 2);
					}
					for (int x = 31; x <= 32; x++) {
						f1[x]->draw2(1650 + (x - 31) * 100, 1160, rob.getimageX(), rob.getimageY(), 2);
					}
					for (int x = 33; x <= 34; x++) {
						f1[x]->draw2(1450 + (x - 33) * 100, 1460, rob.getimageX(), rob.getimageY(), 2);
					}
					for (int x = 35; x <= 39; x++) {
						f1[x]->draw2(1450 + (x - 35) * 100, 560, rob.getimageX(), rob.getimageY(), 2);
					}
					for (int x = 40; x <= 41; x++) {
						f1[x]->draw2(2900 + (x - 40) * 100, 760, rob.getimageX(), rob.getimageY(), 2);
					}
					for (int x = 42; x <= 45; x++) {
						f1[x]->draw2(3300 + (x - 42) * 100, 460 , rob.getimageX(), rob.getimageY(), 2);
					}
					f1[46]->draw2(3440, 1260, rob.getimageX(), rob.getimageY(), 2);
					f1[47]->draw2(3740, 1260, rob.getimageX(), rob.getimageY(), 2);

					//wall
					f1[51]->draw2(800, 1800, rob.getimageX(), rob.getimageY(), 2);
					f1[52]->draw2(600, 560, rob.getimageX(), rob.getimageY(), 2);
					for (int x = 53; x <= 55; x++) {
						f1[x]->draw2(3100, 10 + (x - 53) * 150, rob.getimageX(), rob.getimageY(), 2);
					}
					for (int x = 56; x <= 57; x++) {
						f1[x]->draw2(3140, 1760 + (x - 56) * 150, rob.getimageX(), rob.getimageY(), 2);
					}
					for (int x = 58; x <= 59; x++) {
						f1[x]->draw2(3490, 1760 + (x - 58) * 150, rob.getimageX(), rob.getimageY(), 2);
					}
					/*
					for (int x = 60; x <= 63; x++) {
						f1[x]->draw2(600,  0+ (x - 60) * 150, rob.getimageX(), rob.getimageY(), 2);
					}
					*/


					
					//small stone
					//xx&yy=絕對座標位置 ix&iy=背景座標位置 zoom=縮放倍率(長寬一致) disX=移動距離 speed=移動速度 XY(true)=左右移動 back(true)=會回彈
					
					//for (int x = 20; x <= 25; x++) {
					//	f1[x]->draw3(2480, 200 + (50 * x), rob.getimageX(), rob.getimageY(), 2, 500, 4, false, true);
					//}
					


					//stone
					f1[150]->draw2(0, 1960, rob.getimageX(), rob.getimageY(), 2);
					f1[151]->draw2(900, 1960, rob.getimageX(), rob.getimageY(), 2);
					f1[152]->draw2(600, 1660, rob.getimageX(), rob.getimageY(), 2);
					f1[153]->draw2(200, 1660, rob.getimageX(), rob.getimageY(), 2);
					f1[157]->draw2(0, 560, rob.getimageX(), rob.getimageY(), 2);
					f1[158]->draw2(200, 560, rob.getimageX(), rob.getimageY(), 2);
					f1[159]->draw2(650, 560, rob.getimageX(), rob.getimageY(), 2);
					f1[160]->draw2(850, 560, rob.getimageX(), rob.getimageY(), 2);
					f1[161]->draw2(1050, 560, rob.getimageX(), rob.getimageY(), 2);
					for (int x = 162; x <= 178; x++) {
						f1[x]->draw2(1250, 560 + (x - 162) * 100, rob.getimageX(), rob.getimageY(), 2);
					}
					f1[179]->draw2(1450, 2060, rob.getimageX(), rob.getimageY(), 2);
					for (int x = 180; x <= 181; x++) {
						f1[x]->draw2(1650 + (x - 180) * 200, 1760, rob.getimageX(), rob.getimageY(), 2);
					}
					for (int x = 182; x <= 207; x++) {
						f1[x]->draw2(1850 , 1660 - (x - 182) * 100, rob.getimageX(), rob.getimageY(), 2);
					}
					for (int x = 208; x <= 223; x++) {
						f1[x]->draw2(2700, 560 + (x - 208) * 100, rob.getimageX(), rob.getimageY(), 2);
					}
					f1[224]->draw2(3100, 460, rob.getimageX(), rob.getimageY(), 2);
					for (int x = 225; x <= 229; x++) {
						f1[x]->draw2(3700, 0 + (x - 225) * 100, rob.getimageX(), rob.getimageY(), 2);
					}
					for (int x = 230; x <= 232; x++) {
						f1[x]->draw2(3140 + (x - 230) * 200, 2060 , rob.getimageX(), rob.getimageY(), 2);
					}
					for (int x = 233; x <= 234; x++) {
						f1[x]->draw2(3140 + (x - 233) * 200, 1660, rob.getimageX(), rob.getimageY(), 2);
					}
					for (int x = 235; x <= 238; x++) {
						f1[x]->draw2(3240, 1560 - (x - 235) * 100, rob.getimageX(), rob.getimageY(), 2);
					}
					f1[239]->draw2(3540, 1260, rob.getimageX(), rob.getimageY(), 2);
					for (int x = 240; x <= 242; x++) {
						f1[x]->draw2(3100, 560 + (x - 240) * 100, rob.getimageX(), rob.getimageY(), 2);
					}

					//bird
					for (int x = 0; x < 20; x++) {
						bool temp = bird[x]->randomwalk();
						if (!f1[x + 81]->getthro()) {
							f1[x + 81]->setthro(temp);
							f1[x + 81]->setthroposi(bird[x]->getX(), bird[x]->getY());
						}
						bird[x]->draw(rob.getimageX(), rob.getimageY(), 2);
						f1[x + 81]->draw4(rob.getimageX(), rob.getimageY(),2, 500, 5);
					}

					//star
					if (setstar == 0)
					{
						setstar = 1;
					}
				}
				/*************** 2nd background ************/
				//0傳送門 1~9為冰塊 10~20為沙子 21~50箱子 51~80牆壁 81~150為小石頭 150~石頭
				

				else if (sb.getprojection() == 2) {
					if (umbrella.getexist())
						umbrella.draw2(500, 500, rob.getimageX(), rob.getimageY(), 2, sb.getX(), sb.getY(), 2);
					if (ttf == 1) 
					{
						energytime.setenergy(20);
						ttf = 2;
					}
					if (setstar == 1)
					{
						setstar = 2;
					}
					//door
					f2[0]->draw2(2540, 700, rob.getimageX(), rob.getimageY(), 2);
					// 
					//ice
					f2[1]->draw3(0, 2060, rob.getimageX(), rob.getimageY(), 2, 300, 3, true, true, false);
					//f2[2]->draw3(1300, 2060, rob.getimageX(), rob.getimageY(), 2, 300, 4, true, true, false);
					f2[3]->draw3(2040, 1900, rob.getimageX(), rob.getimageY(), 2, 300, 4, true, true, true);

					//sand
					f2[10]->draw2(650, 2060, rob.getimageX(), rob.getimageY(), 2);
					f2[11]->draw2(950, 2060, rob.getimageX(), rob.getimageY(), 2);
					f2[12]->draw2(2640, 1700, rob.getimageX(), rob.getimageY(), 2);
					for (int x = 13; x <= 15; x++) {
						f2[x]->draw2(1400 + (x - 13) * 200, 350, rob.getimageX(), rob.getimageY(), 2);
					}
					//box
					f2[21]->draw2(700, 1700, rob.getimageX(), rob.getimageY(), 2);
					for (int x = 22; x <= 26; x++) {
						f2[x]->draw2(700 + (x - 22) * 100, 550, rob.getimageX(), rob.getimageY(), 2);
					}
					for (int x = 27; x <= 28; x++) {
						f2[x]->draw2(3740 + (x - 27) * 100, 450, rob.getimageX(), rob.getimageY(), 2);
					}
					//wall

					for (int x = 51; x <= 53; x++) {
						f2[x]->draw2(357, 0 + (x - 51) * 150, rob.getimageX(), rob.getimageY(), 2);
					}

					for (int x = 54; x <= 55; x++) {
						f2[x]->draw2(580, 1860 + (x - 54) * 150, rob.getimageX(), rob.getimageY(), 2);
					}
					for (int x = 56; x <= 57; x++) {
						f2[x]->draw2(880, 1860 + (x - 56) * 150, rob.getimageX(), rob.getimageY(), 2);
					}
					/*
					for (int x = 58; x <= 59; x++) {
						f2[x]->draw2(1180, 1860 + (x - 58) * 150, rob.getimageX(), rob.getimageY(), 2);
					}*/
					for (int x = 60; x <= 62; x++) {
						f2[x]->draw2(2240, 0 + (x - 60) * 150, rob.getimageX(), rob.getimageY(), 2);
					}

					f2[63]->draw2(2320, 1550, rob.getimageX(), rob.getimageY(), 2);//要回復!

						//small stone
					for (int x = 81; x <= 88; x++) {
						f2[x]->draw3(800 - (50 * (81 - x)), 750, rob.getimageX(), rob.getimageY(), 2, 600, 4, true, true, true);
					}
					for (int x = 89; x <= 96; x++) {
						f2[x]->draw3(150 + (50 * (89 - x)), 1080, rob.getimageX(), rob.getimageY(), 2, 600, 4, true, true, false);
					}
					for (int x = 97; x <= 104; x++) {
						f2[x]->draw3(800 - (50 * (97 - x)), 1410, rob.getimageX(), rob.getimageY(), 2, 600, 4, true, true, true);
					}
					//
					for (int x = 105; x <= 111; x++) {
						f2[x]->draw3(1500 + (50 * (x - 105)), 600, rob.getimageX(), rob.getimageY(), 2, 400, 3, true, true, false);
					}
					for (int x = 112; x <= 118; x++) {
						f2[x]->draw3(2200 - (50 * (x - 112)), 900, rob.getimageX(), rob.getimageY(), 2, 400, 3, true, true, true);
					}
					for (int x = 119; x <= 125; x++) {
						f2[x]->draw3(1600 + (50 * (x - 119)), 1200, rob.getimageX(), rob.getimageY(), 2, 400, 3, true, true, false);
					}
					for (int x = 126; x <= 132; x++) {
						f2[x]->draw3(2200 - (50 * (x - 126)), 1500, rob.getimageX(), rob.getimageY(), 2, 400, 3, true, true, true);
					}

					//
					for (int x = 133; x <= 135; x++) {
						f2[x]->draw3(2940, 350 + (40 * (x - 133)), rob.getimageX(), rob.getimageY(), 2, 250, 3, false, true, true);
					}
					for (int x = 136; x <= 138; x++) {
						f2[x]->draw3(3240, 400 + (40 * (x - 136)), rob.getimageX(), rob.getimageY(), 2, 250, 3, false, true, true);
					}
					for (int x = 139; x <= 144; x++) {
						f2[x]->draw3(3240 + (50 * (x - 139)), 1100, rob.getimageX(), rob.getimageY(), 2, 200, 3, true, true, false);
					}
					for (int x = 145; x <= 149; x++) {
						f2[x]->draw3(2940, 600 + (50 * (x - 145)), rob.getimageX(), rob.getimageY(), 2, 200, 3, false, true, false);
					}
					/*
					for (int x = 148; x <= 159; x++) {
						f2[x]->draw3(2940 , 1200 - (50 * (x - 145)), rob.getimageX(), rob.getimageY(), 2, 200, 3, false, true, true);
					}
					*/
					/*
					for (int x = 148; x <= 152; x++) {
						f2[x]->draw3(3040, 1500 + (50 * (x - 148)), rob.getimageX(), rob.getimageY(), 2, 200, 3, false, true, true);
					}
					for (int x = 152; x <= 156; x++) {
						f2[x]->draw3(3240, 1500 + (50 * (x - 148)), rob.getimageX(), rob.getimageY(), 2, 200, 3, false, true, true);
					}
					for (int x = 157; x <= 161; x++) {
						f2[x]->draw3(3440, 1500 + (50 * (x - 148)), rob.getimageX(), rob.getimageY(), 2, 200, 3, false, true, true);
					}
					*/
					//stone
					for (int x = 150; x <= 151; x++) {
						f2[x]->draw2(0 + (x - 150) * 200, 450, rob.getimageX(), rob.getimageY(), 2);
					}
					for (int x = 152; x <= 153; x++) {
						f2[x]->draw2(300 + (x - 152) * 200, 1700, rob.getimageX(), rob.getimageY(), 2);
					}
					for (int x = 154; x <= 157; x++) {
						f2[x]->draw2(800 + (x - 154) * 200, 1700, rob.getimageX(), rob.getimageY(), 2);
					}

					for (int x = 159; x <= 175; x++) {
						f2[x]->draw2(1200, 1600 - (x - 159) * 100, rob.getimageX(), rob.getimageY(), 2);
					}
					//f2[175]->draw2(1200, 0, rob.getimageX(), rob.getimageY(), 2);
					f2[176]->draw2(1400, 350, rob.getimageX(), rob.getimageY(), 2);
					for (int x = 177; x <= 183; x++) {
						f2[x]->draw2(2240 + (x - 177) * 200, 450, rob.getimageX(), rob.getimageY(), 2);
					}
					f2[184]->draw2(2640, 350, rob.getimageX(), rob.getimageY(), 2);
					f2[185]->draw2(3040, 0, rob.getimageX(), rob.getimageY(), 2);
					f2[186]->draw2(3440, 350, rob.getimageX(), rob.getimageY(), 2);
					for (int x = 187; x <= 195; x++) {
						f2[x]->draw2(2240, 550 + (x - 187) * 100, rob.getimageX(), rob.getimageY(), 2);
					}
					for (int x = 196; x <= 200; x++) {
						f2[x]->draw2(2240, 1700 + (x - 196) * 100, rob.getimageX(), rob.getimageY(), 2);
					}
					for (int x = 201; x <= 206; x++) {
						f2[x]->draw2(2440 + (x - 201) * 200, 1350, rob.getimageX(), rob.getimageY(), 2);
					}
					f2[207]->draw2(2640, 250, rob.getimageX(), rob.getimageY(), 2);
					//f2[208]->draw2(3040, 100, rob.getimageX(), rob.getimageY(), 2);
					f2[209]->draw2(3440, 250, rob.getimageX(), rob.getimageY(), 2);
					f2[210]->draw2(2240, 1450, rob.getimageX(), rob.getimageY(), 2);
					for (int x = 211; x <= 212; x++) {
						f2[x]->draw2(1600 + (x - 211) * 200, 1700, rob.getimageX(), rob.getimageY(), 2);
					}
					for (int x = 213; x <= 214; x++) {
						f2[x]->draw2(2440 + (x - 213) * 200, 950, rob.getimageX(), rob.getimageY(), 2);
					}

					f2[215]->draw2(1400, 2060, rob.getimageX(), rob.getimageY(), 2);
					f2[216]->draw2(1600, 2060, rob.getimageX(), rob.getimageY(), 2);


				}
				else if (sb.getprojection() == 3) {
				window.clear();
				Text win("WOW you win!!", "../fonts/lazy.ttf", 72, TTF_STYLE_UNDERLINE | TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 750, (1080 / 2) - 40 }, { NULL, NULL }, NULL, no, 100);
				Text loser("click here", "../fonts/lazy.ttf", 72, TTF_STYLE_UNDERLINE | TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 900, 650 }, { NULL, NULL }, NULL, no, 100);
				Mixer m3("../audio/cloudmonster.mp3", MUSIC);
				Background winbg("../images/winner.png", window.getRenderer());
				winbg.setPosition(0, 0);
				winbg.setAlpha(155);
				winbg.draw();
				win.draw();
				loser.draw();
				const int n = 4;
				Sint16 vx4[n] = { 480,480,1920 - 480,1920 - 480 };
				Sint16 vy4[n] = { 600,900,900,600 };
				polygonRGBA(window.getRenderer(), vx4, vy4, n, 0xCC, 0xCC, 0x00, 0xAA);
				bool winc = true;
				m3.play(FOREVER)
					;
				survival.startTimer(0);
				int ST;
				ST = survival.getscore();
				fprintf(wf, "%d %d %d %d %d %d\n", (((ST / 100) / 60) / 10) % 6, ((ST / 100) / 60) % 10, (ST / 1000) % 6, (ST / 100) % 10, (ST / 10) % 10, ST % 10);
				fclose(wf);
				fo = true;

				tt8[0] = ((survival.getscore() % 10) + 48);
				//printf("%c ", tt8[0]);
				tt7[0] = (((survival.getscore() / 10) % 10) + 48);
				//printf("%c ", tt7[0]);
				//secind
				tt5[0] = (((survival.getscore() / 100) % 10) + 48);
				tt4[0] = (((survival.getscore() / 1000) % 6) + 48);
				//min
				tt2[0] = ((((survival.getscore() / 100) / 60) % 10) + 48);
				tt1[0] = (((((survival.getscore() / 100) / 60) / 10) % 6) + 48);
				Text Score("Survival time: ", "../fonts/lazy.ttf", 40, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 0, 238, 118 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 50,50 }, { NULL, NULL }, NULL, no, 100);
				Text Score1(tt1, "../fonts/lazy.ttf", 40, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 255, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 75,100 }, { NULL, NULL }, NULL, no, 100);
				Text Score2(tt2, "../fonts/lazy.ttf", 40, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 255, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 95,100 }, { NULL, NULL }, NULL, no, 100);
				Text Score3(":", "../fonts/lazy.ttf", 40, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 255, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 115,100 }, { NULL, NULL }, NULL, no, 100);
				Text Score4(tt4, "../fonts/lazy.ttf", 40, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 255, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 135,100 }, { NULL, NULL }, NULL, no, 100);
				Text Score5(tt5, "../fonts/lazy.ttf", 40, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 255, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 155,100 }, { NULL, NULL }, NULL, no, 100);
				Text Score6(":", "../fonts/lazy.ttf", 40, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 255, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 175,100 }, { NULL, NULL }, NULL, no, 100);
				Text Score7(tt7, "../fonts/lazy.ttf", 40, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 255, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 195,100 }, { NULL, NULL }, NULL, no, 100);
				Text Score8(tt8, "../fonts/lazy.ttf", 40, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 255, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 215,100 }, { NULL, NULL }, NULL, no, 100);

				Score.draw();
				Score1.draw();
				Score2.draw();
				Score3.draw();
				Score4.draw();
				Score5.draw();
				Score6.draw();
				Score7.draw();
				Score8.draw();
				window.display();

				while (winc) {
					while (SDL_PollEvent(&e) != 0)
					{
						//User requests quit
						if (e.type == SDL_QUIT)
						{
							winc = false;
							quit2 = false;
						}
						mouseHandleEvent(&e, &ms);
					}

					switch (ms.state)
					{
					case NONE:
						break;
					case IN_LB_SC:  // Inside, Left Button, Single Click
						if (ms.x >= 480 && ms.x <= 1920 - 480 && ms.y >= 600 && ms.y <= 900) {
							winc = false;
							quit2 = false;
						}
						ms.state = NONE;
						break;
					}
				}
				win.close();
				m3.close();
				loser.close();
				winbg.close();
				Score.close();
				Score1.close();
				Score2.close();
				Score3.close();
				Score4.close();
				Score5.close();
				Score6.close();
				Score7.close();
				Score8.close();
				break;
				}
				if(setstar == 1)
				{
					for (int x = 0; x < 200; x++) {
						if (s1 == x) {
							st[0]->randomstar(f1[x]->getfloorx() - st[0]->getWidth2() / 2, f1[x]->getfloory() - st[0]->getHeight2());
						}
						if (s2 == x) {
							st[1]->randomstar(f1[x]->getfloorx() - st[1]->getWidth2() / 2, f1[x]->getfloory() - st[1]->getHeight2());
						}
						if (s3 == x) {
							st[2]->randomstar(f1[x]->getfloorx() - st[2]->getWidth2() / 2, f1[x]->getfloory() - st[2]->getHeight2());
						}
					}
				}
				if (setstar == 2)
				{
					for (int x = 150; x < 200; x++) {
						if (s5 == x) {
							st[3]->randomstar(f2[x]->getfloorx() - st[3]->getWidth2() / 2, f2[x]->getfloory() - st[3]->getHeight2());
						}
						if (s6 == x) {
							st[4]->randomstar(f2[x]->getfloorx() - st[4]->getWidth2() / 2, f2[x]->getfloory() - st[4]->getHeight2());
						}
						if (s7 == x) {
							st[5]->randomstar(f2[x]->getfloorx() - st[5]->getWidth2() / 2, f2[x]->getfloory() - st[5]->getHeight2());
						}
					}
				}
				//star
				if (setstar == 1)
				{
					for (int x = 1; x < 3; x++) {
						if (st[x]->getexist())
							st[x]->draw2();
						else
						{
							if (st[x]->geteated() == 0)//當第一次碰到該位置時可以進入
							{
								st[x]->seteated(1);
								//energytime.plusE(1);  //能量+1
								energytime = energytime + 1;
								if (energytime.getenergy() > 20)  //能量>20 則 能量=20
								{
									energytime.setenergy(20);
								}
							}
						}
					}
					
				}

				//
				if (setstar == 2)
				{
					for (int x = 3; x < 6; x++) {
						if (st[x]->getexist())
							st[x]->draw2();
						else
						{
							if (st[x]->geteated() == 0)//當第一次碰到該位置時可以進入
							{
								st[x]->seteated(1);
								//energytime.plusE(1);  //能量+1
								energytime = energytime + 1;
								if (energytime.getenergy() > 20)  //能量>20 則 能量=20
								{
									energytime.setenergy(20);
								}
							}
						}
					}

				}
	
				//energy
				energy.setenergy(energytime.getenergy());
				//printf_s("%d\t", energytime.getenergy());
				energy.draw2();
				//survival time
				t1.draw();
				t2.draw();
				t3.draw();
				t4.draw();
				t5.draw();
				t6.draw();
				t7.draw();
				t8.draw();
				if (sb.getprojection() == 1) {
					
					for (int x = 0; x < 300; x++) {
						if (x == 0 || x == 51 || x== 52 || x==53 || x==54 ||x== 55|| x==56||x==57||x==58||x==59)
							f1[x]->touch(sb, energytime);
						else {
							f1[x]->touch(sb, energytime);
							f1[x]->touch2(sb);
							if (x < 3) {
								st[x]->eatstar(sb);
							}
						}
					}
					//Item
					umbrella.touchItem(sb);
				}
				if (sb.getprojection() == 2)
				{
					for (int x = 0; x < 300; x++) {
						if (x == 0 ||x==51||x==52||x==53 || x == 54 || x == 55 || x == 56 || x == 57 || x == 58 || x == 59 || x == 60 || x == 61 || x == 62 || x == 63)
							f2[x]->touch(sb, energytime);
						else {
							f2[x]->touch(sb, energytime);
							f2[x]->touch2(sb);
							if (x < 6 && x >2) {
								st[x]->eatstar(sb);
							}
						}
					}
					umbrella.touchItem(sb);
				}
				sb.draw2();
				rob.setprojection(sb.getprojection());
				if (energy.getenergy() <= 1) {
					//0612
					survival.startTimer(0);
					int ST;
					ST = survival.getscore();
					fprintf(wf,"%d %d %d %d %d %d\n", (((ST / 100) / 60) / 10) % 6, ((ST / 100) / 60) % 10, (ST / 1000) % 6, (ST / 100) % 10, (ST / 10) % 10, ST % 10);
					fclose(wf);
					fo = true;
	
					bool gameover = true;
					window.clear();
					Text over("Game over loser", "../fonts/lazy.ttf", 72, TTF_STYLE_UNDERLINE | TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 750, (1080 / 2) - 40 }, { NULL, NULL }, NULL, no, 100);
					Mixer m3("../audio/dark.mp3", MUSIC);
					const int n = 4;
					Sint16 vx4[n] = { 480,480,1920 - 480,1920 - 480 };
					Sint16 vy4[n] = { 600,900,900,600 };
					polygonRGBA(window.getRenderer(), vx4, vy4, n, 0xCC, 0xCC, 0x00, 0xAA);
					Text loser("Loser", "../fonts/lazy.ttf", 72, TTF_STYLE_UNDERLINE | TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 900, 650 }, { NULL, NULL }, NULL, no, 100);

					tt8[0] = ((survival.getscore() % 10) + 48);
					//printf("%c ", tt8[0]);
					tt7[0] = (((survival.getscore() / 10) % 10) + 48);
					//printf("%c ", tt7[0]);
					//secind
					tt5[0] = (((survival.getscore() / 100) % 10) + 48);
					tt4[0] = (((survival.getscore() / 1000) % 6) + 48);
					//min
					tt2[0] = ((((survival.getscore() / 100) / 60) % 10) + 48);
					tt1[0] = (((((survival.getscore() / 100) / 60) / 10) % 6) + 48);
					Text Score("Survival time: ", "../fonts/lazy.ttf", 40, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 0, 238, 118 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 50,50 }, { NULL, NULL }, NULL, no, 100);
					Text Score1(tt1, "../fonts/lazy.ttf", 40, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 255, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 75,100 }, { NULL, NULL }, NULL, no, 100);
					Text Score2(tt2, "../fonts/lazy.ttf", 40, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 255, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 95,100 }, { NULL, NULL }, NULL, no, 100);
					Text Score3(":", "../fonts/lazy.ttf", 40, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 255, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 115,100 }, { NULL, NULL }, NULL, no, 100);
					Text Score4(tt4, "../fonts/lazy.ttf", 40, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 255, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 135,100 }, { NULL, NULL }, NULL, no, 100);
					Text Score5(tt5, "../fonts/lazy.ttf", 40, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 255, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 155,100 }, { NULL, NULL }, NULL, no, 100);
					Text Score6(":", "../fonts/lazy.ttf", 40, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 255, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 175,100 }, { NULL, NULL }, NULL, no, 100);
					Text Score7(tt7, "../fonts/lazy.ttf", 40, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 255, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 195,100 }, { NULL, NULL }, NULL, no, 100);
					Text Score8(tt8, "../fonts/lazy.ttf", 40, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 255, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 215,100 }, { NULL, NULL }, NULL, no, 100);

					over.draw();

					Score.draw();
					Score1.draw();
					Score2.draw();
					Score3.draw();
					Score4.draw();
					Score5.draw();
					Score6.draw();
					Score7.draw();
					Score8.draw();

					loser.draw();
					m3.play(FOREVER);
					window.display();
					while (gameover) {
						while (SDL_PollEvent(&e) != 0)
						{
							//User requests quit
							if (e.type == SDL_QUIT)
							{
								gameover = false;
								quit2 = false;
							}
							mouseHandleEvent(&e, &ms);
						}

						switch (ms.state)
						{
						case NONE:
							break;
						case IN_LB_SC:  // Inside, Left Button, Single Click
							if (ms.x >= 480 && ms.x <= 1920 - 480 && ms.y >= 600 && ms.y <= 900) {
								gameover = false;
								quit2 = false;
							}
							ms.state = NONE;
							break;
						}
					}
					m3.close();
					over.close();

					Score.close();
					Score1.close();
					Score2.close();
					Score3.close();
					Score4.close();
					Score5.close();
					Score6.close();
					Score7.close();
					Score8.close();

					loser.close();
				}

				Sint16 vx5[n] = { 810,810,1110,1110 };
				Sint16 vy5[n] = { 390,690,690,390 };
				polygonRGBA(window.getRenderer(), vx5, vy5, n, 0xCC, 0xCC, 0x00, 0xAA);
				window.display();
			}
			sb.close();
			rob.close();
			for (int x = 0; x < 300; x++) {
				f1[x]->close();
				f2[x]->close();
				if (x < 6) {
					st[x]->close();
				}
			}
			for (int x = 0; x < 42; x++) {
				ff[x]->close();
				if (x < 6) {
					st[x]->close();
				}
			}
			for (int x = 0; x < 20; x++) {
				bird[x]->close();
			}
			ff.clear();
			bird.clear();
			st.clear();
			energy.close();
			m1.play(FOREVER);
			umbrella.close();
			survival.close();
			actionStatus = none;
		}
		else if (li == 2) {
			window.clear();
			bool quit = false;
			bool quit2 = true;
			//background totoro("../images/02.png", window.getRenderer());
			Text retur("Return", "../fonts/lazy.ttf", 35, TTF_STYLE_UNDERLINE | TTF_STYLE_BOLD, { 255,255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 20, 1000 }, { NULL, NULL }, NULL, no, 255);

			Text story("Story", "../fonts/lazy.ttf", 50, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 255,255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 1920 / 2 - 100, 100 }, { NULL, NULL }, NULL, no, 255);
			Text story1("The cute Totoro is locked in the forest! Please help him to find the way home.", "../fonts/lazy.ttf", 30, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 255,255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 150, 180 }, { NULL, NULL }, NULL, no, 255);
			Text story2("Move the Totoro by keyboard to eat the star and keep the life energy before it", "../fonts/lazy.ttf", 30, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 255,255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 150, 210 }, { NULL, NULL }, NULL, no, 255);
			Text story3("getting lose, and click the mouse to teleport immediately.", "../fonts/lazy.ttf", 30, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 255, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 150, 240 }, { NULL, NULL }, NULL, no, 255);
			Text story4("Be careful!!!", "../fonts/lazy.ttf", 30, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 255,255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 150, 270 }, { NULL, NULL }, NULL, no, 255);

			Text story6("How to play?", "../fonts/lazy.ttf", 50, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 255,255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 1920 / 2 - 200, 330 }, { NULL, NULL }, NULL, no, 255);

			int M = 30;
			Background esc("../images/esc.png", window.getRenderer());
			Background Shift("../images/Shift.png", window.getRenderer());
			Background Space("../images/Space.png", window.getRenderer());
			Background movestory("../images/move.png", window.getRenderer());
			Background mouse("../images/mouse.png", window.getRenderer());
			Background unbrella("../images/umbrella.png", window.getRenderer());
			Background sta("../images/sta.png", window.getRenderer());
			Background stb("../images/stb.png", window.getRenderer());
			Background ste("../images/ste.png", window.getRenderer());

			Text st1("pause", "../fonts/lazy.ttf", 30, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 255,255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 100 + M + 10, 470 + M + 60 }, { NULL, NULL }, NULL, no, 255);
			Text st2("Run", "../fonts/lazy.ttf", 30, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 255,255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 70 + M + 10, 570 + M + 60 }, { NULL, NULL }, NULL, no, 255);
			Text st3("Move", "../fonts/lazy.ttf", 30, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 255,255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 220 + M + 60, 470 + M + 130 }, { NULL, NULL }, NULL, no, 255);
			Text st4("Jump", "../fonts/lazy.ttf", 30, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 255,255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 200 + M + 70, 630 + M + 60 }, { NULL, NULL }, NULL, no, 255);
			Text st5("Shoot the", "../fonts/lazy.ttf", 30, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 255,255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 450 + M - 60, 500 + M - 30 }, { NULL, NULL }, NULL, no, 255);
			Text st5_2("object", "../fonts/lazy.ttf", 30, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 255,255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 450 + M - 60, 500 + M }, { NULL, NULL }, NULL, no, 255);
			Text st6("Teleport", "../fonts/lazy.ttf", 30, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 255,255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 450 + M + 100, 520 + M - 45 }, { NULL, NULL }, NULL, no, 255);

			Text st7("Life energy", "../fonts/lazy.ttf", 30, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 255,255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 930, 505 }, { NULL, NULL }, NULL, no, 255);
			Text st8("Star", "../fonts/lazy.ttf", 30, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 255,255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 815, 570 }, { NULL, NULL }, NULL, no, 255);
			Text st9("Box", "../fonts/lazy.ttf", 30, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 255,255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 878, 645 }, { NULL, NULL }, NULL, no, 255);
			Text st10("Magic tools", "../fonts/lazy.ttf", 30, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 255,255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 1120 + 60, 507 }, { NULL, NULL }, NULL, no, 255);

			Star story5("../images/story/", 3, window.getRenderer());

			Mixer m2("../audio/life.mp3", MUSIC);
			Sint16 vx4[n] = { 0,0,100,100 };
			Sint16 vy4[n] = { 1030,1080,1080,1030 };
			polygonRGBA(window.getRenderer(), vx4, vy4, n, 0xCC, 0xCC, 0x00, 0xAA);
			Sint16 vx5[n] = { 100,100,(1920 / 2) - 100,(1920 / 2) - 100 };
			Sint16 vy5[n] = { 100,930,930,100 };
			polygonRGBA(window.getRenderer(), vx5, vy5, n, 0xCC, 0xCC, 0x00, 0xAA);
			//backgroud
			SDL_SetRenderDrawColor(window.getRenderer(), 0, 0, 0, 200);
			SDL_RenderClear(window.getRenderer());


			story.draw();
			story1.draw();
			story2.draw();
			story3.draw();
			story4.draw();
			story6.draw();

			story5.setPosition(1420, 781);
			story5.startTimer(100);


			esc.draw3(100 + M, 470 + M, 122, 58);
			Shift.draw3(70 + M, 570 + M, 84, 48);
			movestory.draw3(220 + M, 470 + M, 168, 167);
			Space.draw3(200 + M, 630 + M, 209, 51);
			mouse.draw3(450 + M, 500 + M, 178, 188);

			st1.draw();
			st2.draw();
			st3.draw();
			st4.draw();
			st5.draw();
			st5_2.draw();
			st6.draw();
			st7.draw();
			st8.draw();
			st9.draw();
			st10.draw();

			ste.draw3(770, 505, 148, 24);
			sta.draw3(770, 565, 39, 39);
			stb.draw3(770, 635, 100, 50);
			unbrella.draw3(1120, 490, 53, 53);
			retur.draw();
			m2.play(FOREVER);
			window.display();
			while (!quit && quit2)
			{
				story5.draw2();
				window.display();
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					mouseHandleEvent(&e, &ms);
				}
				switch (ms.state)
				{
				case NONE:
					break;
				case IN_LB_SC:  // Inside, Left Button, Single Click
					if (ms.x >= 0 && ms.x <= 180 && ms.y >= 950 && ms.y <= 1080) {
						quit2 = false;
					}
					ms.state = NONE;
					break;
				}
			}
			story.close();
			story1.close();
			story2.close();
			story3.close();
			story4.close();
			story5.close();
			story6.close();

			esc.close();
			Shift.close();
			Space.close();
			movestory.close();
			mouse.close();

			st1.close();
			st2.close();
			st3.close();
			st4.close();
			st5.close();
			st5_2.close();
			st6.close();
			st7.close();
			st8.close();
			st9.close();
			st10.close();

			unbrella.close();
			sta.close();
			stb.close();
			ste.close();

			retur.close();
			m2.close();
			m1.play(FOREVER);

		}
		//0613
		else if (li == 3)
		{
			fclose(wf);//先把資料夾關閉
			fo = true;

			window.clear();
			bool quit = false;
			bool quit2 = true;

			Text retur("Return", "../fonts/lazy.ttf", 35, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 255, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 40, 1025 }, { NULL, NULL }, NULL, no, 255);
			Mixer m2("../audio/life.mp3", MUSIC);
			Star story5("../images/story/", 3, window.getRenderer());

			retur.draw();
			m2.play(FOREVER);

			story5.setPosition(1420, 781);
			story5.startTimer(100);
			/*
			//backgroud
			SDL_SetRenderDrawColor(window.getRenderer(), 113, 203, 255, 150);
			SDL_RenderClear(window.getRenderer());
			//排名板底色
			boxRGBA(window.getRenderer(), 1360, 140, 560, 940, 255, 231, 186, 255);

			thickLineRGBA(window.getRenderer(), 550, 140, 1370, 140, 10, 139, 126, 102, 255);
			thickLineRGBA(window.getRenderer(), 555, 140, 555, 950, 10, 139, 126, 102, 255);
			thickLineRGBA(window.getRenderer(), 550, 946, 1370, 946, 10, 139, 126, 102, 255);
			thickLineRGBA(window.getRenderer(), 1366, 140, 1366, 950, 10, 139, 126, 102, 255);
			
			boxRGBA(window.getRenderer(), 1260, 190, 660, 290, 139, 126, 102, 150);
			boxRGBA(window.getRenderer(), 1260, 340, 660, 440, 139, 126, 102, 150);
			boxRGBA(window.getRenderer(), 1260, 490, 660, 590, 139, 126, 102, 150);
			boxRGBA(window.getRenderer(), 1260, 640, 660, 740, 139, 126, 102, 150);
			

			window.display();
			*/
			//rf = fopen("../Score.txt", "r");
			int x1, x2, x3, x4 ,x5, x6;
			if ((erf = fopen_s(&rf, "../Score.txt", "r")) != 0) 
			{
				//fscanf_s(rf, "%d %d %d %d %d %d", &x1, &x2,&x3, &x4, &x5, &x6,1);
				//printf("%d %d : %d %d : %d %d\n", x1, x2, x3, x4, x5, x6);
				printf("open error with Score.txt");
			}
			char **c;
			c = new char* [1000];
			for (int x = 0; x < 1000; x++)
				c[x] = new char[12];
			int k = 0;
			while (fgets(c[k], 12, rf) != NULL)
			{
				k++;
			}
			rsort(c, k);
			//binary
			ewb = fopen_s(&wb, "Score.dat", "wb");
			rewind(wb);

			for (int i = 0; i < k; i++)
				fwrite(c[i], 12000, 1, wb);

			fclose(wb);

			vector<Text*> Score1;

			ewb = fopen_s(&wb, "Score.dat", "rb");
			rewind(wb);
			char t[12000];
			int xx = 0;
			while (!feof(wb) && fread(t, 12000, 1, wb)) 
			{
				Score1.push_back(new Text(t, "../fonts/lazy.ttf", 100, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 0, 0, 0 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 650,195 + 150 * (xx % 4) }, { NULL, NULL }, NULL, no, 255));
				xx += 1;
				printf("%s g\n", t);
			}
			fclose(wb);

			//for (int x = 0; x < k; x++)
			//	printf("%s", c[x]);
			
			/*
			for (int x = 0; x < 4; x++)
				Score1[x]->draw();
			*/

			k = (k / 2);
			int state = 0;
			Text next("NextPage", "../fonts/lazy.ttf", 35, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 255, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 1050, 850 }, { NULL, NULL }, NULL, no, 255);
			Text Previous("Previous", "../fonts/lazy.ttf", 35, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 255, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 650, 850 }, { NULL, NULL }, NULL, no, 255);


			Text s1(":", "../fonts/lazy.ttf", 100, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 0, 0, 0 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 800, 190 }, { NULL, NULL }, NULL, no, 255);
			Text s2(":", "../fonts/lazy.ttf", 100, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 0, 0, 0 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 1000, 190 }, { NULL, NULL }, NULL, no, 255);
			Text s3(":", "../fonts/lazy.ttf", 100, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 0, 0, 0 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 800, 340 }, { NULL, NULL }, NULL, no, 255);
			Text s4(":", "../fonts/lazy.ttf", 100, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 0, 0, 0 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 1000, 340 }, { NULL, NULL }, NULL, no, 255);
			Text s5(":", "../fonts/lazy.ttf", 100, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 0, 0, 0 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 800, 490 }, { NULL, NULL }, NULL, no, 255);
			Text s6(":", "../fonts/lazy.ttf", 100, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 0, 0, 0 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 1000, 490 }, { NULL, NULL }, NULL, no, 255);
			Text s7(":", "../fonts/lazy.ttf", 100, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 0, 0, 0 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 800, 640 }, { NULL, NULL }, NULL, no, 255);
			Text s8(":", "../fonts/lazy.ttf", 100, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 0, 0, 0 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 1000, 640 }, { NULL, NULL }, NULL, no, 255);

			while (!quit && quit2)
			{	
				if (state == 0) 
				{
					window.clear();
					//backgroud
					SDL_SetRenderDrawColor(window.getRenderer(), 113, 203, 255, 150);
					SDL_RenderClear(window.getRenderer());
					//排名板底色
					boxRGBA(window.getRenderer(), 1360, 140, 560, 940, 255, 231, 186, 255);

					thickLineRGBA(window.getRenderer(), 550, 140, 1370, 140, 10, 139, 126, 102, 255);
					thickLineRGBA(window.getRenderer(), 555, 140, 555, 950, 10, 139, 126, 102, 255);
					thickLineRGBA(window.getRenderer(), 550, 946, 1370, 946, 10, 139, 126, 102, 255);
					thickLineRGBA(window.getRenderer(), 1366, 140, 1366, 950, 10, 139, 126, 102, 255);

					boxRGBA(window.getRenderer(), 1260, 190, 660, 290, 139, 126, 102, 150);
					boxRGBA(window.getRenderer(), 1260, 340, 660, 440, 139, 126, 102, 150);
					boxRGBA(window.getRenderer(), 1260, 490, 660, 590, 139, 126, 102, 150);
					boxRGBA(window.getRenderer(), 1260, 640, 660, 740, 139, 126, 102, 150);
					retur.draw();

					s1.draw();
					s2.draw();
					s3.draw();
					s4.draw();
					s5.draw();
					s6.draw();
					s7.draw();
					s8.draw();

					for (int x = 4 * state; x < (4 * (state + 1)); x++)
						Score1[x]->draw();

					next.draw();
					story5.draw2();
					window.display();
				}
				else if ((k % 4) == 0) 
				{
					if (state != 0 && state != (k / 4) - 1)
					{

						window.clear();
						//backgroud
						SDL_SetRenderDrawColor(window.getRenderer(), 113, 203, 255, 150);
						SDL_RenderClear(window.getRenderer());
						//排名板底色
						boxRGBA(window.getRenderer(), 1360, 140, 560, 940, 255, 231, 186, 255);

						thickLineRGBA(window.getRenderer(), 550, 140, 1370, 140, 10, 139, 126, 102, 255);
						thickLineRGBA(window.getRenderer(), 555, 140, 555, 950, 10, 139, 126, 102, 255);
						thickLineRGBA(window.getRenderer(), 550, 946, 1370, 946, 10, 139, 126, 102, 255);
						thickLineRGBA(window.getRenderer(), 1366, 140, 1366, 950, 10, 139, 126, 102, 255);

						boxRGBA(window.getRenderer(), 1260, 190, 660, 290, 139, 126, 102, 150);
						boxRGBA(window.getRenderer(), 1260, 340, 660, 440, 139, 126, 102, 150);
						boxRGBA(window.getRenderer(), 1260, 490, 660, 590, 139, 126, 102, 150);
						boxRGBA(window.getRenderer(), 1260, 640, 660, 740, 139, 126, 102, 150);
						retur.draw();

						s1.draw();
						s2.draw();
						s3.draw();
						s4.draw();
						s5.draw();
						s6.draw();
						s7.draw();
						s8.draw();

						for (int x = 4 * state; x < (4 * (state + 1)); x++)
							Score1[x]->draw();

						next.draw();
						Previous.draw();
						story5.draw2();
						window.display();
					}
					else if (state == (k / 4) - 1)
					{
						window.clear();
						//backgroud
						SDL_SetRenderDrawColor(window.getRenderer(), 113, 203, 255, 150);
						SDL_RenderClear(window.getRenderer());
						//排名板底色
						boxRGBA(window.getRenderer(), 1360, 140, 560, 940, 255, 231, 186, 255);

						thickLineRGBA(window.getRenderer(), 550, 140, 1370, 140, 10, 139, 126, 102, 255);
						thickLineRGBA(window.getRenderer(), 555, 140, 555, 950, 10, 139, 126, 102, 255);
						thickLineRGBA(window.getRenderer(), 550, 946, 1370, 946, 10, 139, 126, 102, 255);
						thickLineRGBA(window.getRenderer(), 1366, 140, 1366, 950, 10, 139, 126, 102, 255);

						boxRGBA(window.getRenderer(), 1260, 190, 660, 290, 139, 126, 102, 150);
						boxRGBA(window.getRenderer(), 1260, 340, 660, 440, 139, 126, 102, 150);
						boxRGBA(window.getRenderer(), 1260, 490, 660, 590, 139, 126, 102, 150);
						boxRGBA(window.getRenderer(), 1260, 640, 660, 740, 139, 126, 102, 150);
						retur.draw();

						s1.draw();
						s2.draw();
						s3.draw();
						s4.draw();
						s5.draw();
						s6.draw();
						s7.draw();
						s8.draw();

						for (int x = 4 * state; x < (4 * (state + 1)); x++)
							Score1[x]->draw();

						Previous.draw();
						story5.draw2();
						window.display();
					}
				}
				else if ((k % 4) != 0)
				{
					if (state != 0 && state != (k / 4))
					{

						window.clear();
						//backgroud
						SDL_SetRenderDrawColor(window.getRenderer(), 113, 203, 255, 150);
						SDL_RenderClear(window.getRenderer());
						//排名板底色
						boxRGBA(window.getRenderer(), 1360, 140, 560, 940, 255, 231, 186, 255);

						thickLineRGBA(window.getRenderer(), 550, 140, 1370, 140, 10, 139, 126, 102, 255);
						thickLineRGBA(window.getRenderer(), 555, 140, 555, 950, 10, 139, 126, 102, 255);
						thickLineRGBA(window.getRenderer(), 550, 946, 1370, 946, 10, 139, 126, 102, 255);
						thickLineRGBA(window.getRenderer(), 1366, 140, 1366, 950, 10, 139, 126, 102, 255);

						boxRGBA(window.getRenderer(), 1260, 190, 660, 290, 139, 126, 102, 150);
						boxRGBA(window.getRenderer(), 1260, 340, 660, 440, 139, 126, 102, 150);
						boxRGBA(window.getRenderer(), 1260, 490, 660, 590, 139, 126, 102, 150);
						boxRGBA(window.getRenderer(), 1260, 640, 660, 740, 139, 126, 102, 150);
						retur.draw();

						s1.draw();
						s2.draw();
						s3.draw();
						s4.draw();
						s5.draw();
						s6.draw();
						s7.draw();
						s8.draw();

						for (int x = 4 * state; x < (4 * (state + 1)); x++)
							Score1[x]->draw();

						next.draw();
						Previous.draw();
						story5.draw2();
						window.display();
					}
					else if (state == (k / 4))
					{
						window.clear();
						//backgroud
						SDL_SetRenderDrawColor(window.getRenderer(), 113, 203, 255, 150);
						SDL_RenderClear(window.getRenderer());
						//排名板底色
						boxRGBA(window.getRenderer(), 1360, 140, 560, 940, 255, 231, 186, 255);

						thickLineRGBA(window.getRenderer(), 550, 140, 1370, 140, 10, 139, 126, 102, 255);
						thickLineRGBA(window.getRenderer(), 555, 140, 555, 950, 10, 139, 126, 102, 255);
						thickLineRGBA(window.getRenderer(), 550, 946, 1370, 946, 10, 139, 126, 102, 255);
						thickLineRGBA(window.getRenderer(), 1366, 140, 1366, 950, 10, 139, 126, 102, 255);

						retur.draw();

						if (k % 4 == 1) 
						{
							boxRGBA(window.getRenderer(), 1260, 190, 660, 290, 139, 126, 102, 150);
							s1.draw();
							s2.draw();
						}
						else if (k % 4 == 2) 
						{
							boxRGBA(window.getRenderer(), 1260, 190, 660, 290, 139, 126, 102, 150);
							boxRGBA(window.getRenderer(), 1260, 340, 660, 440, 139, 126, 102, 150);
							s1.draw();
							s2.draw();
							s3.draw();
							s4.draw();
						}
						else 
						{
							boxRGBA(window.getRenderer(), 1260, 190, 660, 290, 139, 126, 102, 150);
							boxRGBA(window.getRenderer(), 1260, 340, 660, 440, 139, 126, 102, 150);
							boxRGBA(window.getRenderer(), 1260, 490, 660, 590, 139, 126, 102, 150);
							s1.draw();
							s2.draw();
							s3.draw();
							s4.draw();
							s5.draw();
							s6.draw();
						}

						for (int x = 4 * state; x < (4 * state) + (k % 4); x++)
							Score1[x]->draw();

						Previous.draw();
						story5.draw2();
						window.display();
					}
				}
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					mouseHandleEvent(&e, &ms);
				}
				switch (ms.state)
				{
				case NONE:
					break;
				case IN_LB_SC:  // Inside, Left Button, Single Click
					if (ms.x >= 0 && ms.x <= 180 && ms.y >= 950 && ms.y <= 1080) {
						quit2 = false;
					}
					if (ms.x >= 1020 && ms.x <= 1200 && ms.y >= 800 && ms.y <= 900)
					{
						if ((k%4)!=0) 
						{
							if(state < (k / 4))
								state += 1;
						}
						else
							if (state < (k / 4) - 1)
								state += 1;
						//printf("%d \n", state);
					}
					if (ms.x >= 620 && ms.x <= 800 && ms.y >= 800 && ms.y <= 900 && state != 0) {
						state -= 1;
						//printf("%d \n", state);
					}
					ms.state = NONE;
					break;
				}
			}
			retur.close();
			m2.close();
			m1.play(FOREVER);

			fclose(rf);
			for (int x = 0; x < 1000; x++)
				delete[] c[x];
			delete[] c;

			for (int x = 0; x < k; x++)
				Score1[x]->close();

			next.close();
			Previous.close();

			s1.close();
			s2.close();
			s3.close();
			s4.close();
			s5.close();
			s6.close();
			s7.close();
			s8.close();
		}
		li = 0;
	}
	//Free resources and close SDL
	rbtotoro1.close();
	rbtotoro2.close();
	rbtotoro3.close();
	story.close();
	m1.close();
	peko.close();
	start.close();
	leave.close();
	window.close();
	sdl.close();

	return 0;
}