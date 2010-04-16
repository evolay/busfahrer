#include <iostream>
#include "TrudyTheCrawler.h"
#include "curl/curl.h"
#include <string>
#include "HTTP.h"
#include "HTMLParser.h"

using namespace std;
using namespace htmlcxx::HTML;
using namespace TrudyTheCrawler;


class worker : public IThreadable
{
	public:
		void run(){
			std::cout << "execute Task" << std::endl;
			boost::this_thread::sleep( boost::posix_time::milliseconds(2000) );
		}
};


int main(char** argv, char** argc)
{
/*	ThreadPool _threadPool(4);
	for( int i=0; i < 100; i++)
	{
		_threadPool.submitTask( new worker() );
	}
	
*/	
	HTMLParser var;
	vector<string> html;
	html = var.parse("<html><a href=\"http://www.google.de\">google</a><a href=\"javascript:alert('hallo')\">asfd</a></html>");
	
	cout << "URLs:\n";
	
    for(uint i=0; i<html.size(); i++)
    	cout << html[i] << " url\n";

/*	
 	HTTP httptest;
	cout << httptest.get("http://microsoft.de")<<endl;
	cout << httptest.getOutput();

	while(true)
	{
	}*/
}
