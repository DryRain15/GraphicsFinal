#include "PhysicsManager.h"

bool PhysicsManager::bDestroyed = false;
PhysicsManager* PhysicsManager::instance = NULL;

void PhysicsManager::ProcessCollsionInternal(CollisionData* data, float dt) {
	Box* A = data->GetColliderA();
	Box* B = data->GetColliderB();
	glm::vec3 point = data->GetPoint();

	glm::vec3 inertiaA = A->getMomentumAtPoint(point);
	glm::vec3 inertiaB = B->getMomentumAtPoint(point);
	
	// �浹�޴� ���
	// Overlap Point�� ���ؼ� Position fit�� ���־�� �Ѵ�.
	// �浹 ��ü�� STATIC�� ���� ���� ����.
	glm::vec3 dist = A->getCenter() - point;
	glm::vec3 overlap = (dist + (A->getIntersectionPoint(dist) - A->getCenter())) * dt;

	switch (A->type)
	{
	case DYNAMIC:
		{
		inertiaA = A->getMomentumAtPoint(point);
		A->translation(-overlap.x - dt, -overlap.y - dt, -overlap.z - dt);
		break;
		}
	case KINEMETIC:
		{
		// TODO: KINEMATIC�� �̵��� �� ������ ����� ��� �����ؾ� �ұ�.
		inertiaA = A->getMomentumAtPoint(point);
		break;
		}
	default:
		{
		break;
		}
	}

	switch (B->type)
	{
	case STATIC: 
	{
		// �浹 ��ü���� ��� ��� å���� �������� �����Ѵ�.
		glm::vec3 totalInertia = inertiaA;
		glm::vec3 halfInertia = totalInertia;
		
		A->applyExternalMomentumAtPoint(point, -halfInertia);

		break;
	}
	case DYNAMIC:
	{
		// �浹 ��ü�� �浹�޴� ����� ����� ������ �����ش�.
		glm::vec3 totalInertia = inertiaA + inertiaB;
		glm::vec3 halfInertia = totalInertia / 2.0f;

		A->applyExternalMomentumAtPoint(point, halfInertia);
		B->applyExternalMomentumAtPoint(point, halfInertia);
		
		break;
	}
	case KINEMETIC:
	{
		break;
	}
	default:
	{
		break;
	}
	}
}