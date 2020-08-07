'''
Escribir una función bool es_bipartito(grafo) que dado un grafo no dirigido devuelva true o false de acuerdo a si es bipartito o no. Indicar y justificar el orden del algoritmo. ¿Qué tipo de recorrido utiliza?
'''

from grafo import Grafo
from collections import deque

def es_bipartito(grafo):
  '''
  Decide si un grafo es o no bipartito.
  Devuelve True|False.
  
  Precondición: el grafo debe ser no dirigido.
  '''
  color = {}
  VERDE = 1
  ROJO = 2

  for v in grafo:
    color[v] = None

  origen = grafo.obtener_vertice_aleatorio()
  color[origen] = 1

  q = deque()
  q.append(origen)

  while len(q):
    v = q.popleft()
    for w in grafo.obtener_adyacentes(v):
      if color[w] and color[w] == color[v]:
        return False
      if not color[w]:
        if color[v] == VERDE:
          color[w] = ROJO
        else:
          color[w] = VERDE
        q.append(w)
  return True

def prueba_1():
  grafo = Grafo()
  
  grafo.agregar_vertice("a")
  grafo.agregar_vertice("b")
  grafo.agregar_vertice("c")
  grafo.agregar_vertice("d")

  grafo.agregar_arista("a", "b")
  grafo.agregar_arista("b", "c")
  grafo.agregar_arista("c", "d")
  print(es_bipartito(grafo))

def prueba_2():
  grafo = Grafo()
  
  grafo.agregar_vertice("a")
  grafo.agregar_vertice("b")
  grafo.agregar_vertice("c")

  grafo.agregar_arista("a", "b")
  grafo.agregar_arista("b", "c")
  grafo.agregar_arista("a", "c")
  print(es_bipartito(grafo))

if __name__ == "__main__":
  prueba_1()  # Es bipartito  : True
  prueba_2()  # NO es bipartito : False

'''
El algoritmo tiene una complejidad lineal, de O(V+E). Realiza un recorrido de tipo BFS.
'''