#include <iostream>
#include "Crawler.h"
#include <fstream>
#include "time.h"

int main(char** argv, char** argc)
{	
	time_t seconds;
	seconds = time(NULL);	
	Crawler* _crawler = new Crawler( "http://webreload.de", 100 );

	while( !_crawler->requestsFinished())
	{
		printf ("%f requests per second\n", (float)_crawler->getRequestCount() / (float)(time(NULL) - seconds));
	}

	//getting map & iterator
	std::map< std::string, ParseResult>* _map = _crawler->getResultMap();
	std::map< std::string, ParseResult>::iterator _iter = _map->begin();
	
	//writing to logfile
	std::ofstream file( "Log.txt", std::ios::out );
	for( ; _iter != _map->end(); _iter++)
	{
		file << (*_iter).first << "\n";
		file << "Broken: " << (*_iter).second._broken << "\n";
		file << "ParentUrl: " << (*_iter).second._parentUrl << "\n\n";
	}
	file.close();

	std::cout << std::endl << "End" << std::endl;

	int pause;
	std::cin >> pause;
	
	delete _crawler;
	return 0;
}


