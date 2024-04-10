#include "../../header/Enemy/EnemyController.h"
#include "../../header/Global/ServiceLocator.h"
#include "../../header/Player/PlayerController.h"
#include "../../header/Particle/ParticleSystem.h"
#include "../../header/Sound/SoundService.h"
#include <SFML/Graphics.hpp> // Include necessary headers for SFML types

namespace Enemy
{
    using namespace Global;
    using namespace Player;
    using namespace Particle;
    using namespace Sound;

    EnemyController::EnemyController(EnemyType type)
    {
        enemy_view = new EnemyView();
        enemy_model = new EnemyModel(type);
    }

    EnemyController::~EnemyController()
    {
        delete enemy_view;
        delete enemy_model;
    }

    void EnemyController::initialize()
    {
        enemy_model->initialize();
        enemy_model->setEnemyPosition(getRandomInitialPosition());
        enemy_view->initialize(this);
    }

    void EnemyController::update()
    {
        move();
        enemy_view->update();
        handleOutOfBounds();
    }

    void EnemyController::render()
    {
        enemy_view->render();
    }

    // Other member function implementations...

    void EnemyController::destroy()
    {
        sf::Vector2f enemyPosition = enemy_model->getEnemyPosition();

        ServiceLocator* serviceLocator = ServiceLocator::getInstance();

        serviceLocator->getParticleService()->spawnParticleSystem(enemyPosition, Particle::ParticlesType::EXPLOSION);
        serviceLocator->getSoundService()->playSound(SoundType::EXPLOSION);
        serviceLocator->getEnemyService()->destroyEnemy(this);
    }
}
