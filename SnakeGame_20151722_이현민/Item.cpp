#include <iostream>
#include <string>
#include "Gotoxy.h"
#include "Item.h"

using namespace std;

Item::Item(int _x, int _y) : Object(_x, _y, "¢¾", Type::ITEM)
{
}

Item:: ~Item()
{
}