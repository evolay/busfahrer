#include <iostream>
#include "Crawler.h"
#include <fstream>


int main(char** argv, char** argc)
{	
	Crawler* _crawler = new Crawler( "http://webreload.de", 60 );
	
	int pause = 1;
	do{
		std::cin >> pause;
	}
	while( pause != 0 );

	std::ofstream file( "Log.txt", std::ios::out );
	
	std::map< std::string, ParseResult>* _map = _crawler->getResultMap();
	std::map< std::string, ParseResult>::iterator _iter = _map->begin();
	
	for( ; _iter != _map->end(); _iter++)
	{
		file << (*_iter).first << "\n";
		file << "Broken: " << (*_iter).second._broken << "\n";
		file << "ParentUrl: " << (*_iter).second._parentUrl << "\n\n";
	}

	file.close();
	std::cout << std::endl << "End" << std::endl;

	std::cin >> pause;
	
	delete _crawler;
	return 0;
}


