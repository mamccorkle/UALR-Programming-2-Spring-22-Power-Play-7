#ifndef MONSTER_H
#define MONSTER_H

    #include "Object.h"

    class Player;
    class Monster: public Object
    {
    public:
        Monster() {};
        Monster(const Player& player);

//        int damage() const;
//        void defense(int damage);

        virtual int attack() const override;
        virtual void defend( int damage ) override;
        virtual void update(Player& player, std::vector<Monster>& monsters) override;

        virtual void print(std::ostream& o) const override;

    private:
        int AC{ 0 };

    };

#endif // !MONSTER_H