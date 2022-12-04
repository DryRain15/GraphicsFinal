#include "Box.h"

Box::Box(float* vertexes, Collider_Type type, float weight, glm::vec3 velocity) : Collider(type, weight, velocity) {
	
	
	//this->verticeAttributes = vertices;

	/*
	0 1 2 A
	3 4 5 B
	6 7 8 C
	9 10 11 D 
	12 13 14 E
	15 16 17 F
	18 19 20 G
	21 22 23 H
	*/
	
	this->maxPoint = glm::vec3(vertexes[9], vertexes[10], vertexes[11]);
	this->minPoint = glm::vec3(vertexes[12], vertexes[13], vertexes[14]);
	this->center = (this->maxPoint + this->minPoint) * 0.5f;
	float vertices[] = {
		vertexes[12], vertexes[13], vertexes[14], 0.0f, 0.0f, -1.0f,//E
		vertexes[18], vertexes[19], vertexes[20], 0.0f, 0.0f, -1.0f,// G
		vertexes[6], vertexes[7], vertexes[8], 0.0f, 0.0f, -1.0f, // C
		vertexes[6], vertexes[7], vertexes[8], 0.0f, 0.0f, -1.0f,
		vertexes[0], vertexes[1], vertexes[2], 0.0f, 0.0f, -1.0f, //A
		vertexes[12], vertexes[13], vertexes[14], 0.0f, 0.0f, -1.0f,

		vertexes[15], vertexes[16], vertexes[17], 0.0f, 0.0f, 1.0f, // F
		vertexes[21], vertexes[22], vertexes[23], 0.0f, 0.0f, 1.0f, // H
	    vertexes[9], vertexes[10], vertexes[11], 0.0f, 0.0f, 1.0f, // D
		vertexes[9], vertexes[10], vertexes[11], 0.0f, 0.0f, 1.0f, //
		vertexes[3], vertexes[4], vertexes[5], 0.0f, 0.0f, 1.0f, 
		vertexes[15], vertexes[16], vertexes[17], 0.0f, 0.0f, 1.0f,

		vertexes[3], vertexes[4], vertexes[5], -1.0f, 0.0f, 0.0f, // B
		vertexes[0], vertexes[1], vertexes[2], -1.0f, 0.0f, 0.0f, // A
		vertexes[12], vertexes[13], vertexes[14], -1.0f, 0.0f, 0.0f, //E
		vertexes[12], vertexes[13], vertexes[14], -1.0f, 0.0f, 0.0f, //E
		vertexes[15], vertexes[16], vertexes[17], -1.0f, 0.0f, 0.0f, // F
		vertexes[3], vertexes[4], vertexes[5], -1.0f, 0.0f, 0.0f,

		vertexes[9], vertexes[10], vertexes[11], 1.0f, 0.0f, 0.0f, // D
		vertexes[6], vertexes[7], vertexes[8], 1.0f, 0.0f, 0.0f,// C
		vertexes[18], vertexes[19], vertexes[20], 1.0f, 0.0f, 0.0f, //G
		vertexes[18], vertexes[19], vertexes[20], 1.0f, 0.0f, 0.0f,
		vertexes[21], vertexes[22], vertexes[23], 1.0f, 0.0f, 0.0f, //H
		vertexes[9], vertexes[10], vertexes[11], 1.0f, 0.0f, 0.0f,

		vertexes[12], vertexes[13], vertexes[14], 0.0f, -1.0f, 0.0f, // E
		vertexes[18], vertexes[19], vertexes[20], 0.0f, -1.0f, 0.0f, //G
		vertexes[21], vertexes[22], vertexes[23], 0.0f, -1.0f, 0.0f, // H
		vertexes[21], vertexes[22], vertexes[23], 0.0f, -1.0f, 0.0f, // H
		vertexes[15], vertexes[16], vertexes[17], 0.0f, -1.0f, 0.0f, // F
		vertexes[12], vertexes[13], vertexes[14], 0.0f, -1.0f, 0.0f,

		vertexes[0], vertexes[1], vertexes[2], 0.0f, 1.0f, 0.0f,  // A
		vertexes[6], vertexes[7], vertexes[8], 0.0f, 1.0f, 0.0f, // C
		vertexes[9], vertexes[10], vertexes[11], 0.0f, 1.0f, 0.0f,
		vertexes[9], vertexes[10], vertexes[11], 0.0f, 1.0f, 0.0f,// D
		vertexes[3], vertexes[4], vertexes[5], 0.0f, 1.0f, 0.0f, // B
		vertexes[0], vertexes[1], vertexes[2], 0.0f, 1.0f, 0.0f // A
	};
	
	this->color = glm::vec3(1.0, 0.5, 0);
	this->matrix = glm::mat4(1.0f);
	this->rotationMatrix = glm::mat4(1.0f);
	this->translationMatrix = glm::mat4(1.0f);

	// 점 8 개를 216 개로 만들어주는 거 만들기 
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// 216
	glBufferData(GL_ARRAY_BUFFER, 216 * sizeof(float), vertices, GL_STATIC_DRAW);

	glBindVertexArray(vao);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
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
	this->center = this->center + glm::vec3(dx, dy, dz);
}

glm::vec3 Box::getCenter() {
	return this->center;
}

void Box::render() {
 	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}