CC = gcc
CXX = g++
CFLAGS = -Wall -g
CXXFLAGS = -Wall -g
LDFLAGS = -ldl -lpthread

SERVER_OBJS = main.o server.o module.o common.o
MODULES = libtime.so libissue.so libdiskfree.so libprocess.so

all: server $(MODULES)

server: $(SERVER_OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

libtime.so: time.cpp
	$(CXX) $(CXXFLAGS) -shared -fPIC -o $@ $<

libissue.so: issue.cpp
	$(CXX) $(CXXFLAGS) -shared -fPIC -o $@ $<

libdiskfree.so: diskfree.cpp
	$(CXX) $(CXXFLAGS) -shared -fPIC -o $@ $<

libprocess.so: process.cpp
	$(CXX) $(CXXFLAGS) -shared -fPIC -o $@ $<

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f server $(SERVER_OBJS) $(MODULES)

run: all
	./server --address localhost --port 8008

main.o: main.cpp server.h
server.o: server.cpp server.h
module.o: module.cpp server.h
common.o: common.cpp server.h

.PHONY: all clean run