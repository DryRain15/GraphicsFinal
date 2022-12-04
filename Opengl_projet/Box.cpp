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
	this->type = type;
	this->rotationMatrix = glm::mat4(1.0f);
	this->translationMatrix = glm::mat4(1.0f);
	
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

/*
bool Box::isCollideWith(Box * box)
{
	return(this->maxPoint.x > box->minPoint.x &&
		this->minPoint.x < box->maxPoint.x&&
		this->maxPoint.y > box->minPoint.y &&
		this->minPoint.y < box->maxPoint.y&&
		this->maxPoint.z > box->minPoint.z &&
		this->minPoint.z < box->maxPoint.z);
}
*/

// Check if two OBBs are colliding
bool Box::isCollideWith(Box* box)
{
	// Compute rotation matrix expressing box1 in box2's coordinate frame
	glm::mat3 R = glm::mat3(box->getMatrix()) * glm::transpose(glm::mat3(this->getMatrix()));

	glm::vec3 T = box->center - this->center;
	// Bring translation into box2's coordinate frame
	T = glm::vec3(glm::dot(T, glm::vec3(box->getMatrix()[0])), glm::dot(T, glm::vec3(box->getMatrix()[1])), glm::dot(T, glm::vec3(box->getMatrix()[2])));

	// Compute common subexpressions. Add in an epsilon term to
	// counteract arithmetic errors when two edges are parallel and
	// their cross product is (near) null (see text for details)
	glm::vec3 absR[3];
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			absR[i][j] = abs(R[i][j]) + FLT_EPSILON;

	glm::vec3 extentThis = (this->maxPoint - this->minPoint) / 2.0f;
	glm::vec3 extentOther = (box->maxPoint - box->minPoint) / 2.0f;

	// Test axes L = A0, L = A1, L = A2
	for (int i = 0; i < 3; i++)
	{
		float ra = extentOther[i];
		float rb = glm::dot(extentThis, absR[i]);
		if (abs(T[i]) > ra + rb) return false;
	}

	// Test axes L = B0, L = B1, L = B2
	for (int i = 0; i < 3; i++)
	{
		float ra = extentOther[0] * absR[0][i] + extentOther[1] * absR[1][i] + extentOther[2] * absR[2][i];
		float rb = extentThis[i];
		if (abs(T[0] * R[0][i] + T[1] * R[1][i] + T[2] * R[2][i]) > ra + rb) return false;
	}

	// Test axis L = A0
	float ra = extentOther[1] * absR[2][0] + extentOther[2] * absR[1][0];
	float rb = extentThis[1] * absR[0][2] + extentThis[2] * absR[0][1];
	if (abs(T[2] * R[1][0] - T[1] * R[2][0]) > ra + rb) return false;
	
	// Test axis L = A1
	ra = extentOther[0] * absR[2][1] + extentOther[2] * absR[0][1];
	rb = extentThis[0] * absR[1][2] + extentThis[2] * absR[1][0];
	if (abs(T[2] * R[0][1] - T[0] * R[2][1]) > ra + rb) return false;
	
	// Test axis L = A2
	ra = extentOther[0] * absR[1][2] + extentOther[1] * absR[0][2];
	rb = extentThis[0] * absR[2][1] + extentThis[1] * absR[2][0];
	if (abs(T[1] * R[0][2] - T[0] * R[1][2]) > ra + rb) return false;
	
	// Since no separating axis is found, the OBBs must be intersecting
	return true;
}


void Box::translation(float directionX, float directionY, float directionZ)
{
	float dx = directionX * velocity.x;
	float dy = directionY * velocity.y;
	float dz = directionZ * velocity.z;
	this->minPoint = glm::vec3(minPoint.x + dx, minPoint.y + dy, minPoint.z + dz);
	this->maxPoint = glm::vec3(maxPoint.x + dx, maxPoint.y + dy, maxPoint.z + dz);
	this->center = this->center + glm::vec3(dx, dy, dz);
}

glm::vec3 Box::getCenter() {
	return this->center;
}


glm::vec3 Box::getDirectionalMomentumAtPoint(glm::vec3 point) {
	glm::vec3 total = glm::vec3(0);

	// TODO: Implement here
	total = this->velocity * this->weight;

	return total;
}

glm::vec3 Box::getAngularMomentumAtPoint(glm::vec3 point) {
	glm::vec3 total = glm::vec3(0);

	// TODO: Implement here

	// Convert Rotation per second as Quaternion into angualr momentum
	glm::vec3 angularVelocity = glm::vec3(this->angularVelocity.x, this->angularVelocity.y, this->angularVelocity.z);
	glm::vec3 angularMomentum = angularVelocity * this->weight;
	glm::vec3 distance = point - this->center;
	glm::vec3 crossProduct = glm::cross(angularMomentum, distance);
	total = crossProduct;
	
	return total;
}

glm::vec3 Box::getMomentumAtPoint(glm::vec3 point) {
	glm::vec3 totalMomentum = glm::vec3(0);
	
	totalMomentum += this->getDirectionalMomentumAtPoint(point) + this->getAngularMomentumAtPoint(point);
	
	return totalMomentum;
}

void Box::resetMomentum(float defaultValue = 0.0f)
{
	this->velocity = glm::vec3(defaultValue);
	this->angularVelocity = glm::vec3(0);
}

void Box::applyExternalMomentumAtPoint(glm::vec3 point, glm::vec3 momentum) {
	// split momentum into two parts:
	// one is the vector which is from point to center
	// another is the vector which is perpendicular to the first one and will applied to angular momentum
	glm::vec3* result = new glm::vec3[2];
	glm::vec3 distance = point - this->center;
	glm::vec3 pointToCenterNormalized = getVelocityNormalized(distance);
	glm::vec3 momentumToCenter = glm::dot(momentum, pointToCenterNormalized) * pointToCenterNormalized;
	glm::vec3 momentumToAngular = momentum - momentumToCenter;
	this->velocity = momentumToCenter / this->weight;

	// Convert linear momentum "momentumToAngular" into angular momentum as Quaternion
	glm::vec3 angularMomentum = glm::cross(distance, momentumToAngular);
	glm::vec3 angularVelocity = angularMomentum / this->weight;
	this->angularVelocity = glm::quat(angularVelocity);
}

glm::vec3 Box::getClosestPoint(glm::vec3 point) {
	glm::vec3 closestPoint = glm::vec3(0);
	
	// get the closest point on the box to the point
	// point is the point which is outside the box
	// closestPoint is the point which is on the box and closest to the point
	closestPoint = glm::vec3(
		glm::clamp(point.x, this->minPoint.x, this->maxPoint.x),
		glm::clamp(point.y, this->minPoint.y, this->maxPoint.y),
		glm::clamp(point.z, this->minPoint.z, this->maxPoint.z)
	);	
	
	return closestPoint;
}

glm::vec3 Box::getIntersectionPoint(glm::vec3 line)
{
	// Calculate the dimensions of the box
	glm::vec3 boxSize = this->maxPoint - this->minPoint;

	// Calculate the point on the line that is closest to the center of the box
	float t = glm::dot(line, (center - this->minPoint)) / glm::dot(line, line);
	glm::vec3 closestPoint = center + t * line;

	// Check if the closest point is inside the box
	if (closestPoint.x >= this->minPoint.x && closestPoint.x <= this->maxPoint.x &&
		closestPoint.y >= this->minPoint.y && closestPoint.y <= this->maxPoint.y &&
		closestPoint.z >= this->minPoint.z && closestPoint.z <= this->maxPoint.z)
	{
		// The line intersects with the box, so return the coordinates of the intersection point
		return closestPoint;
	}
	else
	{
		// The line does not intersect with the box, so return (0, 0, 0)
		return glm::vec3(0, 0, 0);
	}
}
void Box::render() {
	cout << "box box" << endl;
 	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}