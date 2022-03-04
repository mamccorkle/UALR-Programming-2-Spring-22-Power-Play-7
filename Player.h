#ifndef PLAYER_H
#define PLAYER_H

    #include "Object.h"
    #include "Item.h"

    class Player: public Object
    {
    public:
        Player();

        void levelUp();

        int getLevel() const;
        int getSP() const;
//        int damage() const;
        std::map<Item::Type, Item> getInventory() const;
//        void defense(int damage);
        void heal();

        virtual int attack() const override;
        virtual void defend( int damage ) override;
        virtual void update(Player& player, std::vector<Monster>& monsters) override;

        virtual void print(std::ostream& o) const override;

    private:
        std::map<Item::Type, Item> inventory;
        int SP{ 0 };
    };
    std::ostream& operator<< (std::ostream& o, const Player& src);
    std::ostream& operator<< (std::ostream& o, const std::map<Item::Type, Item>& src);

#endif // !PLAYER_H