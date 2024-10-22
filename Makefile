CC=g++
CFLAGS= -g -Wall 

all: proxy

proxy: Proxy_Server_With_Cache.c
	$(CC) $(CFLAGS) -o proxy_parse.o -c ImplementationFiles/proxy_parse.c -lpthread
	$(CC) $(CFLAGS) -o proxy.o -c Proxy_Server_With_Cache.c -lpthread
	$(CC) $(CFLAGS) -o proxy proxy_parse.o proxy.o -lpthread


clean:
	rm -f proxy *.o

tar:
	#tar -cvzf ass1.tgz proxy_server_with_cache.c README Makefile proxy_parse.c proxy_parse.h	