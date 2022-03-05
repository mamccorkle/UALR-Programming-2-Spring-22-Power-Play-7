#ifndef PLAYER_H
#define PLAYER_H

    #include "Object.h"
    #include "Item.h"

    class Player: public Object
    {
    public:
        Player();

        void levelUp();

        int getLevel() const override;
        int getSP() const;
//        int damage() const;
        std::map<Item::Type, Item> getInventory() const;
//        void defense(int damage);
        void heal();

        int attack() const override;
        void defend( int damage ) override;
        void update(Player& player, std::vector<Monster>& monsters) override;

        void print(std::ostream& o) const override;

    private:
        std::map<Item::Type, Item> inventory;
        int SP{ 0 };
    };
    std::ostream& operator<< (std::ostream& o, const Player& src);
    std::ostream& operator<< (std::ostream& o, const std::map<Item::Type, Item>& src);

#endif // !PLAYER_H