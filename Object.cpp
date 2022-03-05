#include <random>
#include <iostream>
#include "Object.h"
std::random_device Object::seed;
std::default_random_engine Object::engine(seed());

bool Object::nameOnly{ false };

Object::Object(Type name, int strength, int health, int level) : name{ name }, strength{ strength }, health{ health }, level{ level }
{ }

bool Object::isDead() const
{
	return health <= 0;
}

Object::Type Object::getName() const
{
	return name;
}

int Object::getLevel() const
{
	return level;
}

int Object::getHealth() const
{
	return health;
}

std::ostream& operator<<(std::ostream& o, const Object& src)
{
    src.print( o );
	return o;
}

void Object::print(std::ostream& o) const
{
    switch (getName())
    {
        case Object::Type::player:
            std::cout << "Player";
            break;
        case Object::Type::slime:
            std::cout << "Slime";
            break;
        case Object::Type::orc:
            std::cout << "Orc";
            break;
        case Object::Type::sprite:
            std::cout << "Sprite";
            break;
        case Object::Type::dragon:
            std::cout << "Dragon";
            break;
        case Type::numTypes:
            break;
    }
}

int Object::damageDone( int modification ) const
{
    int potentialDamage{ strength + modification };
    std::normal_distribution<double> damageDealt(potentialDamage, 2.0);
    std::cout << *this << " deals ";
    return std::max(1, (int)damageDealt(engine));
}

int Object::damageTaken(int damageDone, int AC)
{
    std::normal_distribution<double> defense(AC, 1.0 / level);
    damageDone = std::max(0, damageDone - (int)defense(engine));
    std::cout << damageDone << " damage to ";
    nameOnly = true;
    std::cout << *this << "!!!" << std::endl;
    return health -= damageDone;
}