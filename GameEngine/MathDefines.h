#pragma once

enum pos{
	OBJ_FRONT=0,
	OBJ_BACK,
	OBJ_ON_PLANE,
	OBJ_CLIPPED,
	OBJ_CULLED,
	OBJ_VISIBLE
};

#ifndef PI
#define PI 3.1415926535897
#endif

#define GET_RADIANS(angel) (float)(angel / 180.0f * PI)

