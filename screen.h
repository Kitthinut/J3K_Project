#ifndef SCREEN_H
#define SCREEN_H

#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>

class Screen
{
private:
    std::vector<std::string> buffer;
    const int width = 50;

    std::string repeatChar(char c, int times)
    {
        return std::string(times, c);
    }

    std::string centerText(const std::string &text, int w)
    {
        int space = w - text.size();
        int left = space / 2;
        int right = space - left;
        return std::string(left, ' ') + text + std::string(right, ' ');
    }

    std::string padText(const std::string &text, int w)
    {
        if (text.size() >= w)
            return text.substr(0, w);
        return text + std::string(w - text.size(), ' ');
    }

public:
    void drawBox(const std::string &title, const std::vector<std::string> &lines)
    {
        buffer.push_back("┌" + repeatChar('-', width - 2) + "┐");
        buffer.push_back("│" + centerText(title, width - 2) + "│");
        buffer.push_back("├" + repeatChar('-', width - 2) + "┤");
        for (const auto &line : lines)
        {
            buffer.push_back("│" + padText(line, width - 2) + "│");
        }
        buffer.push_back("└" + repeatChar('-', width - 2) + "┘");
        buffer.push_back("");
    }

    void render(bool delay = false)
    {
        for (const auto &line : buffer)
        {
            std::cout << line << std::endl;
            if (delay)
                std::this_thread::sleep_for(std::chrono::milliseconds(30));
        }
    }

    void clear()
    {
        buffer.clear();
        std::cout << "[2J[1;1H";
        // [2J (also written as \033[2J) is the escape sequence for clearing the screen. It deletes everything on the terminal window.
        // [1;1H (also written as \033[1;1H) is the escape sequence to move the cursor to the top-left corner of the terminal (row 1, column 1).
    }

    void print(const std::string &text, bool newline = true)
    {
        if (newline)
            std::cout << text << std::endl;
        else
            std::cout << text;
    }

    void rawPrint(const std::string &art)
    {
        std::cout << art << std::endl;
    }
    
};

#endif
