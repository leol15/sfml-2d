#ifndef VEC2_H_
#define VEC2_H_

#include <ostream>
struct vec2 {
	float x, y;
	vec2(float x_, float y_) : x(x_), y(y_) { }
	vec2() : vec2(0, 0) { }
	vec2(const vec2 &o) : x(o.x), y(o.y) { }
	vec2& operator+=(const vec2& other);
	vec2& operator-=(const vec2& other);
	vec2& operator*=(float v);
	vec2& operator/=(float v);
	vec2 operator-() const;
};
std::ostream& operator<<(std::ostream& out, const vec2& v);
vec2 operator+(const vec2& me, const vec2& other);
vec2 operator-(const vec2& me, const vec2& other);

float operator*(const vec2& me, const vec2& other);

vec2 operator*(vec2 me, float v);
vec2 operator*(float v, vec2 me);

vec2 operator/(vec2 me, float v);

float magnitude(const vec2& v);
vec2 normalize(const vec2& v);


#endif  // VEC2_H_
