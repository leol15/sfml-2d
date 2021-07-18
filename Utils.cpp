#include "Utils.h"


std::ostream& operator<<(std::ostream& out, const vec2& v) {
	out << v.x << "," << v.y;
	return out;
}

float operator*(const vec2& me, const vec2& other) {
	return me.x * other.x + me.y * other.y;
}

vec2 operator*(vec2 me, float v) {
	return vec2(me.x * v, me.y * v);
}

vec2 operator*(float v, vec2 me) {
	return me * v;
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

// reflect when hitting the bounds
void reflect(float & pos, float & vel, float min, float max) {
	if (pos < min) {
		pos = min;
		vel = vel < 0 ? -vel : vel;
		vel *= 0.9f;
	} else if (pos > max) {
		pos = max;
		vel = vel > 0 ? -vel : vel;
		vel *= 0.9f;
	}
}


float sqDist(float x, float y, float x2, float y2) {
	return (x2 - x) * (x2 - x) + (y2 - y) * (y2 - y);
}

float sqDist(const vec2& p1, const vec2& p2) {
	return sqDist(p1.x, p1.y, p2.x, p2.y);
}

vec2 normalize(const vec2& v) {
	if (v.x == 0 && v.y == 0) {
		return vec2(1, 0);
	}
	float m = magnitude(v);
	return vec2(v.x / m, v.y / m);
}

float magnitude(const vec2& v) {
	return static_cast<float>(sqrt(v.x * v.x + v.y * v.y));
}

void bound(float& val, float max, float min) {
	val = val > max ? max : (val < min ? min : val);
}

