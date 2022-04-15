//in the name of God

#include <iostream>
#include <vector>
#include <string>

#include "Player.hpp"
#include "Shop.hpp"
#include "Error.hpp"

using namespace std;

#define MAX_HEALTH 100
#define START_MONEY 1000
#define MAX_SAVED_MONEY 10000

#define DONT_HAVE_THIS_WEAPON NULL

Player::Player(string user_name, string team)
	:
	name(user_name),
	team(team),
	health(MAX_HEALTH),
	money(START_MONEY),
	can_attack(true),
	kills(0),
	deaths(0)
{
}

void Player::print_your_status()
{
	cout << this->name << " ";
	cout << this->kills << " ";
	cout << this->deaths << " ";
	cout << endl;
}

void Player::add_money(int amount)
{
	this->money += amount;
	if(this->money > MAX_SAVED_MONEY)
		this->money = MAX_SAVED_MONEY;
}

bool Player::is_dead()
{
	return (health == 0) ? true : false;
}

void Player:: add_health(int amount)
{
	this->health += amount;
	if(this->health < 0)
		this->health = 0;
}

void Player::restore_health()
{
	this->health = MAX_HEALTH;
}


bool Player::is_your_name(string name)
{
	return (this->name == name) ? true : false;
}

bool Player::is_terrorist()
{
	return (this->team == "terrorist") ? true : false;
}

bool Player::is_winner(std::string winner_group)
{
	if ((winner_group == "terrorist" && is_terrorist()) ||
	    (winner_group == "counter-terrorist" && !is_terrorist()))
		return true;
	return false;
}

bool Player::has_this_weapon(std::string weapon_name)
{
	return (find_weapon(weapon_name) == DONT_HAVE_THIS_WEAPON) ? false : true;
}

Weapon* Player::find_weapon(string weapon_name)
{
	for (int i = 0; i < weapons.size(); ++i)
		if (weapons[i].name == weapon_name)
			return &(weapons[i]);
	return DONT_HAVE_THIS_WEAPON;
}

void Player::add_weapon(Weapon weapon)
{
	weapons.push_back(weapon);
}

void Player::shoot(Player* attacked, string weapon_name)
{
	if (!this->has_this_weapon(weapon_name))
		throw Error("attacker doesn't have this gun", "Player.cpp");

	else if (this->is_terrorist() == attacked->is_terrorist())
		throw Error("you can't shoot this player");

	auto chosen_weapon = find_weapon(weapon_name);

	attacked->add_health(-chosen_weapon->health_reduce);

	if (attacked->is_dead())
	{
		this->add_money(chosen_weapon->moeny_when_kill);
		this->kills ++;
		attacked->deaths ++;
	}
}

void Player::erase_weapons()
{
	this->weapons.clear();
}





