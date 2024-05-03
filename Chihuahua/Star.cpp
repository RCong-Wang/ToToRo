#include "Star.h"
#include "constants.h"
#include <stdio.h>
#include <math.h>
Star::Star(){}
Star::Star(const char* path, int n, SDL_Renderer* ren) : Role(path, n, ren)
{
}

void Star::randomstar(int xx, int yy)
{
	setPosition(xx, yy);
	//startTimer(125);
}

void Star::eatstar(Playerrole& pl)
{
	if (pl.getX() < getX()) {//玩家位於物體的左側
		if (pl.getY() < getY()) {//玩家位於物體的上方
			if (getX() - pl.getX() < pl.getWidth2()) {
				if (getY() - pl.getY() < pl.getHeight2()) {
					//碰到
					setexist(false);
				}
				else if (getY() - pl.getY() == pl.getHeight2()) {
					//碰到
					setexist(false);
				}
				else {
					//沒碰到

				}
			}
			else if (getX() - pl.getX() == pl.getWidth2()) {
				if (getY() - pl.getY() < pl.getHeight2()) {
					//沒碰到(先當沒碰到)

				}
				else if (getY() - pl.getY() == pl.getHeight2()) {
					//沒碰到(先當沒碰到)

				}
				else {
					//沒碰到

				}
			}
			else {
				//沒碰到

			}
		}
		else if (pl.getY() == getY()) {
			if (getX() - pl.getX() < pl.getWidth2()) {
				//碰到
				setexist(false);
			}
			else if (getX() - pl.getX() == pl.getWidth2()) {
				//沒碰到(先當沒碰到)

			}
			else {
				//沒碰到

			}
		}
		else {
			if (getX() - pl.getX() < pl.getWidth2()) {
				if (pl.getY() - getY() < getHeight()) {
					//碰到
					setexist(false);
				}
				else if (pl.getY() - getY() == getHeight()) {
					//先當沒碰到

				}
				else {
					//沒碰到

				}
			}
			else if (getX() - pl.getX() == pl.getWidth2()) {
				if (pl.getY() - getY() < getHeight()) {
					//先當沒碰到

				}
				else if (pl.getY() - getY() < getHeight()) {
					//先當沒碰到

				}
				else {
					//沒碰到

				}
			}
			else {
				//沒碰到

			}
		}

	}
	else if (pl.getX() == getX()) {
		if (pl.getY() < getY()) {
			if (getY() - pl.getY() < pl.getHeight2()) {
				//碰到
				setexist(false);
			}
			else if (getY() - pl.getY() == pl.getHeight2()) {
				//碰到
				setexist(false);
			}
			else {
				//沒碰到

			}

		}
		else if (pl.getY() == getY()) {
			//碰到
			setexist(false);
		}
		else {
			if (pl.getY() - getY() < getHeight()) {
				//碰到
				setexist(false);
			}
			else if (pl.getY() - getY() == getHeight()) {
				//先當沒碰到

			}
			else {
				//沒碰到

			}
		}
	}
	else {
		if (pl.getY() < getY()) {
			if (pl.getX() - getX() < pl.getWidth2()) {
				if (getY() - pl.getY() < pl.getHeight2()) {
					//碰到
					setexist(false);
				}
				else if (getY() - pl.getY() == pl.getHeight2()) {
					//碰到
					setexist(false);
				}
				else {
					//沒碰到

				}
			}
			else if (pl.getX() - getX() == getWidth()) {
				if (getY() - pl.getY() < pl.getHeight2()) {
					//先當沒碰到

				}
				else if (getY() - pl.getY() == pl.getHeight2()) {
					//先當沒碰到

				}
				else {
					//沒碰到

				}
			}
			else {
				//沒碰到

			}
		}
		else if (pl.getY() == getY()) {
			if (pl.getX() - getX() < getWidth()) {
				//碰到
				setexist(false);
			}
			else if (pl.getX() - getX() == getWidth()) {
				//先當沒碰到

			}
			else {
				//沒碰到

			}
		}
		else {
			if (pl.getX() - getX() < getWidth()) {
				if (pl.getY() - getY() < getHeight()) {
					//碰到
					setexist(false);
				}
				else if (pl.getY() - getY() == getHeight()) {
					//先當沒碰到
				}
				else {
					//沒碰到
				}
			}
			else if (pl.getX() - getX() == getWidth()) {
				if (pl.getY() - getY() < getHeight()) {
					//先當沒碰到
				}
				else if (pl.getY() - getY() == getHeight()) {
					//先當沒碰到
				}
				else {
					//沒碰到
				}
			}
			else {
				//沒碰到
			}
		}
	}
}

void Star::setexist(bool f)
{
	exist = f;
}
bool Star::getexist()
{
	return exist;
}

void Star::startTimer(Uint32 t)
{
	settime(t);
	settimeID(SDL_AddTimer(gettime(), timing, this)); // Set Timer callback
}

Uint32 Star::timing(Uint32 interval, void* param)
{
	Star* p = (Star*)param;

	if (p->gettime() != 0 && p->gettime() != 10 && p->gettime() < 1000)
	{
		p->setframe((p->getframe() + 1) % p->getnum());// image frame	
		return interval;
	}
	else if (p->gettime() == 10)
	{
		if (p->energy == 20)
		{
			p->setframe((p->getframe() - p->getframe() + 19));  // image frame
			//p->reduceE(1);
			return interval;
		}
		else if (p->energy == 19)
		{
			p->setframe((p->getframe() - p->getframe() + 18));  // image frame
			//p->reduceE(1);
			return interval;
		}
		else if (p->energy == 18)
		{
			p->setframe((p->getframe() - p->getframe() + 17));  // image frame
			//p->reduceE(1);
			return interval;
		}
		else if (p->energy == 17)
		{
			p->setframe((p->getframe() - p->getframe() + 16));  // image frame
			//p->reduceE(1);
			return interval;
		}
		else if (p->energy == 16)
		{
			p->setframe((p->getframe() - p->getframe() + 15));  // image frame
			//p->reduceE(1);
			return interval;
		}
		else if (p->energy == 15)
		{
			p->setframe((p->getframe() - p->getframe() + 14));  // image frame
			//p->reduceE(1);
			return interval;
		}
		else if (p->energy == 14)
		{
			p->setframe((p->getframe() - p->getframe() + 13));  // image frame
			//p->reduceE(1);
			return interval;
		}
		else if (p->energy == 13)
		{
			p->setframe((p->getframe() - p->getframe() + 12));  // image frame
			//p->reduceE(1);
			return interval;
		}
		else if (p->energy == 12)
		{
			p->setframe((p->getframe() - p->getframe() + 11));  // image frame
			//p->reduceE(1);
			return interval;
		}
		else if (p->energy == 11)
		{
			p->setframe((p->getframe() - p->getframe() + 10));  // image frame
			//p->reduceE(1);
			return interval;
		}
		else if (p->energy == 10)
		{
			p->setframe((p->getframe() - p->getframe() + 9));  // image frame
			//p->reduceE(1);
			return interval;
		}
		else if (p->energy == 9)
		{
			p->setframe((p->getframe() - p->getframe() + 8));  // image frame
			//p->reduceE(1);
			return interval;
		}
		else if (p->energy == 8)
		{
			p->setframe((p->getframe() - p->getframe() + 7));  // image frame
			//p->reduceE(1);
			return interval;
		}
		else if (p->energy == 7)
		{
			p->setframe((p->getframe() - p->getframe() + 6));  // image frame
			//p->reduceE(1);
			return interval;
		}
		else if (p->energy == 6)
		{
			p->setframe((p->getframe() - p->getframe() + 5));  // image frame
			//p->reduceE(1);
			return interval;
		}
		else if (p->energy == 5)
		{
			p->setframe((p->getframe() - p->getframe() + 4));  // image frame
			//p->reduceE(1);
			return interval;
		}
		else if (p->energy == 4)
		{
			p->setframe((p->getframe() - p->getframe() + 3));  // image frame
			//p->reduceE(1);
			return interval;
		}
		else if (p->energy == 3)
		{
			p->setframe((p->getframe() - p->getframe() + 2));  // image frame
			//p->reduceE(1);
			return interval;
		}
		else if (p->energy == 2)
		{
			p->setframe((p->getframe() - p->getframe() + 1));  // image frame
			//p->reduceE(1);
			return interval;
		}
		else if (p->energy == 1)
		{
			//p->setframe((p->getframe() - p->getframe() + 1));  // image frame
			return interval;
		}

	}
	if (p->gettime() != 0 && p->gettime() > 1000)
	{
		if (p->energy != 1)
			p->reduceE(1);// image frame
		else
			p->energy = 1;
		return interval;
	}
	else
	{
		return 0;
	}
}

void Star::setenergy(int e)
{
	energy = e;
}
int Star::getenergy()
{
	return energy;
}

void Star::reduceE(int e)
{
	energy = energy - e;
}

void Star::plusE(int e)
{
	energy = energy + e;
}
Star Star::operator+(int i) {
	Star* st = this;
	st->energy = st->energy + i;
	return *st;
}
Star Star::operator-(int i) {
	Star* st = this;
	st->energy = st->energy - i;
	return *st;
}
void Star::seteated(int e)
{
	eated = eated + 1;
}
int Star::geteated()
{
	return eated;
}


Star::~Star()
{

}
