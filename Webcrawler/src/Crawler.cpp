#include "Crawler.h"
#include <boost/regex.hpp>

Crawler::Crawler( std::string url, int poolsize )
	: _threadPool( new ThreadPool( poolsize ) ),
	_rootDomainName( url ), _request_count(0)
{
	//starting first worker with given url
	_threadPool->submitTask( new Worker( this, url, url ) );
}

Crawler::~Crawler(void)
{
	delete _threadPool;
}

void Crawler::countUp()
{
	boost::mutex::scoped_lock( getThreadPool()->_mutex );
	_request_count++;
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

bool Crawler::requestsFinished()
{
	return _threadPool->getTasksFinished( 1000 ); //returns value every 5 seconds
}

int Crawler::getRequestCount()
{
	return _request_count;
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
	_crawler->countUp();
	try{
		HTTP _request;
		//getting map from crawler
		std::map< std::string, ParseResult >* _resultMap = _crawler->getResultMap();

		//checking domains
		boost::regex _e;
		boost::smatch _match;
		bool request_state = _request.get( _url );
		_crawler->getThreadPool()->decreaseTaskCount();
		if( request_state )
		{	
			std::cout << _url << " not broke " << std::endl;

			//adding current url + parentUrl to map
			(*_resultMap)[ _url ] = ParseResult( false, _parentUrl );

			// check if we are on another domain
			_e.assign( "^(?:[^\\/]+:\\/\\/)?([^\\/:]+)", boost::regex_constants::icase);
			boost::regex_search( _url, _match, _e );

			if( _crawler->getDomainName() != _match.str()) 
			{
				//_crawler->getThreadPool()->decreaseTaskCount();
				return;			
			}
		
			//getting linklist by parser
			HTMLParser parser;
			std::vector<std::string> _list = parser.parse( _request.getOutput(), _parentUrl );

			for( uint i=0; i<_list.size(); i++)
			{
				//lock the loop for 
				boost::mutex::scoped_lock( _crawler->getThreadPool()->_mutex);
				//check if link is already in map
				if( (*_resultMap).find( _list[i] ) == (*_resultMap).end() )
					_crawler->getThreadPool()->submitTask( new Worker( _crawler, _list[i], _url ) );
			}
		}
		else
		{
			std::cout << _url << " broken" << std::endl;

			//adding current url + parentUrl to map
			(*_resultMap)[ _url ] = ParseResult( true, _parentUrl );
		}
	}
	catch( boost::bad_expression& e)
	{
		//catch regularmatch fail -> on fail: exit
		std::cout << "Error in regex-compare: Crawler.cpp " << e.what() << std::endl;
	}
	//_crawler->getThreadPool()->decreaseTaskCount();

}
