#include "htmlcxx/html/ParserDom.h"
#include <string>
	
class HTMLParser
{	
	public:
		HTMLParser();
		~HTMLParser( void );
		void parse(string str);

	private:
		HTML::ParserDom parser;
};
