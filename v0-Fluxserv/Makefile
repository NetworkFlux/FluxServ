CC = c++

CFLAGS = -g
COMMON_OBJS = common.o

all: $(COMMON_OBJS)	tcpclient tcpserver

common.o: common.hpp common.cpp
	$(CC) $(CFLAGS) -c common.cpp

tcpclient: tcpclient.cpp $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o tcpclient tcpclient.cpp $(COMMON_OBJS)

tcpserver: tcpserver.cpp $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o tcpserver tcpserver.cpp $(COMMON_OBJS)

clean:
	rm -rf *.o *.dSYM tcpclient tcpserver