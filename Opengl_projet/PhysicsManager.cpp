#include "PhysicsManager.h"

bool PhysicsManager::bDestroyed = false;
PhysicsManager* PhysicsManager::instance = NULL;

void PhysicsManager::ProcessCollsionInternal(CollisionData* data, float dt) {
	Box* A = data->GetColliderA();
	Box* B = data->GetColliderB();
	glm::vec3 point = data->GetPoint();

	glm::vec3 inertiaA = A->getMomentumAtPoint(point);
	glm::vec3 inertiaB = B->getMomentumAtPoint(point);
	
	// 충돌받는 대상
	// Overlap Point에 대해서 Position fit을 해주어야 한다.
	// 충돌 주체가 STATIC인 경우는 없을 예정.
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
		// TODO: KINEMATIC이 이동할 때 고정된 운동량을 어떻게 전달해야 할까.
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
		// 충돌 주체에게 모든 운동량 책임을 반전시켜 전가한다.
		glm::vec3 totalInertia = inertiaA;
		glm::vec3 halfInertia = totalInertia;
		
		A->applyExternalMomentumAtPoint(point, -halfInertia);

		break;
	}
	case DYNAMIC:
	{
		// 충돌 주체와 충돌받는 대상의 운동량을 반으로 나눠준다.
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