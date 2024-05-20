CFLAGS = -Wall -g -ansi
BINARY = tcpserv

tcpserv: less_simple_tcpserv.c
	$(CC) $(CFLAGS) less_simple_tcpserv.c -o $(BINARY)

run: tcpserv
	./tcpserv

tags:
	ctags less_simple_tcpsesrv.c

clean:
	rm $(BINARY) *.o
