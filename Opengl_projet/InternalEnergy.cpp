#include "InternalEnergy.h"

glm::vec3 InternalEnergy::getMomentumAtPoint(glm::vec3 point) {
	glm::vec3 totalMomentum;

	// E = 1/2 * m * v^2
	// P = dF
	// ���� �̵��� ���� ������� ��� ������ ������ ������ �����Ѵ�.
	totalMomentum += 0.5f * this->m_weight * this->getVelocityMagnitudeSqr() * this->getVelocityNormalized();

	glm::vec3 AngualrMomentum;

	totalMomentum += AngualrMomentum;
}