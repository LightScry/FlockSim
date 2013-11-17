# first define target file : account 
#              dependencies are the object files that build the program

bin/flock: bin/flock bin/Manager.o bin/Main.o bin/Algo.o bin/Graph.o bin/Node.o
	g++ -o bin/flock bin/Manager.o bin/Main.o bin/Algo.o bin/Graph.o bin/Node.o

# now define how each object file is a target and list dependencies and how
#  to build that object file if any dependencies change

bin/Node.o: src/Node.cpp src/Node.h
	g++ -c src/Node.cpp -o bin/Node.o

bin/Graph.o: src/Graph.cpp src/Graph.h
	g++ -c src/Graph.cpp -o bin/Graph.o

bin/Algo.o: src/Algo.cpp src/Algo.h
	g++ -c src/Algo.cpp -o bin/Algo.o
	
bin/Manager.o: src/Manager.cpp src/Manager.h
	g++ -c src/Manager.cpp -o bin/Manager.o

bin/Main.o: src/Main.cpp
	g++ -c src/Main.cpp -o bin/Main.o

# Clean all files in this directory
clean:
	rm bin/*