#include "BattlePhase.hpp"

#include "Dungeon.hpp"
#include "Skill.hpp"

#include <iostream>

// Player picks a skill
void PlayerPickPhase::handleEvent(Dungeon *dungeon, const sf::Event &event,
                                  bool &exit) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            exit = true;
            dungeon->reset();
            return;
        }
        if (event.key.code >= sf::Keyboard::Num1 &&
            event.key.code <= sf::Keyboard::Num5 && dungeon->getPlayer()) {
            int    skillIndex = event.key.code - sf::Keyboard::Num1;
            Skill *skill      = dungeon->getPlayer()->getSkill(skillIndex);
            if (skill) {
                if (skill->getManaCost() >
                    dungeon->getPlayer()->getCurrentMana()) {
                    dungeon->showMessage("Not enough mana!");
                    return;
                }
                dungeon->setSelectedSkillIndex(skillIndex);
                // Reset confirmation if new skill is selected
                dungeon->setConfirmNormalAtFullMana(false);
            }
        }
        // Confirm with E
        if (event.key.code == sf::Keyboard::E &&
            dungeon->getSelectedSkillIndex() != -1) {
            int    idx   = dungeon->getSelectedSkillIndex();
            Skill *skill = dungeon->getPlayer()->getSkill(idx);
            if (skill && skill->getManaCost() == 0 &&
                dungeon->getPlayer()->getCurrentMana() >=
                    dungeon->getPlayer()->getMaxMana()) {
                // If already confirming, proceed; otherwise, prompt
                if (!dungeon->isConfirmNormalAtFullMana()) {
                    dungeon->showMessage(
                        "Mana is full! Are you sure you want to use " +
                        skill->getName() + "? Press E again to confirm.");
                    dungeon->setConfirmNormalAtFullMana(true);
                    return;
                }
            }
            // Reset confirmation and proceed
            dungeon->setConfirmNormalAtFullMana(false);
            dungeon->setPendingSkillIndex(idx);
            dungeon->setPhase(Dungeon::Phase::PlayerAttack);
        }
    }
}

void PlayerPickPhase::update(Dungeon *) {}

void PlayerPickPhase::render(Dungeon *dungeon, sf::RenderWindow &window,
                             sf::Font &font) {
    Player *player   = dungeon->getPlayer();
    float   y        = 900;
    int     selected = dungeon->getSelectedSkillIndex();
    if (player) {
        for (int i = 0; i < 5; ++i) {
            Skill *skill = player->getSkill(i);
            if (skill) {
                // Highlight if selected
                sf::Color boxColor =
                    (i == selected)
                        ? sf::Color(255, 255, 255, 220) // Brighter for selected
                        : sf::Color(0, 0, 0, 180);      // Normal for others

                sf::Color textColor =
                    (i == selected) ? sf::Color::Black : sf::Color::White;

                std::string skillStr =
                    "[" + std::to_string(i + 1) + "] " + skill->getName();
                std::string manaStr =
                    "Mana: " + std::to_string(skill->getManaCost());
                std::string dmgStr =
                    "Dmg: " + std::to_string(skill->getBaseDamage());

                dungeon->drawCenteredBoxWithText(window, skillStr, 200, 40,
                                                 200 + i * 300, y, font, 20,
                                                 boxColor, textColor);
                dungeon->drawCenteredBoxWithText(
                    window, manaStr, 100, 30, 200 + i * 300, y + 30, font, 16,
                    sf::Color(0, 0, 0, 120), sf::Color::Cyan);
                dungeon->drawCenteredBoxWithText(
                    window, dmgStr, 100, 30, 200 + i * 300, y + 60, font, 16,
                    sf::Color(0, 0, 0, 120), sf::Color::Red);
            }
        }
        std::string manaStr = "Mana: " + std::to_string(player->getCurrentMana());
        dungeon->drawCenteredBoxWithText(window, manaStr, 200, 40, 200, 1000, font,
                                         20, sf::Color(0, 0, 0, 180),
                                         sf::Color::Cyan);

        // Show reminder if a skill is selected
        if (selected != -1) {
            dungeon->drawCenteredBoxWithText(
                window, "Press E to select this skill", 400, 40, 960, 850, font,
                24, sf::Color(255, 255, 255, 200), sf::Color::Black);
        }
    }
}

// Player attacks with selected skill
void PlayerAttackPhase::handleEvent(Dungeon *dungeon, const sf::Event &event,
                                    bool &) {
    if (dungeon->isWaitingForContinue() && event.type == sf::Event::KeyPressed &&
        event.key.code == sf::Keyboard::Space) {
        Player *player = dungeon->getPlayer();
        Entity *boss   = dungeon->getBoss();
        int     idx    = dungeon->getPendingSkillIndex();
        if (player && boss && idx >= 0 && idx < 5) {
            Skill *skill = player->getSkill(idx);
            if (skill) {
                // Deduct mana
                int newMana = player->getCurrentMana() - skill->getManaCost();
                player->setCurrentMana(newMana);
                player->castSkill(idx, boss);
            }
        }
        dungeon->setWaitingForContinue(false);
        dungeon->setPhase(Dungeon::Phase::OpponentPick);
    }
}

void PlayerAttackPhase::update(Dungeon *dungeon) {
    if (!dungeon->isWaitingForContinue()) {
        // Trigger animation only, don't apply damage yet
        dungeon->triggerBossHitFlash();
        dungeon->setWaitingForContinue(true);
    }
}

void PlayerAttackPhase::render(Dungeon *dungeon, sf::RenderWindow &window,
                               sf::Font &font) {
    dungeon->drawCenteredBoxWithText(
        window, "Player attacks! (Press SPACE to confirm)", 800, 80, 960, 800,
        font, 32, sf::Color(0, 0, 0, 200), sf::Color::White);
}

// Opponent picks a skill (random)
void OpponentPickPhase::handleEvent(Dungeon *dungeon, const sf::Event &event,
                                    bool &) {
    if (dungeon->isWaitingForContinue() && event.type == sf::Event::KeyPressed &&
        event.key.code == sf::Keyboard::Space) {
        dungeon->setWaitingForContinue(false);
        dungeon->setPhase(Dungeon::Phase::OpponentAttack);
    }
}

void OpponentPickPhase::update(Dungeon *dungeon) {
    if (!dungeon->isWaitingForContinue()) {
        Entity *boss   = dungeon->getBoss();
        Player *player = dungeon->getPlayer();
        if (boss && player) {
            boss->attack(player); // Normal attack
            int newMana = std::min(player->getCurrentMana() +
                                       dungeon->getManaRestoreAmount(),
                                   player->getMaxMana());
            player->setCurrentMana(newMana);
        }
        dungeon->setWaitingForContinue(true);
    }
}

void OpponentPickPhase::render(Dungeon *dungeon, sf::RenderWindow &window,
                               sf::Font &font) {
    dungeon->drawCenteredBoxWithText(
        window, "Boss attacks! (Press SPACE to continue)", 800, 80, 960, 800, font,
        32, sf::Color(0, 0, 0, 200), sf::Color::Red);
}

// Opponent attacks
void OpponentAttackPhase::handleEvent(Dungeon *, const sf::Event &, bool &) {}

void OpponentAttackPhase::update(Dungeon *dungeon) {
    // After showing the attack message, go back to player pick phase
    // You can add animation logic here if you want a delay
    dungeon->setPhase(Dungeon::Phase::PlayerPick);
}

void OpponentAttackPhase::render(Dungeon *dungeon, sf::RenderWindow &window,
                                 sf::Font &font) {
    dungeon->drawCenteredBoxWithText(window, "Boss attacks!", 800, 80, 960, 800,
                                     font, 32, sf::Color(0, 0, 0, 200),
                                     sf::Color::Red);
}