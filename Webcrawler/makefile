VPATH=src/
CXXFLAGS = -Wall -Iinclude/ -I/usr/include/mysql -I/usr/local/include/mysql++
CXX = g++ -g

all: Webcrawler

Webcrawler: src/main.o src/ThreadPool.o src/HTTP.o src/HTMLParser.o src/Crawler.o src/Mysql.o
	$(CXX) -pthread -o $@ src/main.o src/ThreadPool.o src/HTTP.o src/HTMLParser.o src/Crawler.o src/Mysql.o -lboost_thread-mt -lboost_regex-mt -lcurl -lhtmlcxx -lmysqlpp

#main.o:
#	$(CXX) -c -o $@ -pthread src/main.cpp
