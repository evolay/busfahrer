#include <iostream>
#include "TrudyTheCrawler.h"


int main( char** argv, char** argc)
{
	
	TrudyTheCrawler::ThreadPool _thradpool( 10 );
	_thradpool.start();
	
	while(true)
	{
	}
	return 0;

}
