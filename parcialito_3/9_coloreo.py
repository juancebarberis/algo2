'''
Implementar un algoritmo que reciba un grafo y un número n que, utilizando backtracking, indique si es posible pintar cada vértice con n colores de tal forma que no hayan dos vértices adyacentes con el mismo color.
'''
from grafo import Grafo


def coloreo(grafo, n):
    colores = []
    for color in range(0, n):
        colores.append(color)

    return _coloreo(grafo, colores, grafo.obtener_vertices(), {}, 0)


def _coloreo(grafo, colores, vertices, coloreados, n):
    if len(grafo) == len(coloreados):
        return True

    for c in colores:
        coloreados[vertices[n]] = c
        if not es_valido(grafo, vertices[n], coloreados):
            #print("No es válido. Backtracking!")
            del coloreados[vertices[n]]
            continue
        if _coloreo(grafo, colores, vertices, coloreados, n + 1):
            return True

    del coloreados[vertices[n]]
    return False


def es_valido(grafo, v, coloreados):
    for w in grafo.obtener_adyacentes(v):
        if w in coloreados and coloreados[w] == coloreados[v]:
            return False
    return True


def main():
    grafo = Grafo()

    grafo.agregar_vertice("Arg")
    grafo.agregar_vertice("Bol")
    grafo.agregar_vertice("Bra")
    grafo.agregar_vertice("Uru")
    grafo.agregar_vertice("Chi")
    grafo.agregar_vertice("Per")
    grafo.agregar_vertice("Ecu")
    grafo.agregar_vertice("Col")
    grafo.agregar_vertice("Ven")
    grafo.agregar_vertice("Par")

    grafo.agregar_arista("Arg", "Chi")
    grafo.agregar_arista("Arg", "Uru")
    grafo.agregar_arista("Arg", "Par")
    grafo.agregar_arista("Arg", "Bra")
    grafo.agregar_arista("Arg", "Bol")

    grafo.agregar_arista("Bra", "Uru")
    grafo.agregar_arista("Bra", "Par")
    grafo.agregar_arista("Bra", "Col")
    grafo.agregar_arista("Bra", "Bol")
    grafo.agregar_arista("Bra", "Per")
    grafo.agregar_arista("Bra", "Ven")

    grafo.agregar_arista("Per", "Bol")
    grafo.agregar_arista("Per", "Ecu")
    grafo.agregar_arista("Per", "Col")
    grafo.agregar_arista("Per", "Chi")

    grafo.agregar_arista("Bol", "Par")
    grafo.agregar_arista("Bol", "Chi")

    grafo.agregar_arista("Ecu", "Col")

    grafo.agregar_arista("Col", "Ven")

    print(coloreo(grafo, 4))


if __name__ == "__main__":
    main()
