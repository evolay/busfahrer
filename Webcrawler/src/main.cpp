#include <iostream>
#include "TrudyTheCrawler.h"
#include "curl/curl.h"
#include <string>
#include "HTTP.h"
#include "HTMLParser.h"

using namespace std;
using namespace htmlcxx::HTML;

/*int main( char** argv, char** argc)
{

	TrudyTheCrawler::ThreadPool _thradpool( 10 );
	_thradpool.start();
	
	while(true)
	{
	}
	return 0;
	
}
*/

int main(char** argv, char** argc)
{
	HTMLParser var;
	vector<string> html;
	html = var.parse("<html><a href=\"http://www.google.de\">google</a><a href='test.html'>asfd</a></html>");
	
	cout << "URLs:\n";
	
    for(uint i=0; i<html.size(); i++)
    	cout << html[i] << " url\n";

	/* EXAMPLE
 	HTTP httptest;
	httptest.get("http://klamm.de");
	std::cout << httptest.getOutput();
*/

}
