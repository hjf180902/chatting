client:socket.o  client.o
	gcc socket.o client.o -o client -pthread
	
socket.o:tcp_net_socket.c tcp_net_socket.h
	gcc -c tcp_net_socket.c -pthread -o socket.o
	
client.o:tcp_net_client.c tcp_net_socket.h
	gcc -c tcp_net_client.c -pthread -o client.o

clean:
	rm -rf *.o
