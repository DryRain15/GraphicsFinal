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
	/// 대상 point에서 현재 프레임에 해당하는 국소 지점에서의 운동량.
	/// Quaternion을 Euler Angle로 바꾸어 각속도를 구하고 
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
