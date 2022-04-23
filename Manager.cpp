//in the name of God

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "Manager.hpp"
#include "Error.hpp"
#include "Player.hpp"

using namespace std;

#define PLAYER_NOT_FOUND NULL
#define WINNERS_MONEY 2700
#define LOOSERS_MONEY 2400

bool players_priority(Player* a, Player* b)
{
	if (a->kills != b->kills)
		return (a->kills > b->kills);
	else if (a->deaths != b->deaths)
		return (a->deaths < b->deaths);
	else
		return (a->name < b->name);
}

Manager::Manager()
	:
	start(false)
{
}

Manager::~Manager()
{
	for (auto player : players)
		delete player;
}


void Manager::add_user()
{
	string user_name;
	string team;
	cin >> user_name >> team;
	Player *new_player = new Player(user_name, team);
	players.push_back(new_player);
	shop.sell(new_player, "knife");
	cout << "ok" << endl;
}

void Manager::handle_round()
{
	int num_of_commands;
	string command;
	cin >> num_of_commands;

	for (int i = 0; i < num_of_commands; ++i)
	{
		cin >> command;
		try{handle_round_command(command);}
		catch(Error &err){cout << err.what() << endl;}
	}
	finish_round();
}

void Manager::finish_round()
{
	string winner_group = find_winner_group();

	this->start = false;
	shop.weapon_trade_time = true;

	for (auto player :players)
	{
		if (player->is_winner(winner_group))
			player->add_money(WINNERS_MONEY);
		else
			player->add_money(LOOSERS_MONEY);
		player->erase_weapons();
		shop.sell(player,"knife");
		player->restore_health();
	}
	cout << winner_group << " won" << endl;
}

string Manager::find_winner_group()
{
	int alive_terrorists_num = 0, alive_counter_terrorists_num = 0;
	for (auto player :players)
	{
		if (player->is_terrorist() && !player->is_dead() && player->can_attack)//add afk here if necessary
			alive_terrorists_num ++;
		else if (!player->is_terrorist() && !player->is_dead() && player->can_attack)//add afk here if necessary
			alive_counter_terrorists_num ++;
	}
	if (alive_counter_terrorists_num == 0)
		return "terrorist";
	return "counter-terrorist";
}

void Manager::handle_round_command(string command)
{
	if (command == "start")
		start_command();
	else if (command == "get-money")
		get_money_command();
	else if (command == "get-health")
		get_health_command();
	else if (command == "go-afk")
		go_afk_command();
	else if (command == "go-atk")
		go_atk_command();
	else if (command == "shoot")
		shoot_command();
	else if (command == "buy")
		buy_command();
	else if (command == "score-board")
		print_score_board();
	else
		cout << "unrecognized command in this round" << endl;
}

void Manager::start_command()
{
	this->start = true;
	shop.weapon_trade_time = false;
	cout << "fight!" << endl;
}

void Manager::get_money_command()
{
	string user_name;
	cin >> user_name;
	cout << find_player(user_name)->get_money() << endl;
}

void Manager::get_health_command()
{
	string user_name;
	cin >> user_name;
	cout << find_player(user_name)->get_health() << endl;

}

void Manager::go_afk_command()
{
	string user_name;
	cin >> user_name;
	find_player(user_name)->can_attack = false;
	cout << "ok" << endl;
}

void Manager::go_atk_command()
{
	string user_name;
	cin >> user_name;
	find_player(user_name)->can_attack = true;
	cout << "ok" << endl;
}

void Manager::shoot_command()
{
	string attacker_name, attacked_name, weapon_type;
	cin >> attacker_name >> attacked_name >> weapon_type;
	auto attacker = find_player(attacker_name);
	auto attacked = find_player(attacked_name);

	if (attacker == PLAYER_NOT_FOUND || attacked == PLAYER_NOT_FOUND ||
		!attacker->can_attack || !attacked->can_attack)
		throw Error("user not available", "Manager.cpp");

	else if (attacker->is_dead())
		throw Error("attacker is dead", "Manager.cpp");

	else if (attacked->is_dead())
		throw Error("attacked is dead", "Manager.cpp");

	else if (this->start == false)
		throw Error("The game hasn't started yet", "Manager.cpp");

	attacker->shoot(attacked, weapon_type);
	cout << "nice shot" << endl;
}

void Manager::buy_command()
{
	string user_name, weapon_type;
	cin >> user_name >> weapon_type;
	auto player = find_player(user_name);

	if (player == PLAYER_NOT_FOUND || !player->can_attack)
		throw Error("user not available", "Manager.cpp");

	shop.sell(player, weapon_type);
	cout << "weapon bought successfully" << endl;
}

void Manager::print_score_board()
{
	sort(players.begin(), players.end(), players_priority);
	cout << "counter-terrorist players:" << endl;
	for (auto counter_terrorist : players)
		if (!counter_terrorist->is_terrorist())
			counter_terrorist->print_your_status();

	cout << "terrorist players:" << endl;
	for (auto terrorist : players)
		if (terrorist->is_terrorist())
			terrorist->print_your_status();
}

Player* Manager::find_player(string name)
{
	for (auto player : players)
		if (player->is_your_name(name))
			return player;
	return PLAYER_NOT_FOUND;
}

