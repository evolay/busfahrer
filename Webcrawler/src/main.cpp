#include <iostream>
#include "Crawler.h"
#include <fstream>
#include <sstream>
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

	std::stringstream _oss;
	_oss << _brokenLinks;
	file << "Searched URL \"" << _crawler->getDomainName() << "\" for broken links...\n";
	file << "Found\n" << _oss.str() << " broken Links\n"; _oss.clear();
	_oss << ( _map->size() - _brokenLinks );
	file << _oss.str() << " good links\n"; _oss.clear();
	_oss << _map->size();
	file << "from " << _oss.str() << " links to search\n";
	file.close();

	std::cout << std::endl << "End" << std::endl;

	int pause;
	std::cin >> pause;
	
	delete _crawler;
	return 0;
}


