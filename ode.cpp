#include <stdio.h>
#include <math.h>
#include "iostream"
#include "fstream"
using namespace std;

//Valores iniciales. 
float g = 10; 
float c=0.2; //Coeficiente de friccion
float m= 0.2; // kg.
float ht=0.0002; // paso de tiempo, tiempo total

ofstream archivoDatos("datoProyectil.txt"); // Con posiciones X, Y, velocidadX, velicidadY.
ofstream archivoAdicional("adicionalProyectil.txt");

float xo =0.0;
float yo= 0.0;
float to = 0.0; 
float vo=300;

//Derivada  posicion x
float derivada_x(float vx)
{
	return vx;
}

//Derivada posicion y
float derivada_y(float vy)
{
	return vy;
}
//Derivada de la velocidad x
float derivada_vx(float vx, float vy)
{ 
	float vectorNorma;
	vectorNorma = sqrt( pow(vx,2) + pow(vy,2) ); //Se ignora la gravedad porque es la derivada en X.
	return -c*( pow(vectorNorma,2)/m)*(vx/vectorNorma);
}
//Derivada de la velocidad y
float derivada_vy(float vx, float vy)
{ 
	float vectorNorma;
	vectorNorma = sqrt( pow(vx,2) + pow(vy,2) );
	return -g -c*( pow(vectorNorma,2)/m)*(vy/vectorNorma); //Muy parecida a la derivada en X pero debe agregarsele la gravedad porque va en Y.
}

//Metodo Rakuta para cada K, 4ks por cada variable
float pendientex=0.0, k1x=0.0, k2x=0.0, k3x=0.0, k4x=0.0;
float pendientey=0.0, k1y=0.0, k2y=0.0, k3y=0.0, k4y=0.0;
float pendientevx=0.0, k1vx=0.0, k2vx=0.0, k3vx=0.0, k4vx=0.0;
float pendientevy=0.0, k1vy=0.0, k2vy=0.0, k3vy=0.0, k4vy=0.0;

void k( float vx, float vy)
{
	float k1x= derivada_x(vx), k1y= derivada_y(vy), k1vx = derivada_vx(vx, vy), k1vy = derivada_vy(vx, vy);

	float pasoX2 =0.5*ht*k1vx, pasoY2 =0.5*ht*k1vy;
	k2x = derivada_x(vx + pasoX2);
	k2y = derivada_y(vy + pasoY2);
	k2vx = derivada_vx(vx + pasoX2, vy + pasoY2);
	k2vy = derivada_vy(vx + pasoX2, vy + pasoY2);

	float pasoX3 =0.5*ht*k2vx, pasoY3 =0.5*ht*k2vy;
	k3x = derivada_x(vx + pasoX3);
	k3y = derivada_y(vy + pasoY3);
	k3vx = derivada_vx(vx + pasoX3, vy + pasoY3);
	k3vy = derivada_vy(vx + pasoX3, vy + pasoY3);

	float pasoX4 = ht*k3vx, pasoY4 = ht*k3vy;
	k4x = derivada_x(vx + pasoX4);
	k4y = derivada_y(vy + pasoY4);
	k4vx = derivada_vx(vx + pasoX4, vy + pasoY4);
	k4vy = derivada_vy(vx + pasoX4, vy + pasoY4);

}

float proyectil(float angulo)
{ 	
	std::cout << "Trayectoria proyectil en " << angulo << " grados" << endl;
	float anguloRadianes = angulo/180*3.14159; //En radianes.

	// x,y,vx,vy en el pasado 0 y en el futuro 1
	float x0=xo, x1;
	float y0=yo, y1;
	float vx0=vo*cos(anguloRadianes), vx1;
	float vy0=vo*sin(anguloRadianes), vy1;
	
	int i=0;
	do
	{
		archivoDatos << x0 << " " << vx0 << " " << y0 << " " << vy0 << endl;
		// Derivada en el punto que conozco
		k(vx0, vy0);

		// Pendiente a partir de las 4ks
		pendientex = (1.0*k1x + 2.0*k2x + 2.0*k3x + 1.0*k4x)/6.0;
		pendientey = (1.0*k1y + 2.0*k2y + 2.0*k3y + 1.0*k4y)/6.0;
		pendientevx = (1.0*k1vx + 2.0*k2vx + 2.0*k3vx + 1.0*k4vx)/6.0;
		pendientevy = (1.0*k1vy + 2.0*k2vy + 2.0*k3vy + 1.0*k4vy)/6.0;

		// Actualizar x1 y pone x1 como posición pasada
		x1 = x0 + pendientex*ht, y1 = y0 + pendientey*ht, vx1 = vx0 + pendientevx*ht, vy1 = vy0 + pendientevy*ht;
		x0 = x1, y0 = y1, vx0 = vx1, vy0 = vy1,	i+=1;

	} while (i!=0 and y0>0);
	archivoAdicional << i << endl; 
	std::cout << "Distancia recorrida en x= " << x0 << endl;
	std::cout << "Trayectoria calculada para proyectil a " << angulo << " grados" << endl << endl;
	return x0;
}


int main()
{
	//Primer punto para caso 45º:
	float angulo=45.0;
	float x0=proyectil(angulo);

	//Segundo punto para caso angulos de 10 en 10 hasta 70:
	float distancias[7];
	int i =0;
	float dMax=0;
	int iMax=0;
	do 
	{
		angulo = 10.0*(i+1);
		distancias[i] = proyectil(angulo);
		//std::cout << abs(distancias[i]) << "  " << dMax<< endl;
		if( abs(distancias[i]) > dMax )
		{	
			dMax = distancias[i];
			iMax = i; // encontrar angulo de maxima distancia
		}
		i+=1;
	}while (i <7);
	std::cout << "El angulo que con la mayor distancia es " << (iMax+1)*10 << endl << endl;

	return 0;
}
