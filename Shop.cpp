//in the name of God

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <memory>

#include "Shop.hpp"
#include "Error.hpp"
#include "Player.hpp"

using namespace std;

Shop::Shop()
	:
	weapon_trade_time(true)
{
	weapons = 
			{
				{"heavy", 3000, 45, 100},
				{"pistol", 400, 20, 200},
				{"knife", 0, 35, 500}
			};

}

Weapon Shop::find_weapon(string weapon_name)
{
	for (auto weapon : weapons)
		if (weapon.name == weapon_name)
			return weapon;
	throw Error("weapon not available", "Shop.cpp");
}

void Shop::sell(Player* player, string weapon_name)
{
	if (weapon_trade_time == false)
		throw Error("you can't buy weapons anymore", "Shop.cpp");
		
	auto weapon = find_weapon(weapon_name);

	if (player->has_this_weapon(weapon_name))
		throw Error("you already have this weapon", "Shop.cpp");
		
	else if (player->get_money() < weapon.price)
		throw Error("insufficient money", "Shop.cpp");

	player->add_money(-weapon.price);
	player->add_weapon(weapon);
}
