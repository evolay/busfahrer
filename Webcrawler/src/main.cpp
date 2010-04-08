#include <iostream>
#include "TrudyTheCrawler.h"
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
	ThreadPool _threadPool(4);
	for( int i=0; i < 100; i++)
	{
		_threadPool.submitTask( new worker() );
	}
	
	while(true)
	{
	}
	HTMLParser var;
	//var.parseHTML("<html><a href=\"http://www.google.de\">google</a><a href='test.html'>asfd</a></html>");
	var.parse();
}
