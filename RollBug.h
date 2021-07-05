#ifndef ROLLBUG_H_
#define ROLLBUG_H_

#include "Critter.h"

class RollBug: public Critter {
public:
	~RollBug() override { }
	Action getAction() const override;
};


#endif


