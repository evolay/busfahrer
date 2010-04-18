#include <iostream>
#include "Crawler.h"
#include <fstream>
#include "time.h"

int main(char** argv, char** argc)
{	
	time_t seconds;
	seconds = time(NULL);	
	Crawler* _crawler = new Crawler( "http://betty.multimediatechnology.at", 100 );

	int abort = 0;
	while( !_crawler->requestsFinished())
	{
		printf ("%f requests per second\n", (float)_crawler->getRequestCount() / (float)(time(NULL) - seconds));
	}

	//getting map & iterator
	std::map< std::string, ParseResult>* _map = _crawler->getResultMap();
	std::map< std::string, ParseResult>::iterator _iter = _map->begin();
	
	//writing to logfile
	std::ofstream file( "Log.txt", std::ios::out );
	int _brokenLinks = 0;

	for( ; _iter != _map->end(); _iter++)
	{
		if( (*_iter).second._broken )
		{
			file << "Found broken URL: " << (*_iter).first << "\n";
			file << "ParentUrl: " << (*_iter).second._parentUrl << "\n\n";
			++_brokenLinks;
		}
	}

	file << "Searched URL \"" << _crawler->getDomainName() << "\" for broken links...\n";
	file << "Found\n" << _brokenLinks << " broken Links\n";
	file << ( _map->size() - _brokenLinks ) << " good links\n";
	file << "from " << _map->size() << " links to search\n";
	file.close();

	std::cout << std::endl << "End" << std::endl;

	delete _crawler;
	return 0;
}


