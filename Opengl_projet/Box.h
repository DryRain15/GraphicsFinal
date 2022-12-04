#ifndef BOX_H
#define BOX_H
#include "ThreeDimensionalFigure.h"
#include "Collider.h"

class Box : public ThreeDimensionalFigure, public Collider
{
private:
	glm::vec3 maxPoint;
	glm::vec3 minPoint;
	glm::vec3 center;
public:
	Box(float* vertices, vector<unsigned int> vertexAttributeNumbers = { 3}, unsigned int eachAttributeNumber = 3, Collider_Type type  = DYNAMIC, float weight = 1, glm::vec3 velocity = glm::vec3(0.3));
    bool isCollideWith(Box * box);
	glm::vec3 getCenter();
	virtual void translation(float directionX, float directionY, float directionZ);
	void render();
};
#endif

