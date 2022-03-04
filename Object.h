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


	bool isDead();
	Type getName() const;
	int getLevel() const;
	int getHealth() const;

protected:
	Type name{ Type::numTypes };
	int strength{ 0 };
	int health{ 0 };
	int level{ 0 };

};

std::ostream& operator<< (std::ostream& o, const Object& src);
#endif // !OBJECT_H

