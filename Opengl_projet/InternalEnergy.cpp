#include "InternalEnergy.h"

glm::vec3 InternalEnergy::getMomentumAtPoint(glm::vec3 point) {
	glm::vec3 totalMomentum;

	// E = 1/2 * m * v^2
	// P = dF
	// 직선 이동에 대한 모멘텀은 모든 점에서 일정한 것으로 간주한다.
	totalMomentum += 0.5f * this->m_weight * this->getVelocityMagnitudeSqr() * this->getVelocityNormalized();

	glm::vec3 AngualrMomentum;

	totalMomentum += AngualrMomentum;
}