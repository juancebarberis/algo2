'''
Se cuenta con un grafo en el que sus aristas tiene peso 1 o 2, únicamente. Implementar un algoritmo que permita obtener el camino mínimo de un vértice hacia todos los demás, en tiempo O(V + E).
'''
from grafo import Grafo
from collections import deque
import math
import time

def camino_minimo(grafo, origen):
    '''
    El origen es obligatorio. Porque sí.
    '''
    d = {}  # Dic de distancia
    for v in grafo:
        d[v] = None
    d[origen] = 0

    for v in grafo:
        if v == origen: continue
        d[v] = distancia(grafo, origen, v)

    return d


def distancia(grafo, origen, destino):
    dist = {}
    for v in grafo: dist[v] = math.inf
    dist[origen] = 0
    cola = deque()
    cola.append(origen)
    while len(cola):
      v = cola.popleft()
      for w in grafo.obtener_adyacentes(v):
        if dist[v] + grafo.obtener_peso_arista(v, w) < dist[w]:
          dist[w] = dist[v] + grafo.obtener_peso_arista(v, w)
          cola.append(w)

    return dist[destino]

def main():
  t1 = time.time()
  grafo = Grafo()
  grafo.agregar_vertice("Juan")
  grafo.agregar_vertice("Chino")
  grafo.agregar_vertice("Lucho")
  grafo.agregar_vertice("Sere")
  grafo.agregar_vertice("Tiago")
  grafo.agregar_vertice("Messi")
  grafo.agregar_vertice("Maradona")
  grafo.agregar_vertice("Pele")

  grafo.agregar_arista("Juan", "Chino", 1)
  grafo.agregar_arista("Juan", "Pele", 2)
  grafo.agregar_arista("Chino", "Lucho", 2)
  grafo.agregar_arista("Lucho", "Sere", 1)
  grafo.agregar_arista("Lucho", "Maradona", 1)
  grafo.agregar_arista("Sere", "Tiago", 2)
  grafo.agregar_arista("Sere", "Messi", 2)
  grafo.agregar_arista("Sere", "Maradona", 1)

  print(camino_minimo(grafo, "Chino"))
  t2 = time.time()
  print("Tomó: "+ str(t2 - t1) + "ms")

if __name__ == "__main__":
    main()

'''
Podemos decir que la complejidad del algoritmo es O(V+E) ya que no necesitamos el Heap para el camino
'''