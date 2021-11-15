
all: server
	gcc *.c *.h -lpthread
server:
	gcc server/*.h server/*.c -lpthread -o TIC-TAC_server
clean:
	rm a.out