import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Leer los datos
data = pd.read_csv('Teoria de la computacion\\Programa 1\\ocurrencias.csv')

# Elimina espacios al inicio y al final de los nombres de las columnas
data.columns = data.columns.str.strip()

# Crear una nueva figura con un tamaño específico para ambas gráficas
plt.figure(figsize=(14, 10))  # Ajusta el tamaño en pulgadas para dar espacio a ambos gráficos

# Primera gráfica: Valores originales
plt.subplot(2, 1, 1)  # 2 filas, 1 columna, primera gráfica
plt.plot(data['Cadena'], data['OcurrenciaA'], 'o-', markerfacecolor='#1f77b4', lw=0.5)
plt.legend(['Ocurrencia de A'], loc='best')
plt.xlabel('Cadena')
plt.ylabel('Ocurrencias de A')
plt.title('Ocurrencias de A por Cadena')
# plt.grid()  # Cuadrícula
plt.ylim([-.5, data['OcurrenciaA'].max() + .5])  # Ajusta los límites del eje Y, agregando un poco de espacio por arriba

# Segunda gráfica: logaritmo aplicado a cada valor
ocurrenciaA_log = data['OcurrenciaA'].astype(float)
# Encuentra los índices donde la ocurrencia es mayor a cero
indices_no_cero = ocurrenciaA_log > 0
ocurrenciaA_log[indices_no_cero] = np.log10(ocurrenciaA_log[indices_no_cero])

plt.subplot(2, 1, 2)  # 2 filas, 1 columna, segunda gráfica
plt.plot(data['Cadena'], ocurrenciaA_log, 'o-', markerfacecolor='#1f77b4', lw=0.5)
plt.xlabel('Cadena')
plt.ylabel('Log10 de Ocurrencias de A')
plt.title('Log10 de Ocurrencias de A por Cadena')
plt.legend(['Log10 de Ocurrencia de A'], loc='best')
# plt.grid() # Cuadrícula
plt.ylim([-.5, np.max(ocurrenciaA_log) + 1])  # Ajusta el límite superior para dar espacio adicional

plt.tight_layout()  # Ajusta automáticamente el espaciado entre subplots
plt.show()  # Muestra la figura con ambos gráficos
