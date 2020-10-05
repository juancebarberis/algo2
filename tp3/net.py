from grafo import Grafo
import utils
from random import shuffle
import sys
import time
from heapq import heappop, heappush, heapify
from collections import deque

COLOR_VERDE = '\033[92m'
COLOR_ROJO = '\033[91m'
COLOR_NORMAL = '\033[0m'

class Net:
  def __init__(self, datos, debug = False):
    '''
    Inicializa una instancia de Netstats. 
    Recibe por parámetro una lista de listas, con los datos del programa.
    '''
    self.grafo = Grafo(True)
    self.debug = debug
    self.comandos = { # Comandos del programa con sus respectivos argumentos
      # "comando": (tuple) (cantidad minima de parametros, cantidad maxima)
      "listar_operaciones": [0, 0],
      "camino": [2, 2],
      "mas_importantes": [1, 1],
      "conectados": [1, 1],
      "ciclo": [2, 2],
      "lectura": [1, "INF"],
      "diametro": [0, 0],
      "rango": [2, 2],
      "comunidad": [1, 1],
      "navegacion": [1 ,1],
      "clustering": [0, 1]
      }
    
    # Diccionarios de cache
    self.__conectados_cache = set()
    self.__pr_cache = {}
    self.__diametro_chache = []
    
    for linea in datos:  #  Se procesa la linea (lista).
      for item in linea:  # Cada elemento de la lista se agrega al grafo
        self.grafo.agregar_vertice(item)

      for i in range(0, len(linea)):  # Se agregan las conexiones entre los vertices agregados
        if i != len(linea) - 1:
          self.grafo.agregar_arista(linea[0], linea[i+1])

  def procesar_comando(self, entrada):
    '''
    Se encarga de procesar el comando de entrada y lo dirige a su correspondiente método.
    '''
    entrada = entrada.split()
    comando = entrada.pop(0)
    if comando == "":
      raise KeyboardInterrupt
    elif comando in self.comandos:
      self.params = (" ".join(entrada)).split(",")
      if self.params[0] == "": self.params.pop(0)

      actual = self.comandos[comando]
      if actual[1] == "INF": actual[1] = len(self.grafo)

      if len(self.params) < actual[0] or len(self.params) > actual[1]:
        print(f"{COLOR_ROJO}ERROR {COLOR_NORMAL} - parámetros incorrectos para comando {comando}.")
      else:
        try:
          if self.debug: 
            print(f"Comando: {comando}")
            t0 = round(time.time() * 1000)
          getattr(self, comando)()
          if self.debug: 
            t1 = round(time.time() * 1000)
            print(f"{COLOR_VERDE}PASS{COLOR_NORMAL}: {comando} tardó {str(t1 - t0)}ms")
        except KeyError:
          print(f"{COLOR_ROJO}ERROR{COLOR_NORMAL} - No existe el/los datos.")
    else:
      print(f"{COLOR_ROJO}ERROR{COLOR_NORMAL} - Comando incorrecto")

  '''
  Métodos de cada comando.
  Hay un método por cada item de self.comandos.
  La validacion de parámetros básica se realiza en self.procesar_comando().
  '''

  def listar_operaciones(self):
    for comando in self.comandos:
      if comando == "listar_operaciones": continue
      print(comando)
  
  def camino(self):
    origen = self.params[0]
    destino = self.params[1]
    padres, orden = utils.bfs(self.grafo, origen)

    lista = []
    actual = destino
    while actual != origen:
      if actual == None: 
        print("No se encontro recorrido")
        return
      else:
        lista.insert(0, actual)
        actual = padres[actual]
    
    resultado = origen + " -> "
    for elemento in lista:
      if elemento == destino: continue
      resultado += elemento + " -> "
    print(resultado + destino)
    print(f"Costo: {orden[destino]}")

  def diametro(self):
    if self.__diametro_chache:
      print(self.__diametro_chache[0])
      print("Costo: " + str(self.__diametro_chache[1]))
      return

    grafo = self.grafo
    diametro = 0
    for v in grafo:
      padre, distancia = utils.bfs(grafo, v)
      for w in grafo:
        if diametro < distancia[w]:
          inicio = v
          fin = w
          diametro = distancia[w]
          padre_definitivo = padre
    
    lista = []
    actual = fin
    while actual != inicio:
      lista.insert(0, actual)
      actual = padre_definitivo[actual]
    
    camino = inicio + " -> "
    for pagina in lista:
      if pagina == fin: continue
      camino += pagina + " -> " 
    camino += fin
    
    self.__diametro_chache.append(camino)
    self.__diametro_chache.append(diametro)
    print(camino)
    print("Costo: " + str(diametro))

  def rango(self):
    origen = self.params[0]
    n = int(self.params[1])

    print(utils.vertices_en_radio_n(self.grafo, origen, n))
  
  def comunidad(self):
    grafo = self.grafo
    pagina = self.params[0]
    if not grafo.vertice_pertenece(pagina): return None

    iteraciones = 50 # Condición de corte que decidimos
    label = {} 
    padres_adyacentes = utils.padres(grafo)

    indice = 0
    for v in grafo:
      label[v] = indice
      indice += 1

    orden_aleatorio = list(grafo.obtener_vertices())
    label_nuevo = label.copy()
    for i in range(0,iteraciones): 
      shuffle(orden_aleatorio)
      for v in orden_aleatorio:
        if len(padres_adyacentes[v]) == 0: continue
        label_nuevo[v] = utils.label_mayor_frecuencia(padres_adyacentes[v], label) # Usamos el label de la iteración anterior!
        
      label = label_nuevo.copy() # Para actualizar asincrónicamente
  
    resultado = []
    comunidad_pag = label_nuevo[pagina]
    for v in grafo:
      if label_nuevo[v] == comunidad_pag:
        resultado.append(v)
    print(", ".join(resultado))

  def navegacion(self):
    actual = self.params[0]
    resultado = []
    if actual not in self.grafo:
      print(f"ERROR - {actual} no se encuentra en el sistema")      
    else:
      for _ in range(0, 21):
        resultado.append(actual)
        adyacentes = self.grafo.obtener_adyacentes(actual)
        if(len(adyacentes) == 0): break
        actual = adyacentes[0]
      print(" -> ".join(resultado))

  def lectura(self):
    grafo_aux = Grafo(True)
    
    for param in self.params:
      grafo_aux.agregar_vertice(param)

    for param in self.params:
      for w in self.grafo.obtener_adyacentes(param):
        if w in self.params:
          grafo_aux.agregar_arista(w, param)

    grados = utils.grado_entrada(grafo_aux)
    
    q = deque()

    for v in grafo_aux:
      if grados[v] == 0:
        q.append(v)

    res = []

    while len(q):
      v = q.popleft()
      res.append(v)
      for w in grafo_aux.obtener_adyacentes(v):
        grados[w] -= 1
        if grados[w] == 0:
          q.append(w)

    if len(res) == len(grafo_aux):
      print(", ".join(res))        
    else:
      print("No existe forma de leer las paginas en orden")

  def clustering(self):
    grafo = self.grafo
    pagina = None
    if self.params:
      pagina = self.params[0]
    
    if pagina:
      print("%1.3f" % round(utils.obtener_clustering_v(grafo, pagina),3))
      return

    clustering_total = 0
    for v in grafo:
      clustering_total += utils.obtener_clustering_v(grafo, v)
    print("%1.3f" % round(clustering_total / len(grafo),3))

  def conectados(self):
    pagina = self.params[0]

    # Si esta consulta ya se realizó antes 
    if pagina in self.__conectados_cache:
      utils.imprimir_json("conectados_"+pagina)
      return

    # Vamos a tocar un poco la recursión en esta ejecución porque se puede poner peluda
    recursion_limit = sys.getrecursionlimit()
    sys.setrecursionlimit(100000)

    visitados = set()
    pila = []
    mas_bajo = {}
    orden = {}
    apilados = set()
    componentes = []

    orden[pagina] = 0
    visitados, pila, apilados, orden, componentes, mas_bajo, indice = utils.tarjan(self.grafo, pagina, visitados, pila, apilados, orden, mas_bajo, componentes, 0)
    resultado = []
    

    for c in componentes:
      if pagina not in c: continue
      for elemento in c:
        resultado.append(elemento)
    
    utils.guardar_json("conectados_"+pagina, resultado)
    self.__conectados_cache.add("conectados_"+pagina)
    utils.imprimir_json("conectados_"+pagina)
    
    # Volvemos a la normalidad, no queremos heridos
    sys.setrecursionlimit(recursion_limit)

  def mas_importantes(self):
    n = int(self.params[0])

    if self.__pr_cache:
      print(list(self.__pr_cache.keys())[:n])
      return

    precision = 6 # Cuanto mayor este número, más preciso es pero más tarda
    grafo = self.grafo

    padres_adyacentes = utils.padres(grafo)
    vertices = list(grafo.obtener_vertices())
    shuffle(vertices)
    grado_salida = utils.grado_salida(grafo)

    d = 0.85  # Coeficiente de amortiguación
    primer_termino = (1 - d) / len(vertices)
    pr = {}  # Pagerank

    for v in grafo:
      pr[v] = primer_termino  # Inicializamos así los pr

    pr_nueva_iteracion = pr.copy()
    seguir_iterando = True
    while seguir_iterando:
      seguir_iterando = False
      for v in vertices:
        if not padres_adyacentes[v]: continue
        suma_prs_adyacentes_sobre_grado = 0
        for w in padres_adyacentes[v]:
          suma_prs_adyacentes_sobre_grado += pr[w] / grado_salida[w]
        nuevo_pr = primer_termino + d * suma_prs_adyacentes_sobre_grado
        if round(nuevo_pr,precision) != round(pr[v],precision): # Si no redondeamos tarda mucho en converger
          pr_nueva_iteracion[v] = nuevo_pr
          seguir_iterando = True

      pr = pr_nueva_iteracion.copy()
    #Ordenamos y printeamos los más importantes
    aux = sorted(pr.items(), key=lambda item: item[1], reverse = True)
    res = {k: v for k, v in aux}
    self.__pr_cache = res # Guardamos los resultados para usarlos en futuras llamadas
    print(list(res.keys())[:n]) 
  
  def ciclo(self):
    # Vamos a tocar un poco la recursión en esta ejecución porque se puede poner peluda
    recursion_limit = sys.getrecursionlimit()
    sys.setrecursionlimit(100000)

    pagina = self.params[0]
    n = int(self.params[1])
    ciclo = utils.ciclo_de_vertices(self.grafo, pagina, n)
    if ciclo:
      print(" -> ".join(ciclo))
    else:
      print("No se encontro recorrido")
    
    # Volvemos a la normalidad, no queremos heridos
    sys.setrecursionlimit(recursion_limit)