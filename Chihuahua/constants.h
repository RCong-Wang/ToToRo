#pragma once

//Screen dimension constants
#define WIDTH  1920
#define HEIGHT 1080
#define ALLREGION -1
#define SOLID 100
#define SHADED 101
#define BLENDED 102
#define NO_TRANSPARENT_BG {0, 0, 0, 0}

// New in this example
#define MUSIC 10
#define EFFECT 11
#define FOREVER -1
#define ONE 0
#define ALLCHANNEL -1

#define VELOCITY 5
extern int sysStatus,actionStatus;
enum
{
	stop,
	right,
	left,
	up,
	buttom,
	force,
	jump,
	none,
	start,
	fly,
};

enum MouseState
{
	NONE = 0,
	OUT = 1, // Mouse out
	IN_LB_SC = 2,  // Inside, Left Button, Single Click
	IN_RB_SC = 3,  // Inside, RIGHT Button, Single Click
	IN_LB_DC = 4,  // Inside, Left Button, Double Click
	IN_RB_DC = 5,  // Inside, RIGHT Button, Double Click
	IN_LB_PR = 6,  // Inside, Left Button, Press
	IN_RB_PR = 7,  // Inside, Left Button, Press
	IN_WU = 8,  // Inside, Wheel UP
	IN_WD = 9,  // Inside, Wheel DOWN
	HOVER = 10, // Mouse hover
	IN_LB_PR_HOVER = 11, // Inside, Left Button, Press, Hover
	IN_RB_PR_HOVER = 12 // Inside, Left Button, Press, Hover
};

