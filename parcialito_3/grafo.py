import random
from collections import deque

class Grafo:
  def __init__(self, dirigido = False):
    '''
    Constructor.

    Args:
      - 'dirigido' (bool) especifica si el grafo es o no dirigido. False por defecto.

    Consideraciones:
      - Todos los métodos de la clase Grafo trabajan con identificadores únicos (strings) para cada vértice. Cada vez que se deba trabajar con estos, los parámetros tienen el prefijo id_
    '''
    self.vertices = {}  # Se implementa con listas de adyacencias
    self.dirigido = dirigido
    self.cantidad_vertices = 0

  def obtener_vertices(self):
    '''
    Devuelve una tupla con todos los vértices.
    '''
    return tuple(self.vertices.keys())

  def obtener_vertice_aleatorio(self):
    '''
    Devuelve un vértice aleatorio (id) del grafo. Si no hay vértices en el grafo, devuelve None.
    '''
    vertices = self.obtener_vertices()
    return vertices[random.randint(0, self.cantidad_vertices - 1)] if self.cantidad_vertices != 0 else None

  def agregar_vertice(self, id_vertice):
    '''
    Agrega un nuevo vértice al grafo.
    Recibe el identificador único del vértice.
    
    Si ya existe un vértice en el grafo con el mismo nombre, devuelve False. True en caso de que se haya agregado correctamente.
    '''
    if self.vertice_pertenece(id_vertice):
      return False

    self.vertices[id_vertice] = {}
    self.cantidad_vertices += 1
    return True

  def borrar_vertice(self, id_vertice):
    '''
    Borra un vértice del grafo y todas las aristas salientes y entrantes a él. 
    Recibe el identificador único del vértice.
    
    Si el vértice no se encuentra en el grafo, arroja KeyError.
    '''
    if not self.vertice_pertenece(id_vertice):
      raise KeyError
      
    for v in self.vertices:
      if id_vertice in self.vertices[v]: 
        self.vertices[v].pop(id_vertice)  

    self.vertices.pop(id_vertice)
    self.cantidad_vertices -= 1
    return id_vertice
  
  def agregar_arista(self, id_origen, id_destino, peso = 1):
    '''
    Agrega una nueva arista que conecta dos vértices. Devuelve True si se agregó la arista correctamente, False en caso contrario (la arista ya existía).
    Recibe el identificador único de ambos vértices y (opcionalmente) el peso de la arista.

    El peso de la arista debe ser distinto distinto de 0.

    Si alguno de los vértices no se encuentran en el grafo, arroja KeyError.
    '''
    if not self.vertice_pertenece(id_origen) or not self.vertice_pertenece(id_destino):
      raise KeyError

    if self.obtener_peso_arista(id_origen, id_destino) or peso == 0 or id_origen == id_destino: # Si la arista existe, o el peso recibido es 0
      return False

    self.vertices[id_origen][id_destino] = peso

    if not self.dirigido:
      self.vertices[id_destino][id_origen] = peso

    return True

  def borrar_arista(self, id_origen, id_destino):
    '''
    Borra la arista que conecta origen con destino.
    Recibe el identificador único de ambos vértices.

    Si alguno de los vértices no se encuentran en el grafo, arroja KeyError.
    '''
    del self.vertices[id_origen][id_destino]  # El operador 'del' arroja un KeyError si no encuentra lo que se intenta eliminar.

  def obtener_peso_arista(self, id_origen, id_destino):
    '''
    Devuelve el peso de la arista que une a los vertices origen y destino. Si la arista no existe, devuelve 0.
    Recibe el identificador único de ambos vértices.

    Si alguno de los vértices no se encuentran en el grafo, arroja KeyError.
    '''
    if not self.vertice_pertenece(id_origen) or not self.vertice_pertenece(id_destino):
      raise KeyError

    return self.vertices[id_origen][id_destino] if id_destino in self.vertices[id_origen] else 0 

  def obtener_adyacentes(self, id_vertice):
    '''
    Devuelve una tupla con todos los vertices adyacentes al vertice recibido por parámetro.
    Recibe el identificador único del vértice.

    Si el vértice no se encuentra en el grafo, arroja KeyError
    '''
    if not self.vertice_pertenece(id_vertice):
      raise KeyError

    return tuple(self.vertices[id_vertice].keys())

  def son_adyacentes(self, vertice_a, vertice_b):
    '''
    Devuelve True si vertice_b es adyacente al vertice_a. False en caso contrario.
    Recibe el identificador único de ambos vértices.

    Arroja KeyError en caso de que alguno de los vertices no pertenezcan al grafo.

    Si el grafo es dirigido, la adyacencia verifica que (a)---->(b), es decir, b es adyacente de a, pero no al revés.
    '''
    if not self.vertice_pertenece(vertice_a) or not self.vertice_pertenece(vertice_b):
      raise KeyError

    return vertice_b in self.vertices[vertice_a]  # Dirigido o no, es indistinto.

  def vertice_pertenece(self, id_vertice):
    '''
    Devuelve True si el vértice pertenece al grafo. False en caso contrario
    Recibe el identificador único del vértice.
    '''
    return id_vertice in self.vertices 

  def grado_entrada(self, id_vertice):
    '''
    Recibe el identificador de un vértice y devuelve su grado de entrada

    Si el vertice no existe, arroja KeyError
    '''
    if id_vertice not in self.vertices: 
      raise KeyError

    if not self.dirigido:
      return self.grado_salida(id_vertice)
    else:
      res = 0
      for v in self.vertices:
        if id_vertice in self.vertices[v]:
          res += 1
      return res

  def grado_salida(self, id_vertice):
    '''
    Recibe el identificador de un vértice y devuelve su grado de salida

    Si el vertice no existe, arroja KeyError
    '''
    return len(self.vertices[id_vertice].keys())

  def __iter__(self):
    '''
    Itera todos los vertices del grafo
    '''
    return iter(self.vertices.keys())

  def __len__(self):
    '''
    Devuelve la cantidad de vértices en el grafo.
    '''
    return self.cantidad_vertices

  def __del__(self):
    '''
    Destruye el grafo
    '''
    self.vertices = None
    self.cantidad_vertices = None
    self.dirigido = None

  def recorrido_aleatorio(self, n, id_origen = None):
    '''
    Devuelve una tupla con un recorrido aleatorio de 'n' elementos realizado sobre el grafo.
    Recibe:
      - n: cantidad de elementos a recorrer. Este parámetro es una cota superior, es decir, puede devolver hasta n vértices. Podrían ser menos.
      - id_origen (opcional): si se quiere comenzar desde un vertice en especial. Si el origen no se encuentra, arroja KeyError.
    '''
    resultado = []

    actual = id_origen if id_origen else self.obtener_vertice_aleatorio()
    n = n if n > self.cantidad_vertices else self.cantidad_vertices

    for _ in range(0, n):
      resultado.append(actual)
      adyacentes = self.obtener_adyacentes(actual)
      adyacentes_len = len(adyacentes)
      if adyacentes_len == 0: break
      actual = adyacentes[random.randint(0, adyacentes_len - 1)]

    return resultado

  def __bfs(self, visitados, padres, orden, origen):
    cola = deque()
    cola.append(origen)

    while len(cola):
      actual = cola.popleft()
      for adyacente in self.obtener_adyacentes(actual):
        if adyacente not in visitados:
          visitados.add(adyacente)
          padres[adyacente] = actual
          orden[adyacente] = orden[actual] + 1
          cola.append(adyacente)
    
    return visitados, padres, orden

  def bfs(self, origen = None):
    '''
    Realiza un recorrido del grafo utilizando la técnica BFS.  
    Recibe (opcionalmente) un id de origen por el cual comenzar. Si este no re recibe, se usa uno aleatorio.

    Devuelve dos diccionarios, uno de padres y otro de orden.
    '''
    visitados = set()
    padres = {}
    orden = {}

    if not origen:
      origen = self.obtener_vertice_aleatorio()
   
    orden[origen] = 0
    padres[origen] = None
    visitados.add(origen)

    visitados, padres, orden = self.__bfs(visitados, padres, orden, origen)

    for v in self:
      if v not in visitados:
        visitados.add(v)
        padres[v] = None
        orden[v] = 0
        visitados, padres, orden = self.__bfs(visitados, padres, orden, v)

    return padres, orden

  def dfs(self, origen = None):
    '''
    Realiza un recorrido siguiendo la técnica del DFS.
    Recibe un origen (opcionalmente).
    Devuelve dos diccionarios, uno de padres y otro de orden.
    '''
    visitados = set()
    padres = {}
    orden = {}

    if not origen:
      origen = self.obtener_vertice_aleatorio()
    
    orden[origen] = 0
    padres[origen] = None
    visitados.add(origen)

    visitados, padres, orden = self.__dfs(visitados, padres, orden, origen)

    for v in self:
      if v not in visitados:
        visitados.add(v)
        padres[v] = None
        orden[v] = 0
        visitados, padres, orden = self.__dfs(visitados, padres, orden, v)
    
    print(padres)
    print("")
    print(orden)
    #return padres, orden
  
  def __dfs(self, visitados, padres, orden, origen):
    for adyacente in self.obtener_adyacentes(origen):
      if adyacente not in visitados:
        visitados.add(adyacente)
        padres[adyacente] = origen
        orden[adyacente] = orden[origen] + 1
        visitados, padres, orden = self.__dfs(visitados, padres, orden, adyacente)
    return visitados, padres, orden