#pragma once

#ifndef VECTOR_H
#define VECTOR_H

struct Vec2
{
	float x, y;
	constexpr Vec2() : x(0.0f), y(0.0f) {}
	constexpr Vec2(float _x, float _y) : x(_x), y(_y) {}
};
#endif // !VECTOR_H