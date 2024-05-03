#pragma once
#include "Role.h"


class Background :
    public Role
{
    public:
        // Ren 4/23
        Background();
        Background(const char* pa, SDL_Renderer* ren);
        void draw();
        void draw2(int vx,int vy);
        void changebackground();
        void setprojection(int posi);
        // Ren 4/24
        int getscreensize();
        int getscreenheigh();
        int getimageX();
        int getimageY();
        void setimageX(int xx);
        void setimageY(int yy);
        ~Background();
    private:
        SDL_DisplayMode DM;
        int width;
        int heigh;
        int imageX = 0;
        int imageY = 300;
        int projection=1;
        char file[100];
        char path[100];

};

