<h1 align="center">Teoría de la Computación </h1>

<!--Crear el indice-->
<h2 align="center">Indice</h2>

- [Automata paridad](#automata-paridad)
- [Primer bloque](#primer-bloque)
  - [1. Universo](#1-universo)
  - [2. Buscador de palabras](#2-buscador-de-palabras)
- [Segundo bloque](#segundo-bloque)
  - [3. Automata de pila](#3-automata-de-pila)
  - [4. Backus-Naur](#4-backus-naur)
  - [5. Gramática no ambigua](#5-gramática-no-ambigua)
  - [6. Maquina de Turing](#6-maquina-de-turing)

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
El programa ``universo.cpp`` genera y analiza el universo de cadenas binarias sobre el alfabeto $\Sigma = \lbrace a,b \rbrace$ considerando todas las longitudes desde 0 hasta n.
Formalmente la salida corresponde al conjunto $L = \cup_{k=0}^n \Sigma^k$

> **📑Ejemplo con $n = 4$** \
> $L = \lbrace \epsilon, a, b, aa, ab, ba, bb, aaa, ..., bbbb \rbrace$ 
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

> **📝Nota** \
> Se intentó graficar con el código de MATLAB en una laptop con 16 GB de RAM con un $n = 28$ pero el sistema se volvió tan lento que era casi imposible realizar alguna acción.

En caso de querer graficar usando estos scripts se debe hacer lo siguiente:
- Para Python:
    ```
    python graficas.py
    ```
- Para MATLAB:
    - Abre el archivo `graficas.m` en MATLAB y ejecútalo (por ejemplo, con el botón "Run" o desde la consola con `graficas`).

Ambos scripts requieren que el archivo `ocurrencias.csv` esté en el mismo directorio.

## 2. Buscador de palabras
El programa `buscador.cpp` implementa un automata que reconoce todas las palabras del conjunto {feminal, feminazi, tonta, torta, vieja, feminista} dentro de un texto.

En primer lugar, se diseñó el autómata finito no determinista (NFA) correspondiente al conjunto de palabras objetivo. Posteriormente, para la implementación este NFA fue transformado en un autómata finito determinista (DFA) mediante el método de los subconjuntos creando y traduciendo la tabla de transiciones en el DFA.
<p align="center">
 <img src="Images/NFA buscador.png" alt="NFA buscador de palabras" width="600"/>
</p>
<p align="center">
 <img src="Images/Tabla de transiciones.png" alt="Tabla de transiciones" width="600"/>
</p>
<p align="center">
 <img src="Images/DFA buscador.png" alt="DFA buscador de palabras" width="600"/>
</p>

> **📑Ejemplo de palabras reconocidas** \
> Para el texto: \
> "Esa feminista y esa torta estaban con una feminazi y una vieja tonta"
>
> El programa detectará y contará las apariciones de cada palabra reservada, indicando su posición dentro del texto (numero de párrafo y numero de palabra).

El autómata recorre el texto carácter por carácter y utiliza el DFA para identificar, contar y ubicar cada aparición exacta de las palabras buscadas, especificando la posición donde fueron encontradas.

La ejecución del programa genera el archivo de salida `proceso.txt` el cual registra, para cada carácter leído, el estado actual del autómata, mostrando toda la secuencia de estados y transiciones recorridas durante el procesamiento del texto.

Adicionalmente, el programa genera con ayuda de un script en python una visualización gráfica del DFA utilizado para el reconocimiento de las palabras, permitiendo analizar su estructura y funcionamiento.

Para la compilación del programa se necesita tener los archivos `automata.py`, `html_txt.py`, y un archivo html (en este caso `temas de genero.html`) para lectura en el mismo directorio que el programa principal `buscador.cpp` y utilizar el siguiente comando:

```
g++ buscador.cpp -o buscador
```

Una vez creado el ejecutable se podrá utilizar el programa.

# Segundo bloque

## 3. Automata de pila
El programa ``stackAutomata.cpp`` implementa un automata de pila diseñado para reconocer el lenguaje libre de contexto:

$$L = \lbrace 0^n 1^n | n \geqslant 1 \rbrace$$

es decir, todas las cadenas que consisten en una secuencia de ceros seguida por una secuencia de unos, con igual cantidad de cada uno.

Las transiciones del autómata de pila son las siguientes:

- $\delta (q, 0, Z_0) = {(q, XZ_0)}$
Si estamos en el estado $q$, leemos un $0$ y el símbolo en el tope de la pila es $Z_0$, permanecemos en $q$ y apilamos una $X$ encima de $Z_0$.

- $\delta (q, 0, X) = {(q, XX)}$
Si estamos en $q$, leemos un $0$ y el tope es $X$, permanecemos en $q$ y apilamos otro $X$ (por cada $0$ leído, se apila un $X$).

- $\delta (q, 1, X) = {(p, \epsilon)}$
Si estamos en $q$, leemos un $1$ y el tope es $X$, cambiamos al estado $p$ y desapilamos un $X$ (por cada $1$ leído en este punto, se desapila un $X$).

- $\delta (p, 1, X) = {(p, \epsilon)}$
Si estamos en $p$, leemos un $1$ y el tope es $X$, permanecemos en $p$ y desapilamos un $X$ (por cada $1$, se desapila un $X$).

- $\delta (p, \epsilon, Z_0) = {(f, Z_0)}$
Si estamos en $p$, la entrada se ha consumido ($\epsilon$) y el tope es $Z_0$, pasamos al estado final $f$ y la pila solo contiene $Z_0$ (aceptación).

La cadena de entrada puede ser introducida manualmente por el usuario o generada aleatoriamente por el programa. En el modo automático, la longitud máxima de la cadena es de $100,000$ caracteres.

> **📑 Ejemplo de cadenas aceptadas** \
> $011$ → no aceptada \
> $0011$ → aceptada \
> $000111$ → aceptada \
> $00011$ → no aceptada

Si la cadena ingresada tiene longitud menor o igual a 10, el programa ofrece una animación visual del funcionamiento del autómata de pila, mostrando paso a paso las transiciones y el contenido de la pila.

A la salida del programa se genera el archivo ``transitions.txt`` el cual contiene el registro de la evaluación completa del automata a traves de IDs para la cadena procesada.

Para la compilación del programa se necesita tener el archivo ``graficoSA.py`` en el mismo directorio que el programa principal ``stackAutomata.cpp`` y utilizar el siguiente comando:

```
g++ stackAutomata.cpp -o stackAutomata
```

Una vez creado el ejecutable, podrá ejecutarse y seguir las instrucciones para ingresar la cadena manualmente o permitir que se genere automáticamente.

> **📝Nota** \
> El archivo ``gráficoSA.py`` es necesario para la animación del autómata cuando se procesan cadenas de longitud menor o igual a 10.

## 4. Backus-Naur
El programa ``backusNaur.cpp`` implementa una derivación automática de la gramática Backus-Naur que define un condicional IF en la siguiente forma:

$$S \quad \rightarrow \quad iCtSA$$

$$A \quad \rightarrow \quad ;eS \space | \space \epsilon $$

El programa genera derivaciones de la gramática hasta alcanzar un número de IF's determinado por el usuario o por la máquina (con un limite de 1000 derivaciones) y al final muestra estas derivaciones.

Además, el programa genera dos archivos, uno llamado ``derivations.txt`` que muestra el paso a paso de las derivaciones y otro llamado ``pseudocode.txt`` que contiene el pseudo-código de la cadena generada con la gramática.

Para la compilación del archivo solo basta con usar el siguiente comando:
```
g++ backusNaur.cpp -o backusNaur
```
Y para usarlo solo se debe ejecutar el archivo ``backusNaur.exe`` generado.

## 5. Gramática no ambigua
Este programa llamado ``unambiguousGram.cpp`` procesa la siguiente gramática no ambigua para paréntesis balanceados y evalúa cadenas proporcionadas por el usuario o generadas automáticamente:

$$B \quad \rightarrow \quad (RB \space | \space ε$$

$$R \quad \rightarrow \quad ) \space | \space (RR$$

La evaluación se realiza expandiendo los no terminales $B$ y $R$ conforme a las producciones, en función del símbolo de entrada que se está leyendo.

- $B \rightarrow (RB$: Si el símbolo esperado es ( desde el no terminal $B$, se genera un bloque que deberá cerrarse más adelante.
- $B \rightarrow \epsilon$: Al finalizar correctamente, $B$ puede vaciarse.
- $R \rightarrow)$: Cierre inmediato de un paréntesis abierto.
- $R \rightarrow (RR$: Anidación; desde $R$ puede iniciarse una nueva apertura que requerirá dos cierres.

La cadena de entrada puede ser introducida manualmente por el usuario o generada aleatoriamente por el programa (sesgo: más "(" en la primera mitad y más ")" en la segunda mitad para favorecer balanceo). La longitud máxima de la cadena es de 1,000 caracteres.

> **📑 Ejemplos** \
> Aceptadas: $(), \space (()), \space ()(),\space (()())$ \
> No aceptadas: $)(, \space ((), \space ())(, \space ())$

Durante la ejecución se registra paso a paso la evaluación: símbolo/no terminal evaluado, producción aplicada y cadena intermedia resultante.

A la salida del programa se genera el archivo ``steps.txt``, el cual contiene el registro completo de la evaluación para la cadena procesada.

Para la compilación del programa utilice el siguiente comando:
```
g++ unambiguousGram.cpp -o unambiguousGram
```
Una vez creado el ejecutable, podrá ejecutarse y seguir las instrucciones para ingresar la cadena manualmente o permitir que se genere automáticamente.

## 6. Maquina de Turing
El programa ``turingMachine.cpp`` implementa una máquina de Turing determinista para reconocer el lenguaje:

$$
L = \lbrace 0^n 1^n \mid n \geq 1 \rbrace
$$

es decir, cadenas formadas por una secuencia de ceros seguida de una secuencia de unos, con igual cantidad de cada símbolo.

La máquina utiliza el símbolo blanco $B$ para representar una celda vacía y las marcas $X$ y $Y$ para indicar los símbolos $0$ y $1$ que ya han sido procesados.

---

**Tabla de transiciones:**

| Estado | $0$           | $1$           | $X$           | $Y$           | $B$           |
| ------ | ------------- | ------------- | ------------- | ------------- | ------------- |
| $q_0$  | $(q_1, X, R)$ | —             | —             | $(q_3, Y, R)$ | —             |
| $q_1$  | $(q_1, 0, R)$ | $(q_2, Y, L)$ | —             | $(q_1, Y, R)$ | —             |
| $q_2$  | $(q_2, 0, L)$ | —             | $(q_0, X, R)$ | $(q_2, Y, L)$ | —             |
| $q_3$  | —             | —             | —             | $(q_3, Y, R)$ | $(q_4, B, R)$ |
| $q_4$  | —             | —             | —             | —             | —             |

**Descripción breve:**

* **q0**: Busca el primer $0$ sin marcar, lo marca como $X$ y avanza a la derecha ($q_1$). Si en cambio encuentra un $Y,$ pasa a la fase de comprobación final ($q_3$).
* **q1**: Avanza a la derecha buscando el primer $1$ sin marcar; al encontrarlo, lo marca como $Y$ y retrocede ($q_2$).
* **q2**: Retrocede hasta encontrar un $X,$ luego avanza de nuevo a $q_0$ para procesar el siguiente $0$.
* **q3**: Comprueba que el resto de símbolos sean solo $Y$ y termina en $q_4$ al encontrar $B$ (aceptación).
* **q4**: Estado de aceptación; la cadena es válida.

---

**Características del programa**

1. **Entrada de la cadena**

   * **Modo manual:** El usuario introduce una cadena de $0$ y $1$.
   * **Modo automático:** Se genera aleatoriamente una cadena de hasta $1,000$ caracteres (válida o inválida).

2. **Salida**

   * Se registra cada paso de la ejecución en un archivo de texto (`IDs.txt`) utilizando descripciones instantáneas.

3. **Animación para cadenas cortas**

   * Si la longitud de la cadena es $\leqslant 16$, el programa ejecuta una animación visual en Python (`TM_animation.py`), que muestra paso a paso la evolución de la cinta y el movimiento del cabezal.

> **📑 Ejemplos** \
> Aceptadas: $01$, $0011$, $000111$ \
> No aceptadas: $011$, $00011$, $111000$

Para compilar el programa solo hay que ejecutar el siguiente comando:
```
g++ turingMachine.cpp -o turingMachine
```
Se creara un ejecutable que podremos abrir para poder empezar a utilizar el programa.

Durante la ejecución:

* Elija modo manual o automático.
* Si la cadena tiene $\leqslant 16$ caracteres, se lanzará la animación de Python (requiere `TM_animation.py` en el mismo directorio).

> **📝Nota** \
> El programa principal está en C++ y la animación en Python. Asegúrese de que Python esté instalado y accesible.
