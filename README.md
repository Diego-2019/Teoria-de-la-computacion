<h1 align="center">Teoría de la Computación </h1>

<!--Crear el indice-->
<h2 align="center">Indice</h2>

- [Automata paridad](#automata-paridad)
- [Primer bloque](#primer-bloque)
  - [1. Universo](#1-universo)

# Automata paridad
``paridad.cpp`` es un código de ejemplo sobre autómatas que verifica que una cadena tenga un numero par de 0's y 1's usando un switch case y funciones para mostrar diferentes formas de programar un automata. 

El automata implementado es el siguiente:
<p align="center">
 <img src="Images/Automata paridad.png" alt="Automata de paridad" width="300"/>
</p>

Para poder utilizar este código solo debe compilarse mediante el siguiente comando:
```
g++ paridad.cpp -o paridad
```
una vez creado el ejecutable podrá utilizarse.


# Primer bloque

## 1. Universo
El programa ``universo.cpp`` genera y analiza el universo de cadenas binarias sobre el alfabeto $\Sigma = {a,b}$ considerando todas las longitudes desde 0 hasta n.
Formalmente la salida corresponde al conjunto $L = \cup_{k=0}^n \Sigma^k$

> **📑Ejemplo con $n = 4$**
> 
> $L = \{\epsilon, a, b, aa, ab, ba, bb, aaa, ..., bbbb\}$ 
> 
> donde $\epsilon$ es la cadena vacía.

El valor de $n$ puede ser especificado por el usuario o determinado automáticamente por el programa (rango permitido: $0 \leqslant n \leqslant 1000$).

El software permite operar en dos modos:
- **Modo automático:** genera el universo de cadenas para valores de $n$ seleccionados automáticamente.
- **Modo manual:** el usuario introduce el valor de $n$ que desea analizar.

Después de cada operación, el programa pregunta si se desea calcular para otro valor de $n$ o finalizar la ejecución.

El programa tiene como salida 2 archivos:
- ``permutaciones.txt``: Contiene el conjunto completo de cadenas generadas, en notación de conjunto.
- ``ocurrencias.csv``: Contiene el numero de ocurrencias de "a" por cadena.

Para poder utilizar este código solo debe compilarse mediante el siguiente comando:
```
g++ universo.cpp -o universo
```
una vez creado el ejecutable podrá utilizarse.

Alternativamente se crearon 2 códigos extra que ocupan el archivo ``ocurrencias.csv`` para análisis: uno en Python para potencias pequeñas y uno en MATLAB para potencias más grandes, aunque se recomienda no usar dichos códigos ya que dependiendo de los recursos de la PC puede trabarse incluso con el código de MATLAB debido a la cantidad de cadenas que podrían generarse.

El script en Python es ideal para valores de $n$ pequeños ($n \leqslant 15$).
Para valores de $n$ mayores (hasta donde la memoria RAM lo permita), el script en MATLAB aprovecha optimizaciones de manejo de matrices, pero aun así el tiempo de ejecución y consumo de memoria pueden volverse prohibitivos para $n$ grandes.

> **📝Nota** 
>
> Se intentó graficar con el código de MATLAB en una laptop con 16 GB de RAM con un $n = 28$ pero el sistema se volvió tan lento que era casi imposible realizar alguna acción.

En caso de querer graficar usando estos scripts se debe hacer lo siguiente:
- Para Python:
    ```
    python graficas.py
    ```
- Para MATLAB:
    - Abre el archivo `graficas.m` en MATLAB y ejecútalo (por ejemplo, con el botón "Run" o desde la consola con `graficas`).

Ambos scripts requieren que el archivo `ocurrencias.csv` esté en el mismo directorio.

<!-- ## 2. Buscador -->