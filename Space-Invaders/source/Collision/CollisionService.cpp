#include "../../header/Collision/CollisionService.h"
#include "../../header/Collision/ICollider.h"
#include <SFML/Graphics.hpp> // Include the appropriate header for sf::Sprite

namespace Collision
{
    CollisionService::CollisionService() {}

    CollisionService::~CollisionService() {}

    void CollisionService::initialize() {}

    void CollisionService::update()
    {
        processCollision();
    }

    void CollisionService::processCollision()
    {
        for (size_t i = 0; i < collider_list.size() - 1; ++i)
        {
            for (size_t j = i + 1; j < collider_list.size(); ++j)
            {
                doCollision(i, j);
            }
        }
    }

    void CollisionService::doCollision(size_t index_i, size_t index_j)
    {
        if (index_i >= collider_list.size() || index_j >= collider_list.size())
            return;

        ICollider* collider_i = collider_list[index_i];
        ICollider* collider_j = collider_list[index_j];

        if (collider_i == nullptr || collider_j == nullptr)
            return;

        if (collider_i->getCollisionState() == CollisionState::DISABLED ||
            collider_j->getCollisionState() == CollisionState::DISABLED)
            return;

        if (hasCollisionOccurred(index_i, index_j))
        {
            collider_i->onCollision(collider_j);
            collider_j->onCollision(collider_i);
        }
    }

    bool CollisionService::hasCollisionOccurred(size_t index_i, size_t index_j)
    {
        const sf::Sprite& collider_one_sprite = collider_list[index_i]->getColliderSprite();
        const sf::Sprite& collider_two_sprite = collider_list[index_j]->getColliderSprite();

        return collider_one_sprite.getGlobalBounds().intersects(collider_two_sprite.getGlobalBounds());
    }

    void CollisionService::addCollider(ICollider* collider)
    {
        collider_list.push_back(collider);
    }

    void CollisionService::removeCollider(ICollider* collider)
    {
        collider_list.erase(std::remove(collider_list.begin(), collider_list.end(), collider), collider_list.end());
    }
}
