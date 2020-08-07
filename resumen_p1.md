# Resumen Parcialito 1

_Temas:_ Punteros. Memoria estática y dinámica. Recursividad. Algoritmos de división y conquista. Cálculo de eficiencia. Teorema Maestro. TDAs. Pilas. Colas. Listas. Iteradores de listas. Ordenamientos comparativos y no comparativos.

## Punteros

Bueno, a esta altura de la cursada, los punteros no son para nada un problema.

## Memoria estática y dinámica

Lo mismo. No nos van a tomar esto porque es muy simple, lo vimos en todas las entregas que hicimos anteriormente.

## Recursividad

Podríamos decir que este tema también ya lo tenemos dominado, pero no es así, siempre nos la pueden poner acá... 

Decimos que un algorítmo es recursivo si podemos escribirlo de tal forma que se pueda resolver llamandose así mismo hasta llegar a una condición de corte. Llamamos a este el __caso base__, y es lo más importante a la hora de programar algo con recursividad, sino, nuestro programa no va a funcionar. 

Ejemplo de un algoritmo recursivo:

```python
def factorial(n):
  if n == 0: return 1
  return n * factorial(n - 1)
```

## División y Conquista

Consiste en resolver problemas utilizando la recursividad (a fines de la materia, se podría hacer iterativo), diviendo los problemas en __B__ cantidad de partes, y llamando recursivamente __A__ veces al algoritmo para resolver cada parte. 

- El primer algoritmo estudiado para explicar DyC es Búsqueda binaria: 

```python
def busqueda_binaria(arreglo, fin, inicio, elemento):
  if inicio > fin: 
    return -1

  medio = (inicio + fin) // 2

  if arreglo[medio] == elemento:
    return medio
  
  if arreglo[medio] < elemento:
    return busqueda_binaria(arreglo, medio + 1, fin, elemento)
  else:
    return busqueda_binaria(arreglo, inicio, medio - 1, elemento)
```

El algoritmo se encarga de buscar un elemento en un arreglo, diviendo en 2 el arreglo por la mitad, y llamando recursivamente para cada mitad. 

Notar que en cada llamado, compara con el elemento medio, y que si no es igual al elemento a buscar, continua llamando recursivamente pero para la parte indicada, descartando toda una mitad. 

- Otro algoritmo que se puede plantear por DyC es el de obtener el máximo de un arreglo

```python
def maximo(arreglo, inicio, fin):
  if inicio == fin:
    return arreglo[inicio]
  medio = (inicio + fin) // 2
  max_izq = maximo(arreglo, inicio, medio)
  max_der = maximo(arreglo, medio + 1, fin)

  return (max_izq > max_der) ? max_izq : max_der
```

- Luego tenemos dos algoritmos de ordenamiento que también utilizan división y conquista
    - Mergesort
    - Quicksort

## Teorema maestro

Nos permite calcular la eficiencia temporal de un algoritmo mediante el analisis de: __A__ cantidad de llamados recursivos, __B__ cantidad de partes en las que dividimos el problema y __C__ el costo computacional de armar la solución. 

Con esta información podemos utilizar el teorema para deducir la complejidad de una manera muy sencilla.

La ecuación general es: 
```math
T(n) = A T(n/B) + O(n^C)

A = cantidad de llamados recursivos
B = proporción del tamaño original
C = costo de partir y juntar
n = cantidad de elementos  
```

__ESTO SOLO SIRVE PARA ALGORITMOS DE DYC__

Entonces se cumple que: 
```math
log B (A) <  C   =>   O (n^C)

log B (A) = C    =>   O (n^C log (n))

log B (A) > C    =>   O (n^(log B (A))) *n elevado a todo el logaritmo*

```

Si nos piden que el ejercicio cumpla con una cierta complejidad, deberíamos partir del teorema para diseñar el algoritmo. Fijamos el A, B y C, y nos ponemos a desarrollar.

En [este video](https://www.youtube.com/watch?v=VplAn4NHYA0&list=PLLfC2vEod54J-QgGG3bJ0vxaMtJGKXZ63&index=7) nos explican cómo calcular la complejidad de los algoritmos ejemplificados anteriormente. 

# Ordenamientos

## Estabilidad

Un algoritmo de ordenamiento es estable cuando se asegura que el orden relativo de los elementos de misma clave es idéntico a la salida que a la entrada.

## Comparativos

Son los algoritmos que ordenan realizando comparaciones. Ejemplo: Selección, Inserción, Mergesort, Quicksort, Burbujeo, etc. La precondición principal es que los elementos sean comparables.

### __Algoritmo de Selección__

![seleccion](https://upload.wikimedia.org/wikipedia/commons/9/94/Selection-Sort-Animation.gif)

El ordenamiento por selección (Selection Sort en inglés) es un algoritmo de ordenamiento que requiere __O(n²)__ operaciones para ordenar una lista de n elementos.

### __Algoritmo de Inserción__

![insercion](https://upload.wikimedia.org/wikipedia/commons/thumb/0/0f/Insertion-sort-example-300px.gif/250px-Insertion-sort-example-300px.gif)

En el mejor de los casos, el arreglo está inicialmente en orden, el algoritmo solo hace una pasada entonces la complejidad es __O(n)__. Y en el peor caso con el arreglo ordenado con el criterio contrario se obtiene una complejidad temporal cuadrática, del orden de __O(n²)__

### __Algoritmo de Mergesort__

![mergesort](https://upload.wikimedia.org/wikipedia/commons/thumb/c/cc/Merge-sort-example-300px.gif/220px-Merge-sort-example-300px.gif)

El algoritmo de ordenamiento por mergesort es un algoritmo de ordenamiento externo estable basado en la técnica de división y conquista. Es de complejidad __O(n log n)__.

### __Algoritmo de Quicksort__

![quicksort](https://upload.wikimedia.org/wikipedia/commons/6/6a/Sorting_quicksort_anim.gif)

El algoritmo de Quicksort se basa en elegir un elemento al azar llamado __pivote__ desde el cual vamos a divir el arreglo en dos partes. Elemento menores que el pivote y mayores a este. Así, de forma recursiva para cada mitad. Mientras las sub-listas generadas a partir de este proceso tengan más de un elemento, se puede seguir realizando. Una vez que finalizamos, si juntamos todas las sublistas, queda ordenada. 

El caso promedio de este algoritmo es de __O(n log n)__. El peor caso sería si elegimos mal el pivote, por ejemplo, al final de la lista, siempre nos quedaría una sublista vacía, y el ordenamiento se degeneraría a una complejidad de __O(n²)__.

### Un algoritmo de ordenamiento comparativo nunca puede ser mejor que __O(n log n)__.

<hr>

## No comparativos

Estos algoritmos se basan en tener información adicional sobre los datos que se intentan ordenar. No son siempre aplicables y/o convenientes para todos los casos. 

Los algoritmos que vamos a ver puntualmente son tres:
- Counting Sort
- Radix Sort
- Bucket Sort

### Counting Sort

- Nos permite ordenar datos enumerables (discretos).
- Debe ser un rango acotado y conocido (o fácilmente obtenible).

[Seguimiento de Counting Sort ordenando un mazo de cartas.](https://www.youtube.com/watch?v=56xR0814To0&list=PLLfC2vEod54KFwQxsBhUvkxICBMCvo7p0&index=3)

¿Counting Sort es estable? __Sí__.

Complejidad: O(n + k) <br> n: elementos | k: rango.

### Radix Sort

- Trabaja con elementos a ordenar que tengan varios dígitos o componentes.
- Utiliza un ordenamiento auxiliar que __tiene que ser estable__. Idealmente, que sea lineal.
- Cada elemento tiene que tener la misma cantidad de cifras, o muy similar. 
- Ordena (utilizando el ordenamiento auxiliar) de la __cifra menos significativa__ a la __más significativa__.

#### Ejemplo: ordenar números.

- Arreglo [703, 042, 012, 712, 507, 555, 505, 005].

Utilizamos como ordenamiento interno Counting Sort, versión simplificada.

Ordenamos primero por cifra menos significativa (unidades).

Nos queda temporalmente esto [012, 042, 712, 703, 555, 505, 005, 507].

Ordenamos por la siguiente cifra significativa (decenas). 

Nos queda temporalmente [703, 505, 005, 507, 012, 712, 042, 555].

Si ahora vamos con las centenas, el arreglo nos queda: [005, 012, 042, 505, 507, 555, 703, 712]

¡Y esto ya está ordenado! 
<hr>

__Complejidad: O( l(n+k) )__ donde l es la cantidad de dígitos. Y suponiendo que siempre usamos Counting Sort por dentro.

### Bucket Sort

- En este caso vamos a querer ordenar algo que no tenga un rango enumerable, pero sí una distribución conocida. 

- Los datos deben ser uniformemente distribuidos. 

- Este algoritmo es útil más que nada si no podemos aplicar alguno de los anteriores (por ej. números decimales).

[Videos con seguimientos del algoritmo. Cartas y jugador de fútbol.](https://www.youtube.com/watch?v=M_dSzwhRvvU&list=PLLfC2vEod54KFwQxsBhUvkxICBMCvo7p0&index=6)

__Complejidad: O(n + b)__. Con __n__ cantidad de elementos, y __b__ cantidad de baldes.



