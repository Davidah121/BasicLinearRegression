#include "BasicIO.h"



BasicIO::BasicIO(char * fileName)
{
	file = std::fstream(fileName, std::fstream::in);
	filename = fileName;
}

BasicIO::BasicIO(std::string fileName)
{
	file = std::fstream(fileName, std::fstream::in);
	filename = fileName;
}

BasicIO::~BasicIO()
{
	close();
}

bool BasicIO::isEndOfFile()
{
	return file.eof();
}

bool BasicIO::isOpen()
{
	return file.is_open();
}

char BasicIO::readByte()
{
	return file.get();
}

std::string BasicIO::getFilename()
{
	return filename;
}

void BasicIO::close()
{
	if(file.is_open())
		file.close();
}
