#pragma once

#include "SlotIem.hpp"

#include <vector>

class Inventory {
    private:
        int                   _maxSize;   // The maximum size of the inventory
        std::vector<slotItem> _itemsList; // The slots of the inventory
    public:
        Inventory() = default; // Default constructor

        Inventory(int maxSize): _maxSize(maxSize) {}

        ~Inventory() = default;

        int getMaxSize() const { return _maxSize; }

        slotItem getSlotItem(int index) const { return _itemsList[index]; }

        std::vector<slotItem> getItemsList() const { return _itemsList; }

        std::string getItmeName(int index) const {
            return _itemsList[index].getItem()->getName();
        }

        int getItemQuantity(int index) const {
            return _itemsList[index].getQuantity();
        }

        void setMaxSize(int maxSize) { _maxSize = maxSize; }

        void addItem(Item *item, int quantity);
        void removeItem(int index, int quantity);
        void deleteItem(int index);
        void useItem(int index, Entity &entity);
        void moveItemToNewInventory(int index, Inventory &newInventory);
        void moveItemToNewInventory(int index, Inventory &newInventory,
                                    int quantity);

        void showInventory() const {
            for (const auto &slot : _itemsList) {
                if (!slot.isEmpty()) {
                    std::cout << "Item: " << slot.getItemName()
                              << ", Quantity: " << slot.getQuantity() << std::endl;
                }
            }
        }
};