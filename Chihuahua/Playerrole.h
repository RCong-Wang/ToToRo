#pragma once

#ifndef PLAYERROLE_H
#define PLAYERROLE_H

#include "Role.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h> // Using SDL
#include "SDL2_gfxPrimitives.h" // Using SDL2_gfx
#include "RenderWindow.h"
#include "System.h"
#include "constants.h"
#include "background.h"
#include <vector>
using namespace std;


struct Mouse
{
    MouseState state;
    int x;
    int y;
};
class Playerrole :
    public Role
{
public:
    Playerrole();
    Playerrole(const char* path, int n, int hhn, int wwn, SDL_Renderer* ren,int map);
    Playerrole(const char* path, int n, SDL_Renderer* ren, int map, Uint8 r, Uint8 g, Uint8 b);
    Playerrole(const char* path, int n, SDL_Renderer* ren, int map, Uint8 r, Uint8 g, Uint8 b, int seed);
    void mouseHandleEvent(SDL_Event* e);
    bool handlevent(SDL_Event& e, RenderWindow& win);
    int getprojection();
    void setprojection(int pp);
    //Uint32 setAction(Uint32 interval, void* param)
    //void setAngle(double a);
    Playerrole operator / (int i);


    // Lan 4/24
    int getVX();
    void setVX(int x);
    int getVY();
    void setVY(int y);
    void move(int imageX,int imageY,int yy);
    void setflag(bool);
    bool getflag();
    void statusAction(void);
    void Action(Background& bg);
    int getStatus();
    void setcharturn(bool charturn);
    void startTimer(Uint32 t);
    //Ren
    int getspeedX();
    int getspeedY();
    void setnowpos(int posi);
    int getmas();
    int getstay();
    void setstay(int v);
    int getfo();
    void setfo(int f);
    int getphy();
    void setphy(int ph);
    // Ren
    void draw(int ix, int iy, int zoom);
    void draw2();
    vector<Sint16> getvx();
    vector<Sint16> getvy();
    int getvxsize();
    void setvector(int xx,int yy);
    void setar(bool t);
    void setfriction(double fr);
    void setsilp(int s);
    int getsilp();
    int getimageVX();
    void setimageVX(int vvx);
    int getimageVY();
    void setimageVY(int vvy);
    void setoriposi(int xx, int yy,int bgx,int bgy);
    bool randomwalk();

    //0605
    void setspeed(int a);
    int getlist();
    void getv(int a);
    friend void move(Playerrole& pl);
    friend void reducemove(Playerrole& pl);
    ~Playerrole();
private:
    // Ren 4/23
    int mapsize;
    double angle;
    int p = 1;
    SDL_Point dir;
    SDL_DisplayMode DM;
    int v = 0;
    int phy=1;
    int fo;
    //Lan 4/24
    int wait=0;
    int status;
    int speed;
    int speedX;
    int speedY;
    bool flag;
    bool characterturn = false;
    static Uint32 changeRole(Uint32 interval, void* param); // Timer callback 
    int nowpos;
    //Ren
    int mas;
    int stay=0;
    Mouse m;
    vector<Sint16> vx, vy;
    SDL_TimerID arrow_ID;
    static Uint32 arrow(Uint32 interval, void* param);
    bool ar = false;
    bool arr = false;
    double friction = 1;
    int list=0;
    int silp = 0;
    int imageVX;
    int imageVY;
    int oriX;
    int oriY;
    int oribgX, oribgY;
    int randonmode;
    int shitposiX;
    int shitposiY;
    int shittime;
    bool thro;
};

#endif
