#include <stdio.h>
#include <math.h>
#include "iostream"

double k = 1.626;
double Cp = 820;
double p = 2.71;
double v= k/(Cp*p);

int main(int argc, char const *argv[])
{
	
	std::cout<<"Hola "<<v<<"\n"; 		
	return 0;
}
