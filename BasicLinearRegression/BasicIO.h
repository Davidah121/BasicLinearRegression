#pragma once
#include <iostream>
#include <fstream>

class BasicIO
{
public:
	BasicIO(char* fileName);
	BasicIO(std::string fileName);

	~BasicIO();

	std::string getFilename();
	bool isEndOfFile();
	bool isOpen();
	char readByte();
	void close();
private:
	std::fstream file;
	std::string filename = "";
};

