#include <iostream>
#include <string>

#include "Error.hpp"

using namespace std;

Error::Error(string d, string f, int l)
	:
	description(d),
	file_name(f),
	line_num(l)
{
	
}

string Error::info()
{
	return get_line_num() + get_file_name() + get_description();
}

void Error::print()
{
	cerr << this->info() << endl;
}

string Error::get_line_num()
{
	if (this->line_num == 0)
		return " ";
	string line = " -Line:";
	return line + to_string(this->line_num);
}

string Error::get_file_name()
{
	if (this->file_name == "")
		return " ";
	string file = " -File:";
	return file + this->file_name;
}

string Error::get_description()
{
	if (this->description == "")
		return "***Error occured with no description*** ";
	string error = " -what:";
	return error + this->description;
}