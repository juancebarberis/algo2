'''
 La teoría de los 6 grados de separación dice que cualquiera en la Tierra puede estar conectado a cualquier otra persona del planeta a través de una cadena de conocidos que no tiene más de cinco intermediarios (conectando a ambas personas con solo seis enlaces). Suponiendo que se tiene un grafo G en el que cada vértice es una persona y cada arista conecta gente que se conoce (el grafo es no dirigido):

a. Implementar un algoritmo para comprobar si se cumple tal teoría para todo el conjunto de personas representadas en el grafo G. Indicar el orden del algoritmo.

b. Suponiendo que en el grafo G no habrán altas ni bajas de vértices, pero podrían haberla de aristas (la gente se va conociendo), explicar las ventajas y desventajas que tendría implementar al grafo G con una matriz de adyacencia.
'''

from grafo import Grafo
from collections import deque

'''
a)
'''

def cumple_teoria_seis_grados(grafo):
  '''
  Verifica si un grafo cumple con la teoría de los seis grados de separación.
  Devuelve True|False en caso de cumplirse o no.

  Precondición para Grafo: no dirigido y conexo.
  '''
  visitados = set()
  orden = {}
  q = deque()

  origen = grafo.obtener_vertice_aleatorio()
  orden[origen] = 0
  visitados.add(origen)
  q.append(origen)

  while len(q):
    v = q.popleft()
    for w in grafo.obtener_adyacentes(v):
      if w not in visitados:
        orden[w] = orden[v] + 1
        visitados.add(w)
        q.append(w)
  
  print(orden)

  for o in orden:
    if orden[o] > 5: 
      return False

  return True    

def main():
  grafo = Grafo()
  grafo.agregar_vertice("Juan")
  grafo.agregar_vertice("Chino")
  grafo.agregar_vertice("Lucho")
  grafo.agregar_vertice("Sere")
  grafo.agregar_vertice("Tiago")
  grafo.agregar_vertice("Messi")
  grafo.agregar_vertice("Maradona")
  grafo.agregar_vertice("Pele")

  grafo.agregar_arista("Juan", "Chino")
  grafo.agregar_arista("Juan", "Pele")
  grafo.agregar_arista("Chino", "Lucho")
  grafo.agregar_arista("Lucho", "Sere")
  grafo.agregar_arista("Lucho", "Maradona")
  grafo.agregar_arista("Sere", "Tiago")
  grafo.agregar_arista("Sere", "Messi")
  grafo.agregar_arista("Sere", "Messi")
  print("Comprobando...")
  print(cumple_teoria_seis_grados(grafo))

if __name__ == "__main__":
  main()

'''
El algoritmo tiene una complejidad de O(V + E) (complejidad de BFS implementado con listas)
'''

'''
b) La ventaja es que en una matriz de adyacencia, agregar una arista tiene un costo de O(1).
   Una desventaja sería que la matriz de adyacencia, tiene una complejidad cuadrática al agregar vértices.
'''