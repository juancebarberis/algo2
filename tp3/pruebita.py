from grafo import Grafo
import utils
import sys
from heapq import heapify, heappop, heappush
from random import shuffle
from collections import deque


# def mas_importantes(self):
#   n = int(self.params[0])
#   grafo = self.grafo
#   heap_minimos = [] # Contendrá a las n páginas más importantes

#   padres_adyacentes = utils.padres(grafo)
#   vertices = list(grafo.obtener_vertices())
#   shuffle(vertices)
#   grado_salida = utils.grado_salida(grafo)

#   d = 0.85 # Coeficiente de amortiguación
#   primer_termino = (1 - d) / len(vertices)
#   pr = {} # Pagerank
#   i = 0
#   for v in grafo:
#     pr[v] = primer_termino # Inicializamos así los pr
#     if i < n:
#       heappush(heap_minimos, (pr[v], v)) # Aprovechamos para llenar el heap con n elementos, que luego iremos cambiando
#       i += 1

#   pr_nueva_iteracion = pr.copy()
#   seguir_iterando = True
#   i=0
#   while seguir_iterando:
#     print(i)
#     i+=1
#     seguir_iterando = False
#     for v in vertices:
#       if len(padres_adyacentes[v]) == 0: continue
#       suma_prs_adyacentes_sobre_grado = 0
#       for w in padres_adyacentes[v]:
#         suma_prs_adyacentes_sobre_grado += pr[w] / grado_salida[w]

#       nuevo_pr = primer_termino + d * suma_prs_adyacentes_sobre_grado

#       if nuevo_pr != pr[v]:
#         pr_nueva_iteracion[v] = nuevo_pr
#         seguir_iterando = True

#         #Heap
#         j=0
#         for _,vert in heap_minimos: # Si v está en el heap hay que actualizar el pr nomás
#           if v == vert:
#             heap_minimos[j] = (nuevo_pr, vert)
#             heapify(heap_minimos)
#             j+=1
#             break
#           j+=1
#         if (pr[v],v) in heap_minimos:

#         if j == 0: # Si v no estaba en el heap
#           pr_min_heap,vert_min_heap = heappop(heap_minimos)
#           if nuevo_pr > pr_min_heap:
#             heappush(heap_minimos, (nuevo_pr, v))
#           else:
#             heappush(heap_minimos, (pr_min_heap, vert_min_heap))
#     pr = pr_nueva_iteracion.copy()


def conectados(grafo, pagina):
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
    visitados, pila, apilados, orden, componentes, mas_bajo, indice = utils.tarjan(
        grafo, pagina, visitados, pila, apilados, orden, mas_bajo, componentes, 0)
    resultado = []

    for c in componentes:
        if pagina not in c:
            continue
        for elemento in c:
            resultado.append(elemento)

    print(resultado)
    print(f"Len resultado: {len(resultado)}. Se esperan ~44764")

    # Volvemos a la normalidad, no queremos heridos
    sys.setrecursionlimit(recursion_limit)


def lectura(grafo, params):
    grafo_aux = Grafo(True)

    for param in params:
        grafo_aux.agregar_vertice(param)

    for param in params:
        for w in grafo.obtener_adyacentes(param):
            if w in params:
                grafo_aux.agregar_arista(w, param)

    grados = {}
    for v in grafo_aux:
        grados[v] = 0

    for v in grafo_aux:
        for w in grafo_aux.obtener_adyacentes(v):
            grados[w] += 1

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
    print(grafo_aux)
    for param in params:
        if param not in res:
            print("No existe forma de leer las paginas en orden")
            return

    params.reverse()
    print(", ".join(params))


def main():
    v1 = "1"
    v2 = "2"
    v3 = "3"
    v4 = "4"
    v5 = "5"
    v6 = "6"
    v7 = "7"
    v8 = "8"
    v9 = "9"

    grafo = Grafo(True)
    grafo.agregar_vertice(v1)
    grafo.agregar_vertice(v2)
    grafo.agregar_vertice(v3)
    grafo.agregar_vertice(v4)
    grafo.agregar_vertice(v5)
    grafo.agregar_vertice(v6)
    grafo.agregar_vertice(v7)
    grafo.agregar_vertice(v8)
    grafo.agregar_vertice(v9)

    grafo.agregar_arista(v1, v2)
    grafo.agregar_arista(v5, v3)
    grafo.agregar_arista(v1, v3)
    grafo.agregar_arista(v1, v4)
    grafo.agregar_arista(v5, v2)
    grafo.agregar_arista(v5, v6)
    grafo.agregar_arista(v6, v3)
    grafo.agregar_arista(v3, v1)
    grafo.agregar_arista(v3, v4)
    grafo.agregar_arista(v4, v5)
    grafo.agregar_arista(v7, v8)
    grafo.agregar_arista(v8, v7)

    # print(utils.grado_salida(grafo))
    #mas_importantes(grafo, 9)
    lectura(grafo, [v1, v2, v3, v4, v5, v6, v7, v8, v9])


main()
