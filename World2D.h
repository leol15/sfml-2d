
#ifndef WORLD2D_H_
#define WORLD2D_H_

#include <chrono>

#include "Critter.h"

typedef std::chrono::time_point<std::chrono::high_resolution_clock> time_point_t;

struct WorldCritter {
	Critter * critter;
	CritterState * critter_state;
	CritterProp * critter_prop;
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
