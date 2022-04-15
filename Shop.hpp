#ifndef __Shop__
#define __Shop__

#include <iostream>
#include <vector>
#include <string>

class Player;

struct Weapon
{
	std::string name;
	int price;
	int health_reduce;
	int moeny_when_kill;	
};

class Shop
{
public:
	Shop();

	Weapon find_weapon(std::string weapon_name);
	void sell(Player* player, std::string weapon_name);
	bool weapon_trade_time;

private:
	std::vector<Weapon> weapons;	
};
#endif	
