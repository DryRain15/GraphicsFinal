#include "CollisionData.h"

CollisionData::CollisionData(Box* a, Box* b, glm::vec3 point)
{
	this->a = a;
	this->b = b;
	this->point = point;
}

CollisionData::CollisionData(Box* a, Box* b)
{
	this->a = a;
	this->b = b;
	this->point = a->getClosestPoint(b->getClosestPoint(a->getCenter()));
}

Box* CollisionData::GetColliderA()
{
	return a;
}


Box* CollisionData::GetColliderB()
{
	return b;
}

glm::vec3 CollisionData::GetPoint()
{
	return point;
}
