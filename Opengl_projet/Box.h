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
	float getVelocityMagnitude() {
		float x = velocity.x;
		float y = velocity.y;
		float z = velocity.z;

		return glm::sqrt(x * x + y * y + z * z);
	}

	float getVelocityMagnitudeSqr() {
		float x = velocity.x;
		float y = velocity.y;
		float z = velocity.z;

		return x * x + y * y + z * z;
	}

	glm::vec3 getVelocityNormalized() {
		float mag = getVelocityMagnitude(velocity);
		if (mag == 0)
			return glm::vec3(0, 0, 0);

		return velocity / mag;
	}

	float getVelocityMagnitude(glm::vec3 velocity) {
		float x = velocity.x;
		float y = velocity.y;
		float z = velocity.z;

		return glm::sqrt(x * x + y * y + z * z);
	}

	float getVelocityMagnitudeSqr(glm::vec3 velocity) {
		float x = velocity.x;
		float y = velocity.y;
		float z = velocity.z;

		return x * x + y * y + z * z;
	}
	
	glm::vec3 getVelocityNormalized(glm::vec3 velocity) {
		float mag = getVelocityMagnitude(velocity);
		if (mag == 0)
			return glm::vec3(0, 0, 0);

		return velocity / mag;
	}

	// Convert Angular momentum into rotation per second as Quaternion
	glm::quat getAngularVelocity() {
		float w = angularVelocity.w;
		float x = angularVelocity.x;
		float y = angularVelocity.y;
		float z = angularVelocity.z;

		float mag = glm::sqrt(x * x + y * y + z * z);
		if (mag == 0)
			return glm::quat(1, 0, 0, 0);

		float angle = 2 * glm::acos(w);
		float s = glm::sin(angle / 2);

		return glm::quat(glm::cos(angle / 2), x / s, y / s, z / s);
	}

public:
	Box(float* vertices, vector<unsigned int> vertexAttributeNumbers = { 3}, unsigned int eachAttributeNumber = 3, Collider_Type type  = DYNAMIC, float weight = 1, glm::vec3 velocity = glm::vec3(0.3));
    bool isCollideWith(Box * box);
	glm::vec3 getCenter();
	glm::vec3 getDirectionalMomentumAtPoint(glm::vec3 point);
	glm::vec3 getAngularMomentumAtPoint(glm::vec3 point);
	glm::vec3 getMomentumAtPoint(glm::vec3 point);
	glm::vec3 getClosestPoint(glm::vec3 point);
	glm::vec3 getIntersectionPoint(glm::vec3 line);
	void resetMomentum(float defaultValue);
	void applyExternalMomentumAtPoint(glm::vec3 point, glm::vec3 externalMomentum);
	virtual void translation(float directionX, float directionY, float directionZ);
	void render();
};
#endif

