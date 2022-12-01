#ifndef INTERNAL_ENERGY_H
#define INTERNAL_ENERGY_H

#include <stdlib.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

struct InternalEnergy {
private:
	float getVelocityMagnitude() {
		float x = m_Velocity.x;
		float y = m_Velocity.y;
		float z = m_Velocity.z;

		return glm::sqrt(x * x + y * y + z * z);
	}
	
	float getVelocityMagnitudeSqr() {
		float x = m_Velocity.x;
		float y = m_Velocity.y;
		float z = m_Velocity.z;

		return x * x + y * y + z * z;
	}

	glm::vec3 getVelocityNormalized() {
		float mag = getVelocityMagnitude(m_Velocity);
		if (mag == 0)
			return glm::vec3(0, 0, 0);

		return m_Velocity / mag;
	}

	/// <summary>
	/// ��� point���� ���� �����ӿ� �ش��ϴ� ���� ���������� ���.
	/// Quaternion�� Euler Angle�� �ٲپ� ���ӵ��� ���ϰ� 
	/// </summary>
	/// <returns></returns>
	glm::vec3 getAngularMomentumAtPoint(glm::vec3 point) {

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

public:
	float m_weight;
	glm::vec3* p_center;
	glm::vec3 m_Velocity;
	glm::vec4 m_AngularVelocity;

	glm::vec3 getMomentumAtPoint(glm::vec3 point);
};

#endif
