//in the name of God

//usage: Error(string description, string file_name, int line_num)

#ifndef __Error__
#define __Error__ 

class Error
{
public:
	Error(std::string d = "", std::string f = "", int l = 0);

	virtual std::string what(){return this->description;}
	virtual std::string info();
	void print();

	std::string get_line_num();
	std::string get_file_name();
	std::string get_description();

protected: 
	std::string description;
	std::string file_name;
	int  line_num;
};

#endif


