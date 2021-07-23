#ifndef CRitter_H_
#define CRitter_H_

#include <SFML/Graphics.hpp>
#include "../util/Utils.h"

class Critter {
public:
	virtual Action getAction() const = 0;
	virtual ~Critter() { };
};

// for world update
class CritterState {
public:
	vec2 p, v, f;
	float radius = 20;
	float mass;
	CritterState() : CritterState({0, 0}, {0, 0}) { }
	CritterState(vec2 p_, vec2 vel = {0, 0}, float radius = 20, float m = 1)
		: p(p_), v(vel), f({0, 0}),
		radius(radius), mass(m) { }
};

// for drawing
class CritterProp {
public:
	sf::Color color;
	CritterProp(sf::Color col) : color(col) { }
};

#endif
