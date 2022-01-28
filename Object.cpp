#include "Object.h"

std::string Object::toString()
{
	return typeid(*this).name();
}
