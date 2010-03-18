#include <iostream>
#include "TrudyTheCrawler.h"


int main( char** argv, char** argc)
{
	
	TrudyTheCrawler::ThreadPool _thradpool( 10 );
	_thradpool.start();
	
	int bla;
	std::cin >> bla;
	return 0;

}
