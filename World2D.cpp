#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "RollBug.h"
#include "World2D.h"


World2D::World2D(int width, int height)
	: width_(width), height_(height) {
	// 10 critters at random location
	for (int i = 0; i < 1000; i++) {
		WorldCritter wc = {new RollBug(),
			new CritterState({
				static_cast<float>(rand() % width_), 
				static_cast<float>(rand() % height_)
			})};
		wc.critter_state->v.x = static_cast<float>(rand() % 100 - 50) / 100;
		wc.critter_state->v.y = static_cast<float>(rand() % 100 - 50) / 100;
		wc.critter_state->radius = 5;
		critters.push_back(wc);
	}
}

void World2D::render(sf::RenderWindow& window) const {
	// draw background, environemnt
	// draw critters
	for (auto& wc : critters) {
		const CritterState& st = *(wc.critter_state); 
		sf::CircleShape shape(st.radius);
		shape.setFillColor(sf::Color::Red);
		shape.setPosition(st.p.x - st.radius, st.p.y - st.radius);
		window.draw(shape);
	}
}

void World2D::update() {
	// move them!
	for (unsigned int i = 0; i < critters.size(); i++) {
		auto& wc = critters[i];
		CritterState * st = wc.critter_state;

		// circle collision
		for (unsigned int j = i + 1; j < critters.size(); j++) {
			auto& wc2 = critters[j];
			// ?
			CritterState * st2 = wc2.critter_state;
			// DBUG(sqDist(wc.critter_state->p, wc2.critter_state->p));
			float sqD = sqDist(wc.critter_state->p, wc2.critter_state->p);
			float touch_dist = st->radius + st2->radius;
			if (sqD < (touch_dist) * (touch_dist)) {
				// !
				vec2 d12 = normalize(st2->p - st->p);
				float v12_mag =  (st-> v * d12) * 0.95f;
				float v21_mag = -(st2->v * d12) * 0.95f;
				// todo mass
				st->v -= v12_mag * d12;
				st2->v += v12_mag * d12;
				st->v -= v21_mag * d12;
				st2->v += v21_mag * d12;
				// push back
				float distance = magnitude(st2->p - st->p) - touch_dist;
				if (distance < 0) {
					distance -= 0.01f;
					st->p += d12 * (distance / 2);
					st2->p -= d12 * (distance / 2);
				}
			}
		}

	}

	// forces
	for (auto & critter : critters) {
		auto * critter_state = critter.critter_state;
		// drag
		// critter_state->v *= 0.9999f;
		// gravity
		critter_state->v += {0, 0.009f};
	}

	// actaully move them
	for (auto& wc : critters) {
		CritterState * st = wc.critter_state;
		// bound(st->v.x, 0.1f, -0.1f);
		// bound(st->v.y, 0.1f, -0.1f);

		// update
		st->p += st->v;

		// constaint
		reflect(st->p.x, st->v.x, 0, width_);
		reflect(st->p.y, st->v.y, 0, height_);
	}
}




