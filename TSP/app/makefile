GCC_FLAGS=-O3 --std=c++11

main: TSP.o Logger.o City.o
	make clean
	mkdir build
	g++ $(GCC_FLAGS) src/app.cpp src/City.o src/TSP.o src/Logger.o -o build/app

TSP.o:
	g++ -c $(GCC_FLAGS) src/TSP.cpp -o src/TSP.o

Logger.o:
	g++ -c $(GCC_FLAGS) src/Logger.cpp -o src/Logger.o

City.o:
	g++ -c $(GCC_FLAGS) src/City.cpp -o src/City.o

clean:
	rm -rf build