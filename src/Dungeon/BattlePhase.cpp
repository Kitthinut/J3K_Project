#include "Dungeon/BattlePhase.hpp"

#include <iostream>

// Player picks a skill
void PlayerPickPhase::handleEvent(const sf::Keyboard::Key &key, bool &exit) {
    if (dungeon->isGameEnded()) return;

    if (key == sf::Keyboard::Escape) {
        exit = true;
        dungeon->reset();
        return;
    }

    if (key >= sf::Keyboard::Num1 && key <= sf::Keyboard::Num5 && player) {
        int skillIndex = key - sf::Keyboard::Num1;
        dungeon->setSelectedSkillIndex(skillIndex);
        return;
    }

    // Confirm with E
    int idx = dungeon->getSelectedSkillIndex();
    if (key == sf::Keyboard::E && idx != -1) {
        Skill *skill = player->getSkill(idx);
        if (skill) {
            if (skill->getManaCost() > player->getCurrentMana()) {
                dungeon->showMessage("Not enough mana! (Press SPACE to continue)");
                return;
            }
            // Reset confirmation and proceed
            dungeon->setPendingSkillIndex(idx);
            dungeon->setPhase(Dungeon::Phase::PlayerAttack);
        }
    }
}

// Render the player pick phase
void PlayerPickPhase::render(sf::RenderWindow &window) {
    if (dungeon->isGameEnded()) return;

    float x        = 360;
    float y        = 900;
    int   selected = dungeon->getSelectedSkillIndex();
    if (player) {
        for (int i = 0; i < 5; ++i) {
            Skill *skill = player->getSkill(i);
            if (skill) {
                // Highlight if selected
                sf::Color boxColor =
                    (i == selected) ? sf::Color(255, 255, 255,
                                                220) // Brighter for selected
                                    : sf::Color(0, 0, 0, 180); // Normal for others

                sf::Color textColor =
                    (i == selected) ? sf::Color::Black : sf::Color::White;

                std::string skillStr =
                    "[" + std::to_string(i + 1) + "] " + skill->getName();
                std::string manaStr =
                    "Mana: " + std::to_string(skill->getManaCost());
                std::string dmgStr =
                    "Dmg: " + std::to_string(skill->getBaseDamage());

                float pos = x + i * 300;
                dungeon->drawCenteredBoxWithText(window, skillStr, 220, 50, pos, y,
                                                 25, boxColor, textColor);
                dungeon->drawCenteredBoxWithText(
                    window, manaStr, 120, 40, pos, y + 45, 20,
                    sf::Color(0, 0, 0, 120), sf::Color::Cyan);
                dungeon->drawCenteredBoxWithText(
                    window, dmgStr, 120, 40, pos, y + 85, 20,
                    sf::Color(0, 0, 0, 120), sf::Color::Red);
            }
        }

        // Show reminder if a skill is selected
        if (selected != -1) {
            dungeon->drawCenteredBoxWithText(
                window, "Press E to select this skill", 400, 40, WINDOW_WIDTH / 2,
                850, 24, sf::Color(255, 255, 255, 200), sf::Color::Black);
        }
    }
}

// Player attacks with selected skill
void PlayerAttackPhase::handleEvent(const sf::Keyboard::Key &key, bool &) {
    if (dungeon->isGameEnded()) return;
    if (key == sf::Keyboard::Space) {
        Entity *boss = dungeon->getBoss();
        int     idx  = dungeon->getPendingSkillIndex();
        if (player && boss && idx >= 0 && idx < 5) {
            Skill *skill = player->getSkill(idx);
            if (skill) {
                dungeon->triggerBossHitFlash();

                // Apply damage to the boss
                player->castSkill(idx, boss);

                // Restore mana if Normal Attact
                if (skill->getName() == "Normal Attact") {
                    int restore = dungeon->getManaRestoreAmount();
                    player->increaseCurrentMana(restore);
                }

                if (boss->getCurrentHP() <= 0) {
                    int exp = (boss->getLevel() + 10) * BOSS_FACTOR;
                    player->increaseEXP(exp);
                    dungeon->showMessage("You win! (Press ESC to exit)");
                    dungeon->setGameEnded(true);
                    return;
                }
            }
        }
        dungeon->setPhase(Dungeon::Phase::OpponentPick);
    }
}

// Render the player attack phase
void PlayerAttackPhase::render(sf::RenderWindow &window) {
    if (dungeon->isGameEnded()) return;
    dungeon->drawCenteredBoxWithText(
        window, "Player attacks! (Press SPACE to confirm)", 800, 80,
        WINDOW_WIDTH / 2, 800, 32, sf::Color(0, 0, 0, 200), sf::Color::White);
}

// Opponent picks a skill (random)
void OpponentPickPhase::handleEvent(const sf::Keyboard::Key &key, bool &) {
    if (dungeon->isGameEnded()) return;
    if (key == sf::Keyboard::Space) {
        Entity *boss = dungeon->getBoss();
        if (boss && player) {
            boss->castSkill(0, player); // Use Normal Attact
            if (player->getCurrentHP() <= 0) {
                player->setEXP(player->getEXP() / 2); // Lose half EXP on defeat
                dungeon->showMessage("You lose! (Press ESC to exit)");
                dungeon->setGameEnded(true);
                return;
            }
        }
        dungeon->setPhase(Dungeon::Phase::OpponentAttack);
    }
}

// Render the opponent pick phase
void OpponentPickPhase::render(sf::RenderWindow &window) {
    if (dungeon->isGameEnded()) return;
    dungeon->drawCenteredBoxWithText(
        window, "Boss attacks! (Press SPACE to continue)", 800, 80,
        WINDOW_WIDTH / 2, 800, 32, sf::Color(0, 0, 0, 200), sf::Color::Red);
}

// OpponentAttackPhase implementations
void OpponentAttackPhase::update() {
    if (dungeon->isGameEnded()) return;
    dungeon->triggerPlayerHitFlash();
    dungeon->setPhase(Dungeon::Phase::PlayerPick);
}