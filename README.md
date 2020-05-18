# CAT
This software aims to control the phase of an antenna array based in DNP3 address.

Compile it on linux:
1-g++ -c ServerTCPIP.cpp -o Server.o
2-g++ -c ClientTCPIP.cpp -o Client.o
3-g++ -c cat.cpp Server.o Client.o -o Cat.o
4-g++ main.cpp Cat.o -o br

