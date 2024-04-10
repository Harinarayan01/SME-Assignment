#include "../../header/Elements/ElementService.h"
#include "../../header/Collision/ICollider.h"
#include "../../header/Elements/Bunker/BunkerController.h"
#include "../../header/Global/ServiceLocator.h"

namespace Element
{
    using namespace Collision;
    using namespace Bunker;
    using namespace Global;

    ElementService::ElementService() { }

    ElementService::~ElementService() { destroy(); }

    void ElementService::initialize() { spawnBunkers(); }

    void ElementService::update()
    {
        for (auto bunker : bunker_list)
            bunker->update();

        destroyFlaggedBunkers();
    }

    void ElementService::render()
    {
        for (auto bunker : bunker_list)
            bunker->render();
    }

    void ElementService::spawnBunkers()
    {
        for (auto& bunker_data : bunker_data_list)
        {
            BunkerController* bunker_controller = new BunkerController();
            bunker_controller->initialize(bunker_data);
            bunker_list.push_back(bunker_controller);

            ICollider* collider = dynamic_cast<ICollider*>(bunker_controller);
            if (collider)
                ServiceLocator::getInstance()->getCollisionService()->addCollider(collider);
            else
                delete bunker_controller; // Dynamic cast failed, delete the object to avoid memory leak
        }
    }

    void ElementService::destroyBunker(BunkerController* bunker_controller)
    {
        flagged_bunker_list.push_back(bunker_controller);
    }

    void ElementService::destroyFlaggedBunkers()
    {
        for (auto bunker : flagged_bunker_list)
        {
            ICollider* collider = dynamic_cast<ICollider*>(bunker);
            if (collider)
                ServiceLocator::getInstance()->getCollisionService()->removeCollider(collider);
            bunker_list.erase(std::remove(bunker_list.begin(), bunker_list.end(), bunker), bunker_list.end());
            delete bunker;
        }
        flagged_bunker_list.clear();
    }

    void ElementService::destroy()
    {
        for (auto bunker : bunker_list)
        {
            ICollider* collider = dynamic_cast<ICollider*>(bunker);
            if (collider)
                ServiceLocator::getInstance()->getCollisionService()->removeCollider(collider);
            delete bunker;
        }
        bunker_list.clear();
    }

    void ElementService::reset()
    {
        destroy();
        spawnBunkers();
    }
}
