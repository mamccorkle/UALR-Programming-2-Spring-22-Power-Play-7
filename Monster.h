#ifndef MONSTER_H
#define MONSTER_H

    #include "Object.h"

    class Player;
    class Monster: public Object
    {
    public:
        Monster() = default;
        explicit Monster(const Player& player);

//        int damage() const;
//        void defense(int damage);

        int attack() const override;
        void defend( int damage ) override;
        void update(Player& player, std::vector<Monster>& monsters) override;

        void print(std::ostream& o) const override;

    private:
        int AC{ 0 };

    };

#endif // !MONSTER_H