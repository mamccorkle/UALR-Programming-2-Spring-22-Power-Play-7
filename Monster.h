#ifndef MONSTER_H
#define MONSTER_H
#include "Object.h"

class Player;
class Monster :
	public Object
{
public:
	Monster() {};
	Monster(const Player& player);
	int damage() const;
	void defense(int damage);
private:
	int AC{ 0 };

};

#endif // !MONSTER_H