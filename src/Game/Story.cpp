#include "Game/Story.hpp"

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

// Function to display the introduction story
void Story::introduction(sf::RenderWindow &window) {
    std::vector<std::string> story = {
        "You are a robotics engineering student, just starting Year 1... >_<",
        "Late nights, confusing lectures, endless tasks... T_T",
        "One morning, something strange happens... o_O",
        "Every time you enter class, the world changes.",
        "Your classroom turns into a Chinese-style...",
        "World???",
        "Filled with traps, trials, and ancient guardians. >_<",
        "You are now caught in a mysterious 40-day loop.",
        "Each day, you must survive classes.",
        "Fight, survive, and gather points to grow stronger.",
        "Win battles to upgrade your stats: attack, defense, HP... (^_^)/",
        "Failing doesn't reset the loop... but it slows you down. -_-",
        "The loop doesn't care how tired you are... it keeps going.",
        "Only by surviving 40 days can you escape. \\o/",
        "Will you endure the grind and power through to the end?",
        "...",
        "Press SPACE to begin your journey. >_<"
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

void Story::showEnding(sf::RenderWindow &window) {
    std::vector<std::string> lines = {"You survived all 40 days.",
                                      "The classroom fades back to normal...",
                                      "The dungeons disappear.",
                                      "The pressure is gone.",
                                      "You're finally free...?",
                                      "...",
                                      "Or maybe...",
                                      "It's just the beginning. o_o"};

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);

    sf::RectangleShape bg(sf::Vector2f(window.getSize().x, window.getSize().y));
    bg.setFillColor(sf::Color::Black);

    for (const auto &line : lines) {
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

            text.setString(line);
            sf::FloatRect textRect = text.getLocalBounds();
            text.setOrigin(textRect.left + textRect.width / 2.0f,
                           textRect.top + textRect.height / 2.0f);
            text.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
            window.draw(text);
            window.display();
        }

        // Wait for spacebar release
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
            window.draw(text);
            window.display();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }

    // TO BE CONTINUED - red and dramatic
    sf::Text finalText;
    finalText.setFont(font);
    finalText.setString("TO BE CONTINUED");
    finalText.setCharacterSize(42);
    finalText.setFillColor(sf::Color(255, 60, 60)); // red
    sf::FloatRect bounds = finalText.getLocalBounds();
    finalText.setOrigin(bounds.left + bounds.width / 2.0f,
                        bounds.top + bounds.height / 2.0f);
    finalText.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);

    sf::Text note;
    note.setFont(font);
    note.setString("(if we have to OwO)");
    note.setCharacterSize(24);
    note.setFillColor(sf::Color::White);
    sf::FloatRect noteBounds = note.getLocalBounds();
    note.setOrigin(noteBounds.left + noteBounds.width / 2.0f,
                   noteBounds.top + noteBounds.height / 2.0f);
    note.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f + 50);

        
    // Display the final text for 3 seconds
    sf::Clock clock;
    float     elapsed = 0;
    while (elapsed < 3.0f && window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }
        }

        elapsed += clock.restart().asSeconds();
        window.clear();
        window.draw(bg);
        window.draw(finalText);
        window.draw(note);
        window.display();
    }
}

// Function to display the credits at the end of the game
void Story::showCredits(sf::RenderWindow &window) {
    std::vector<std::string> credits = {
        "        FIBO XI Dungeon",
        "     (An RPG of pain and growth)",
        "",
        "       Developed by: J3K Corporation",
        "",
        "       Story & World Design:",
        "       Kitthinut Changtham",
        "",
        "       Pixel Art, UI & Scene Layout:",
        "       Kitthinut Changtham",
        "",
        "       Classroom & Lobby Systems:",
        "       Kitthinut Changtham",
        "       Chawanakorn Jenkit",
        "",
        "       Dungeon & Boss Design:",
        "       Pirakan You",
        "",
        "       Task & Dungeon Manager Systems:",
        "       Pirakan You",
        "",
        "       Potion, EXP & Shop Systems:",
        "       Sarayuth Sainiyom",
        "",
        "       Balance & System Improvement:",
        "       Sarayuth Sainiyom",
        "       Pirakan You",
        "",
        "       Code Integration & Cleanup:",
        "       Chawanakorn Jenkit",
        "",
        "       Beta Testers:",
        "       Chawanakorn Jenkit",
        "       Pirakan You",
        "       Sarayuth Sainiyom",
        "",
        "       Gameplay Design & Balance:",
        "       Everyone in J3K Corporation",
        "",
        "       Story Inspiration:",
        "       FRAB11 : The FIBO Life",
        "",
        "       Special Thanks:",
        "       SFML, Countless sleepless nights, and robotics engineering pain",
        "",
        "       Thank you for playing! T_T",
        "       Good luck escaping the time loop!",
        "       (If You Want To Though)",
        "",
        "       Press SPACE to skip..."};

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
