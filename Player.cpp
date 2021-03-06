#include <algorithm>
#include <random>
#include <iostream>
#include "Player.h"
#include "Monster.h"

Player::Player() :Object(Object::Type::player, 0, 1, 0)
{ }

void Player::levelUp()
{
	level++;
	std::normal_distribution<double> randomHealth(20.0 + level * 5, 5.0);
	health += std::max(1, (int)randomHealth(engine));

	std::normal_distribution<double> randomStrength(3.0 + level, 1.0);
	strength += std::max(1, (int)randomStrength(engine));
	SP += std::max(1, (int)randomStrength(engine));

	//grab new item.
	std::uniform_int_distribution<int> randomItem(0, (int)Item::Type::numTypes - 1);
	std::normal_distribution<double> randomBonus((double)level, (double)level / 2);
	Item found{ (Item::Type)randomItem(engine), std::max(1, (int)randomBonus(engine)) };

	std::cout << "You found a " << found << "!!!!" << std::endl;
	if (
		auto haveOne{ inventory.find(found.getClassification()) };
		haveOne == inventory.end()
		|| inventory[found.getClassification()] < found
		)
	{
		std::cout << "You keep the shiny new toy!" << std::endl;
		inventory[found.getClassification()] = found;
	}
	else
	{
		std::cout << "You toss aside the ugly old thing!" << std::endl;
	}
}

int Player::getLevel() const
{
	return level;
}

int Player::getSP() const
{
	return SP;
}

std::map<Item::Type, Item> Player::getInventory() const
{
	return inventory;
}

void Player::heal()
{
    nameOnly = true;
	if (SP >= 2)
	{
		std::normal_distribution<double> randomHeal(strength, 3.0);
		int  amountHealed{ std::max(1, (int)randomHeal(engine)) };

		SP -= 2;
		std::cout << *this << " is healed by " << amountHealed << "hp!" << std::endl;
		health += amountHealed;
	}
	else
	{
		std::cout << "Not enough SP!!!" << std::endl;
	}
}

std::ostream& operator<<(std::ostream& o, const std::map<Item::Type, Item>& src)
{
	std::for_each(src.begin(), src.end(), [&](std::pair<Item::Type, Item> item)
		{
			o << "  " << item.second << std::endl;
		});
	return o;
}

// Loop through the players inventory to see if they have a sword in hand
// If they do:
//     pass its bonus value on to inflict the damage onto the monster
// else
//     pass in zero for the bonus value
int Player::attack() const
{
    if( auto inventoryItr{ inventory.find( Item::Type::sword ) }; inventoryItr != inventory.end() )
        return damageDone( inventoryItr->second.getBonusValue() );
    else
        return damageDone( 0 );
}

// Defend calculates the amount of defense the player has based on its inventory
// AC is the combination of the armors bonusValue and shields bonusValue
//
// Find if the player has armor or a shield
// Then use the bonus values from each and add to the AC value
// Than pass the amount of damage and the AC and pass it to damageTaken
void Player::defend( int damage )
{
    // Calculate AC:
    int AC{ };
    if( auto inventoryItr{ inventory.find( Item::Type::armor ) }; inventoryItr != inventory.end() )
        AC += inventoryItr->second;
    if( auto inventoryItr{ inventory.find( Item::Type::shield ) }; inventoryItr != inventory.end() )
        AC += inventoryItr->second;
    damageTaken( damage, AC );
}

// The Player update virtual member function will allow you to select the monster to attack or allow you to heal.
void Player::update(Player& player, std::vector<Monster>& monsters)
{
    std::cout << "What do you do? (a)ttack (h)eal ";
    char command{ 'x' };
    std::cin >> command;
    switch (command)
    {
        case 'a':
        {
            std::cout << "Which Monster: ";
            int monsterNum{ 0 };
            std::cin >> monsterNum;
            if (monsterNum > 0 && monsterNum <= static_cast<int>(monsters.size()))
                monsters.at( monsterNum - 1 ).defend( player.attack() );
            break;
        }
        case 'h':
            heal();
            break;
        default:
            std::cout << "please enter a or h" << std::endl;
            break;
    }
}

void Player::print(std::ostream &o) const
{
    if(nameOnly)
        Object::print(o);
    else
    {
        o << "L:" << getLevel() << " ";
        Object::print(o);
        o << " h:" << getHealth() << ", SP:" << getSP() << std::endl;
        o << inventory;
    }
}