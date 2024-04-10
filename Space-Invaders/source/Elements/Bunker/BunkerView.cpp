#include "../../header/Elements/Bunker/BunkerView.h"
#include "../../header/Global/ServiceLocator.h"
#include "../../header/Graphics/GraphicService.h"
#include "../../header/Global/Config.h"
#include "../../header/Elements/Bunker/BunkerController.h"
#include "../../header/UI/ImageView.h" // Assuming ImageView is part of UI namespace

namespace Element
{
    namespace Bunker
    {
        using namespace Global;
        using namespace Graphics;
        using namespace UI;

        BunkerView::BunkerView() : bunker_image(new ImageView()) { createUIElements(); }

        BunkerView::~BunkerView() { delete bunker_image; }

        void BunkerView::initialize(BunkerController* controller)
        {
            bunker_controller = controller;
            initializeImage();
        }

        void BunkerView::createUIElements() {}

        void BunkerView::initializeImage()
        {
            bunker_image->initialize(Config::bunker_texture_path, bunker_sprite_width, bunker_sprite_height, bunker_controller->getBunkerPosition());
        }

        void BunkerView::update() { bunker_image->update(); }

        void BunkerView::render() { bunker_image->render(); }

        const sf::Sprite& BunkerView::getBunkerSprite() 
        {
            return bunker_image->getSprite();
        }
    }
}
