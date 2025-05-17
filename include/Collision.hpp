#pragma once

#include "Enum/Room.hpp"
#include "Struct/Interactable.hpp"

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>

class Collision {
    private:
        std::unordered_map<Room, std::vector<sf::FloatRect>> room_obstacles;
        std::unordered_map<Room, std::vector<sf::FloatRect>> room_warps;
        std::unordered_map<Room, std::vector<Interactable>>  room_interactables;
        Room current_room = Room::Dorm;

        const std::vector<sf::FloatRect> &getCurrentObstacles() {
            return room_obstacles.at(current_room);
        }

        const std::vector<sf::FloatRect> &getCurrentWarps() {
            return room_warps.at(current_room);
        }

        const std::vector<Interactable> &getCurrentInteractables() {
            return room_interactables.at(current_room);
        }

        bool hitCollisions(sf::FloatRect player, std::vector<sf::FloatRect> type);

        void drawCollisions(sf::RenderWindow &window, const sf::Color &color,
                            std::vector<sf::FloatRect> type);

        void drawInteractables(sf::RenderWindow &window, Interact interact);

    public:
        Collision();

        void loadObstacles();

        Room getCurrentRoom() { return current_room; }

        void setCurrentRoom(Room room) { current_room = room; }

        bool        hitObstacles(sf::FloatRect player);
        Room        hitWarps(sf::FloatRect player);
        Interact onInteractables(sf::FloatRect player);

        void draw(sf::RenderWindow &window, Interact interact,
                  bool debug = false);
};