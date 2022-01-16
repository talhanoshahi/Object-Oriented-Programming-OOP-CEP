CC = g++
CFLAGS = -Wall -g

# ****************************************************
# Targets needed to bring the executable up to date

main: Main.o Graph.o Edge.o Node.o Functions.o
	$(CC) $(CFLAGS) -o GraphWriter Main.o Graph.o Edge.o Node.o Functions.o -lstdc++fs

# The main.o target can be written more simply

main.o: Main.cpp Graph.hpp Edge.hpp Node.hpp Functions.hpp
	$(CC) $(CFLAGS) -c Main.cpp

Node.o: Node.hpp

Node.o: Edge.hpp

Functions.o: Node.hpp

Graph.o: Edge.hpp Functions.hpp

clean :
	-rm *.o $(objects) 
