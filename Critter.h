#ifndef CRitter_H_
#define CRitter_H_

#include "Utils.h"

class Critter {
public:
	virtual Action getAction() const = 0;
	virtual ~Critter() { };
};

// for world update
class CritterState {
public:
	vec2 p, v;
	float radius = 20;
	float mass;
	CritterState() : CritterState({0, 0}) { }
	CritterState(vec2 p_)
		: p(p_), v(),
		radius(20), mass(1) { }
};

// for drawing
class CritterProp {
public:
	sf::Color color;
	CritterProp(sf::Color col) : color(col) { }
};

#endif
