#include <iostream>
#include "TrudyTheCrawler.h"
#include "HTMLParser.h"

using namespace std;
using namespace htmlcxx::HTML;


int main(char** argv, char** argc)
{
	HTMLParser var;
	//var.parseHTML("<html><a href=\"http://www.google.de\">google</a><a href='test.html'>asfd</a></html>");
	var.parse();
}
