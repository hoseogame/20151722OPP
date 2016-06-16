#pragma once
#include "Object.h"

class Item : public Object
{
private:

public:
	Item(int x = 0, int y = 0);
	virtual ~Item();
};