
#ifndef WORLD2D_H_
#define WORLD2D_H_

#include "Critter.h"

struct WorldCritter {
	Critter * critter;
	CritterState * critter_state;
};

class World2D {
public:
	World2D(int width, int height);
	~World2D() { }
	void render(sf::RenderWindow& window) const;
	void update();
private:
	int width_, height_;
	std::vector<WorldCritter> critters;
};


#endif
