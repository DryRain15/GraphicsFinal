#include "Collider.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Collider::Collider(Collider_Type type, float weight, glm::vec3 velocity)
{
	this->type = type;
	this->weight = weight;
	this->velocity = velocity;
}
