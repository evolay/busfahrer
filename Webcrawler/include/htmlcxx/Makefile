VPATH=src:test
CXX=g++ -g
CXXFLAGS=-Wall -Iinclude

all: visit

SRCS = $(subst src/,,$(wildcard src/*.cc))
OBJS = $(patsubst %.cc,%.o,$(SRCS))

libhtmlcxx.a: $(OBJS)
	$(AR) rcv $@ $(OBJS)
	
visit: visit.o libhtmlcxx.a
	$(CXX) -o $@ visit.o -L. -lhtmlcxx

tests: tests.o libhtmlcxx.a
	$(CXX) -o $@ tests.o -L. -lhtmlcxx

uriTests: uriTests.o libhtmlcxx.a
	$(CXX) -o $@ uriTests.o -L. -lhtmlcxx

clean:
	rm -f $(OBJS) visit uriTests tests libhtmlcxx.a *.o *~ 

test: visit
	./visit index.html

alltests: uriTests tests
	./uriTests
	./tests
