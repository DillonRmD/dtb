/*  ============================================================================================
*  PROJECT:  Dillon's Tool Box Math Edition
*  AUTHOR:   Dillon Williams
*  LICENSE:  Do What The Fuck Ever license
*  LANGUAGE: C\C++
*
*  INFORMATION:
*  To implement into your code base just include this file into your main compilation unit
*  This is meant to work in both C as well as C++
*
*  This is developed in my free time, constant and consistent updates should not be expected.
*  Feel free to modify this code to your preference.
*  
*  ============================================================================================
*/

#if !defined DTB_MATH_H

typedef union v2
{
	struct
	{
		float x, y;
	};
	
	struct
	{
		float width, height;
	};
	
	struct
	{
		float left, right;
	};
	
	struct
	{
		float u, v;
	};
	
	float elements[2];
	
}v2;

typedef union v3
{
	struct
	{
		float x, y, z;
	};
	
	struct
	{
		float u, v, w;
	};
	
	struct
	{
		float r, g, b;
	};
	
	float elements[3];
	
}v3;

typedef union v4
{
	struct
	{
		float x, y, z, w;
	};
	
	struct
	{
		float r, g, b, a;
	};
	
	float elements[4];
	
}v4;

typedef struct m4
{
	float elements[4][4];
}m4;


// NOTE(DILLON): Vector 2's
inline v2 V2(float x, float y)
{
	v2 result = {0};
	result.x = x;
	result.y = y;
	return result;
}

inline v2 V2z()
{
	v2 result = {0};
	return result;
}

inline v2 V2_Add(v2 left, v2 right)
{
	v2 result = {0};
	result.x = left.x + right.x;
	result.y = left.y + right.y;
	return result;
}

inline v2 V2_Subtract(v2 left, v2 right)
{
	v2 result = {0};
	result.x = left.x - right.x;
	result.y = left.y - right.y;
	return result;
}

inline v2 V2_Multiply(v2 left, v2 right)
{
	v2 result = {0};
	result.x = left.x * right.x;
	result.y = left.y * right.y;
	return result;
}

inline v2 V2_Divide(v2 left, v2 right)
{
	v2 result = {0};
	result.x = left.x / right.x;
	result.y = left.y / right.y;
	return result;
}

// NOTE(DILLON): Vector 3's
inline v3 V3(float x, float y, float z)
{
	v3 result = {0};
	result.x = x;
	result.y = y;
	result.z = z;
	return result;
}

inline v3 V3z()
{
	v3 result = {0};
	return result;
}

inline v3 V3_Add(v3 left, v3 right)
{
	v3 result = {0};
	result.x = left.x + right.x;
	result.x = left.y + right.y;
	result.x = left.z + right.z;
	return result;
}

inline v3 V3_Subtract(v3 left, v3 right)
{
	v3 result = {0};
	result.x = left.x - right.x;
	result.x = left.y - right.y;
	result.x = left.z - right.z;
	return result;
}

inline v3 V3_Multiply(v3 left, v3 right)
{
	v3 result = {0};
	result.x = left.x * right.x;
	result.x = left.y * right.y;
	result.x = left.z * right.z;
	return result;
}

inline v3 V3_Divide(v3 left, v3 right)
{
	v3 result = {0};
	result.x = left.x / right.x;
	result.x = left.y / right.y;
	result.x = left.z / right.z;
	return result;
}


// NOTE(DILLON): Vector 4's
inline v4 V4(float x, float y, float z, float w)
{
	v4 result = {0};
	result.x = x;
	result.y = y;
	result.z = z;
	result.w = w;
	return result;
}

inline v4 V4z()
{
	v4 result = {0};
	return result;
}

inline v4 V4_Add(v4 left, v4 right)
{
	v4 result = {0};
	result.x = left.x + right.x;
	result.y = left.y + right.y;
	result.z = left.z + right.z;
	result.w = left.w + right.w;
	return result;
}

inline v4 V4_Subtract(v4 left, v4 right)
{
	v4 result = {0};
	result.x = left.x - right.x;
	result.y = left.y - right.y;
	result.z = left.z - right.z;
	result.w = left.w - right.w;
	return result;
}

inline v4 V4_Multiply(v4 left, v4 right)
{
	v4 result = {0};
	result.x = left.x * right.x;
	result.y = left.y * right.y;
	result.z = left.z * right.z;
	result.w = left.w * right.w;
	return result;
}

inline v4 V4_Divide(v4 left, v4 right)
{
	v4 result = {0};
	result.x = left.x / right.x;
	result.y = left.y / right.y;
	result.z = left.z / right.z;
	result.w = left.w / right.w;
	return result;
}




// NOTE(DILLON): ExTRA STUFF
inline float Sqrt(float number)
{
	int i;
	float x, y;
	x = number * 0.5;
	y = number;
	i = *(int *)&y;
	i = 0x5f3759df - (i >> 1);
	y = *(float *)&i;
	y = y * (1.5 - (x * y * y));
	y = y * (1.5 - (x * y * y));
	return number * y;
}

//TODO(dillon): This isn't very effiecent fix this later
inline v3 V3_Normalize(v3 vec)
{
	v3 Result = { 0 };
	
	float f;
	f = Sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	vec.x /= f;
	vec.y /= f;
	vec.z /= f;
	
	Result.x = vec.x;
	Result.y = vec.y;
	Result.z = vec.z;
	
	return Result;
}

inline v3 V3_Cross(v3 left, v3 right)
{
	v3 Result;
	
	Result.x = (left.y * right.z) - (left.z * right.y);
	Result.y = (left.z * right.x) - (left.x * right.z);
	Result.z = (left.x * right.y) - (left.y * right.x);
	
	return (Result);
}

inline float V3_Dot(v3 left, v3 right)
{
	float Result = (left.x * right.x) + (left.y * right.y) + (left.z * right.z);
	
	return (Result);
}


inline m4 M4_Perspective(float right, float left, float top, float bottom, float mFar, float mNear)
{
	m4 Result = {0};
	
	Result.elements[0][0] = ((2 * mNear) / (right - left));
	Result.elements[0][2] = ((right + left) / (right - left));
	Result.elements[1][1] = ((2 * mNear) / (top - bottom));
	Result.elements[1][2] = ((top + bottom) / (top - bottom));
	Result.elements[2][2] = (-(mFar + mNear) / (mFar - mNear));
	Result.elements[2][3] = (-2 * (mFar * mNear) / (mFar - mNear));
	Result.elements[3][2] = -1;
	
	return Result;
}

inline m4 M4_Orthographic(float right, float left, float top, float bottom, float mFar, float mNear)
{
	m4 Result = {0};
	
	Result.elements[0][0] = (2 / (right - left));
	Result.elements[0][3] = -((right + left) / (right - left));
	Result.elements[1][1] = (2 / (top - bottom));
	Result.elements[1][3] = -((top + bottom) / (top - bottom));
	Result.elements[2][2] = (-2 / (mFar - mNear));
	Result.elements[2][3] = -((mFar + mNear) / (mFar - mNear));
	Result.elements[3][3] = 1;
	
	return Result;
}

inline m4 M4_Projection(float right, float left, float top, float bottom, float mFar, float mNear)
{
	m4 Result = {0};
	
	Result.elements[0][0] = 2 / (right - left);
	Result.elements[0][3] = -((right + left) / (right - left));
	Result.elements[1][1] = 2 / (top - bottom);
	Result.elements[1][3] = -((top + bottom) / (top - bottom));
	Result.elements[2][2] = -(2 / (mFar - mNear));
	Result.elements[2][3] = -((mFar + mNear) / (mFar - mNear));
	Result.elements[3][3] = 1;
	
	return Result;
}


inline m4 M4_LookAt(v3 Eye, v3 Center, v3 Up)
{
	m4 Result;
	
	v3 F = V3_Normalize(V3_Subtract(Center, Eye));
	v3 S = V3_Normalize(V3_Cross(F, Up));
	v3 U = V3_Cross(S, F);
	
	Result.elements[0][0] = S.x;
	Result.elements[0][1] = U.x;
	Result.elements[0][2] = -F.x;
	Result.elements[0][3] = 0.0f;
	
	Result.elements[1][0] = S.y;
	Result.elements[1][1] = U.y;
	Result.elements[1][2] = -F.y;
	Result.elements[1][3] = 0.0f;
	
	Result.elements[2][0] = S.z;
	Result.elements[2][1] = U.z;
	Result.elements[2][2] = -F.z;
	Result.elements[2][3] = 0.0f;
	
	Result.elements[3][0] = -V3_Dot(S, Eye);
	Result.elements[3][1] = -V3_Dot(U, Eye);
	Result.elements[3][2] = V3_Dot(F, Eye);
	Result.elements[3][3] = 1.0f;
	
	return (Result);
}

inline v2 Cross2f(v2 vec) 
{
	v2 result = {0};
	result.x = vec.y;
	result.y = -vec.x;
	return result;
}

#define DTB_MATH_H
#endif