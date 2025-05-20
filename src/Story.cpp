#include "Story.hpp"

#include <chrono>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

Story::Story() {
    if (!font.loadFromFile("assets/fonts/Electrolize-Regular.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }
}

void Story::introduction(sf::RenderWindow &window) {
    std::vector<std::string> story = {
        "You are just a regular engineering student, living the daily grind... "
        ";-;",
        "Late nights, tough exams, endless assignments... T_T",
        "But one day, something strange happens... o_O",
        "You find yourself trapped in a time loop, stuck reliving your school "
        "days... >_<",
        "Every time you enter class, the world transforms-",
        "Turning into a mysterious dungeon filled with challenges... O_O",
        "To pass your subjects, you must defeat powerful Chinese bosses-",
        "Guardians of your grades. >:(",
        "But beware: before facing the final boss, you must overcome the Teaching "
        "Assistants-",
        "Smaller, tricky foes blocking your way... ;-;",
        "Fail to defeat the TAs three times, and the loop consumes you-",
        "Ending your journey forever... :'(",
        "Succeed in battling both TAs and bosses, and you gain EXP and coins-",
        "To upgrade your skills: attack, defense, and HP! (^_^)/",
        "Win or lose, your battles affect your real-world grades.",
        "Can you survive the loop, defeat the bosses, and break free to the light "
        "of graduation? \\o/",
        "The time loop won't affect reality if you finish your boss fights,",
        "but fail, and you'll face the same trials all over again... -_-",
        "...",
        "Press SPACE to begin your journey... >_<",
    };

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(28);
    text.setFillColor(sf::Color::White);

    sf::RectangleShape bg(sf::Vector2f(window.getSize().x, window.getSize().y));
    bg.setFillColor(sf::Color::Black);

    for (const auto &block : story) {
        // Split block into lines
        std::vector<std::string> lines;
        std::istringstream       iss(block);
        std::string              subline;
        while (std::getline(iss, subline)) {
            lines.push_back(subline);
        }

        // Calculate total height
        float lineSpacing = text.getLineSpacing();
        float totalHeight =
            lines.size() * text.getCharacterSize() +
            (lines.size() - 1) * (lineSpacing - text.getCharacterSize());

        // Start drawing from vertical center minus half the block height
        float startY = window.getSize().y / 2.f - totalHeight / 2.f;

        bool next = false;
        while (!next && window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return;
                }
                if (event.type == sf::Event::KeyPressed &&
                    event.key.code == sf::Keyboard::Space) {
                    next = true;
                }
            }
            window.clear();
            window.draw(bg);

            // Draw each line centered horizontally
            float y = startY;
            for (const auto &l : lines) {
                text.setString(l);
                sf::FloatRect textRect = text.getLocalBounds();
                text.setOrigin(textRect.left + textRect.width / 2.0f, 0);
                text.setPosition(window.getSize().x / 2.f, y);
                window.draw(text);
                y += lineSpacing;
            }

            window.display();
        }
        // Wait for spacebar to be released before continuing
        while (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
               window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return;
                }
            }
            window.clear();
            window.draw(bg);

            float y = startY;
            for (const auto &l : lines) {
                text.setString(l);
                sf::FloatRect textRect = text.getLocalBounds();
                text.setOrigin(textRect.left + textRect.width / 2.0f, 0);
                text.setPosition(window.getSize().x / 2.f, y);
                window.draw(text);
                y += lineSpacing;
            }

            window.display();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
}

void Story::showCredits(sf::RenderWindow &window) {
    std::vector<std::string> credits = {
        "         FIBO XI Dungeon",
        "      (An RPG of pain and growth)",
        "",
        "        Developed by: J3K Corporation",
        "",
        "        Story & World Design:",
        "        Kitthinut Changtham",
        "",
        "        Pixel Art, UI & Scene Layout:",
        "        Kitthinut Changtham",
        "",
        "        Classroom & Lobby Systems:",
        "        Kitthinut Changtham",
        "",
        "        Dungeon & Boss Design:",
        "        Pirakan You",
        "",
        "        Task & Dungeon Manager Systems:",
        "        Pirakan You",
        "",
        "        Potion, EXP & Shop Systems:",
        "        Sarayuth Sainiyom",
        "",
        "        Balance & System Improvement:",
        "        Sarayuth Sainiyom",
        ""
        "        Code Integration & Cleanup:",
        "        Chawanakorn Jenkit",
        "",
        "        Beta Testers:",
        "        Chawanakorn Jenkit",
        "        Pirakan You",
        "        Sarayuth Sainiyom",
        "",
        "        Gameplay Design & Balance:",
        "        Everyone in J3K Corporation",
        "",
        "        Story Inspiration:",
        "        FRAB11 : The FIBO Life",
        "",
        "        Special Thanks:",
        "        SFML, Countless sleepless nights, and robotics engineering pain",
        "",
        "        Thank you for playing! T_T",
        "        Good luck escaping the time loop!",
        "",
        "        Press SPACE to skip..."};

    std::vector<sf::Text> textLines;
    float                 spacing = 50.0f; // vertical space between lines

    for (size_t i = 0; i < credits.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(credits[i]);
        text.setCharacterSize(28);
        text.setFillColor(sf::Color::White);
        sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin(bounds.left + bounds.width / 2.0f,
                       bounds.top + bounds.height / 2.0f);
        text.setPosition(window.getSize().x / 2.0f,
                         window.getSize().y + i * spacing);
        textLines.push_back(text);
    }

    sf::RectangleShape bg(sf::Vector2f(window.getSize().x, window.getSize().y));
    bg.setFillColor(sf::Color::Black);

    sf::Clock clock;
    float     speed = 40.0f; // pixels per second

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }
            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Space) {
                return; // skip credits
            }
        }

        float delta = clock.restart().asSeconds();
        for (auto &text : textLines) {
            text.move(0, -speed * delta);
        }

        window.clear();
        window.draw(bg);
        for (const auto &text : textLines) {
            if (text.getPosition().y + text.getGlobalBounds().height >= 0)
                window.draw(text);
        }
        window.display();

        // Stop when last line scrolls off top
        const sf::Text &last = textLines.back();
        if (last.getPosition().y + last.getGlobalBounds().height < 0) {
            break;
        }
    }
}
