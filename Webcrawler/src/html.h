#include <htmlcxx/html/ParserDom.h>

namespace TrudyTheCrawler
{

typedef unsigned int uint;
	
class HTML
{	
	public:
		HTML();
		~HTML( void );
		List parse(string str);

	private:
		HTML::ParserDom parser;
};

};