#include <iostream>
#include "TrudyTheCrawler.h"
#include "HTMLParser.h"

using namespace std;

/*int main( char** argv, char** argc)
{
	
	TrudyTheCrawler::ThreadPool _thradpool( 10 );
	_thradpool.start();
	
	while(true)
	{
	}
	return 0;

}*/

int main(char** argv, char** argc)
{
	HTMLParser var;
	//var.parseHTML("<html><a href=\"http://www.google.de\">google</a><a href='test.html'>asfd</a></html>");
	var.parse();
	cout << "asdjf";
}