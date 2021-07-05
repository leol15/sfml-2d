#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "RollBug.h"
#include "World2D.h"


World2D::World2D(int width, int height) : width_(width), height_(height) {
	std::cerr << "world2d" << std::endl;
	// 10 critters at random location
	for (int i = 0; i < 10; i++) {
		WorldCritter wc = {new RollBug(), 
			new CritterState({
				static_cast<float>(rand() % width_), 
				static_cast<float>(rand() % height_)
			})};
		wc.critter_state->v.x = static_cast<float>(rand() % 100 - 50) / 1000;
		wc.critter_state->v.y = static_cast<float>(rand() % 100 - 50) / 1000;
		critters.push_back(wc);
	}
}

void World2D::render(sf::RenderWindow& window) const {
	// draw background, environemnt

	// draw critters
	for (auto& wc : critters) {
		sf::CircleShape shape(wc.critter_state->radius);
		shape.setFillColor(sf::Color::Blue);
		shape.setPosition(wc.critter_state->p.x, wc.critter_state->p.y);
		window.draw(shape);
	}
}

void World2D::update() {
	// move them!
	for (auto& wc : critters) {
		CritterState * st = wc.critter_state;
		st->p += st->v;

		// circle collision
		for (auto& wc2 : critters) {
			if (&wc == &wc2) break;
			// ?
			CritterState * st2 = wc2.critter_state;
			// DBUG(sqDist(wc.critter_state->p, wc2.critter_state->p));
			if (sqDist(wc.critter_state->p, wc2.critter_state->p) < 
					(st->radius + st2->radius) * (st->radius + st2->radius)) {
				// !
				vec2 d12 = normalize(st->p - st2->p);
				vec2 v12 = (st->v * d12) * d12;
				vec2 v21 = -(st2->v * d12) * d12;
				DBUG(d12);
				DBUG(v12);
				DBUG(v21);
				// todo mass
				st->v += v21 - v12;
				st2->v -= v21 - v12;
			}
		}

		// constaint
		reflect(st->p.x, st->v.x, 0, width_);
		reflect(st->p.y, st->v.y, 0, height_);
	}
}




