#include "htmlcxx/html/ParserDom.h"
#include <iostream>


class HTMLParser
{	
	public:
		HTMLParser();
		~HTMLParser( void );
		void parse(std::string str);

	private:
		HTML::ParserDom parser;
};
