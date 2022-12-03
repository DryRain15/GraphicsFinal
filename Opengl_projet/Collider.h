#ifndef COLLIDER_H
#define COLLIDER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum Collider_Type {
	STATIC, 
	DYNAMIC,
	KINEMETIC
};

class Collider
{
public:
	Collider_Type type;
	glm::vec3 velocity;
	glm::quat angularVelocity;
	float weight;

	Collider(Collider_Type type, float weight, glm::vec3 velocity);
};
#endif
