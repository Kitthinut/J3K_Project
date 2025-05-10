class Player{
    public: 
        int max_hp;
        int max_mana;
        int hp;
        int mana;
};

class Skill{
public:
    int id;
    int level;
    Skill(int id, int level) : id(id), level(level) {}
    void useSkill(Player& player) {
        // Implement skill usage logic here    
    }
};


class Item{
    protected:
        int hpRestore;
        int manaRestore;
    public:
    virtual void use(Player& player) {
        // Implement potion usage logic here
    }
};

class Potion : public Item{
    public:
        void use(Player& player) override {
            // Implement potion usage logic here
            // For example, restore player's HP and mana
            player.hp += hpRestore;
            player.mana += manaRestore;
        }
};

class Food : public Item{
    public:
        void use(Player& player) override {
            // Implement food usage logic here
            // For example, restore player's HP and mana
            player.hp += hpRestore;
            player.mana += manaRestore;
        }
};
