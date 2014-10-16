VPATH=src/
CXXFLAGS = -Wall -Iinclude/
CXX = g++ -g

all: Webcrawler

Webcrawler: src/main.o src/ThreadPool.o src/HTTP.o src/HTMLParser.o src/Crawler.o
	$(CXX) -pthread -o $@ src/main.o src/ThreadPool.o src/HTTP.o src/HTMLParser.o src/Crawler.o -lboost_thread-mt -lboost_regex-mt -lcurl -lhtmlcxx

#main.o:
#	$(CXX) -c -o $@ -pthread src/main.cpp


#this is my makefile sample (by evolay)
CURRENT_FILE=$(wildcard *.cpp)

SRC_DIR=./src
SRC_FILE=$(wildcard $(SRC_DIR)/*.cpp)

FILES=$(CURRENT_FILE) $(SRC_FILE)

PTHREAD_LIB=-lpthread
BOOST_THREAD_LIB=-L$(BOOST_LIB) -lboost_thread
BOOST_REGEX_LIB=-L$(BOOST_LIB) -lboost_regex
BOOST_SYSTEM_LIB=-L$(BOOST_LIB) -lboost_system
CURL_LIB=-lcurl
HTMLXXX_LIB=-lhtmlcxx

LIBS=$(PTHREAD_LIB) $(BOOST_THREAD_LIB) $(BOOST_REGEX_LIB) \
        $(BOOST_SYSTEM_LIB) $(HTMLXXX_LIB) $(CURL_LIB) 

PRINCIPAL_INC_DIR=./include

ALL_INCL=-I. -I$(PRINCIPAL_INC_DIR) -I$(BOOST_INC)

OPR=-g -Wall
CC=g++
CFLAGS=$(OPR)

OBJ=$(FILES:.cpp=.o)

TARGET=a.out

ALL:$(OBJ)
        rm -rf $(TARGET)
        $(CC) -o $(TARGET) $? $(LIBS)

$(OBJ):%.o : %.cpp
        $(CC) $(ALL_INCL) -c $(CFLAGS) $< -o $@

.PHONY:
clean:
        -rm -rf ./$(TARGET) $(SRC_DIR)/*.o ./*.o
