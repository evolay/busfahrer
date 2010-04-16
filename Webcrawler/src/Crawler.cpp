#include "Crawler.h"
#include <boost/regex.hpp>

Crawler::Crawler( std::string url, int poolsize )
	: _threadPool( new ThreadPool( poolsize ) ),
	_rootDomainName( url )
{
	//starting first worker with given url
	_threadPool->submitTask( new Worker( this, url, "root" ) );
}

Crawler::~Crawler(void)
{
	delete _threadPool;
}

std::map< std::string, ParseResult >* Crawler::getResultMap()
{
	return &_resultMap;
}

std::string Crawler::getDomainName()
{
	boost::regex _e;
	boost::smatch _match;
	_e.assign( "^(?:[^\\/]+:\\/\\/)?([^\\/:]+)", boost::regex_constants::icase);
	boost::regex_search( _rootDomainName, _match, _e );
	return _match.str();
}


//--------------------------------------------------------------->


ThreadPool* Crawler::getThreadPool()
{
	return _threadPool;
}

Worker::Worker( Crawler* crawler, const std::string& url, const std::string& parentUrl )
	: _url( url ),
	_crawler( crawler ),
	_parentUrl( parentUrl )
{
}

void Worker::run()
{
	try{
		HTTP _request;
		//getting map from crawler
		std::map< std::string, ParseResult >* _resultMap = _crawler->getResultMap();

		//checking domains
		boost::regex _e;
		boost::smatch _match;
		_e.assign( "^(http)", boost::regex_constants::icase);

		if( !boost::regex_search( _url, _match, _e ) )
		{
			_e.assign( "\\A(.*\\/)", boost::regex_constants::icase);
			boost::regex_search( _parentUrl, _match, _e );
			_url = _match.str() + _url;
		}

		if( _request.get( _url ) )
		{	
			std::cout << _url << " not broke " << std::endl;

			//adding current url + parentUrl to map
			(*_resultMap)[ _url ] = ParseResult( false, _parentUrl );
			_e.assign( "^(?:[^\\/]+:\\/\\/)?([^\\/:]+)", boost::regex_constants::icase);
				
			boost::regex_search( _url, _match, _e );
			std::string _bla, _blu;
			_bla = _crawler->getDomainName();
			_blu = _match.str();
			if(  _crawler->getDomainName() != _match.str())
				return;
		
			
			//getting linklist by parser
			HTMLParser parser;
			std::vector<std::string> _list = parser.parse( _request.getOutput() );

			for( uint i=0; i<_list.size(); i++)
			{
				//lock the loop for thread-safety while writing in map
				boost::mutex::scoped_lock( _mutex );
				//check if link is already in map
				if( (*_resultMap).count( _list[i] ) == 0 )
					_crawler->getThreadPool()->submitTask( new Worker( _crawler, _list[i], _url ) );
			}
		}
		else
		{
			std::cout << _url << "broke" << std::endl;

			//adding current url + parentUrl to map
			(*_resultMap)[ _url ] = ParseResult( true, _parentUrl );
		}
	}
	catch( boost::bad_expression& e)
	{
		//catch regularmatch fail -> on fail: exit
		std::cout << "Error in regex-compare: Crawler.cpp " << e.what() << std::endl;
	}

}
