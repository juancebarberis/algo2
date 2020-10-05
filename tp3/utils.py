'''
Módulo de utilidades. 
'''

import csv
import json
from grafo import Grafo
from collections import deque
from random import randint

'''
Funciones de grafos
'''
def dfs(grafo, origen = None):
  '''
  Realiza un recorrido DFS.
  Recibe (opcionalmente) un id de origen por el cual comenzar. Si este no re recibe, se usa uno aleatorio.
  Devuelve dos diccionarios, uno de padres y otro de orden.
  '''
  visitados = set()
  padres = {}
  orden = {}

  if not origen:
    origen = grafo.obtener_vertice_aleatorio()
  
  padres[origen] = None
  orden[origen] = 0
  visitados.add(origen)

  visitados, padres, orden = __dfs(grafo, visitados, padres, orden, origen)

  for v in grafo:
    if v not in visitados:
      visitados.add(v)
      padres[v] = None
      orden[v] = 0
      visitados, padres, orden = __dfs(grafo, visitados, padres, orden, v)

  return padres, orden
  
def __dfs(grafo, visitados, padres, orden, origen):
  for adyacente in grafo.obtener_adyacentes(origen):
    if adyacente not in visitados:
      visitados.add(adyacente)
      padres[adyacente] = origen
      orden[adyacente] = orden[origen] + 1
      visitados, padres, orden = __dfs(grafo, visitados, padres, orden, adyacente)

  return visitados, padres, orden

def bfs(grafo, origen = None):
  '''
  Realiza un recorrido del grafo utilizando BFS.  
  Recibe (opcionalmente) un id de origen por el cual comenzar. Si este no re recibe, se usa uno aleatorio.
  Devuelve dos diccionarios, uno de padres y otro de orden.
  '''
  visitados = set()
  padres = {}
  orden = {}

  if not origen:
    origen = grafo.obtener_vertice_aleatorio()
  
  padres[origen] = None
  orden[origen] = 0
  visitados.add(origen)

  visitados, padres, orden = __bfs(grafo, visitados, padres, orden, origen)

  for v in grafo:
    if v not in visitados:
      visitados.add(v)
      padres[v] = None
      orden[v] = 0
      visitados, padres, orden = __bfs(grafo, visitados, padres, orden, v)

  return padres, orden

def __bfs(grafo, visitados, padres, orden, origen):
  cola = deque()
  cola.append(origen)

  while len(cola):
    actual = cola.popleft()
    for adyacente in grafo.obtener_adyacentes(actual):
      if adyacente not in visitados:
        visitados.add(adyacente)
        padres[adyacente] = actual
        orden[adyacente] = orden[actual] + 1
        cola.append(adyacente)

  return visitados, padres, orden

def grado_entrada(grafo):
  '''
  Exclusivamente para grafos dirigidos. Devuelve un diccionario con los grados de entrada de todos los vértices del grafo.
  '''
  grado_entrada = {}
  for v in grafo: 
    grado_entrada[v] = 0

  for v in grafo:
    for w in grafo.obtener_adyacentes(v):
      grado_entrada[w] += 1
  
  return grado_entrada

def grado_salida(grafo):
  '''
  Devuelve un diccionario con los grados de salida de todos los vértices del grafo.
  '''
  grado_salida = {}
  for v in grafo: 
    grado_salida[v] = 0

  for v in grafo:
    for w in grafo.obtener_adyacentes(v):
      grado_salida[v] += 1
  
  return grado_salida

def vertices_en_radio_n(grafo, origen, n):
  '''
  Devuelve la cantidad de vértices que se encuentran exactamente a n aristas de distancia del origen.
  '''
  resultado = 0
  visitados = set()
  visitados.add(origen)
  orden = {}
  orden[origen] = 0

  cola = deque()
  cola.append(origen)

  while len(cola):
    v = cola.popleft()
    if orden[v] == n:
      resultado += 1
    elif orden[v] > n:
      break

    for w in grafo.obtener_adyacentes(v):
      if w not in visitados:
        visitados.add(w)
        orden[w] = orden[v] + 1
        cola.append(w)
    
  return resultado

def padres(grafo):
  '''
  Exclusivamente para grafos dirigidos. Devuelve un diccionario cuyas claves son los vértices del grafo, y cuyos valores 
  son listas con los vértices cuyas aristas de salida llegan a dicho vértice.
  '''
  padres = {}
  for v in grafo:
    padres[v] = []
  
  for v in grafo:
    for w in grafo.obtener_adyacentes(v):
      padres[w].append(v)
  
  return padres

def label_mayor_frecuencia(vertices, label):
  '''
  Devuelve la etiqueta que aparece más frecuentemente entre toda la lista de vértices.
  '''
  frecuencia = {}
  for v in vertices:
    if label[v] not in frecuencia:
      frecuencia[label[v]] = 0
    frecuencia[label[v]] += 1

  label_mayor_freq = label[vertices[0]]
  for l in frecuencia:
    if frecuencia[l] > frecuencia[label_mayor_freq]:
      label_mayor_freq = l

  return label_mayor_freq

def obtener_clustering_v(grafo, vertice):
  '''
  Devuelve el coeficiente de clustering del vértice página en el grafo.
  '''
  adyacentes = set(grafo.obtener_adyacentes(vertice))
  if vertice in adyacentes: # Si v tiene un bucle lo removemos de adyacentes
    adyacentes.remove(vertice)

  if len(adyacentes) < 2: 
    return 0

  aristas_entre_adyacentes = 0
  for v in adyacentes:
    for w in grafo.obtener_adyacentes(v):
      if v == w: continue # No cuento los bucles
      if w in adyacentes:
        aristas_entre_adyacentes += 1
  
  largo_ady = len(adyacentes)
  return aristas_entre_adyacentes / (largo_ady*(largo_ady-1))

def tarjan(grafo, v, visitados, pila, apilados, orden, mas_bajo, componentes, indice):
  visitados.add(v)
  pila.append(v)
  apilados.add(v)
  mas_bajo[v] = orden[v]
  for w in grafo.obtener_adyacentes(v):
    if w not in visitados:
      orden[w] = indice + 1
      indice += 1
      visitados, pila, apilados, orden, componentes, mas_bajo, indice = tarjan(grafo, w, visitados, pila, apilados, orden, mas_bajo, componentes, indice)
      mas_bajo[v] = min(mas_bajo[v], mas_bajo[w])
    elif w in apilados:
      mas_bajo[v] = min(mas_bajo[v], orden[w])
  if mas_bajo[v] == orden[v]:
    nueva_componente = []
    while True:
      w = pila.pop()
      apilados.remove(w)
      nueva_componente.append(w)
      if v == w: break
    componentes.append(nueva_componente)

  return visitados, pila, apilados, orden, componentes, mas_bajo, indice

def ciclo_de_vertices(grafo, origen, n):
  '''
  Devuelve una lista con algún ciclo de n vertices en el grafo.
  '''
  visitados = set()
  visitados, camino, estado = _ciclo_de_vertices(grafo, origen, visitados, n, origen, [])
  return camino if estado else None

def _ciclo_de_vertices(grafo, v, visitados, n, origen, camino):
  visitados.add(v)
  camino.append(v)

  if origen in grafo.obtener_adyacentes(v) and len(camino) == n:
    camino.append(origen)
    return visitados, camino, True

  for w in grafo.obtener_adyacentes(v):
    if len(camino) >= n:
      break
    if w not in visitados:
      visitados, camino, estado = _ciclo_de_vertices(grafo, w, visitados, n, origen, camino)
      if estado: 
        return visitados, camino, True
  
  visitados.remove(v)
  camino.pop()
  return visitados, camino, False

'''
Funciones auxiliares
'''

def devuelve_exception(method, arg1, arg2 = None, err = KeyError):
  '''
  Devuelve True si es que el método devuelve error (KeyError por defecto). False en caso contrario.
  Utilizado para pruebas y ahorrar bloques try/except.
  '''
  try:
    if not arg2:
      method(arg1)
    else:
      method(arg1, arg2)
    return False
  except err:
    return True

def parse_tsv(filename):
  '''
  Parsea un archivo tsv. 
  Devuelve una lista de listas, donde cada lista corresponde a una linea del archivo.
  '''
  res = []
  with open(filename) as file:
    reader = csv.reader(file, delimiter="\t")
    for l in reader:
      res.append(l)
  return res

def guardar_json(nombre_archivo, datos):
  '''
  Recibe: (str) nombre del archivo a guardar y (dic/lista/tupla) datos.
  Se encarga de guardar el diccionario/lista/tupla datos, a un archivo.json.
  El archivo se guarda en la carpeta /cache
  '''
  with open("cache/"+nombre_archivo + ".json", mode="w", encoding='utf-8') as archivo_salida:
      json.dump(datos, archivo_salida, ensure_ascii=False, indent=4)

def imprimir_json(nombre_archivo):
  '''
  Recibe el nombre del archivo que se aloja en /cache y lo imprime
  '''
  with open("cache/"+nombre_archivo + ".json", mode="r", encoding="utf-8") as archivo:
    output = json.load(archivo)
    if type(output) == list:
      print(", ".join(output))
    else:
      print(output)

'''
Excepciones
'''

class ParametrosFaltantes(Exception):
  '''
  Excepción utilizada cuando no se reciben los parámetros necesarios para correr el programa
  '''
  def __init__(self, msj = "Faltan parámetros para inicializar el programa"):
    self.msj = msj
    super().__init__(self.msj)

  def __str__(self):
    return self.msj