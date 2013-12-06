flags = -std=gnu++11 #-stdlib=libc++

# first define target file : account 
#              dependencies are the object files that build the program

bin/flock: bin/Vector.o bin/Manager.o bin/Main.o bin/Algo.o bin/Graph.o bin/Node.o
	g++ -o bin/flock bin/Vector.o bin/Manager.o bin/Main.o bin/Algo.o bin/Graph.o bin/Node.o $(flags)

# now define how each object file is a target and list dependencies and how
#  to build that object file if any dependencies change

bin/Node.o: src/Node.cpp src/Node.h src/Vector.h
	g++ -c src/Node.cpp -o bin/Node.o $(flags)

bin/Graph.o: src/Graph.cpp src/Graph.h src/Node.h src/Vector.h src/Algo.h
	g++ -c src/Graph.cpp -o bin/Graph.o $(flags)

bin/Algo.o: src/Algo.cpp src/Algo.h src/Node.h src/Vector.h
	g++ -c src/Algo.cpp -o bin/Algo.o $(flags)
	
bin/Manager.o: src/Manager.cpp src/Manager.h src/Graph.h src/Node.h src/Vector.h src/Algo.h
	g++ -c src/Manager.cpp -o bin/Manager.o  $(flags)

bin/Main.o: src/Main.cpp src/Manager.h src/Graph.h src/Node.h src/Vector.h src/Algo.h
	g++ -c src/Main.cpp -o bin/Main.o $(flags)

bin/Vector.o: src/Vector.cpp src/Vector.h
	g++ -c src/Vector.cpp -o bin/Vector.o $(flags)

# Clean all files in this directory
clean:
	rm bin/*
