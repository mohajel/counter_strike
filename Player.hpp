#ifndef __Player__
#define __Player__

#include "Shop.hpp"

class Player
{
public:
	Player(std::string user_name, std::string team);

	void print_your_status();

	void add_money(int amount);
	void add_health(int amount);
	void restore_health();

	bool is_dead();
	bool is_your_name(std::string name);
	bool is_terrorist();
	bool is_winner(std::string winner_group);

	bool has_this_weapon(std::string weapon_name);
	Weapon* find_weapon(std::string weapon_name);
	void add_weapon(Weapon weapon);

	void shoot(Player* attacked, std::string weapon_name);
	void erase_weapons();

	int get_money(){return this->money;}
	int get_health(){return this->health;}

	bool can_attack;
	std::string name;
	int kills;
	int deaths;
	
private:
	std::vector<Weapon> weapons;
	std::string team;
	int health;
	int money;
};
#endif	
