from grafo import Grafo
from utils import *
import time
import random

def pruebas_grafo():
  '''
  Pruebas unitarias para el TDA Grafo.
  '''
  prueba_inicial_casos_borde()
  prueba_grafo_dirigido()

def prueba_inicial_casos_borde():
  print("Iniciando prueba de casos borde...")
  t_inicial = time.time()
  #
  grafo = Grafo()

  assert type(grafo.obtener_vertices()) == tuple, "El método obtener_vertices debe devolver una tupla"
  assert len(grafo.obtener_vertices()) == 0, "El método obtener_vertices debe estar vacío"
  assert len(grafo) == 0, "El método __len__ debe ser 0"
  assert not grafo.vertice_pertenece("perro"), "El vértice no pertenece al grafo. Grafo vacío!"
  assert devuelve_exception(grafo.borrar_vertice, "perro"), "Intento de borrado. El vertice 'perro' no existe en el grafo"
  assert devuelve_exception(grafo.borrar_arista, "perro", "gato"), "Intento de borrado. La arista que conecta perro y gato no existe en el grafo"
  assert devuelve_exception(grafo.obtener_peso_arista, "perro", "gato"), "Los vértices no existe en el grafo"
  assert devuelve_exception(grafo.obtener_adyacentes, "perro"), "Intento de adyacencia. El vertice 'perro' no existe en el grafo"
  assert devuelve_exception(grafo.son_adyacentes, "perro", "gato"), "Intento de adyacencia. El vertice 'perro' y el vértice 'gato' no existen en el grafo"
  
  assert grafo.agregar_vertice("perro"), "No fue posible agregar el vértice 'perro'"
  assert grafo.vertice_pertenece("perro"), "El vértice pertenece al grafo"
  assert len(grafo) == 1, "Len de grafo distinto de 1"
  assert type(grafo.obtener_adyacentes("perro")) == tuple, "Los adyacentes de perro deben ser una tupla vacía"
  assert len(grafo.obtener_adyacentes("perro")) == 0, "Los adyacentes de perro deben ser una tupla vacía"
  assert devuelve_exception(grafo.son_adyacentes, "perro", "gato"), "Intento de adyacencia 2. El vertice 'perro' existe, pero el vértice 'gato' no."

  assert grafo.agregar_vertice("gato"), "No se pudo agregar el vertice 'gato'"
  assert not grafo.agregar_vertice("gato"), "El vértice ya existe"
  assert len(grafo) == 2, "Len de grafo distinto de 2"
  assert grafo.vertice_pertenece("gato"), "El vertice fue agregado, pero no pertenece"

  assert grafo.agregar_arista("perro", "gato"), "Agregar arista que conecta 'perro' y 'gato'"
  assert grafo.son_adyacentes("perro", "gato"), "'perro' y 'gato' deben ser adyacentes"
  assert grafo.obtener_peso_arista("perro", "gato") == 1, "El peso de la arista creada debe ser 1"
  assert grafo.obtener_peso_arista("gato","perro") == 1, "El peso de la arista inversa (grafo no dirigido) debe ser 1"
  assert len(grafo.obtener_adyacentes("gato")) == 1 and len(grafo.obtener_adyacentes("perro")) == 1, "Ambos adyacentes deben ser len 1"
  assert grafo.obtener_adyacentes("gato")[0] == "perro" and grafo.obtener_adyacentes("perro")[0] == "gato", "Ambos adyacentes deben contenerse el uno a otro"

  assert not devuelve_exception(grafo.borrar_arista, "perro", "gato"), "Borrar arista"
  assert grafo.agregar_arista("perro", "gato"), "Agregar arista que conecta 'perro' y 'gato' de nuevo"
  assert grafo.borrar_vertice("perro"), "Borrar vertice 'perro'"
  
  assert len(grafo) == 1, "Len de grafo distinto de 1"
  assert grafo.borrar_vertice("gato"), "Borrar vertice 'gato'"
  assert len(grafo) == 0, "Len de grafo distinto de 0"
  # 
  t_final = time.time()
  print(f"Prueba finalizada. Total tiempo transcurrido {t_final - t_inicial}ms\n")

def prueba_grafo_dirigido():
  print("Iniciando prueba de grafo dirigido...")
  t_inicial = time.time()
  #
  grafo = Grafo(True)
  #La repr. grafica de este grafo está en esta imagen https://drive.google.com/file/d/12DVFpMLxQ4N6i2udXwfpu2y4kC55x91R/view?usp=sharing
  #Se supone que las aristas son vias de un sentido a las que se puede ir de una ciudad a otra. Por eso el grafo dirigido
  ciudades = (
    "caba",
    "la_plata",
    "cordoba",
    "entre_rios",
    "bahia_blanca",
    "santa_rosa",
    "bariloche",
    "mdq",
    "chile"
  )
  for ciudad in ciudades:
    assert grafo.agregar_vertice(ciudad), "No fue posible agregar la ciudad"
  
  assert len(grafo) == len(ciudades), "No se guardaron todos los vértices en el grafo"

  #Agregar las aristas
  assert grafo.agregar_arista("caba", "la_plata"), "No se pudo agregar la arista"
  assert grafo.agregar_arista("caba", "entre_rios"), "No se pudo agregar la arista"
  assert grafo.agregar_arista("la_plata", "bahia_blanca"), "No se pudo agregar la arista"
  assert grafo.agregar_arista("la_plata", "mdq"), "No se pudo agregar la arista"
  assert grafo.agregar_arista("bahia_blanca", "bariloche"), "No se pudo agregar la arista"
  assert grafo.agregar_arista("bariloche", "chile"), "No se pudo agregar la arista"
  assert grafo.agregar_arista("entre_rios", "santa_rosa"), "No se pudo agregar la arista"
  assert grafo.agregar_arista("entre_rios", "cordoba"), "No se pudo agregar la arista"
  assert grafo.agregar_arista("santa_rosa", "bariloche"), "No se pudo agregar la arista"
  assert grafo.agregar_arista("santa_rosa", "cordoba"), "No se pudo agregar la arista"
  assert grafo.agregar_arista("cordoba", "santa_rosa"), "No se pudo agregar la arista doble"
  # Vemos si las adyacencias de cada uno son correctas
  assert grafo.obtener_adyacentes("caba") == ("la_plata", "entre_rios"), "Adyacentes incorrectos"
  assert grafo.obtener_adyacentes("la_plata") == ("bahia_blanca", "mdq"), "Adyacentes incorrectos"
  assert grafo.obtener_adyacentes("bahia_blanca") == ("bariloche",), "Adyacentes incorrectos"
  assert grafo.obtener_adyacentes("bariloche") == ('chile',), "Adyacentes incorrectos"
  assert grafo.obtener_adyacentes("entre_rios") == ("santa_rosa", "cordoba"), "Adyacentes incorrectos"
  assert grafo.obtener_adyacentes("cordoba") == ("santa_rosa",), "Adyacentes incorrectos"
  
  assert not grafo.son_adyacentes("caba", "chile"), "No son adyacentes"
  assert grafo.son_adyacentes("bariloche", "chile"), "Son adyacentes"

  #grafo.bfs()
  #grafo.dfs()

  assert grafo.grado_entrada("caba") == 0
  assert grafo.grado_entrada("entre_rios") == 1
  assert grafo.grado_entrada("cordoba") == 2
  assert grafo.grado_entrada("bariloche") == 2

  assert grafo.grado_salida("caba") == 2
  assert grafo.grado_salida("entre_rios") == 2
  assert grafo.grado_salida("cordoba") == 1
  assert grafo.grado_salida("bariloche") == 1

  assert devuelve_exception(grafo.grado_entrada,"asldkjasldkja")
  assert devuelve_exception(grafo.grado_salida, "asldkjasldkja")
  #
  t_final = time.time()
  print(f"Prueba de grafo dirigido finalizada. Total tiempo transcurrido {t_final - t_inicial}ms\n")


if __name__ == '__main__':
  pruebas_grafo()
