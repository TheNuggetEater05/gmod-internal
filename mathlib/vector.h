#pragma once

#ifndef VECTOR_H
#define VECTOR_H

#include "vector2d.h"

typedef float vec_t;

class QAngle;

class Vector
{
public:
	vec_t x, y, z;

	Vector() = default;

	Vector(vec_t X, vec_t Y, vec_t Z) : x(X), y(Y), z(Z) {};
	explicit Vector(vec_t XYZ) : x(XYZ), y(XYZ), z(XYZ) {};

	vec_t operator[](int i) const;
	vec_t& operator[](int i);

	Vector2D& AsVector2D();
	const Vector2D& AsVector2D() const;

	void Random(vec_t minVal, vec_t maxVal);
	inline void Zero();

	bool operator==(const Vector& v) const;
	bool operator!=(const Vector& v) const;

	inline Vector& operator+=(const Vector& v);
	inline Vector& operator-=(const Vector& v);
	inline Vector& operator*=(const Vector& v);
	inline Vector& operator*=(float s);
	inline Vector& operator/=(const Vector& v);
	inline Vector& operator/=(float s);
	inline Vector& operator+=(float fl);
	inline Vector& operator-=(float fl);	

	inline vec_t LengthSqr(void) const
	{
		return (x * x + y * y + z * z);
	}

	bool IsZero(float tolerance = 0.01f) const
	{
		return (x > -tolerance && x < tolerance &&
			y > -tolerance && y < tolerance &&
			z > -tolerance && z < tolerance);
	}

	Vector& operator=(const Vector& vOther);

	Vector	operator-(void) const;

	Vector	operator+(const Vector& v) const;
	Vector	operator-(const Vector& v) const;
	Vector	operator*(const Vector& v) const;
	Vector	operator/(const Vector& v) const;
	Vector	operator*(float fl) const;
	Vector	operator/(float fl) const;

	Vector	Cross(const Vector& vOther) const;

	Vector	Min(const Vector& vOther) const;
	Vector	Max(const Vector& vOther) const;

private:
	Vector(const Vector& vOther);
};

class QAngle
{
public:
	vec_t x, y, z;

	QAngle() = default;
	QAngle(vec_t X, vec_t Y, vec_t Z);

	//operator QAngleByValue& () { return *((QAngleByValue*)(this)); }
	//operator const QAngleByValue& () const { return *((const QAngleByValue*)(this)); }

	void Init(vec_t ix = 0.0f, vec_t iy = 0.0f, vec_t iz = 0.0f);
	void Random(vec_t minVal, vec_t maxVal);

	bool IsValid() const;
	void Invalidate();

	vec_t operator[](int i) const;
	vec_t& operator[](int i);

	vec_t* Base();
	vec_t const* Base() const;

	bool operator==(const QAngle& v) const;
	bool operator!=(const QAngle& v) const;

	QAngle& operator+=(const QAngle& v);
	QAngle& operator-=(const QAngle& v);
	QAngle& operator*=(float s);
	QAngle& operator/=(float s);

	vec_t	Length() const;
	vec_t	LengthSqr() const;

	QAngle& operator=(const QAngle& src);

	QAngle	operator-(void) const;

	QAngle	operator+(const QAngle& v) const;
	QAngle	operator-(const QAngle& v) const;
	QAngle	operator*(float fl) const;
	QAngle	operator/(float fl) const;
};

#endif