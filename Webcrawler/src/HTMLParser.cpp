#include "HTMLParser.h"

using namespace std;
using namespace htmlcxx;
using namespace RudyTheCrawler;


vector<string> HTMLParser::parse(string html, std::string parentUrl ) {
	transform(html.begin(), html.end(), html.begin(), ::tolower);
	
	htmlcxx::HTML::ParserDom parser;
	tree<HTML::Node> dom = parser.parseTree(html);

	tree<HTML::Node>::iterator it = dom.begin();
	tree<HTML::Node>::iterator end = dom.end();
	
	vector<string> linklist;
	boost::regex ex("/^javascript:/gi");
	
	for(; it != end; ++it)
	{
		if(it->tagName() == "a")
		{
			it->parseAttributes();
			pair<bool, string> link = it->attribute("href");
			if(link.first)
			{
				if(!regex_match(link.second, ex))
				{
					boost::smatch _match;
					ex.assign( "^(http)", boost::regex_constants::icase);
					std::string _url = link.second;

					if( !boost::regex_search( _url, _match, ex ) )
					{
						ex.assign( "\\A(.*\\/)", boost::regex_constants::icase);
						boost::regex_search( parentUrl, _match, ex );
						_url = _match.str() + _url;
					}
					ex.assign( "^([^#]*)", boost::regex_constants::icase );
					boost::regex_search( _url, _match, ex );
					_url = _match.str();
					linklist.push_back( _url );
				}
			}
		}
	}
	return linklist;
}
