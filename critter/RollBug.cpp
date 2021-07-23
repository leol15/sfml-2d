
#include "RollBug.h"

Action RollBug::getAction() const {
	return Action(rand(), rand());
}

