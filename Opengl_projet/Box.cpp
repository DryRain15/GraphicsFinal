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

	this->translationMatrix[3][0] = this->center.x;
	this->translationMatrix[3][1] = this->center.y;
	this->translationMatrix[3][2] = this->center.z;
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

/*
// Check if two OBBs are colliding
bool Box::isCollideWith(Box* box)
{
	// Compute rotation matrix expressing box1 in box2's coordinate frame
	glm::mat3 R = glm::mat3(box->getRotationMatrix()) * glm::transpose(glm::mat3(this->getRotationMatrix()));

	glm::vec3 T = box->center - this->center;
	// Bring translation into box2's coordinate frame
	T = glm::vec3(glm::dot(T, glm::vec3(box->translationMatrix[0])), glm::dot(T, glm::vec3(box->translationMatrix[1])), glm::dot(T, glm::vec3(box->translationMatrix[2])));

	// Compute common subexpressions. Add in an epsilon term to
	// counteract arithmetic errors when two edges are parallel and
	// their cross product is (near) null (see text for details)
	glm::vec3 absR[3];
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			absR[i][j] = (R[i][j]) + FLT_EPSILON;

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

*/

bool Box::isCollideWith(Box* box)
{
	// Compute the transformation matrix for each OBB
	glm::mat3 R1 = this->getRotationMatrix();
	glm::mat3 R2 = box->getRotationMatrix();
	glm::mat3 R = R1 * glm::transpose(R2);

	glm::mat4 tM1 = this->getTranslationMatrix();
	glm::mat4 tM2 = box->getTranslationMatrix();
	glm::vec3 t1 = glm::vec3(tM1[3][0], tM1[3][1], tM1[3][2]);
	glm::vec3 t2 = glm::vec3(tM2[3][0], tM2[3][1], tM2[3][2]);
	glm::vec3 t = t1 - t2;

	// Compute the half-widths of each OBB along its local axes
	glm::vec3 h1 = this->maxPoint - this->center;
	glm::vec3 h2 = box->maxPoint - box->center;

	// For each of the 3 axes of the OBBs
	for (int i = 0; i < 3; i++)
	{
		// Compute the projection interval of the OBBs along the current axis
		float r1 = glm::dot(h1, glm::abs(R[i]));
		float r2 = glm::dot(h2, glm::abs(R[i]));
		float r = glm::dot(t, glm::abs(R[i]));

		// Check for OBB collision along the current axis
		if (r > r1 + r2)
		{
			return false;
		}
	}

	// For each of the 3 axes of the OBBs
	for (int i = 0; i < 3; i++)
	{
		// Compute the projection interval of the OBBs along the current axis
		float r1 = glm::dot(h1, glm::vec3(R[0][i], R[1][i], R[2][i]));
		float r2 = glm::dot(h2, glm::vec3(R[0][i], R[1][i], R[2][i]));
		float r = glm::dot(t, glm::vec3(R[0][i], R[1][i], R[2][i]));

		// Check for OBB collision along the current axis
		if (r > r1 + r2)
		{
			return false;
		}
	}

	// For each of the 9 axes formed by the cross product of the axes of the OBBs
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			// Compute the projection interval of the OBBs along the current axis
			glm::vec3 axis = glm::cross(R[i], R[j]);
			float r1 = glm::dot(h1, glm::abs(axis));
			float r2 = glm::dot(h2, glm::abs(axis));
			float r = glm::dot(t, glm::abs(axis));

			// Check for OBB collision along the current axis
			if (r > r1 + r2)
			{
				return false;
			}
		}
	}
	
	// No separating axis found, the OBBs must be intersecting
	return true;
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

	cout << "Translation : C(" << getCenter().x << ", " << getCenter().y << ", " << getCenter().z << ")"
		<< " ~ M(" << getMatrix()[3][0] << ", " << getMatrix()[3][1] << ", " << getMatrix()[3][2] << ")" << endl;

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
 	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}