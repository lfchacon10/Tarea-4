from numpy import *
from matplotlib.pyplot import *
#Parte ODE
datosProyectil = np.genfromtxt("datoProyectil.txt")
datosProyectilAd = np.genfromtxt("adicionalProyectil.txt")
datos = np.cumsum(datosProyectilAd) # indices de los proyectiles
i0 = int(0)
i1 = int(datos[0])

title ("Recorrido proyectil a 45º")
grid()
xlabel("Distancia (m)")
ylabel("Altura (m)")
plot(datosProyectil[i0:i1,0], datosProyectil[i0:i1,2])
savefig('p45.png')

figure()
title ("Recorrido proyectil para diferentes ángulos")
grid()
xlabel("Distancia (m)")
ylabel("Altura (m)")
for i in range(6):
	i0 = int(datos[i])
	i1 = int(datos[i+1])
	plot(datosProyectil[i0:i1,0], datosProyectil[i0:i1,2], label=str((i+1)*10))
i0=int(datos[-1])
i1=-1
plot(datosProyectil[i0:i1,0], datosProyectil[i0:i1,2], label=str(70))
legend(loc='best')
savefig('proyectiles.png')

## Graficas PDE
def meanT(M, total_instantes, n):
	# calcula promedios de total_instantes matrices nxn
	promedio = np.zeros((n,1))
	for i in range(n):
		promedio[i] = np.sum(np.sum( M[i*n:(i+1)*n] ))/(n**2)
	return promedio

def graficarInstantes( titulo, pN, instantes):
	for i in instanteGrafica:
		i0 = i*n
		i1 = i0 + n
		figure()
		imshow(calcita[i0:i1,:], vmax=100, vmin=0)
		title('Fijas')
		colorbar()
		savefig( titulo + str(i) + '.png')


calcita = np.genfromtxt("fronterasFijas.txt")
n = np.size(calcita,1)
lineas = np.size(calcita,0)
instantes = lineas/n
fijas = meanT(calcita,instantes,n)
instanteGrafica = [0, int(0.25*instantes), int(0.75*instantes), int(instantes-1)]
graficarInstantes("calcitaFija", n, instanteGrafica) 


calcita = genfromtxt("fronterasAbiertas.txt")
n = np.size(calcita,1)
lineas = np.size(calcita,0)
instantes = lineas/n
abiertas = meanT(calcita, instantes, n)
instanteGrafica = [0, int(0.25*instantes), int(0.75*instantes), int(instantes-1)]
graficarInstantes("calcitaAbierta", n, instanteGrafica)

calcita = genfromtxt("fronterasPeriodicas.txt")
n = np.size(calcita,1)
lineas = np.size(calcita,0)
instantes = lineas/n
periodicas = meanT(calcita, instantes, n)
instante_a_graficar = [0, int(0.25*instantes), int(0.75*instantes), int(instantes-1)]
graficarInstantes("calcitaPeriodica", n, instanteGrafica)


figure()
plot(abiertas, label='Fronteras Abiertas')
plot(periodicas, label='Fronteras Periodicas')
plot(fijas, label='Fronteras Fijas')
legend()
title('Temperatura promedio[c]')
savefig('calcita_Tmedia.png')


