#pragma once

#include <functional>
#include <SFML/Graphics.hpp>
#include <string>

struct Interactable {
        sf::FloatRect         bounds;
        std::string           name;
        std::function<void()> onInteract;
};
