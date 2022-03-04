//
//  main.cpp
//
//  Project: UALR - Programming 2 - Spring 22 - Power Play 7
//  Created by: Mark McCorkle on 20220304
//  Based on: Code Provided by Sean Orme
//  IDE: CLion 2021.2.3     - VERIFIED WORKING
//  IDE: XCode              - VERIFIED/UNVERIFIED
//  IDE: Visual Studio 2022 - VERIFIED/UNVERIFIED
//  IDE: Linux via g++      - VERIFIED/UNVERIFIED
//
/*  OBJECTIVES:

    Object.h gets four purely virtual methods:
        1)  virtual int attack() const = 0;                                                                 -   Complete
            a)  Player: calls damageDone passing in bonusValue for sword or 0. returns value returned by damageDone
            b)  Monster: calls damageDone(0) and returns the returned value.
        2)  virtual void defend(int damage) = 0;                                                            -   Complete
            a)  Player: calculates AC, passes along damage and AC to damageTaken
            b)  Monster: calls damageTaken(damage, AC);
        3)  virtual void update(Player& player, std::vector<Monster>& monsters) = 0;                        -   Complete
            a)  Player: lines 44-60 from Goal.6.cpp goes here. The part dealing with attacking vs healing.
                Also playerAttack function is no longer a function, just put the code in the ‘a’ case.
            b)  Monster: The part inside the for_each goes here. for_each now just calls the update…
        4)  virtual void print(std::ostream& o) const;                                                      -   Complete
            a)  the overload of the << operator will call this to make sure it the proper one is called!

    And two protected methods:
        1)  int damageDone(int modification) const;                                                         -   Complete
            a)  does the common bits for attack. Monsters pass in 0, player based on sword
        2)  int damageTaken(int damageDone, int AC);                                                        -   Complete
            a)  does the common bits for defend.

*/
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>
#include <map>

#include "Item.h"
#include "Object.h"
#include "Player.h"
#include "Monster.h"

std::vector<Monster> createMonsters(const Player& player);

void displayBattle(const Player& player, const std::vector<Monster>& monsters);
void bringOutYourDead(std::vector<Monster>& monsters);


int main()
{
    Player player;
    std::vector<Monster> monsters;
    while (!player.isDead())
    {
        player.levelUp();
        monsters = createMonsters(player);

        std::cout << monsters.size() << " monster(s) approaches!!" << std::endl;
        system("pause");
        system("cls");

        while (!player.isDead() && monsters.size() > 0)
        {

            displayBattle(player, monsters);

            player.update(player, monsters);

            bringOutYourDead(monsters);

            std::cout << std::endl;
            std::for_each(monsters.begin(), monsters.end(), [&](Monster& monster)
            {
                monster.update(player, monsters);
            });

            system("PAUSE");
            system("CLS");
        }
    }

    if (player.isDead())
    {
        std::cout << "You Have Died" << std::endl;
    }
    if (player.isDead() && monsters.size() == 0)
    {
        std::cout << "BUT" << std::endl;
    }
    if (monsters.size() == 0)
    {
        std::cout << "You have killed the monsters!!!" << std::endl;
    }
    system("PAUSE");

}



void displayBattle(const Player& player, const std::vector<Monster>& monsters)
{
    Object::nameOnly = false; //TODO:: get rid of this and just dot he full cout.
    std::cout << player << std::endl;
    std::cout << std::endl << "  Monsters: " << std::endl;
    {
        int i{ 1 };
        std::for_each(monsters.begin(), monsters.end(), [&](const Monster& monster)
        {
            std::cout << "   " << i << ". " << monster << std::endl;

            i++;
        });
    }
}

std::vector<Monster> createMonsters(const Player& player)
{
    std::normal_distribution<double> randomNumMonsters((double)player.getLevel(), player.getLevel() / 2.0);
    std::vector<Monster> monsters(std::max(1, (int)randomNumMonsters(Object::engine)));
    std::generate(monsters.begin(), monsters.end(), [&]()
    {
        return Monster(player);
    });
    return monsters;
}

void bringOutYourDead(std::vector<Monster>& monsters)
{
    Object::nameOnly = true;
    monsters.erase(
            std::remove_if(monsters.begin(), monsters.end(),
                           [](Object& monster)
                           {
                               if (monster.isDead())
                               {

                                   std::cout << monster << " has died!!!" << std::endl << std::endl;
                                   return true;
                               }
                               return false;
                           }),
            monsters.end());

}
