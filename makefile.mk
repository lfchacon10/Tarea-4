#make file  Resultados_hw4.pdf
#FALTA ultimo txt

Resultados.pdf : p45.png proyectiles.png calcitaFija0.png calcitaAbierta0.png calcitaPeriodica0.png Resultados_hw4.tex
	pdflatex Resultados_hw4.tex

p45.png proyectiles.png calcitaFija0.png calcitaAbierta0.png calcitaPeriodica0.png : datoProyectil.txt adicionalProyectil.txt fronterasFijas.txt fronterasAbiertas.txt fronterasPeriodicas.txt
	python3 Plots_hw4.py

datoProyectil.txt adicionalProyectil.txt: ./ode.x
	./ode.x 

./ode.x: ode.cpp
	 g++ ode.cpp -o ode.x

fronterasFijas.txt:./pde.x
	./pde.x 0 fronterasFijas.txt

fronterasAbiertas.txt:./pde.x
	./pde.x 1 fronterasAbiertas.txt

fronterasPeriodicas.txt: ./pde.x
	./pde.x 2  fronterasPeriodicas.txt

./pde.x: ode.cpp
	 g++ pde.cpp -o pde.x

