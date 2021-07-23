#include "vec2.h"


float operator*(const vec2& me, const vec2& other) {
	return me.x * other.x + me.y * other.y;
}

vec2 operator*(vec2 me, float v) {
	return vec2(me.x * v, me.y * v);
}

vec2 operator*(float v, vec2 me) { return me * v; }

vec2 operator/(vec2 me, float v) {
	return vec2(me.x / v, me.y / v);
}


vec2 operator+(const vec2& me, const vec2& other) {
	vec2 v(me);
	v += other;
	return v;
}

vec2& vec2::operator+=(const vec2& other) {
	this->x += other.x;
	this->y += other.y;
	return *this;
}

vec2 vec2::operator-() const {
	return vec2(-x, -y);
}

vec2 operator-(const vec2& me, const vec2& other) {
	vec2 v(me);
	v -= other;
	return v;
}

vec2& vec2::operator-=(const vec2& other) {
	this->x -= other.x;
	this->y -= other.y;
	return *this;
}

vec2& vec2::operator*=(float v) {
	this->x *= v;
	this->y *= v;
	return *this;
}

vec2& vec2::operator/=(float v) {
	this->x /= v;
	this->y /= v;
	return *this;
}
