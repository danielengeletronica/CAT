# CAT
This software aims to control the phase of an antenna array based in DNP3 address.

Use Makefile

or 

Compile it on linux:
1-g++ -c ./src/ServerTCPIP.cpp -I./include -o ./obj/Server.o
2-g++ -c ./src/ClientTCPIP.cpp -I./include -o ./obj/Client.o
3-g++ -c ./src/cat.cpp -I./include ./obj/Server.o ./obj/Client.o -o ./obj/Cat.o
4-g++ ./apps/main.cpp ./obj/Cat.o -I./include -o ./bin/br

