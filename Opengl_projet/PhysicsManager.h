#ifndef PHYSICS_MANAGER_H
#define PHYSICS_MANAGER_H

#include "Collider.h"
#include "CollisionData.h"
#include <stack>
#include <unordered_map>
#include <new>
#include <stdlib.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class PhysicsManager {
private:
	// Phoenix Singleton
	// Code reference: [Modern C++ Design]
	static bool bDestroyed;
	static PhysicsManager* instance;

	PhysicsManager() {};
	PhysicsManager(const PhysicsManager& other);
	~PhysicsManager() {
		bDestroyed = true;
	}

	static void Create() {
		static PhysicsManager ins;
		instance = &ins;
	}

	static void KillPhysicsManager() {
		instance -> ~PhysicsManager();
	}

	// Physics Manager
	std::stack<CollisionData*> dataStack;
	std::unordered_map<Collider*, Collider_Type> colliderHash;

	void ProcessCollision() {
		while (!dataStack.empty()) {
			CollisionData* data = dataStack.top();
			dataStack.pop();

			ProcessCollsionInternal(data);
		}
	}

	/// <summary>
	/// 물체 충돌시 연산 구현부
	/// </summary>
	/// <param name="data"></param>
	void ProcessCollsionInternal(CollisionData* data);

	// 물체의 이동 속도는 Vector3 per sec로 구한다.
	// 물체의 회전 각속도는 Quaternion per sec로 구한다.
	glm::vec3 GetTargetMomentum(float weight, glm::vec3 velocity, glm::vec4 angularVelocity);

public:
	// Phoenix Singleton
	// Code reference: [Modern C++ Design]
	static PhysicsManager* getInstance() {
		if (bDestroyed) {
			new(instance) PhysicsManager;
			atexit(KillPhysicsManager);
			bDestroyed = false;
		}
		else if (instance == NULL) {
			Create();
		}

		return instance;			
	}

	void RequestCollisionProcessing(CollisionData* data) {
		dataStack.push(data);
	}

	void ResisterPhysicsCollider(Collider* collider, Collider_Type t) {
		colliderHash[collider] = t;
	}

	void UnresisterPhysicsCollider(Collider* collider, Collider_Type t) {
		colliderHash.erase(collider);
	}
};



#endif
