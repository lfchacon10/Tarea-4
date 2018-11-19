import numpy as np
import matplotlib.pyplot as plt

#Parte ODE
datosProyectil = np.genfromtxt("datoProyectil.txt")
datosProyectilAd = np.genfromtxt("adicionalProyectil.txt")
datos = np.cumsum(datosProyectilAd) # indices de los proyectiles
i0 = int(0)
i1 = int(datos[0])

plt.title ("Recorrido proyectil a 45º")
plt.grid()
plt.xlabel("Distancia (m)")
plt.ylabel("Altura (m)")
plt.plot(datosProyectil[i0:i1,0], datosProyectil[i0:i1,2])
plt.savefig('p45.png')

plt.figure()
plt.title ("Recorrido proyectil para diferentes ángulos")
plt.grid()
plt.xlabel("Distancia (m)")
plt.ylabel("Altura (m)")
for i in range(6):
	i0 = int(datos[i])
	i1 = int(datos[i+1])
	plt.plot(datosProyectil[i0:i1,0], datosProyectil[i0:i1,2], label=str((i+1)*10))
i0=int(datos[-1])
i1=-1
plt.plot(datosProyectil[i0:i1,0], datosProyectil[i0:i1,2], label=str(70))
plt.legend(loc='best')
plt.savefig('proyectiles.png')


