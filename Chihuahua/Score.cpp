#include "Score.h"
#include<stdio.h>;
Score::Score()
{
}
int Score::getscore()
{
	return score;
}
void Score::setscore(int a)
{
	score == a;
}
void Score::addscore(int a)
{
	score += a;
}

void Score::startTimer(Uint32 t)
{
	settime(t);
	settimeID(SDL_AddTimer(gettime(), causcore, this)); // Set Timer callback
}

Uint32 Score::causcore(Uint32 interval, void* param)
{
	Score* p = (Score*)param;

	if (p->gettime() != 0)
	{
		p->addscore(1);
		return interval;
	}

	else
	{
		return 0;
	}
}

Score::~Score()
{

}