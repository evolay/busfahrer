#include <iostream>
#include "TrudyTheCrawler.h"
#include "htmlcxx/html/ParserDom.h"

using namespace std;

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
  HTML::ParserDom parser;
  tree<HTML::Node> dom = parser.parseTree(html);
  
  //Print whole DOM tree
  cout << dom << endl;
  
  //Dump all links in the tree
  tree<HTML::Node>::iterator it = dom.begin();
  tree<HTML::Node>::iterator end = dom.end();
  for (; it != end; ++it)
  {
  	if (it->tagName() == "A")
  	{
  		it->parseAttributes();
  		cout << it->attributes("href");
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
}*/