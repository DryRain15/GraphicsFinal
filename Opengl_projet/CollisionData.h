#ifndef COLLISION_DATA_H
#define COLLISION_DATA_H
#include "Box.h"

class Box;

class CollisionData
{
private:
	Box* a;
	Box* b;
	glm::vec3 point;
public:
	CollisionData(Box* a, Box* b, glm::vec3 point);
	CollisionData(Box* a, Box* b);
	Box* GetColliderA();
	Box* GetColliderB();
	glm::vec3 GetPoint();
};

#endif

