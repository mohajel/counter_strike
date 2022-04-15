#ifndef __Manager__
#define __Manager__

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <memory>

#include "Player.hpp"

class Manager
{
public:
	Manager();
	~Manager();

	Player* find_player(std::string name);
	std::string find_winner_group();

	void add_user();
	void print_score_board();

	void handle_round();
	void handle_round_command(std::string command);	
	void start_command();
	void get_money_command();
	void get_health_command();
	void go_afk_command();
	void go_atk_command();
	void shoot_command();
	void buy_command();

	void finish_round();



private:
	bool start;
	Shop shop;
	std::vector<Player *> players;
	
};
#endif	
