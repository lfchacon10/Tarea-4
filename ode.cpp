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

ofstream archivo_salida("proyectil.txt");
ofstream archivo_adicional("proyectil_info.txt");

float xo =0; 
float to = 0; 
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
	float vectorNormal;
	vectorNormal = sqrt( pow(vx,2) + pow(vy,2) ); //Se ignora la gravedad porque es la derivada en X.
	return -c*( pow(vectorNormal,2)/m)*(vx/vectorNormal);
}
//Derivada de la velocidad y
float derivada_vy(float vx, float vy)
{ 
	float vectorNormal;
	vectorNormal = sqrt( pow(vx,2) + pow(vy,2) );
	return -g -c*( pow(vectorNormal,2)/m)*(vy/vectorNormal); //Muy parecida a la derivada en X pero debe agregarsele la gravedad porque va en Y.
}

//Metodo Rakuta para cada K:
// 4ks por cada variable y una variable para la pendiente de cada variable
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

int main(int argc, char const *argv[])
{
	
	std::cout<<"Hola"<<"\n"; 		
	return 0;
}
