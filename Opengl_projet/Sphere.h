#include "ThreeDimensionalFigure.h"
#include "Collider.h"
#include <windows.h>

class Sphere : public Collider, public Shape
{
private:
	glm::vec3 center;
	float radius;
public:
	Sphere(glm::vec3 center, float radius, Collider_Type type = DYNAMIC, float weight = 1, glm::vec3 velocity = glm::vec3(0.3));
	~Sphere();
	virtual void render();

};

