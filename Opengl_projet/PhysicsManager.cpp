#include "PhysicsManager.h"

bool PhysicsManager::bDestroyed = false;
PhysicsManager* PhysicsManager::instance = NULL;

void PhysicsManager::ProcessCollsionInternal(CollisionData* data) {

}

glm::vec3 PhysicsManager::GetTargetMomentum(float weight, glm::vec3 velocity, glm::vec4 angularVelocity) {

}
