#ifndef COLLISION_MANAGER_HPP
#define COLLISION_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>
#include "Enum/Room.hpp"


class CollisionManager {
public:
    CollisionManager();

    void loadObstacles();
    void setCurrentRoom(Room room);
    const std::vector<sf::FloatRect>& getCurrentObstacles() const;

private:
    std::unordered_map<Room, std::vector<sf::FloatRect>> roomObstacles;
    Room currentRoom = Room::Dorm;
};

#endif // COLLISION_MANAGER_HPP
