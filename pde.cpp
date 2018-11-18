#include <stdio.h>
#include <math.h>
#include "iostream"

double k = 1.626;  //m2s-1
double Cp = 820;  
double p = 2.71;  // gcm-3
double v= k/(Cp*p);

double T = 100; // En centímetros
double areaT = 0.50*0.50; // En metros


int main(int argc, char const *argv[])
{
	
	std::cout<<"Hola "<<v<<"\n"; 		
	return 0;
}


//Caso 1

double Tfrontera = 10;
