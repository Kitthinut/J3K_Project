#include "Game/Collision.hpp"

Collision::Collision() { loadObstacles(); }

Interact Collision::onInteractables(sf::FloatRect player) {
    for (const Interactable &interactable : getCurrentInteractables()) {
        if (player.intersects(interactable.bounds)) {
            return interactable.name;
        }
    }
    return Empty;
}

bool Collision::hitCollisions(sf::FloatRect              player,
                              std::vector<sf::FloatRect> type) {
    return std::any_of(type.begin(), type.end(), [&](const sf::FloatRect &ob) {
        return player.intersects(ob);
    });
}

bool Collision::hitObstacles(sf::FloatRect player) {
    return hitCollisions(player, getCurrentObstacles());
}

Room Collision::hitWarps(sf::FloatRect player) {
    bool hit = hitCollisions(player, getCurrentWarps());
    if (hit) return current_room;
    return None;
}

void Collision::drawCollisions(sf::RenderWindow &window, const sf::Color &color,
                               std::vector<sf::FloatRect> type) {
    for (const sf::FloatRect &box : type) {
        sf::RectangleShape rect;
        rect.setPosition(box.left, box.top);
        rect.setSize(sf::Vector2f(box.width, box.height));
        rect.setFillColor(color);
        window.draw(rect);
    }
}

void Collision::drawInteractables(sf::RenderWindow &window, Interact interact) {
    for (const Interactable &box : getCurrentInteractables()) {
        sf::RectangleShape rect;
        rect.setPosition(box.bounds.left, box.bounds.top);
        rect.setSize(sf::Vector2f(box.bounds.width, box.bounds.height));

        sf::Color color(0, 255, 0, 50);
        sf::Color outline(sf::Color::Green);
        float     thickness = 1;
        if (box.name == interact) {
            color     = {255, 255, 0, 100};
            outline   = sf::Color::Yellow;
            thickness = 3;
        }

        rect.setFillColor(color);
        rect.setOutlineColor(outline);
        rect.setOutlineThickness(thickness);
        window.draw(rect);
    }
}

void Collision::draw(sf::RenderWindow &window, Interact interact, bool debug) {
    drawInteractables(window, interact);

    if (debug) {
        // Draw obstacle collision boxes
        drawCollisions(window, sf::Color(255, 0, 0, 100), getCurrentObstacles());

        // Draw warp collision boxes
        drawCollisions(window, sf::Color(0, 0, 255, 100), getCurrentWarps());
    }
}

void Collision::loadObstacles() {
    // Dorm room obstacles
    room_obstacles[Room::Dorm] = {
        {1300,  240,  340,  430},
        { 290,   70,  310,  400},
        { 360,  600,  410,  290},
        {   0,    0,  180, 1080},
        {1770,    0,  150, 1080},
        { 660, 1040,  170,   40},
        {1290,  900,  340,  200},
        {1397,  839,  133,   63},
        {1050,  690,   80,  390},
        { 830, 1000,  220,   80},
        { 180, 1000,  480,   80},
        { 180,    0,   40, 1080},
        { 180,    0, 1590,  350},
        {1710,    0,   60, 1080},
        {1130, 1040,  640,   40},
    };

    // Classroom obstacles
    room_obstacles[Room::Classroom] = {
        {   0,   0, 185, 1080},
        {1760,   0, 160, 1080},
        { 780, 295, 370,  170},
        { 370, 550, 255,  140},
        { 845, 555, 260,  135},
        {1325, 555, 255,  135},
        { 330, 755, 265,  145},
        { 830, 755, 290,  155},
        {1340, 755, 280,  155},
        { 185,   0, 255,  340},
        { 680,   0, 570,  340},
        {1490,   0, 270,  340},
    };

    // Dorm Warps
    room_warps[Room::Dorm] = {
        {610, 1000, 260, 80},
    };

    // Classroom Warps
    room_warps[Room::Classroom] = {
        { 440, 0, 240, 340},
        {1250, 0, 240, 340},
    };

    // Dorm Interactables
    room_interactables[Room::Dorm] = {
        // {  {467, 592, 221, 39},   Dining},
        { {297, 459, 299, 42}, Wardrobe},
        {{1250, 346, 55, 282},      Bed},
    };

    // Classroom Interactables
    room_interactables[Room::Classroom] = {
        {{799, 415, 329, 68}, Teacher_Table}
    };
}