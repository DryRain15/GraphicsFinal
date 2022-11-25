#ifndef COLLISION_DATA_H
#define COLLISION_DATA_H
#include "Collider.h"

class CollisionData
{
private:
	Collider* a;
	Collider* b;
public:
	CollisionData(Collider* a, Collider* b);
};

#endif

