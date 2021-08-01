
#include "algo.h"
#include "Utils.h"

void sphere_collision(CritterState * s1, CritterState * s2) {
    // updates force
    // have they collided?
    float distance = dist(s1->p, s2->p);
    if (distance > s1->radius + s2->radius) return;
}
