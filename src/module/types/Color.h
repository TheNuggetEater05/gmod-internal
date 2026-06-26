#pragma once

#ifndef COLOR_H
#define COLOR_H

struct Color
{
	float r, g, b, a;
	constexpr Color() : r(1.0f), g(1.0f), b(1.0f), a(1.0f) {}
	constexpr Color(float _r, float _g, float _b, float _a = 1.0f) : r(_r), g(_g), b(_b), a(_a) {}
};
#endif // !COLOR_H