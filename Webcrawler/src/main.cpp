#include <iostream>
#include "TrudyTheCrawler.h"
#include <stdio.h>
#include "curl/curl.h"
#include <string>
#include "HTTP.h"

using namespace TrudyTheCrawler;

int main( char** argv, char** argc)
{	
/* EXAMPLE
 	HTTP httptest;
	httptest.get("http://klamm.de");
	std::cout << httptest.getOutput();
*/
	TrudyTheCrawler::ThreadPool _thradpool( 10 );
	_thradpool.start();
	
	while(true)
	{
	}
	return 0;
	
}
