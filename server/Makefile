server:server.o socket.o
	gcc server.o socket.o -o server -lsqlite3 -pthread
	
socket.o:tcp_net_socket.c tcp_net_socket.h
	gcc -c tcp_net_socket.c -pthread -o socket.o
	
server.o:tcp_net_server.c tcp_net_socket.h
	gcc -c tcp_net_server.c -lsqlite3 -pthread -o server.o

clean:
	rm -rf *.o
