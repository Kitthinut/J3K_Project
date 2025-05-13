#include <iostream> // For std::cout and std::endl
#include <vector> // For std::vector
#include "entity.cpp" // Assuming this header file contains the definition of the Entity class
#include "skill.cpp" // Assuming this header file contains the definition of the Skill class
#include "player.h" // Assuming this header file contains the definition of the Player class

int main() {
    // Create a player entity
    Player player(100, 100, 50, 50, 20, 10, 1, 100, 0);

    // Create a target entity
    Entity target(80, 80, 40, 40, 15, 5, 1);

    // // Cast normal attack on the target
    // player.attack(&target);
    // std::cout << "Target's current HP after normal attack: " << target.getCurrentHP() << std::endl;
    player.setSkill(0, &fireball); // Set the normal attack skill
    player.getSkill(0)->printInfo(); // Print the normal attack skill info
    // // Cast fireball skill on the target
    // player.castSkill(0, &target);
    std::cout << "Target's current HP after fireball: " << target.getCurrentHP() << std::endl;

    return 0;
}

