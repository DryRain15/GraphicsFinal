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
protected:
	Collider_Type type;
	glm::vec3 velocity;
	float weight;
public:
	Collider(Collider_Type type, float weight, glm::vec3 velocity);
};
#endif
