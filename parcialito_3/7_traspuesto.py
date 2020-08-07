'''
Proponer una función para calcular el grafo traspuesto G^TG de un grafo dirigido G. El grafo traspuesto G^TG posee los mismos vértices que G, pero con todas sus aristas invertidas (por cada arista (v, w) en G, existe una arista (w, v) en G^T. Indicar la complejidad para un grafo implementado con:
a. lista de adyancencias

b. matriz de adyacencias
'''

from grafo import Grafo
from collections import deque

def grafo_traspuesto(grafo):
  grafo_t = Grafo(True)

  for v in grafo: 
    grafo_t.agregar_vertice(v) 

  for v in grafo:
    for w in grafo.obtener_adyacentes(v):
      grafo_t.agregar_arista(w, v)
  
  return grafo_t

def main():
  grafo = Grafo(True)

  grafo.agregar_vertice("a")
  grafo.agregar_vertice("b")
  grafo.agregar_vertice("c")
  grafo.agregar_vertice("d")
  grafo.agregar_vertice("e")
  grafo.agregar_vertice("f")

  grafo.agregar_arista("a", "b")
  grafo.agregar_arista("a", "c")
  grafo.agregar_arista("a", "d")
  grafo.agregar_arista("d", "b")
  grafo.agregar_arista("c", "b")
  grafo.agregar_arista("c", "e")
  grafo.agregar_arista("e", "f")

  gt = grafo_traspuesto(grafo)
  print(gt.vertices)


if __name__ == "__main__":
    main()

'''
El algoritmo es muy simple en sí. Si simplemente recorrer todos los vertices y dar vuelta las aristas.
Como lo estamos haciendo sobre un nuevo grafo, la complejidad va a depender de la implementación que este tenga.

a_ En listas de adyacencia, agregar una arista y agregar un vértice nos cuesta O(V).
b_ En una matriz de adyacencia, agregar una arista es O(1) y agregar un vértice nos cuesta O(V²). 
'''