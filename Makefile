src = $(wildcard *.cpp)
obj = $(src:.c=.o)
CC = g++ -std=c++11 -g -Wall
LDFLAGS = -lboost_system -lboost_filesystem -lboost_thread -lpthread -lboost_regex -lcrypto -lssl -ljson-c -lsqlite3

voc_client_app: $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f voc_client_app *~
