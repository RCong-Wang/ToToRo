#pragma once
#include "Role.h"
#include "Playerrole.h"
#include "Star.h"

struct position {
    int xx;
    int yy;
};
class Flor :
    public Role
{
    public:
        Flor();
        Flor(const char* path, SDL_Renderer* ren, double fr ,bool si,int num);
        void draw2(int xx, int yy, int ix, int iy, int zoom);
        void draw3(int xx, int yy, int ix, int iy, int zoom, int dis, int speed, bool XY, bool back,bool reverse);
        void draw4(int ix, int iy, int zoom, int dis, int speed);
        void draw(int xx, int yy,int dis);
        void touch(Playerrole& pl, Star& st); //判斷有沒有碰到
        void touch2(Playerrole& pl); //判斷有沒有碰到
        void Action(Playerrole &pl);
        void setturn(int pp);
        //ren
        int getXlen();
        int getYlen();
        //for star position
        int getfloorx();
        int getfloory();
        void print();
        void setthro(bool t);
        bool getthro();
        void setthroposi(int xx, int yy);
        ~Flor();
    private:
        int number;
        int itemStatus;//物品的狀態 
        int props;
        double friction;
        bool silp;
        bool havesilp;
        bool appear;
        int tt;
        int dist;
        int turn;
        static Uint32 disapp(Uint32 interval, void* param);
        SDL_TimerID disID;
        bool thro;
        int throX;
        int throY;
        bool reverse;//反向移動(下到上or右到左)
};

