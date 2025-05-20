#include "Item.hpp"

class slotItem {
    private : 
        Item *item; // The item in the slot
        int quantity; // The quantity of the item in the slot
    public :
        slotItem(Item *item, int quantity) : item(item), quantity(quantity) {}
        slotItem() : item(nullptr), quantity(0) {}
        ~slotItem() = default;
        
        Item* getItem() const { return item; }
        int getQuantity() const { return quantity; }
        
        void setItem(Item *item) { this->item = item; }
        std::string getItemName() const { return item ? item->getName() : ""; }
        void setQuantity(int quantity) { this->quantity = quantity; }
        void addQuantity(int quantity) { this->quantity += quantity; }
        void removeQuantity(int quantity) { this->quantity -= quantity; }

        bool isEmpty() const { return item == nullptr; }
};