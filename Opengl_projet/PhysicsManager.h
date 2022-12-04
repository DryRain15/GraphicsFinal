#ifndef PHYSICS_MANAGER_H
#define PHYSICS_MANAGER_H

#include "CollisionData.h"
#include <stack>
#include <unordered_map>
#include <new>
#include <stdlib.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#define GRAVITY glm::vec3(0.0f, -0.98f, 0.0f)

class PhysicsManager {
private:
	// Physics Manager
	std::stack<CollisionData*> dataStack;
	std::unordered_map<Box*, Collider_Type> colliderHash;

	// Phoenix Singleton
	// Code reference: [Modern C++ Design]
	static bool bDestroyed;
	static PhysicsManager* instance;

	PhysicsManager() {};
	PhysicsManager(const PhysicsManager& other);
	~PhysicsManager() {
		bDestroyed = true;
	}

	static void Create(){
		static PhysicsManager ins;
		instance = &ins;
		instance->dataStack = *new std::stack<CollisionData*>();
	}

	static void KillPhysicsManager() {
		instance -> ~PhysicsManager();
	}

	void UpdateDynamics(float dt) {
		{
			for (auto it = colliderHash.begin(); it != colliderHash.end(); ++it) {

				switch (it->second) {
				case DYNAMIC:
				{
					it->first->angularVelocity *= 1 - dt;
					it->first->velocity *= 1 - dt;
					it->first->velocity += GRAVITY * dt;

					glm::vec3 v = it->first->velocity * dt;
					glm::quat r = it->first->angularVelocity;

					//cout << v.y << endl;

					it->first->translation(v.x, v.y, v.z);
					it->first->rotate(r);
					break;
				}
				case STATIC:
				{
					it->first->resetMomentum(0);
					break;
				}
				default:
				{
					it->first->resetMomentum(1);
					break;
				}
				}
			}
		}
	}

	void ProcessCollision(float dt) {
		while (!dataStack.empty()) {
			CollisionData* data = dataStack.top();
			ProcessCollsionInternal(data, dt);
			dataStack.pop();
		}
	}

	/// <summary>
	/// 물체 충돌시 연산 구현부
	/// </summary>
	/// <param name="data"></param>
	void ProcessCollsionInternal(CollisionData* data, float dt);

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

	void Update(float dt) {
		UpdateDynamics(dt);
		ProcessCollision(dt);
	}

	void RequestCollisionProcessing(CollisionData* data) {
		dataStack.push(data);
	}

	void ResisterPhysicsCollider(Box* collider, Collider_Type t) {
		colliderHash[collider] = t;
		cout << "Resistered Physics Collider:" << collider << " = " << t << endl;
	}

	void UnresisterPhysicsCollider(Box* collider, Collider_Type t) {
		colliderHash.erase(collider);
	}
};



#endif
