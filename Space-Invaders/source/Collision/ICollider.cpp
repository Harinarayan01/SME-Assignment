#include "../../header/Collision/ICollider.h"
#include "../../header/Collision/CollisionState.h" // Include the appropriate header for CollisionState

namespace Collision
{
    ICollider::ICollider() : collision_state(CollisionState::ENABLED) {}

    ICollider::~ICollider() {}

    void ICollider::enableCollision() { collision_state = CollisionState::ENABLED; }

    void ICollider::disableCollision() { collision_state = CollisionState::DISABLED; }

    CollisionState ICollider::getCollisionState() const { return collision_state; }
}
