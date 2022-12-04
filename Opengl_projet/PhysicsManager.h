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

#define GRAVITY glm::vec3(0.0f, -4.9f, 0.0f)

class PhysicsManager {
private:
	// Physics Manager
	std::stack<CollisionData*> dataStack;
	std::unordered_map<Box*, Collider_Type> colliderHash;
	bool UpdateStarted = false;

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
		int count = 0;
		UpdateStarted = true;
		for (auto it = colliderHash.begin(); it != colliderHash.end(); ++it) {

			switch (it->second) {
			case DYNAMIC:
			{
				//it->first->angularVelocity *= 1 - dt;
				//it->first->velocity *= 1 - dt;
				it->first->velocity += GRAVITY * dt;

				glm::vec3 p = it->first->getCenter();
				glm::vec3 v = it->first->velocity * dt;
				glm::quat r = it->first->angularVelocity;
				

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
				break;
			}
			}

			count++;
		}
	}

	void ProcessCollision(float dt) {
		if (!UpdateStarted) {
			while (!dataStack.empty()) {
				dataStack.pop();
			}
			return;
		}
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
		cout << "Resistered Physics Collider:" << collider << " = " << t << endl
			<< "Position: " << collider->getCenter().x << ", " << collider->getCenter().y << ", " << collider->getCenter().z << endl
			<< "Extent: " << collider->getExtent().x << ", " << collider->getExtent().y << ", " << collider->getExtent().z << endl
			<< "Total Physics Collider:" << colliderHash.size() << endl;

		switch (t) {
		case DYNAMIC:
		{
			collider->setColor(glm::vec3(0, 1, 0));
			break;
		}
		case KINEMETIC:
		{
			collider->setColor(glm::vec3(0, 0, 1));
			break;
		}
		default:
		{
			collider->setColor(glm::vec3(1, 1, 1));
			break;
		}
		}
	}

	void UnresisterPhysicsCollider(Box* collider, Collider_Type t) {
		colliderHash.erase(collider);
	}

	void GivePowerToDynamics(glm::vec3 power) {
		for (auto it = colliderHash.begin(); it != colliderHash.end(); ++it) {
			if (it->second == DYNAMIC) {
				it->first->velocity += power / it->first->weight;
			}
		}
	}

	void BlastAtPoint(glm::vec3 point, float radius, float power) {
		for (auto it = colliderHash.begin(); it != colliderHash.end(); ++it) {
			if (it->second == DYNAMIC) {
				glm::vec3 center = it->first->getCenter();
				float distance = glm::distance(center, point);
				if (distance < radius) {
					glm::vec3 direction = (it->first->getCenter() - point) / distance;
					it->first->applyExternalMomentumAtPoint(it->first->getClosestPoint(point),
						(it->first->getCenter() - point) / distance * power);
				}
			}
		}
	}
};



#endif
