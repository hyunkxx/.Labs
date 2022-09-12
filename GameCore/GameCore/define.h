#pragma once

/* Window value */
#define WIDTH				800
#define HEIGHT				600
#define VK_COUNT			0xFF
/* Constant value */
#define PI					3.141592f
#define TEXT_LENGTH			64
/* Event value */
#define EVENT_NONE			0
#define EVENT_DEAD			1

enum class OBJ_TYPE
{
	NONE,
	PLAYER,
	ENEMY,
	COUNT
};