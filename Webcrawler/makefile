VPATH=src/
CXXFLAGS = -Wall -Iinclude/
CXX = g++ -g

all: Webcrawler

Webcrawler: src/main.o src/ThreadPool.o src/HTTP.o
	$(CXX) -pthread -o $@ src/main.o src/ThreadPool.o src/HTTP.o -lboost_thread-mt -lcurl -lhtmlcxx

#main.o:
#	$(CXX) -c -o $@ -pthread src/main.cpp
