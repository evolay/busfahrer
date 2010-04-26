#include <iostream>
#include "Crawler.h"
#include <fstream>
#include "time.h"
#include "Mysql.h"

int main(char** argv, char** argc)
{	
	try {
		Mysql mysql;
		mysql.connect("webcrawler","localhost","root","");
		mysqlpp::Query query = Mysql::_connection.query("TRUNCATE mylink;");
		query.execute();
	} catch(char const* e) { std::cout << e << std::endl; return 1;}

	time_t seconds;
	seconds = time(NULL);	
	Crawler* _crawler = new Crawler( "http://goltergaul.de/crawler/", 100 );

	int abort = 0;
	while( !_crawler->requestsFinished())
	{
		printf ("%f requests per second\n", (float)_crawler->getRequestCount() / (float)(time(NULL) - seconds));
	}

	//getting map & iterator
	std::map< std::string, ParseResult>* _map = _crawler->getResultMap();
	std::map< std::string, ParseResult>::iterator _iter = _map->begin();
	
	//writing to logfile
	std::ofstream file( "Log.txt", std::ios::out );
	int _brokenLinks = 0;

	for( ; _iter != _map->end(); _iter++)
	{
		if( (*_iter).second._broken )
		{
			file << "Found broken URL: " << (*_iter).first << "\n";
			file << "ParentUrl: " << (*_iter).second._parentUrl << "\n\n";
			++_brokenLinks;
		}
	}

	file << "Searched URL \"" << _crawler->getDomainName() << "\" for broken links...\n";
	file << "Found\n" << _brokenLinks << " broken Links\n";
	file << ( _map->size() - _brokenLinks ) << " good links\n";
	file << "from " << _map->size() << " links to search\n";
	file.close();

	std::cout << std::endl << "End\n\nStatistics:\n\n" << std::endl;

	// print out statistics using mysql
	mysqlpp::Query query = Mysql::_connection.query("SELECT parent_url as site, count(*) as links, (SELECT count(*) FROM mylink ml2 WHERE ml2.broken=1 AND ml2.parent_url=ml1.parent_url)as broken_links, (SELECT count(*) FROM mylink ml2 WHERE ml2.broken=0 AND ml2.parent_url=ml1.parent_url)as good_links FROM `mylink` ml1 GROUP BY ml1.parent_url;");
	if (mysqlpp::StoreQueryResult res = query.store()) {
            std::cout << "We have:" << std::endl;
            for (size_t i = 0; i < res.num_rows(); ++i) {
		std::string subselect = "SELECT url FROM mylink WHERE parent_url='"+(std::string)res[i][0]+"' AND broken=1";
		mysqlpp::Query subquery = Mysql::_connection.query(subselect);
                std::cout << res[i][0] << " with " << res[i][1] << " links, " << res[i][2] << " are broken, " << res[i][3] << " are good." << std::endl;
		if (mysqlpp::StoreQueryResult subres = subquery.store()) {
			std::cout << "\tBroken ones:\n";
		    for (size_t i = 0; i < subres.num_rows(); ++i) {
		        std::cout << "\t\t" << subres[i][0] << std::endl;
		    }
		}
            }
        }
        else {
            std::cerr << "Failed to get item list: " << query.error() << std::endl;
        }

	return 0;
}


