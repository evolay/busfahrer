#pragma once
#include "ThreadPool.h"
#include "HTTP.h"
#include "HTMLParser.h"
#include "IThreadable.h"

using namespace RudyTheCrawler;

struct ParseResult;

class Crawler
{
	public:
		Crawler( std::string url, int = 50 );
		~Crawler(void);
		
		std::map< std::string, ParseResult >*	getResultMap(); //returns reference to already parsed links
		int 									_request_count;
		void countUp();
		ThreadPool*								getThreadPool(); //returns reference to pool to submit task
		std::string								getDomainName(); //returns filtert domain name

	private:
		ThreadPool*								_threadPool;
		std::map< std::string, ParseResult >	_resultMap;
		std::string								_rootDomainName;
};


class Worker : public IThreadable
{
	public:
		Worker( Crawler* crawler, const std::string& url, const std::string& parentUrl );
		~Worker();

		void					run();

	private:
		std::string				_url, _parentUrl;
		Crawler*				_crawler;
		boost::mutex			_mutex;
};


struct ParseResult
{
	ParseResult(){}
	ParseResult( bool broken, std::string parentUrl )
		: _broken( broken), _parentUrl( parentUrl )
	{}

	bool				_broken;
	std::string			_parentUrl;
};
