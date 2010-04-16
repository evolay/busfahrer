#include <iostream>
#include "htmlcxx/include/ParserDom.h"
#include <string>
#include <vector>
#include <algorithm>
#include <boost/regex.hpp>

namespace RudyTheCrawler
{
class HTMLParser
{	
	public:
		HTMLParser() {}
		~HTMLParser() {}

		std::vector<std::string> parse(std::string html, std::string parentUrl );
	private:
		std::string UpToLow(std::string str);
};
};