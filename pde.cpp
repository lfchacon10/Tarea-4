#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include "iostream"
#include "fstream"
using namespace std;

float k = 1.626;  //Conductividad m2s-1 
float cEspecifico = 820;  
float p = 2710;  // Densidad gm3
float v= k/(cEspecifico*p); // Coeficiente Difusion

double Tv = 100.0; // En grados
double Tc = 10.0; // En grados
double areaT = 0.50*0.50; // En metros


int main(int argc, char const *argv[])
{
	//Tamano del arreglo
	int npuntos= 50;
	float h = 50.0/(npuntos-1);
	int i,j; //valores "aleatorios"
	float X[npuntos][npuntos];
	float Y[npuntos][npuntos];
	// Inicializa los valores de los arreglos X y Y
	for (i = 0; i < npuntos; ++i)
	{
		for (j = 0; j < npuntos; ++j)
		{
			X[i][j] = i*h;
			Y[i][j] = j*h;
		}
	}
	// Arreglos de la temperatura
	float presente[npuntos][npuntos];
	float futuro[npuntos][npuntos];

	int tipo = atoi(argv[1]);
	ofstream escribir_datos(argv[2]);
	if (tipo==0)
	{
		cout << "Fronteras Fijas" << "\n";
	}else if (tipo==1)
	{
		cout << "Fronteras Abiertas" << "\n";
	}else if (tipo==2)
	{
		cout << "Fronteras periodicas" << "\n";
	}

	// Inicializa valores iniciales
	for (i = 0; i < npuntos; ++i)
	{
		for (j = 0; j < npuntos; ++j)
		{
			if ( pow(X[i][j]-25.0, 2) + pow(Y[i][j]-25.0, 2) <= 10.0 )
			{ // Corresponde a la varilla
				presente[i][j] = 100.0;
				futuro[i][j] = 100.0;
			}else
			{ // Corresponde a calcita
				presente[i][j] = 10;
				futuro[i][j] = 10;
			}
		}
	}

	// Si hay condiciones de frontera fijas, asignar los valores
	if (tipo==0)
	{ 
		for (i = 0; i < npuntos; ++i)
		{
			presente[0][i] = Tc; 
			presente[npuntos-1][i] = Tc; 
			presente[i][0] = Tc;
			presente[i][npuntos-1] = Tc;
			futuro[0][i] = Tc;
			futuro[npuntos-1][i] = Tc;
			futuro[i][0] = Tc;
			futuro[i][npuntos-1]= Tc;
		}
	}
	int pasos = 1000;
	float dT = 0.1*pow(h,2)/v;
	for ( int iT = 0; iT < pasos; ++iT)
	{
		float k= v*dT/pow(h,2);
		for (i = 1; i < npuntos-1; ++i)
		{
			for (j = 1; j < npuntos-1; ++j)
			{
				if ( pow(X[i][j]-25.0, 2) + pow(Y[i][j]-25.0, 2) >= Tc )
				{
					futuro[i][j] = presente[i][j] + k*(presente[i-1][j] + presente[i+1][j] - 4.0*presente[i][j] + presente[i][j-1] + presente[i][j+1]);
				}
			}
		}
		if (tipo==1)
		{
			for (i = 0; i < npuntos; ++i)
			{
				futuro[i][0] = futuro[i][1]; 
				futuro[i][npuntos-1] = futuro[i][npuntos-2];
				futuro[0][i] = futuro[1][i]; 
				futuro[npuntos-1][i] = futuro[npuntos-2][i];
			}
		}else if (tipo==2)
		{ 
			for (i = 1; i < npuntos-1; ++i)
			{
				futuro[i][0] = presente[i][0] + k*(presente[i-1][0] + presente[i+1][0] -4.0*presente[i][0] +presente[i][npuntos-1] +presente[i][0+1]);
				futuro[0][i] = presente[0][i] + k * (presente[npuntos-1][i] + presente[0+1][i] - 4.0*presente[0][i] + presente[0][i-1] + presente[0][i+1]);
				futuro[i][npuntos-1] = presente[i][npuntos-1] + k*(presente[i-1][npuntos-1] + presente[i+1][npuntos-1] - 4.0*presente[i][npuntos-1] + presente[i][npuntos-2] + presente[i][0]);

				futuro[npuntos-1][i] = presente[npuntos-1][i] +k * (presente[npuntos-2][i] + presente[0][i] - 4.0*presente[npuntos-1][i] + presente[npuntos-1][i-1] + presente[npuntos-1][i+1]);
			}

			futuro[0][0] = presente[0][0] + k * (presente[npuntos-1][0] + presente[0+1][0] - 4.0*presente[0][0] + presente[0][npuntos-1] + presente[0][0+1]);
			futuro[npuntos-1][0] = presente[npuntos-1][0] + k * (presente[npuntos-2][0] + presente[0][0] - 4.0*presente[npuntos-1][0] + presente[npuntos-1][npuntos-1] + presente[npuntos-1][0+1]);
			futuro[0][npuntos-1] = presente[0][npuntos-1] + k * (presente[npuntos-1][npuntos-1] + presente[0+1][npuntos-1] - 4.0*presente[0][npuntos-1] + presente[0][npuntos-2] + presente[0][0]);
			futuro[npuntos-1][npuntos-1] = presente[npuntos-1][npuntos-1] + k * (presente[npuntos-2][npuntos-1] + presente[0][npuntos-1] - 4.0*presente[npuntos-1][npuntos-1] + presente[npuntos-1][npuntos-2] + presente[npuntos-1][0]);
		}

		for (i = 0; i < npuntos; ++i)
		{
			for (j = 0; j < npuntos; ++j)
			{
				presente[i][j] = futuro[i][j];
				escribir_datos << futuro[i][j] << " ";
			}
			escribir_datos << "\n";
		}
	}
	return 0;
}
