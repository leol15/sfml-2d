#ifndef UTILS_H_
#define UTILS_H_

#include <iostream>
#include <cmath>

#define DBUG(X) (std::cerr << (#X) << " [" << (X) << "]" << std::endl)


struct Action {
	float dVx, dVy;
	Action() : Action(0, 0) { }
	Action(float _dVx, float _dVy) : dVx(_dVx), dVy(_dVy) { }
	friend std::ostream& operator<<(std::ostream& out, const Action& action) {
		out << action.dVx << "," << action.dVy;
		return out;
	}
};

struct vec2 {
	float x, y;
	vec2(float x_, float y_) : x(x_), y(y_) { }
	vec2() : vec2(0, 0) { }
	vec2(const vec2 &o) : x(o.x), y(o.y) { }
	vec2& operator+=(const vec2& other);
	vec2& operator-=(const vec2& other);
	vec2& operator*=(float v);
	vec2 operator-() const;
};
std::ostream& operator<<(std::ostream& out, const vec2& v);
vec2 operator+(const vec2& me, const vec2& other);
vec2 operator-(const vec2& me, const vec2& other);

float operator*(const vec2& me, const vec2& other);

vec2 operator*(vec2 me, float v);

vec2 operator*(float v, vec2 me);

float magnitude(const vec2& v);
vec2 normalize(const vec2& v);

// reflect when hitting the bounds
void reflect(float & pos, float & vel, float min, float max);


float sqDist(float x, float y, float x2, float y2);
float sqDist(const vec2& p1, const vec2& p2);

void bound(float& val, float max, float min);


#endif


