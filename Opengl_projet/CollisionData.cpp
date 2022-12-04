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
	this->point = b->getClosestPoint(a->getCenter());

	if (a->getCenter().y != a->getMatrix()[3][1])
	{
		cout << "a->getCenter().x = " << a->getCenter().x << " != a->getMatrix()[3][0] = " << a->getMatrix()[3][0] << endl;
		cout << "a->getCenter().y = " << a->getCenter().y << " != a->getMatrix()[3][1] = " << a->getMatrix()[3][1] << endl;
		cout << "a->getCenter().z = " << a->getCenter().z << " != a->getMatrix()[3][1] = " << a->getMatrix()[3][2] << endl;
	}

	cout << "Point: (" << point.x << ", " << point.y << ", " << point.z << ")" << endl << "A: " << a->getCenter().x << ", " << a->getCenter().y << ", " << a->getCenter().z << endl << "B: " << b->getCenter().x << ", " << b->getCenter().y << ", " << b->getCenter().z << endl;
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
