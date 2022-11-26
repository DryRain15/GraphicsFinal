#include "Sphere.h"

Sphere::Sphere(glm::vec3 center, float radius, Collider_Type type, float weight, glm::vec3 velocity) : Collider(type, weight, velocity)
{
	this->radius = radius;
}

Sphere::~Sphere()
{
}

void Sphere::render()
{

}
