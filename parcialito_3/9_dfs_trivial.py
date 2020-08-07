'''
Matías está en Barcelona y quiere recorrer un museo. Su idea es hacer un recorrido bastante lógico: empezar en una sala (al azar), luego ir a una adyacente a ésta, luego a una adyancente a la segunda (si no fue visitada aún), y así hasta recorrer todas las salas. Cuando no tiene más salas adyacentes para visitar (porque ya fueron todas visitadas), simplemente vuelve por donde vino buscando otras salas adyacentes. Teniendo un grafo no dirigido, que representa el mapa del museo (donde los vértices son salas, y las aristas (v, w) indican que las salas v y w se encuentran conectadas), implementar un algoritmo que nos devuelva una lista con un recorrido posible de la idea de Matías para visitar las salas del museo. Indicar el recorrido utilizado y el orden del algoritmo. Justificar.
'''

from grafo import Grafo
from collections import deque

def dfs(grafo):
  visitados = set()
  orden = {}
  padres = {}

  origen = grafo.obtener_vertice_aleatorio()
  orden[origen] = 0
  padres[origen] = None

  visitados, padres, orden = _dfs(grafo, visitados, padres, orden, origen)

  for v in grafo:
    for w in grafo.obtener_adyacentes(v):
      if v not in visitados:
        orden[w] = orden[v] + 1
        padres[w] = v
        visitados, padres, orden = _dfs(grafo, visitados, padres, orden, w)
  return padres, orden

def _dfs(grafo, visitados, padres, orden, vertice):
  visitados.add(vertice)
  for w in grafo.obtener_adyacentes(vertice):
    if w not in visitados:
      orden[w] = orden[vertice] + 1
      padres[w] = vertice
      visitados, padres, orden = _dfs(grafo, visitados, padres, orden, w)
  return visitados, padres, orden

def main():
  grafo = Grafo()
  grafo.agregar_vertice("a")
  grafo.agregar_vertice("b")
  grafo.agregar_vertice("c")
  grafo.agregar_vertice("d")
  grafo.agregar_vertice("e")
  grafo.agregar_vertice("f")
  grafo.agregar_vertice("g")

  grafo.agregar_arista("a", "b")
  grafo.agregar_arista("b", "e")
  grafo.agregar_arista("e", "d")
  grafo.agregar_arista("d", "e")
  grafo.agregar_arista("a", "g")
  grafo.agregar_arista("a", "g")
  grafo.agregar_arista("f", "e")
  grafo.agregar_arista("g", "f")
  grafo.agregar_arista("d", "a")

  print(dfs(grafo))

if __name__ == "__main__":
  main()