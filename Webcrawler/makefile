VPATH=src/
CXXFLAGS = -Wall -Iinclude/
CXX = g++ -g

all: Webcrawler

Webcrawler: src/main.o src/ThreadPool.o 
	$(CXX) -pthread -o $@ src/main.o src/ThreadPool.o -lboost_thread-mt

#main.o:
#	$(CXX) -c -o $@ -pthread src/main.cpp
