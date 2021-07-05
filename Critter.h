#ifndef CRitter_H_
#define CRitter_H_ value

#include "Utils.h"

class Critter {
public:
	virtual Action getAction() const = 0;
	virtual ~Critter() { };
};


class CritterState {
public:
	vec2 p, v;
	float radius = 20;
	CritterState() : CritterState({0, 0}) { }
	CritterState(vec2 p_) : p(p_), v(), radius(20) { }
};

#endif
