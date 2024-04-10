#include "../../header/Elements/Bunker/BunkerData.h"
#include <SFML/System/Vector2.hpp> // Include the appropriate header for sf::Vector2f

namespace Element
{
    namespace Bunker
    {
        BunkerData::BunkerData() { }

        BunkerData::BunkerData(sf::Vector2f position)
        {
            this->position = position;
        }
    }
}
