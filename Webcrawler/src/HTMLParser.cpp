#include "HTMLParser.h"

using namespace std;
using namespace htmlcxx;

vector<string> HTMLParser::parse(string html) {
	transform(html.begin(), html.end(), html.begin(), ::tolower);
	
	htmlcxx::HTML::ParserDom parser;
	tree<HTML::Node> dom = parser.parseTree(html);

	tree<HTML::Node>::iterator it = dom.begin();
	tree<HTML::Node>::iterator end = dom.end();
	
	vector<string> linklist;
	
	for(; it != end; ++it)
	{
		if(it->tagName() == "a")
		{
			it->parseAttributes();
			pair<bool, string> link = it->attribute("href");
			if(link.first)
			{
				linklist.push_back(link.second);
			}
		}
	}
	
	return linklist;
}
