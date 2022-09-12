#pragma once
#include "framework.h"

#include "define.h"
#include <cassert>
#include <list>
#include <string>
#include <vector>

using std::list;
using std::string;
using std::wstring;
using std::vector;

struct Vector2D
{
public:
	float fX;
	float fY;
public:
	Vector2D operator-(const Vector2D& rhs)
	{
		return Vector2D(fX - rhs.fX, fY - rhs.fY);
	}
	Vector2D operator+(const Vector2D& rhs)
	{
		return Vector2D(fX + rhs.fX, fY + rhs.fY);
	}
	Vector2D operator*(const Vector2D& rhs)
	{ 
		return Vector2D(fX * rhs.fX, fY * rhs.fY);
	}
	Vector2D operator/(const Vector2D& rhs)
	{
		assert(!(rhs.fX == 0.f || rhs.fY == 0.f));
		return Vector2D(fX / rhs.fX, fY / rhs.fY);
	}
public:
	Vector2D() :fX(0.f), fY(0.f) {}
	Vector2D(float _x, float _y) :fX(_x), fY(_y) {}
};