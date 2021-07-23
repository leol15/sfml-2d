#include "Utils.h"


std::ostream& operator<<(std::ostream& out, const vec2& v) {
	out << v.x << "," << v.y;
	return out;
}

// reflect when hitting the bounds
void reflect(float & pos, float & vel, float min, float max) {
	if (pos < min) {
		pos = min;
		vel = vel < 0 ? -vel : vel;
		vel *= 0.98f;
	} else if (pos > max) {
		pos = max;
		vel = vel > 0 ? -vel : vel;
		vel *= 0.98f;
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

float bound(float val, float max, float min) {
	return val > max ? max : (val < min ? min : val);
}

