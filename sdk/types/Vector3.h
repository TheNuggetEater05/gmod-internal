#pragma once

#ifndef VECTOR3_H

typedef float vec_t;

class Vector2D;
class VectorByValue;

//=========================================================
// 3D Vector
//=========================================================
class Vector
{
public:
	// Members
	vec_t x, y, z;

	// Construction/destruction:
	Vector() = default;

	Vector(vec_t X, vec_t Y, vec_t Z);
	explicit Vector(vec_t XYZ); ///< broadcast initialize

	// Initialization
	void Init(vec_t ix = 0.0f, vec_t iy = 0.0f, vec_t iz = 0.0f);
	// TODO (Ilya): Should there be an init that takes a single float for consistency?

   // Got any nasty NAN's?
	bool IsValid() const;
	void Invalidate();

	// array access...
	vec_t operator[](int i) const;
	vec_t& operator[](int i);

	// Base address...
	vec_t* Base();
	vec_t const* Base() const;

	// Cast to Vector2D...
	//Vector2D& AsVector2D();
	//const Vector2D& AsVector2D() const;

	// Initialization methods
	void Random(vec_t minVal, vec_t maxVal);
	inline void Zero(); ///< zero out a vector

	// equality
	bool operator==(const Vector& v) const;
	bool operator!=(const Vector& v) const;

	// arithmetic operations
	inline Vector& operator+=(const Vector& v);
	inline Vector& operator-=(const Vector& v);
	inline Vector& operator*=(const Vector& v);
	inline Vector& operator*=(float s);
	inline Vector& operator/=(const Vector& v);
	inline Vector& operator/=(float s);
	inline Vector& operator+=(float fl); ///< broadcast add
	inline Vector& operator-=(float fl); ///< broadcast sub			

	// negate the vector components
	void	Negate();

	// Get the vector's magnitude.
	inline vec_t	Length() const;

	// Get the vector's magnitude squared.
	inline vec_t LengthSqr(void) const
	{
		return (x * x + y * y + z * z);
	}

	// return true if this vector is (0,0,0) within tolerance
	bool IsZero(float tolerance = 0.01f) const
	{
		return (x > -tolerance && x < tolerance &&
			y > -tolerance && y < tolerance &&
			z > -tolerance && z < tolerance);
	}

	vec_t	NormalizeInPlace();
	Vector	Normalized() const;
	bool	IsLengthGreaterThan(float val) const;
	bool	IsLengthLessThan(float val) const;

	// check if a vector is within the box defined by two other vectors
	inline bool WithinAABox(Vector const& boxmin, Vector const& boxmax);

	// Get the distance from this vector to the other one.
	vec_t	DistTo(const Vector& vOther) const;

	// Get the distance from this vector to the other one squared.
	// NJS: note, VC wasn't inlining it correctly in several deeply nested inlines due to being an 'out of line' inline.  
	// may be able to tidy this up after switching to VC7
	inline vec_t DistToSqr(const Vector& vOther) const
	{
		Vector delta;

		delta.x = x - vOther.x;
		delta.y = y - vOther.y;
		delta.z = z - vOther.z;

		return delta.LengthSqr();
	}

	// Copy
	void	CopyToArray(float* rgfl) const;

	// Multiply, add, and assign to this (ie: *this = a + b * scalar). This
	// is about 12% faster than the actual vector equation (because it's done per-component
	// rather than per-vector).
	void	MulAdd(const Vector& a, const Vector& b, float scalar);

	// Dot product.
	vec_t	Dot(const Vector& vOther) const;

	// assignment
	Vector& operator=(const Vector& vOther);

	// 2d
	vec_t	Length2D(void) const;
	vec_t	Length2DSqr(void) const;

	operator VectorByValue& () { return *((VectorByValue*)(this)); }
	operator const VectorByValue& () const { return *((const VectorByValue*)(this)); }

	// copy constructors
//	Vector(const Vector &vOther);

	// arithmetic operations
	Vector	operator-(void) const;

	Vector	operator+(const Vector& v) const;
	Vector	operator-(const Vector& v) const;
	Vector	operator*(const Vector& v) const;
	Vector	operator/(const Vector& v) const;
	Vector	operator*(float fl) const;
	Vector	operator/(float fl) const;

	// Cross product between two vectors.
	Vector	Cross(const Vector& vOther) const;

	// Returns a vector with the min or max in X, Y, and Z.
	Vector	Min(const Vector& vOther) const;
	Vector	Max(const Vector& vOther) const;
};

//-----------------------------------------------------------------------------
// Allows us to specifically pass the vector by value when we need to
//-----------------------------------------------------------------------------
class VectorByValue : public Vector
{
public:
	// Construction/destruction:
	VectorByValue(void) : Vector() {}
	VectorByValue(vec_t X, vec_t Y, vec_t Z) : Vector(X, Y, Z) {}
	VectorByValue(const VectorByValue& vOther) { *this = vOther; }
};

inline Vector::Vector(vec_t X, vec_t Y, vec_t Z)
{
	x = X; y = Y; z = Z;
}

inline Vector::Vector(vec_t XYZ)
{
	x = y = z = XYZ;
}

inline void Vector::Init(vec_t ix, vec_t iy, vec_t iz)
{
	x = ix; y = iy; z = iz;
}

inline void Vector::Random(vec_t minVal, vec_t maxVal)
{
	//x = minVal + ((float)rand() / VALVE_RAND_MAX) * (maxVal - minVal);
	//y = minVal + ((float)rand() / VALVE_RAND_MAX) * (maxVal - minVal);
	//z = minVal + ((float)rand() / VALVE_RAND_MAX) * (maxVal - minVal);
	return;
}

// This should really be a single opcode on the PowerPC (move r0 onto the vec reg)
inline void Vector::Zero()
{
	x = y = z = 0.0f;
}

//-----------------------------------------------------------------------------
// assignment
//-----------------------------------------------------------------------------

inline Vector& Vector::operator=(const Vector& vOther)
{
	x = vOther.x; y = vOther.y; z = vOther.z;
	return *this;
}


//-----------------------------------------------------------------------------
// Array access
//-----------------------------------------------------------------------------
inline vec_t& Vector::operator[](int i)
{
	return ((vec_t*)this)[i];
}

inline vec_t Vector::operator[](int i) const
{
	return ((vec_t*)this)[i];
}


//-----------------------------------------------------------------------------
// Base address...
//-----------------------------------------------------------------------------
inline vec_t* Vector::Base()
{
	return (vec_t*)this;
}

inline vec_t const* Vector::Base() const
{
	return (vec_t const*)this;
}

//-----------------------------------------------------------------------------
// Cast to Vector2D...
//-----------------------------------------------------------------------------

//inline Vector2D& Vector::AsVector2D()
//{
//	return *(Vector2D*)this;
//}

//inline const Vector2D& Vector::AsVector2D() const
//{
//	return *(const Vector2D*)this;
//}

//-----------------------------------------------------------------------------
// IsValid?
//-----------------------------------------------------------------------------

inline bool Vector::IsValid() const
{
	return true; //IsFinite(x) && IsFinite(y) && IsFinite(z);
}

//-----------------------------------------------------------------------------
// Invalidate
//-----------------------------------------------------------------------------

inline void Vector::Invalidate()
{
	//#ifdef _DEBUG
	//#ifdef VECTOR_PARANOIA
	//x = y = z = VEC_T_NAN;
	//#endif
	//#endif

	return;
}

//-----------------------------------------------------------------------------
// comparison
//-----------------------------------------------------------------------------

inline bool Vector::operator==(const Vector& src) const
{
	return (src.x == x) && (src.y == y) && (src.z == z);
}

inline bool Vector::operator!=(const Vector& src) const
{
	return (src.x != x) || (src.y != y) || (src.z != z);
}


//-----------------------------------------------------------------------------
// Copy
//-----------------------------------------------------------------------------

inline void VectorCopy(const Vector& src, Vector& dst)
{
	dst.x = src.x;
	dst.y = src.y;
	dst.z = src.z;
}

inline void	Vector::CopyToArray(float* rgfl) const
{
	rgfl[0] = x, rgfl[1] = y, rgfl[2] = z;
}

//-----------------------------------------------------------------------------
// standard math operations
//-----------------------------------------------------------------------------
// #pragma message("TODO: these should be SSE")

inline void Vector::Negate()
{
	x = -x; y = -y; z = -z;
}

inline  Vector& Vector::operator+=(const Vector& v)
{
	x += v.x; y += v.y; z += v.z;
	return *this;
}

inline  Vector& Vector::operator-=(const Vector& v)
{
	x -= v.x; y -= v.y; z -= v.z;
	return *this;
}

inline  Vector& Vector::operator*=(float fl)
{
	x *= fl;
	y *= fl;
	z *= fl;
	return *this;
}

inline  Vector& Vector::operator*=(const Vector& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}

// this ought to be an opcode.
inline Vector& Vector::operator+=(float fl)
{
	x += fl;
	y += fl;
	z += fl;
	return *this;
}

inline Vector& Vector::operator-=(float fl)
{
	x -= fl;
	y -= fl;
	z -= fl;
	return *this;
}



inline  Vector& Vector::operator/=(float fl)
{
	float oofl = 1.0f / fl;
	x *= oofl;
	y *= oofl;
	z *= oofl;
	return *this;
}

inline  Vector& Vector::operator/=(const Vector& v)
{
	x /= v.x;
	y /= v.y;
	z /= v.z;
	return *this;
}

#endif