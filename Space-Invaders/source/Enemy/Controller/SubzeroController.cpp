#include "../../header/Enemy/Controller/SubzeroController.h"
#include "../../header/Enemy/EnemyView.h"
#include "../../header/Enemy/EnemyModel.h"
#include "../../header/Enemy/EnemyConfig.h"
#include "../../header/Global/ServiceLocator.h"

namespace Enemy
{
    using namespace Global;
    using namespace Time;

    namespace Controller
    {
        // Constructor
        SubzeroController::SubzeroController(EnemyType type) : EnemyController(type) { }

        // Destructor
        SubzeroController::~SubzeroController() { }

        // Initialization
        void SubzeroController::initialize()
        {
            // Initialize base class and set initial attributes
            EnemyController::initialize();
            enemy_model->setMovementDirection(MovementDirection::DOWN);
            reward = subzero_reward;
            rate_of_fire = subzero_rate_of_fire;
            vertical_movement_speed = subzero_vertical_movement_speed;
        }

        // Movement logic
        void SubzeroController::move()
        {
            // Ensure that enemy_model is not nullptr
            if (enemy_model == nullptr) {
                // Handle the error condition appropriately
                return;
            }

            switch (enemy_model->getMovementDirection())
            {
                case MovementDirection::DOWN:
                    moveDown();
                    break;

                // Add implementations for other movement directions here
                // Example: case MovementDirection::LEFT: moveLeft(); break;
            }
        }

        // Move downward
        void SubzeroController::moveDown()
        {
            // Ensure that enemy_model is not nullptr
            if (enemy_model == nullptr) {
                // Handle the error condition appropriately
                return;
            }

            sf::Vector2f currentPosition = enemy_model->getEnemyPosition();
            // Ensure that ServiceLocator::getInstance() and getTimeService() are not nullptr
            if (ServiceLocator::getInstance() != nullptr && ServiceLocator::getInstance()->getTimeService() != nullptr) {
                currentPosition.y += vertical_movement_speed * ServiceLocator::getInstance()->getTimeService()->getDeltaTime();
            }

            enemy_model->setEnemyPosition(currentPosition);
        }

        // Process score when destroyed
        void SubzeroController::processScore()
        {
            // Ensure that ServiceLocator::getInstance() and getPlayerService() are not nullptr
            if (ServiceLocator::getInstance() != nullptr && ServiceLocator::getInstance()->getPlayerService() != nullptr) {
                ServiceLocator::getInstance()->getPlayerService()->increaseScore(reward);
            }
            EnemyController::processScore();
        }
    }
}
