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
	glm::vec3 tc = (this->maxPoint + this->minPoint) * 0.5f;

	for (int v = 0; v < 24; v++) {
		vertexes[v] -= tc[v % 3];
	}

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
	
	this->maxPoint = glm::vec3(vertexes[9], vertexes[10], vertexes[11]);
	this->minPoint = glm::vec3(vertexes[12], vertexes[13], vertexes[14]);
	this->center = glm::vec3(0);
		
	this->color = glm::vec3(1.0, 0.5, 0);
	this->matrix = glm::mat4(1.0f);
	this->type = type;
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

	translation(tc.x, tc.y, tc.z);

	velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	angularVelocity = glm::vec3(0.0f, 0.0f, 0.0f);
}

// 3D OBB Collision Check
bool Box::isCollideWith(Box* box, bool external)
{
	// Compute the transformation matrix for each OBB
	glm::mat3 R1 = this->getRotationMatrix();
	glm::mat3 R2 = box->getRotationMatrix();
	glm::mat3 R = R1 * glm::transpose(R2);

	glm::vec3 c1 = this->getCenter();
	glm::vec3 c2 = box->getCenter();

	float d1 = this->getIntersectionDistance(box->getClosestPoint(c1) - c1);
	float d2 = this->getVelocityMagnitude(box->getClosestPoint(c1) - c1);

	// Check for OBB collision along the current axis
	if (d1 < d2)
	{
		return false;
	}

	return true;

	/*
	float d1 = this->getIntersectionDistance(box->getClosestPoint(c1) - c1);
	float d2 = this->getIntersectionDistance(this->getClosestPoint(c2) - c2);
	float d = getVelocityMagnitude(this->getClosestPoint(c2) - box->getClosestPoint(c1));

	cout << "A :" << this->getIndex() << "| d1 = " << d1 << endl
		<< "B :" << box->getIndex() << "| d2 = " << d2 << endl
		<< "SUM | d = " << d << endl;

	for (int i = 0; i < 3; i++)
	{
		// Check for OBB collision along the current axis
		if (d > d1 + d2)
		{
			return false;
		}
	}

	return true;
	*/
}


void Box::translation(float directionX, float directionY, float directionZ)
{
	float dx = directionX;
	float dy = directionY;
	float dz = directionZ;
	ThreeDimensionalFigure::translation(dx, dy, dz);
	this->minPoint = glm::vec3(minPoint.x + dx, minPoint.y + dy, minPoint.z + dz);
	this->maxPoint = glm::vec3(maxPoint.x + dx, maxPoint.y + dy, maxPoint.z + dz);
	this->center = this->center + glm::vec3(dx, dy, dz);
}

glm::vec3 Box::getCenter() {
	return this->center;
}

glm::vec3 Box::getExtent() {
	return this->maxPoint - this->center;
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
	glm::vec3 distance = this->center- point;
	glm::vec3 pointToCenterNormalized = getVelocityNormalized(distance);
	glm::vec3 momentumToCenter = glm::dot(momentum, pointToCenterNormalized) * glm::abs(pointToCenterNormalized);
	glm::vec3 momentumToAngular = momentum - momentumToCenter;
	this->velocity = momentumToCenter / this->weight;

	// Convert linear momentum "momentumToAngular" into angular momentum as Quaternion
	glm::vec3 angularMomentum = glm::cross(distance, momentumToAngular);
	glm::vec3 angularVelocity = angularMomentum / this->weight;
	this->angularVelocity = glm::quat(angularVelocity);
}

void Box::addExternalMomentumAtPoint(glm::vec3 point, glm::vec3 momentum) {
	// split momentum into two parts:
	// one is the vector which is from point to center
	// another is the vector which is perpendicular to the first one and will applied to angular momentum
	glm::vec3* result = new glm::vec3[2];
	glm::vec3 distance = this->center- point;
	glm::vec3 pointToCenterNormalized = getVelocityNormalized(distance);
	glm::vec3 momentumToCenter = glm::dot(momentum, pointToCenterNormalized) * glm::abs(pointToCenterNormalized);
	glm::vec3 momentumToAngular = momentum - momentumToCenter;
	this->velocity += momentumToCenter / this->weight;

	// Convert linear momentum "momentumToAngular" into angular momentum as Quaternion
	glm::vec3 angularMomentum = glm::cross(distance, momentumToAngular);
	glm::vec3 angularVelocity = angularMomentum / this->weight;
	this->angularVelocity += glm::quat(angularVelocity);
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

glm::vec3 Box::getIntersectionPoint(glm::vec3 direction)
{
	glm::vec3 dir = getVelocityNormalized(direction);
	// Compute the intersection point of the line and the OBB
	glm::vec3 P = this->getCenter();
	// Transpose of rotationMatrix is inverse of rotationMatrix
	glm::mat4 RT = glm::mat4(glm::transpose(glm::mat3(this->getRotationMatrix())));
	RT[3][3] = 1.0f;
	glm::vec3 d = glm::vec3(RT * glm::vec4(dir, 1));
	glm::vec3 e = this->maxPoint - this->center;

	float eM = std::max(std::abs(e.x), std::max(std::abs(e.y), std::abs(e.z)));
	float dM = std::max(std::abs(d.x), std::max(std::abs(d.y), std::abs(d.z)));
	glm::vec3 Q = P;
	float t = getIntersectionDistance(dir);
	
	Q = P + t * dir;

	return Q;
}

float Box::getIntersectionDistance(glm::vec3 direction)
{
	glm::vec3 dir = getVelocityNormalized(direction);
	// Compute the intersection point of the line and the OBB
	glm::vec3 P = this->getCenter();
	// Transpose of rotationMatrix is inverse of rotationMatrix
	glm::mat4 RT = glm::mat4(glm::transpose(glm::mat3(this->getRotationMatrix())));
	RT[3][3] = 1.0f;
	glm::vec3 d = glm::vec3(RT * glm::vec4(dir, 1));
	glm::vec3 e = this->maxPoint - this->center;
	
	float dM = std::max(std::abs(d.x), std::max(std::abs(d.y), std::abs(d.z)));
	glm::vec3 Q = P;
	
	float t = std::min(std::abs(e.x) / std::abs(d.x), std::min(std::abs(e.y) / std::abs(d.y), std::abs(e.z) / std::abs(d.z)));

	return t;
}

void Box::render() {
 	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Box::setIndex(int idx) {
	this->index = idx;
}

int Box::getIndex() {
	return this->index;
}
