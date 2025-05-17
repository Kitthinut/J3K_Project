#include "Struct/CollisionManager.hpp"

CollisionManager::CollisionManager() { loadObstacles(); }

void CollisionManager::loadObstacles() {
    // Dorm room obstacles
    roomObstacles[Room::Dorm] = {
        {1300, 240, 340, 430}, {290, 70, 310, 400},   {360, 600, 410, 290},
        {0, 0, 180, 1080},      {1770, 0, 150, 1080},  {660, 1040, 170, 40},
        {1290, 830, 340, 200},  {1050, 690, 80, 390},  {830, 1000, 220, 80},
        {180, 1000, 480, 80},   {180, 0, 40, 1080},    {180, 0, 1590, 350},
        {1710, 0, 60, 1080},    {1130, 1040, 640, 40}
    }; 

    // Classroom obstacles
    roomObstacles[Room::Classroom] = {
        {440, 0, 240, 340},    {1250, 0, 240, 340},   {0, 0, 185, 1080},
        {1760, 0, 160, 1080},  {780, 295, 370, 170},  {370, 550, 255, 140},
        {845, 555, 260, 135},  {1325, 555, 255, 135}, {330, 755, 265, 145},
        {830, 755, 290, 155},  {1340, 755, 280, 155}, {185, 0, 255, 340},
        {680, 0, 570, 340},    {1490, 0, 270, 340}
    };
}

void CollisionManager::setCurrentRoom(Room room) {
    currentRoom = room;
}

const std::vector<sf::FloatRect>& CollisionManager::getCurrentObstacles() const {
    return roomObstacles.at(currentRoom);
}
