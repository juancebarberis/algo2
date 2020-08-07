'''
Un autor decidió escribir un libro con varias tramas que se puede leer de forma no lineal. Es decir, por ejemplo, después del capítulo 1 puede leer el 2 o el 73; pero la historia no tiene sentido si se abordan estos últimos antes que el 1.

Siendo un aficionado de la computación, el autor ahora necesita un orden para publicar su obra, y decidió modelar este problema como un grafo dirigido, en dónde los capítulos son los vértices y sus dependencias las aristas. Así existen, por ejemplo, las aristas (v1, v2) y (v1, v73).

Escribir un algoritmo que devuelva un orden en el que se puede leer la historia sin obviar ningún capítulo. Indicar la complejidad del algoritmo.
'''

from grafo import Grafo
from collections import deque

#resuelvo el ejercicio mediante orden topologico usando una especie de bfs

def orden_topo(grafo):
  res = []
  grados = {}
  for v in grafo:
    grados[v] = 0

  for v in grafo:
    for w in grafo.obtener_adyacentes(v):
      grados[w] += 1
  
  q = deque()
  
  for v in grafo:
    if grados[v] == 0:
      q.append(v)

  while len(q):
    v = q.popleft()
    res.append(v)
    for w in grafo.obtener_adyacentes(v):
      grados[w] -= 1
      if grados[w] == 0:
        q.append(w)
  if len(res) == len(grafo):
    return res
  else:
    return None

def main():
  grafo = Grafo(True)
  # El ejemplo nada que ver pero bueno, es lo que estaba en el video de la clase :D
  grafo.agregar_vertice("F1")
  grafo.agregar_vertice("F2")
  grafo.agregar_vertice("AM2")
  grafo.agregar_vertice("AL2")
  grafo.agregar_vertice("Algo1")
  grafo.agregar_vertice("Algo2")
  grafo.agregar_vertice("Proba")
  grafo.agregar_vertice("EstrCompu")
  grafo.agregar_vertice("AnNumerico")
  grafo.agregar_vertice("Taller")
  grafo.agregar_vertice("OrdDatos")

  grafo.agregar_arista("F1", "F2")
  grafo.agregar_arista("AM2", "F2")
  grafo.agregar_arista("AL2", "Proba")
  grafo.agregar_arista("AM2", "Proba")
  grafo.agregar_arista("Algo1", "Algo2")
  grafo.agregar_arista("AM2", "AnNumerico")
  grafo.agregar_arista("AL2", "AnNumerico")
  grafo.agregar_arista("Algo2", "AnNumerico")
  grafo.agregar_arista("Algo2", "EstrCompu")
  grafo.agregar_arista("Algo2", "OrdDatos")
  grafo.agregar_arista("EstrCompu", "OrdDatos")
  grafo.agregar_arista("EstrCompu", "Taller")
  grafo.agregar_arista("AnNumerico", "Taller")
  grafo.agregar_arista("F2", "EstrCompu")
  grafo.agregar_arista("AL2", "EstrCompu")

  print(orden_topo(grafo))

main()
  