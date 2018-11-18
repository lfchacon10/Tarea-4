#include <stdio.h>
#include <math.h>
#include "iostream"
using namespace std;

//Valores iniciales. 
double g = 10; 
double c=0.2; //Coeficiente de friccion
double m= 0.2; // kg.

float xo =0; 
float to = 0; 
float vo=300;
//Derivadas respecto a X
float derivada_x(float vx)
{
	return vx;
}

//Derivadas respecto a Y


float derivada_y(float vy)
{
	return vy;
}


int main(int argc, char const *argv[])
{
	
	std::cout<<"Hola"<<"\n"; 		
	return 0;
}
