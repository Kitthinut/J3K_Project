#pragma once

#include "Entity.hpp"

class Item {
    private:
        std::string _name;  // The name of the item
        int         _price; // The price of the item
        int         healHP;
        int         healMana;
        int         quantity; // The quantity of the item
    public:
        Item(std::string name, int price, int healHP, int healMana)
            : _name(name), _price(price), healHP(healHP), healMana(healMana) {}

        Item(std::string name, int price): Item(name, price, 0, 0) {}

        ~Item() = default;

        std::string getName() const { return _name; }

        int getPrice() const { return _price; }

        int getHealHP() const { return healHP; }

        int getHealMana() const { return healMana; }

        void use(Entity &entity) {
            int healedHP   = entity.getCurrentHP() + healHP;
            int healedMana = entity.getCurrentMana() + healMana;
            entity.setCurrentHP(healedHP > entity.getMaxHP() ? entity.getMaxHP()
                                                             : healedHP);
            entity.setCurrentMana(healedMana > entity.getMaxMana()
                                      ? entity.getMaxMana()
                                      : healedMana);
        }
};

class Potion: public Item {
    public:
        Potion(std::string name, int price, int healHP, int healMana)
            : Item(name, price, healHP, healMana) {}

        Potion(std::string name, int price): Item(name, price) {}

        ~Potion() = default;
};

class Food: public Item {
    public:
        Food(std::string name, int price, int healHP, int healMana)
            : Item(name, price, healHP, healMana) {}

        Food(std::string name, int price): Item(name, price) {}

        ~Food() = default;
};
