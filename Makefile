DIR := ${CURDIR}

CXX			= g++ -std=c++2a

INCLUDES	= -I ../fastflow/
FLAGS 	= -O3 -pthread

TARGETS 	=	main.out

.PHONY: all clean

all: $(TARGETS)

utility.o: utility.cpp
	$(CXX) $(FLAGS) $^ -c -o $@

jacobi_threads.o: jacobi_threads.cpp
	$(CXX) $(FLAGS) $^ -c -o $@

jacobi_sequential.o: jacobi_sequential.cpp
	$(CXX) $(FLAGS) $^ -c -o $@

jacobi_ff.o: jacobi_ff.cpp
	$(CXX) $(FLAGS) $^ -c -o $@

main.out: main.cpp jacobi_sequential.o jacobi_threads.o jacobi_ff.o utility.o
	$(CXX) $(INCLUDES) $(FLAGS) $^ -o $@

clean:
	rm -rf *.o *.out