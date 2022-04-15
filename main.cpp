//in the name of God

#include <iostream>
#include <string>
#include "Manager.hpp"
#include "Error.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
	int rounds_num, commands_num;
	cin >> rounds_num;

	string command;
	Manager manager;
	
	while(cin >> command)
	{
		if (command == "add-user")
			manager.add_user();
		else if (command == "round")
			manager.handle_round();
		else if (command == "score-board")
			manager.print_score_board();
		else
			cout << "unrecognized command :" << command << endl;
	}
	return 0;
}	