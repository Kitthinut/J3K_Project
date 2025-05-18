#include<Iventory.hpp>

void Inventory::addItem(Item *item, int quantity) {
    for (auto& slot : _itemsList) {
        if(slot.getItem() != nullptr && slot.getItem()->getName() == item->getName()) {
            slot.addQuantity(quantity);
            std::cout << "Added " << quantity << " " << item->getName() << "(s) to inventory now have " << slot.getQuantity() << "."<< std::endl;
            return;
        }
    }
    if (_itemsList.size() < _maxSize) {
        _itemsList.push_back(slotItem(item, quantity));
        std::cout << "Added " << quantity << " " << item->getName() << "(s) to inventory." << std::endl;
    } else {
        std::cout << "Inventory is full!" << std::endl;
    }
}


void Inventory::removeItem(int index, int quantity) {
    if (index < 0 || index >= _itemsList.size()) {
        std::cout << "Invalid index!" << std::endl;
        return;
    }
    if (_itemsList[index].getQuantity() < quantity) {
        std::cout << "Not enough items in the slot!" << std::endl;
        return;
    }
    _itemsList[index].removeQuantity(quantity);
    if (_itemsList[index].getQuantity() == 0) {
        deleteItem(index);
    }
}

void Inventory::deleteItem(int index) {
    if (index < 0 || index >= _itemsList.size()) {
        std::cout << "Invalid index!" << std::endl;
        return;
    }
    _itemsList.erase(_itemsList.begin() + index);
}

void Inventory::useItem(int index, Entity& entity) {
    if (index < 0 || index >= _itemsList.size()) {
        std::cout << "Invalid index!" << std::endl;
        return;
    }
    if (_itemsList[index].isEmpty()) {
        std::cout << "No item in the slot!" << std::endl;
        return;
    }
    _itemsList[index].getItem()->use(entity);
    removeItem(index, 1);
}