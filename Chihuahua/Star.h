#pragma once
#ifndef STAR_H
#define STAR_H

#include "Playerrole.h"
#include "Image.h"
#include <SDL.h>

class Star :
	public Role
{
public:
	Star();
	Star(const char* path, int n, SDL_Renderer* ren);
	void eatstar(Playerrole& pl); //�P�_���S���Y��P�P
	void randomstar(int xx, int yy);
	void setexist(bool);
	bool getexist();
	void setenergy(int e);
	void reduceE(int e);
	void plusE(int e);
	int getenergy();
	void seteated(int e);
	int geteated();
	friend int getenergy(Star* st);
	friend void setenergy(Star* st);
	void startTimer(Uint32 t);
	Star operator+ (int i);
	Star operator- (int i);
	~Star();
private:
	bool exist = true;
	int eated = 0;
	int energy = 20;//���q��2�h�C������
	static Uint32 timing(Uint32 interval, void* param); // Timer callback
};
#endif


