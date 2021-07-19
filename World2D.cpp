#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>    // std::shuffle
#include <vector>
#include <thread>         // std::thread
#include <chrono>
#include <mutex>          // std::mutex

#include "RollBug.h"
#include "World2D.h"

constexpr float GRAVITY = 0.05;
constexpr float COLLISION_COE = 0.95;


World2D::World2D(int width, int height)
	: width_(width), height_(height) {
	// 10 critters at random location
	for (int i = 0; i < 1000; i++) {
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
		wc.critter_state->radius = 7;
		critters.push_back(wc);
	}
	WorldCritter wc = {
		new RollBug(),
		new CritterState({
			static_cast<float>(300), 
			static_cast<float>(100)
		}),
		new CritterProp(sf::Color::Red)
	};
	// critters.push_back(wc);
	WorldCritter wc2 = {
		new RollBug(),
		new CritterState({
			static_cast<float>(300), 
			static_cast<float>(400)
		}),
		new CritterProp(sf::Color::Red)
	};
	// critters.push_back(wc2);
	wc.critter_state->v = {0, 5};
	wc2.critter_state->v = {0, -5};

	// start update
	update_thread_ = std::thread(World2D::loopedUpdate, this);
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
		std::this_thread::sleep_for(6ms);
		update();
	}
}


void World2D::render(sf::RenderWindow& window) const {
	// draw background, environemnt
	// draw critters
	mtx_.lock();
	for (auto& wc : critters) {
		const CritterState& st = *(wc.critter_state); 
		sf::CircleShape shape(st.radius);
		shape.setFillColor(wc.critter_prop->color);
		shape.setPosition(st.p.x - st.radius, st.p.y - st.radius);
		window.draw(shape);
	}
	mtx_.unlock();
}

void World2D::update() {
	mtx_.lock();
	random_shuffle(critters.begin(), critters.end());
	mtx_.unlock();
	// move them!
	for (unsigned int i = 0; i < critters.size(); i++) {
		auto& wc = critters[i];
		CritterState * st = wc.critter_state;

		// circle collision
		for (unsigned int j = i + 1; j < critters.size(); j++) {
			auto& wc2 = critters[j];
			// ?
			CritterState * st2 = wc2.critter_state;
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
				// todo mass
				const float m1 = wc.critter_state->mass;
				const float m2 = wc2.critter_state->mass;
				const vec2 v12 = st->v - st2->v;
				const vec2 v21 = st2->v - st->v;
				const vec2 d12 = (st->p - st2->p);
				const vec2 d21 = (st2->p - st->p);
				st->v  -= 2 * m2 / (m1 + m2) * 
					(v12 * d12 / (magnitude(d12) * magnitude(d12))) * d12;
				st2->v -= 2 * m1 / (m1 + m2) *
					(v21 * d21 / (magnitude(d21) * magnitude(d21))) * d21;
				st->v *= COLLISION_COE;
				st2->v *= COLLISION_COE;
				// push back
				float distance = magnitude(st2->p - st->p) - touch_dist;
				if (distance < 0) {
					// distance -= 0.01f;
					st->p -= normalize(d12) * (distance / 2);
					st2->p += normalize(d12) * (distance / 2);
					// give it a kick too
					st->v  += normalize(d12) * (abs(distance) / st->radius) * 0.9;
					st2->v -= normalize(d12) * (abs(distance) / st->radius) * 0.9;
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
		reflect(st->p.x, st->v.x, 0 + st->radius, width_ - st->radius);
		reflect(st->p.y, st->v.y, 0 + st->radius, height_ - st->radius);
	}
}

void World2D::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		} else if (event.type == sf::Event::MouseButtonPressed) {
			// add one more circle
			WorldCritter wc = {
				new RollBug(),
				new CritterState({
					static_cast<float>(event.mouseButton.x),
					static_cast<float>(event.mouseButton.y)
				}),
				new CritterProp(sf::Color(
					rand() % 200 + 55,
					rand() % 200 + 55,
					rand() % 200 + 55))
			};
			wc.critter_state->v.y = 30;
			wc.critter_state->mass = 40;
			wc.critter_state->radius = 15;
			mtx_.lock();
			critters.push_back(wc);
			mtx_.unlock();
		}

    }
}



