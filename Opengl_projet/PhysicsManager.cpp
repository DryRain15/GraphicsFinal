#include "PhysicsManager.h"

bool PhysicsManager::bDestroyed = false;
PhysicsManager* PhysicsManager::instance = NULL;

void PhysicsManager::ProcessCollsionInternal(CollisionData* data, float dt) {
	Box* A = data->GetColliderA();
	Box* B = data->GetColliderB();
	glm::vec3 point = data->GetPoint();

	glm::vec3 inertiaA = A->getMomentumAtPoint(point);
	glm::vec3 inertiaB = B->getMomentumAtPoint(point);
	glm::vec3 totalInertia = (inertiaB + inertiaA) * (1 - dt);
	
	// Overlap Point�� ���ؼ� Position fit�� ���־�� �Ѵ�.
	// �浹 ��ü�� STATIC�� ���� ���� ����.
	glm::vec3 dist = B->getClosestPoint(point) - A->getCenter();
	glm::vec3 overlap = ((A->getIntersectionPoint(dist) - A->getCenter()) - dist);

	switch (A->type)
	{
	case DYNAMIC:
		{
		A->translation(-overlap.x, -overlap.y, -overlap.z);
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
	
	// �浹�޴� ���
	switch (B->type)
	{
	case STATIC: 
	{
		// �浹 ��ü���� ��� ��� å���� �������� �����Ѵ�.
		glm::vec3 halfInertia = totalInertia * 0.7f;

		A->applyExternalMomentumAtPoint(point, -halfInertia - overlap);

		break;
	}
	case DYNAMIC:
	{
		// �浹 ��ü�� �浹�޴� ����� ����� �й��Ѵ�.
		if (A->type == KINEMETIC)
		{
			B->translation(overlap.x, overlap.y, overlap.z);
			B->applyExternalMomentumAtPoint(point, totalInertia + overlap);
		}
		else 
		{
			A->applyExternalMomentumAtPoint(point, inertiaB + overlap);
			B->applyExternalMomentumAtPoint(point, inertiaA - overlap);
		}
		
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