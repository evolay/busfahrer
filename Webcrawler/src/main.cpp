#include <iostream>
#include "TrudyTheCrawler.h"
#include "htmlcxx/html/ParserDom.h"

using namespace std;
using namespace htmlcxx::HTML;

int main( char** argv, char** argc)
{
	
	TrudyTheCrawler::ThreadPool _thradpool( 10 );
	_thradpool.start();
	
	while(true)
	{
	}
	return 0;

}

/*

int main(char** argv, char** argc)
{
  //Parse some html code
  string html = "<html><body>hey</body></html>";
  ParserDom parser;
  tree<Node> dom = parser.parseTree(html);
  
  //Print whole DOM tree
  cout << dom << endl;
  
  //Dump all links in the tree
  tree<Node>::iterator it = dom.begin();
  tree<Node>::iterator end = dom.end();
  for (; it != end; ++it)
  {
  	if (it->tagName() == "A")
  	{
  		it->parseAttributes();
		cout << it->attributes().begin()->first;
  	}
  }
  
  //Dump all text of the document
  it = dom.begin();
  end = dom.end();
  for (; it != end; ++it)
  {
  	if ((!it->isTag()) && (!it->isComment()))
  	{
  		cout << it->text();
  	}
  }
}
*/