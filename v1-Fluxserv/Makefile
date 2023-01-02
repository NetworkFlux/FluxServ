CC = c++

CFLAGS = -g
BINS = server
OBJS = server.o myqueue.o

all: $(BINS)

server: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf *.dSYM $(BINS) $(OBJS)