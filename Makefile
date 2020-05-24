
all:
	g++ -c ./src/ServerTCPIP.cpp -I./include -o ./obj/Server.o
	g++ -c ./src/ClientTCPIP.cpp -I./include -o ./obj/Client.o
	g++ -c ./src/cat.cpp -I./include ./obj/Server.o ./obj/Client.o -o ./obj/Cat.o
	g++ ./apps/main.cpp ./obj/Cat.o -I./include -o ./bin/br
	
run: 
	./bin/br
	
clean:
	rm ./obj/*.o
	rm ./bin/*