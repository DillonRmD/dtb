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

#include <math.h>

#define PI 3.14159265358979323846
#define PI32 3.14159265359f
#define TWO_PI PI * 2

#define MIN(a, b) a > b ? b : a
#define MAX(a, b) a < b ? b : a
#define ABS(a) (a > 0 ? a : -(a))
#define MOD(a, m) ((a) % (m)) >= 0 ? ((a) % (m)) : (((a) % (m)) + (m))
#define SQUARE(x) x * x

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

typedef struct circle
{
	float radius, x, y;
}circle;

typedef struct m4
{
	float elements[4][4];
}m4;


// NOTE(DILLON): Strictly utitily functions outside of math structures
inline float ToRadians(float degrees){
	float result = degrees * (PI32 / 180.f);
	return result;
}

inline float Lerp(float a, float time, float b){
	float result = (1.0f, - time) * a + time * b;
	return result;
}

inline float Clamp(float min, float value, float max){
	float result = value;
	
	if(result < min){
		result = min;
	} else if(result > max){
		result = max;
	}
	
	return result;
}

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

inline v2 V2_Addf(v2 left, float right)
{
	v2 result = {0};
	result.x = left.x + right;
	result.y = left.y + right;
	return result;
}


inline v2 V2_Subtract(v2 left, v2 right)
{
	v2 result = {0};
	result.x = left.x - right.x;
	result.y = left.y - right.y;
	return result;
}

inline v2 V2_Subtractf(v2 left, float right)
{
	v2 result = {0};
	result.x = left.x - right;
	result.y = left.y - right;
	return result;
}

inline v2 V2_Multiply(v2 left, v2 right)
{
	v2 result = {0};
	result.x = left.x * right.x;
	result.y = left.y * right.y;
	return result;
}

inline v2 V2_Multiplyf(v2 left, float right)
{
	v2 result = {0};
	result.x = left.x * right;
	result.y = left.y * right;
	return result;
}


inline v2 V2_Divide(v2 left, v2 right)
{
	v2 result = {0};
	result.x = left.x / right.x;
	result.y = left.y / right.y;
	return result;
}

inline v2 V2_Dividef(v2 left, float right)
{
	v2 result = {0};
	result.x = left.x / right;
	result.y = left.y / right;
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

inline v3 V3_Addf(v3 left, float right)
{
	v3 result = {0};
	result.x = left.x + right;
	result.x = left.y + right;
	result.x = left.z + right;
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

inline v3 V3_Subtractf(v3 left, float right)
{
	v3 result = {0};
	result.x = left.x - right;
	result.x = left.y - right;
	result.x = left.z - right;
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

inline v3 V3_Multiplyf(v3 left, float right)
{
	v3 result = {0};
	result.x = left.x * right;
	result.x = left.y * right;
	result.x = left.z * right;
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

inline v3 V3_Dividef(v3 left, float right)
{
	v3 result = {0};
	result.x = left.x / right;
	result.x = left.y / right;
	result.x = left.z / right;
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

inline v4 V4_Addf(v4 left, float right)
{
	v4 result = {0};
	result.x = left.x + right;
	result.y = left.y + right;
	result.z = left.z + right;
	result.w = left.w + right;
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

inline v4 V4_Subtractf(v4 left, float right)
{
	v4 result = {0};
	result.x = left.x - right;
	result.y = left.y - right;
	result.z = left.z - right;
	result.w = left.w - right;
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

inline v4 V4_Multiplyf(v4 left, float right)
{
	v4 result = {0};
	result.x = left.x * right;
	result.y = left.y * right;
	result.z = left.z * right;
	result.w = left.w * right;
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

inline v4 V4_Dividef(v4 left, float right)
{
	v4 result = {0};
	result.x = left.x / right;
	result.y = left.y / right;
	result.z = left.z / right;
	result.w = left.w / right;
	return result;
}

// NOTE(DILLON): Matrix4x4

inline m4 M4(){
	m4 result = {0};
	return result;
}

inline m4 M4d(float diagonal){
	m4 result = M4();
	
	result.elements[0][0] = diagonal;
	result.elements[1][1] = diagonal;
	result.elements[2][2] = diagonal;
	result.elements[3][3] = diagonal;
	return result;
}

inline m4 M4_Add(m4 left, m4 right){
	m4 result;
	
	for(int columns = 0; columns < 4; columns++){
		for(int rows = 0; rows < 4; rows++){
			result.elements[columns][rows] = left.elements[columns][rows] + right.elements[columns][rows];
		}
	}
	
	return result;
}


inline m4 M4_Subtract(m4 left, m4 right){
	m4 result;
	
	for(int columns = 0; columns < 4; columns++){
		for(int rows = 0; rows < 4; rows++){
			result.elements[columns][rows] = left.elements[columns][rows] - right.elements[columns][rows];
		}
	}
	
	return result;
}

inline m4 M4_Multiply(m4 left, m4 right){
	m4 result;
	
	for(int columns = 0; columns < 4; columns++){
		for(int rows = 0; rows < 4; rows++){
			float sum = 0;
			for(int current_matrice = 0; current_matrice < 4; current_matrice++){
				sum += left.elements[current_matrice][rows] * right.elements[columns][current_matrice];
			}
			
			result.elements[columns][rows] = sum;
		}
	}
	
	return result;
}

inline m4 M4_Dividef(m4 matrix, float scalar){
	m4 result;
	
	for(int columns = 0; columns < 4; columns++){
		for(int rows = 0; rows < 4; rows++){
			result.elements[columns][rows] = matrix.elements[columns][rows] / scalar;
		}
	}
	
	return result;
}


#ifdef __cplusplus

inline v2 operator+(v2 left, v2 right){
	return V2_Add(left, right);
}

inline v2 operator-(v2 left, v2 right){
	return V2_Subtract(left, right);
}

inline v2 operator*(v2 left, v2 right){
	return V2_Multiply(left, right);
}

inline v2 operator/(v2 left, v2 right){
	return V2_Divide(left, right);
}

inline v3 operator+(v3 left, v3 right){
	return V3_Add(left, right);
}

inline v3 operator-(v3 left, v3 right){
	return V3_Subtract(left, right);
}

inline v3 operator*(v3 left, v3 right){
	return V3_Multiply(left, right);
}

inline v3 operator/(v3 left, v3 right){
	return V3_Divide(left, right);
}

inline v4 operator+(v4 left, v4 right){
	return V4_Add(left, right);
}

inline v4 operator-(v4 left, v4 right){
	return V4_Subtract(left, right);
}

inline v4 operator*(v4 left, v4 right){
	return V4_Multiply(left, right);
}

inline v4 operator/(v4 left, v4 right){
	return V4_Divide(left, right);
}

inline m4 operator+(m4 left, m4 right){
	return M4_Add(left, right);
}

inline m4 operator-(m4 left, m4 right){
	return M4_Subtract(left, right);
}

inline m4 operator*(m4 left, m4 right){
	return M4_Multiply(left, right);
}

inline m4 operator/(m4 left, float scalar){
	return M4_Dividef(left, scalar);
}

#endif

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

inline m4 Translate(v3 translation){
	m4 result = M4d(1.0f);
	
	result.elements[3][0] = translation.x;
	result.elements[3][1] = translation.y;
	result.elements[3][2] = translation.z;
	
	return result;
}

inline m4 Rotate(float angle, v3 axis){
	m4 result = M4d(1.0f);
	
	axis = V3_Normalize(axis);
	
	float sin_theta = sinf(ToRadians(angle));
	float cos_theta = cosf(ToRadians(angle));
	float cos_value = 1.0f - cos_theta;
	
	result.elements[0][0] = (axis.x * axis.y * cos_value) + cos_theta;
	result.elements[0][1] = (axis.x * axis.y * cos_value) + (axis.z * sin_theta);
	result.elements[0][2] = (axis.x * axis.z * cos_value) - (axis.y * sin_theta);
	
	result.elements[1][0] = (axis.y * axis.x * cos_value) - (axis.z * sin_theta);
	result.elements[1][1] = (axis.y * axis.y * cos_value) + cos_theta;
	result.elements[1][2] = (axis.y * axis.z * cos_value) + (axis.x * sin_theta);
	
	result.elements[2][0] = (axis.z * axis.x * cos_value) + (axis.y * sin_theta);
	result.elements[2][1] = (axis.z * axis.y * cos_value) - (axis.x * sin_theta);
	result.elements[2][2] = (axis.z * axis.z * cos_value) + cos_theta;
	
	return result;
}

inline m4 Frustum(float right, float left, float top, float bottom, float mFar, float mNear)
{
	m4 Result = {0};
	
	Result.elements[0][0] = 2 * mNear / (right - left);
	Result.elements[1][1] = 2 * mNear / (top - bottom);
	Result.elements[2][0] = (right + left) / (right - left);
	Result.elements[2][1] = (top + bottom) / (top - bottom);
	Result.elements[2][2] = -(mFar + mNear) / (mFar - mNear);
	Result.elements[2][3] = -1;
	Result.elements[3][2] = -2 * mFar * mNear / (mFar - mNear);
	
	return Result;
}

inline m4 Orthographic(float left, float right, float bottom, float top, float mNear, float mFar)
{
	m4 Result = {0};
	
	Result.elements[0][0] = 2.0f / (right - left);
    Result.elements[1][1] = 2.0f / (top - bottom);
    Result.elements[2][2] = 2.0f / (mNear - mFar);
    Result.elements[3][3] = 1.0f;
	
    Result.elements[3][0] = (left + right) / (left - right);
    Result.elements[3][1] = (bottom + top) / (bottom - top);
    Result.elements[3][2] = (mFar + mNear) / (mNear - mFar);
	return Result;
}

inline m4 Projection(float right, float left, float top, float bottom, float mFar, float mNear)
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

inline m4 Perspective(float FOV, float AspectRatio, float Near, float Far)
{
	m4 Result = M4();
	
    float Cotangent = 1.0f / tanf(FOV * ( 3.14 / 360.0f));
    
    Result.elements[0][0] = Cotangent / AspectRatio;
    Result.elements[1][1] = Cotangent;
    Result.elements[2][3] = -1.0f;
    Result.elements[2][2] = (Near + Far) / (Near - Far);
    Result.elements[3][2] = (2.0f * Near * Far) / (Near - Far);
    Result.elements[3][3] = 0.0f;
	
    return (Result);
}

inline m4 LookAt(v3 Eye, v3 Center, v3 Up)
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

inline float Distancef(float x1, float y1, float x2, float y2)
{
	return Sqrt(powf(x2 - x1, 2) + powf(y2 - y1, 2));
}

inline float Distancev(v2 left, v2 right)
{
	return Sqrt(powf(right.x - left.x, 2) + powf(right.y - left.y, 2));
}

inline float V2_Length(v2 vec)
{
	return Sqrt(vec.x * vec.x + vec.y * vec.y);
}

inline float V3_Length(v3 vec)
{
	return Sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

inline float V4_Length(v4 vec)
{
	return Sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w);
}

inline void V2_SetAngle(v2 vec, float angle)
{
	float length = V2_Length(vec);
	
	vec.x = cos(angle) * length;
	vec.y = sin(angle) * length;
}


inline int IsCircleColliding(circle c1, circle c2)
{
	return Distancef(c1.x, c1.y, c2.x, c2.y) <= c1.radius + c2.radius;
}

inline int IsCirclePointColliding(float x, float y, circle c)
{
	return Distancef(x, y, c.x, c.y) < c.radius;
}

#define DTB_MATH_H
#endif