
all:
	g++ -c ./src/ServerTCPIP.cpp -pthread -I./include -o ./obj/Server.o
	g++ -c ./src/ClientTCPIP.cpp -pthread -I./include -o ./obj/Client.o
	g++ -c ./src/cat.cpp -pthread -I./include ./obj/Server.o ./obj/Client.o -o ./obj/Cat.o
	g++ ./apps/main.cpp ./obj/Cat.o -pthread -I./include -o ./bin/br
	
run: 
	./bin/br
	
clean:
	rm ./obj/*.o
	rm ./bin/*