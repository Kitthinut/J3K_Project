#pragma once

#include "Enum/Interact.hpp"

#include <functional>
#include <SFML/Graphics.hpp>

struct Interactable {
        sf::FloatRect bounds;
        Interact      name;
};
