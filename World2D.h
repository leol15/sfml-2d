
#ifndef WORLD2D_H_
#define WORLD2D_H_

#include <chrono>
#include <thread>
#include <mutex>

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
	~World2D();
	void render(sf::RenderWindow& window) const;
	void handleEvents(sf::RenderWindow& window);
	void update();
private:
	int width_, height_;
	std::vector<WorldCritter> critters;
	void loopedUpdate();
	bool kill_thread_ = false;
	std::thread update_thread_;
	mutable std::mutex mtx_;
};


#endif
