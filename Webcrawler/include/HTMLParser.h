#include <iostream>
#include "htmlcxx/include/ParserDom.h"
#include <string>
#include <vector>
#include <algorithm>

namespace RudyTheCrawler
{
class HTMLParser
{	
	public:
		HTMLParser() {}
		~HTMLParser() {}

		std::vector<std::string> parse(std::string html);
	private:
		std::string UpToLow(std::string str);
};
};