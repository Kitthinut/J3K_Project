#ifndef RENDER_H
#define RENDER_H

#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

// Helper to change text color in terminal (works on most terminals)
#define RESET_COLOR   "\033[0m"
#define RED_COLOR     "\033[31m"
#define GREEN_COLOR   "\033[32m"
#define YELLOW_COLOR  "\033[33m"
#define BLUE_COLOR    "\033[34m"
#define MAGENTA_COLOR "\033[35m"
#define CYAN_COLOR    "\033[36m"
#define WHITE_COLOR   "\033[37m"
#define BOLD          "\033[1m"
#define UNDERLINE     "\033[4m"

// Cool text effects
#define BLINK "\033[5m" // Blinking text

class Render {
    public:
        // Clears the console
        void clear() {
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif
        }

        // Draws a stylish box with a title and list of options
        void drawBox(const std::string &title, const std::vector<std::string> &content) {
            // Determine the maximum width needed for any line in the content, plus
            // the title
            int width = 0;
            for (const auto &line : content)
                if (line.size() > width) width = line.size();
            if (title.size() > width) width = title.size();
            width += 4;

            std::string border      = "+" + std::string(width, '=') + "+";
            std::string innerBorder = "+" + std::string(width, '-') + "+";

            std::cout << border << "\n";
            std::cout << "| " << centerText(title, width - 2) << " |\n";
            std::cout << innerBorder << "\n";

            for (const auto &line : content) {
                std::cout << "| " << centerText(line, width - 2) << " |\n";
            }

            std::cout << border << "\n";
        }

        // Prints a line of text
        void print(const std::string &text, bool newline = true) {
            if (newline) std::cout << text << "\n";
            else std::cout << text;
        }

        // Prints raw text
        void rawPrint(const std::string &text) { std::cout << text << "\n"; }

        // Dummy render function // literally delay
        void render(bool wait = false) {
            if (wait) std::this_thread::sleep_for(std::chrono::milliseconds(600));
        }

        // Shows the game title screen
        void renderTitleScreen() {
            clear();
            rawPrint(R"(
       _ ____  _  __   _____  ____  _    _ _      _   _ _____ _____ _    _ _______ 
      | |___ \| |/ /  / ____|/ __ \| |  | | |    | \ | |_   _/ ____| |  | |__   __|
      | | __) | ' /  | (___ | |  | | |  | | |    |  \| | | || |  __| |__| |  | |   
  _   | ||__ <|  <    \___ \| |  | | |  | | |    | . ` | | || | |_ |  __  |  | |   
 | |__| |___) | . \   ____) | |__| | |__| | |____| |\  |_| || |__| | |  | |  | |   
  \____/|____/|_|\_\ |_____/ \____/ \____/|______|_| \_|_____\_____|_|  |_|  |_|  
)");

            rawPrint("+-----------------------------------------------------------+");
            rawPrint("|                 WELCOME TO J3K SOULNIGHT                  |");
            rawPrint("+-----------------------------------------------------------+\n");
            std::cout << "1. Enter Dungeon\n2. About\n3. Upgrade\n4. Exit\n" RESET_COLOR;
            rawPrint("+-----------------------------------------------------------+");
        }

        // Shows about/game info screen
        void renderAbout() {
            clear();
            drawBox("About", {YELLOW_COLOR "  The Battle of Souls  ",
                              BLUE_COLOR "  Created with love in C++  ",
                              MAGENTA_COLOR "  Epic RPG experience  ",
                              WHITE_COLOR "  Version 1.0.0  "});
        }

        // Renders dungeon intro screen
        void renderDungeonIntro() {
            clear();
            drawBox("Dungeon Entrance",
                    {RED_COLOR "Behold, the entrance to the Abyss!    ",
                     "Some game data is stored locally,",
                     "and cannot be recovered if the game is deleted.",
                     "Proceed with caution, hero!"});
        }

        // Shows the combat screen info with enhanced visuals
        void renderCombatScene(const std::string &playerName, int playerHP,
                               const std::string &enemyName, int enemyHP) {
            clear();
            rawPrint(YELLOW_COLOR "====== ENTER DUNGEON! ======" RESET_COLOR);
            rawPrint(CYAN_COLOR "Your opponent: " + enemyName + "!" RESET_COLOR);
            rawPrint(GREEN_COLOR + playerName + " HP: " + std::to_string(playerHP) +
                     RESET_COLOR);
            rawPrint(RED_COLOR + enemyName + " HP: " + std::to_string(enemyHP) +
                     RESET_COLOR);
            rawPrint("\n" YELLOW_COLOR "===============================" RESET_COLOR);
        }

        // Shows the upgrade screen with cool, thematic style
        void renderUpgradeScreen() {
            clear();
            rawPrint(YELLOW_COLOR
                     "==================== POWER UP ====================" RESET_COLOR);
            rawPrint(MAGENTA_COLOR "Choose your power path wisely, hero...\n");
            rawPrint(BLUE_COLOR "1. Increase Attack Power");
            rawPrint(GREEN_COLOR "2. Enhance Health");
            rawPrint(RED_COLOR "3. Return to Main Menu");
            rawPrint(WHITE_COLOR "===============================================");
        }

    private:
        // Helper to center text inside the box
        std::string centerText(const std::string &text, int width) {
            int space = width - text.size();
            int left  = space / 2;
            int right = space - left;
            return std::string(left, ' ') + text + std::string(right, ' ');
        }
};

#endif
