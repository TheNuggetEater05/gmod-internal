#pragma once

#ifndef TYPES_H
#define TYPES_H

class Vec2
{
public:
	Vec2(float x, float y) : X(x), Y(y) {};

	static inline Vec2 Zero()
	{
		return Vec2(0, 0);
	}

	inline void Clear()
	{
		X = 0;
		Y = 0;
	}

	float X;
	float Y;
};

#endif