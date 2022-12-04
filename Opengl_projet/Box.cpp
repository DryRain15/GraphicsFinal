#include "Box.h"

Box::Box(float* vertices, vector<unsigned int> vertexAttributeNumbers, unsigned int eachAttributeNumber, Collider_Type type, float weight, glm::vec3 velocity) : Collider(type, weight, velocity) {

	unsigned int* indices = new unsigned int[36] {
		/*Above ABC,BCD*/
		0, 1, 2,
		1, 2, 3,
		/*Following EFG,FGH*/
		4, 5, 6,
		5, 6, 7,
		/*Left ABF,AEF*/
		0, 1, 5,
		0, 4, 5,
		/*Right side CDH,CGH*/
		2, 3, 7,
		2, 6, 7,
		/*ACG,AEG*/
		0, 2, 6,
		0, 4, 6,
		/*Behind BFH,BDH*/
		1, 5, 7,
		1, 3, 7
	};
	this->maxPoint = glm::vec3(vertices[9], vertices[10], vertices[11]);
	this->minPoint = glm::vec3(vertices[12], vertices[13], vertices[14]);
	this->center = (this->maxPoint + this->minPoint) * 0.5f;
	this->verticeAttributes = vertices;
	this->indices = indices;
	this->vertexAttributeNumbers.push_back(3);
	this->eachAttributeNumber = 3;
	this->totalVerticeNumber = 8;
	this->totalIndiceNumber = 36;
	this->totalCoordinateNumber = eachAttributeNumber * totalVerticeNumber;
	this->color = glm::vec3(1.0, 0.5, 0);
	this->matrix = glm::mat4(1.0f);
	this->rotationMatrix = glm::mat4(1.0f);
	this->translationMatrix = glm::mat4(1.0f);
	this->initiliazeVertexBufferDatas();
}

bool Box::isCollideWith(Box * box)
{
	
	return(this->maxPoint.x > box->minPoint.x &&
		this->minPoint.x < box->maxPoint.x&&
		this->maxPoint.y > box->minPoint.y &&
		this->minPoint.y < box->maxPoint.y&&
		this->maxPoint.z > box->minPoint.z &&
		this->minPoint.z < box->maxPoint.z);
}

void Box::translation(float directionX, float directionY, float directionZ)
{
	float dx = directionX * velocity.x;
	float dy = directionY * velocity.y;
	float dz = directionZ * velocity.z;
	ThreeDimensionalFigure::translation(dx, dy, dz);
	this->minPoint = glm::vec3(minPoint.x + dx, minPoint.y + dy, minPoint.z + dz);
	this->maxPoint = glm::vec3(maxPoint.x + dx, maxPoint.y + dy, maxPoint.z + dz);
	this->center = (this->maxPoint + this->minPoint) * 0.5f;
}

glm::vec3 Box::getCenter() {
	return this->center;
}