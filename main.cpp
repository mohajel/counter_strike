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

#include "Manager.hpp"
#include "Error.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
	int rounds_num, commands_num;
	cin >> rounds_num;

	string command;
	Manager manager;

	try
	{
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
	}
	catch(Error &err)
	{
		err.print();
		exit(EXIT_FAILURE);
	}
	
	// while(cin >> command)
	// {
	// 	if (command == "add-user")
	// 		manager.add_user();
	// 	else if (command == "round")
	// 		manager.handle_round();
	// 	else if (command == "score-board")
	// 		manager.print_score_board();
	// 	else
	// 		cout << "unrecognized command :" << command << endl;
	// }
	return 0;
}	