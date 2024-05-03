#pragma once
#include "Role.h"
#include "Image.h"
#include <SDL.h>
class Score :
	public Role
{
public:
	Score();
	int getscore();
	void setscore(int);
	void addscore(int);
	void startTimer(Uint32 t);
	~Score();
private:
	static Uint32 causcore(Uint32 interval, void* param); // Timer callback
	int score;
};

