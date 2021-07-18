#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>    // std::shuffle
#include <vector>
#include <thread>         // std::thread
#include <chrono>

#include "RollBug.h"
#include "World2D.h"

constexpr float GRAVITY = 0;
constexpr float COLLISION_COE = 1;


World2D::World2D(int width, int height)
	: width_(width), height_(height) {
	// 10 critters at random location
	for (int i = 0; i < 30; i++) {
		sf::Color randomColor(rand() % 200 + 55, rand() % 200 + 55, rand() % 200 + 55);
		WorldCritter wc = {
			new RollBug(),
			new CritterState({
				static_cast<float>(rand() % width_), 
				static_cast<float>(rand() % height_)
			}),
			new CritterProp(randomColor)
		};
		wc.critter_state->v.x = static_cast<float>(rand() % 100 - 50) / 10;
		wc.critter_state->v.y = static_cast<float>(rand() % 100 - 50) / 10;
		wc.critter_state->radius = rand() % 10 + 5;
		critters.push_back(wc);
	}

	// start update
	update_thread_ = std::thread(World2D::loopedUpdate, this);
	// updateLoop.detach();
}
World2D::~World2D() {
	this->kill_thread_ = true;
	for (auto & wc : critters) {
		delete wc.critter;
		delete wc.critter_state;
		delete wc.critter_prop;
	}
	update_thread_.join();
}

void World2D::loopedUpdate() {
	using namespace std::chrono_literals;
	while (!kill_thread_) {
		std::this_thread::sleep_for(16ms);
		update();
	}
}


void World2D::render(sf::RenderWindow& window) const {
	// draw background, environemnt
	// draw critters
	for (auto& wc : critters) {
		const CritterState& st = *(wc.critter_state); 
		sf::CircleShape shape(st.radius);
		shape.setFillColor(wc.critter_prop->color);
		shape.setPosition(st.p.x - st.radius, st.p.y - st.radius);
		window.draw(shape);
	}
}

void World2D::update() {
	random_shuffle(critters.begin(), critters.end());
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
			float sqD = sqDist(st->p, st2->p);
			float touch_dist = st->radius + st2->radius;
			if (sqD <= (touch_dist) * (touch_dist)) {
				auto col1 = wc.critter_prop->color;
				auto col2 = wc2.critter_prop->color;
				if (magnitude(st->v) > magnitude(st2->v)) {
					wc2.critter_prop->color = col1;	
				} else {
					wc.critter_prop->color = col2;
				}
				// !
				vec2 d12 = normalize(st2->p - st->p);
				float v12_mag =  (st-> v * d12) * COLLISION_COE;
				float v21_mag = -(st2->v * d12) * COLLISION_COE;
				// todo mass
				st->v -= (v12_mag + v21_mag) * d12;
				st2->v += (v12_mag + v21_mag) * d12;
				// push back
				float distance = magnitude(st2->p - st->p) - touch_dist;
				if (distance < 0) {
					distance -= 0.01f;
					st->p += d12 * (distance / 2);
					st2->p -= d12 * (distance / 2);
					// give it a kick too
					st->v  -= d12 * (abs(distance) / st->radius) * 0.5;
					st2->v += d12 * (abs(distance) / st->radius) * 0.5;
				}
			}
		}

	}

	// forces
	for (auto & critter : critters) {
		auto * critter_state = critter.critter_state;
		// gravity
		critter_state->v += {0, GRAVITY};
		// drag
		// critter_state->v *= 0.9999f;
	}

	// actaully move them
	for (auto& wc : critters) {
		CritterState * st = wc.critter_state;
		// update
		st->p += st->v;

		// constaint
		reflect(st->p.x, st->v.x, 0, width_);
		reflect(st->p.y, st->v.y, 0, height_);
	}
}




