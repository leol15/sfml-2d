#ifndef UTILS_H_
#define UTILS_H_

#include <iostream>
#include <cmath>

#include "vec2.h"

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


// reflect when hitting the bounds
void reflect(float & pos, float & vel, float min, float max);


float sqDist(float x, float y, float x2, float y2);
float sqDist(const vec2& p1, const vec2& p2);
float dist(const vec2& p1, const vec2& p2);

float bound(float val, float max, float min);


#endif


