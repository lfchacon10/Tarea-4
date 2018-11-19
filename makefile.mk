#make file  makefile.mk

p45.png proyectiles.png: datoProyectil.txt adicionalProyectil.txt
	python3 Plots_hw4.py

datoProyectil.txt adicionalProyectil.txt: ./a.out
	./a.out 

./a.out: ode.cpp
	 g++ ode.cpp

#datos2.dat: ./a.out
#	./a.out >> datos2.dat

#./a.out: pde.cpp
#	 g++ pde.cpp
