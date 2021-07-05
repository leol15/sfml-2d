
#include "RollBug.h"
#include "Utils.h"

Action RollBug::getAction() const {
	return Action(rand(), rand());
}

