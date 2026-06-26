#pragma once

#ifndef VECTOR_H
#define VECTOR_H

struct Vec3
{
	float x, y, z;
	constexpr Vec3() : x(0.0f), y(0.0f), z(0.0f) {}
	constexpr Vec3(float _xyz) : x(_xyz), y(_xyz), z(_xyz) {}
	constexpr Vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};

struct Vec2
{
	float x, y;
	constexpr Vec2() : x(0.0f), y(0.0f) {}
	constexpr Vec2(float _xy) : x(_xy), y(_xy) {}
	constexpr Vec2(float _x, float _y) : x(_x), y(_y) {}
};
#endif // !VECTOR_H