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
	int p= 50;
	float h = 50.0/(p-1);
	int i,j; //valores "aleatorios"
	float X[p][p];
	float Y[p][p];
	// Inicializa los valores de los arreglos X y Y
	for (i = 0; i < p; ++i)
	{
		for (j = 0; j < p; ++j)
		{
			X[i][j] = i*h;
			Y[i][j] = j*h;
		}
	}
	// Arreglos de la temperatura
	float presente[p][p];
	float futuro[p][p];

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
	for (i = 0; i < p; ++i)
	{
		for (j = 0; j < p; ++j)
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
		for (i = 0; i < p; ++i)
		{
			presente[0][i] = Tc; 
			presente[p-1][i] = Tc; 
			presente[i][0] = Tc;
			presente[i][p-1] = Tc;
			futuro[0][i] = Tc;
			futuro[p-1][i] = Tc;
			futuro[i][0] = Tc;
			futuro[i][p-1]= Tc;
		}
	}
	int pasos = 1000;
	float dT = 0.1*pow(h,2)/v;
	for ( int iT = 0; iT < pasos; ++iT)
	{
		float k= v*dT/pow(h,2);
		for (i = 1; i < p-1; ++i)
		{
			for (j = 1; j < p-1; ++j)
			{
				if ( pow(X[i][j]-25.0, 2) + pow(Y[i][j]-25.0, 2) >= Tc )
				{
					futuro[i][j] = presente[i][j] + k*(presente[i-1][j] + presente[i+1][j] - 4.0*presente[i][j] + presente[i][j-1] + presente[i][j+1]);
				}
			}
		}
		if (tipo==1)
		{
			for (i = 0; i < p; ++i)
			{
				futuro[i][0] = futuro[i][1]; 
				futuro[i][p-1] = futuro[i][p-2];
				futuro[0][i] = futuro[1][i]; 
				futuro[p-1][i] = futuro[p-2][i];
			}
		}else if (tipo==2)
		{ 
			for (i = 1; i < p-1; ++i)
			{
				futuro[i][0] = presente[i][0] + k*(presente[i-1][0] + presente[i+1][0] -4.0*presente[i][0] +presente[i][p-1] +presente[i][0+1]);
				futuro[0][i] = presente[0][i] + k * (presente[p-1][i] + presente[0+1][i] - 4.0*presente[0][i] + presente[0][i-1] + presente[0][i+1]);
				futuro[i][p-1] = presente[i][p-1] + k*(presente[i-1][p-1] + presente[i+1][p-1] - 4.0*presente[i][p-1] + presente[i][p-2] + presente[i][0]);

				futuro[p-1][i] = presente[p-1][i] +k * (presente[p-2][i] + presente[0][i] - 4.0*presente[p-1][i] + presente[p-1][i-1] + presente[p-1][i+1]);
			}

			futuro[0][0] = presente[0][0] + k * (presente[p-1][0] + presente[0+1][0] - 4.0*presente[0][0] + presente[0][p-1] + presente[0][0+1]);
			futuro[p-1][0] = presente[p-1][0] + k * (presente[p-2][0] + presente[0][0] - 4.0*presente[p-1][0] + presente[p-1][p-1] + presente[p-1][0+1]);
			futuro[0][p-1] = presente[0][p-1] + k * (presente[p-1][p-1] + presente[0+1][p-1] - 4.0*presente[0][p-1] + presente[0][p-2] + presente[0][0]);
			futuro[p-1][p-1] = presente[p-1][p-1] + k * (presente[p-2][p-1] + presente[0][p-1] - 4.0*presente[p-1][p-1] + presente[p-1][p-2] + presente[p-1][0]);
		}

		for (i = 0; i < p; ++i)
		{
			for (j = 0; j < p; ++j)
			{
				presente[i][j] = futuro[i][j];
				escribir_datos << futuro[i][j] << " ";
			}
			escribir_datos << "\n";
		}
	}
	return 0;
}
