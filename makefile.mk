#make file  makefile.mk





datos2.dat: ./a.out
	./a.out >> datos2.dat

./a.out: pde.cpp
	 g++ pde.cpp

datos1.dat: ./a.out
	./a.out >> datos1.dat

./a.out: ode.cpp
	 g++ ode.cpp
