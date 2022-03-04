/*  OBJECTIVES:

    Object.h gets four purely virtual methods:
        1)  virtual int attack() const = 0;                                                                 -   .
            a)  Player: calls damageDone passing in bonusValue for sword or 0.
                returns value returned by damageDone
            b)  Monster: calls damageDone(0) and returns the returned value.
        2)  virtual void defend(int damage) = 0;                                                            -   .
            a)  Player: calculates AC, passes along damage and AC to damageTaken
            b)  Monster: calls damageTaken(damage, AC);
        3)  virtual void update(Player& player, std::vector<Monster>& monsters) = 0;                        -   .
            a)  Player: lines 44-60 from Goal.6.cpp goes here. The part dealing with attacking vs healing.
                Also playerAttack function is no longer a function, just put the code in the ‘a’ case.
            b)  Monster: The part inside the for_each goes here. for_each now just calls the update…
        4)  virtual void print(std::ostream& o) const;                                                      -   .
            a)  the overload of the << operator will call this to make sure it the proper one is called!

    And two protected methods:
        1)  int damageDone(int modification) const;                                                         -   .
            a)  does the common bits for attack. Monsters pass in 0, player based on sword
        2)  int damageTaken(int damageDone, int AC);                                                        -   .
            a)  does the common bits for defend.

*/
#ifndef OBJECT_H
#define OBJECT_H

    #include <map>
    #include <random>


    class Object
    {
    public:
        static std::random_device seed;
        static std::default_random_engine engine;
        enum class Type { player, slime, orc, sprite, dragon, numTypes };

        Object() {}
        Object(Type name, int strength, int health, int level);

        virtual int attack() const = 0;
        virtual void defend(int damage) = 0;
        virtual void update(Player& player, std::vector<Monster>& monsters) = 0;
        virtual void print(std::ostream& o) const;

//        virtual void print(std::ostream& o) const
//        {
//
//        }

        bool isDead();
        Type getName() const;
        int getLevel() const;
        int getHealth() const;

    protected:
        Type name{ Type::numTypes };
        int strength{ 0 };
        int health{ 0 };
        int level{ 0 };

        int damageDone(int modification) const;
        int damageTaken(int damageDone, int AC);

//        int damageDone(int modification) const
//        {
//            return 0;
//        }
//

//        int damageTaken(int damageDone, int AC)
//        {
//            return 0;
//        }

    };

    std::ostream& operator<< (std::ostream& o, const Object& src);

#endif // !OBJECT_H

