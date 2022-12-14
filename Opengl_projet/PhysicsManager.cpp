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
	
	// Overlap Point에 대해서 Position fit을 해주어야 한다.
	// 충돌 주체가 STATIC인 경우는 없을 예정.
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
		// TODO: KINEMATIC이 이동할 때 고정된 운동량을 어떻게 전달해야 할까.
		inertiaA = A->getMomentumAtPoint(point);
		break;
		}
	default:
		{
		break;
		}
	}
	
	// 충돌받는 대상
	switch (B->type)
	{
	case STATIC: 
	{
		// 충돌 주체에게 모든 운동량 책임을 반전시켜 전가한다.
		glm::vec3 halfInertia = totalInertia * 0.7f;

		A->applyExternalMomentumAtPoint(point, -halfInertia - overlap);

		break;
	}
	case DYNAMIC:
	{
		// 충돌 주체와 충돌받는 대상의 운동량을 분배한다.
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