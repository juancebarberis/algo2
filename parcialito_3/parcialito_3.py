'''
Ejercicios:	1)	3)	5).
Padrón:105147
Nombre:Barberis, Juan Celestino.
'''

'''
1) Dado un grafo dirigido que representa un árbol genealógico, donde la arista (x, y) representa que x es padre o madre de
y, detectar si existen anomalías que sólo puedan darse por consecuencia de viajes en el tiempo. Por ejemplo, en un grafo con
aristas (x, y) e (y, x), el algoritmo debe devolver true. Indicar y justificar la complejidad del algoritmo, considerando
que tenemos n personas en nuestro árbol genealógico.
'''

from grafo import Grafo
from collections import deque

def validar_arbol_genealogico(grafo):
  '''
  Recibe un grafo que representa un arbol genealógico, devuelve True si no se encuentan anomalias, False en caso contrario.
  '''
  if len(grafo) == 0: return True

  visitados = set()
  padres = {}

  for v in grafo:
    if v not in visitados and existe_ciclo(grafo, v, padres, visitados):
      return False
  return True

def existe_ciclo(grafo, v, padres, visitados):
  '''
  Devuelve True si existe un ciclo para el vértice v del grafo. False caso contrario.
  '''
  cola = deque()
  cola.append(v)
  visitados.add(v)

  while len(cola):
    actual = cola.popleft()
    for w in grafo.obtener_adyacentes(actual):
      if w in visitados and w != padres[actual]:
        return True
      else:
        padres[w] = actual
        visitados.add(w)
        cola.append(w)
  return False

'''
Estas 'anomalías' serían que un hijo, tenga como adyacente a un superior, en ese caso estaríamos hablando de un ciclo. 
La complejidad de esto es igual a la de BFS, porque en sí lo es: O(N + E) donde N son las personas en el arbol, y E las aristas que las conectan.
'''


'''
3) Existe un barrio en el cual sus integrantes son muy chismosos, hasta con sus propios asuntos. Cuando X habla con Y le
cuenta todas sus novedades (incluso algunas que no debería contar). Y no sólo eso: también le cuenta todas las novedades
que se ha enterado de todos los demás miembros de la comunidad (que le hayan contado). Un detalle importante: no
necesariamente porque X le cuente a Y todo lo que sabe, Y le va a contar algo. Es posible (y hasta bastante probable) que
no lo haga. Pero una vez que una persona empieza a contarle cosas a otra, no puede evitar contarle todo lo que sepa. 
Se sabe también que cuando alguno de estos miembros se entera de algo ilegal, quiere denunciarlo. Ahora bien, el denunciante
puede tener sus propios trapitos sucios y tampoco quiere denunciar a alguien que pueda conocer sus secretos. Dada esta
información, se quiere saber cómo están conformados los grupos de personas que nunca se denunciarían entre sí.
Explicar cómo modelarías este problema utilizando grafos, cómo obtendrías estos grupos de personas y cuál sería la
complejidad de hacer todo ello. Hacer un breve seguimiento de ejemplo que propongas, con unas 6 personas.

SOLUCION:

Esto se podría modelar como un grafo no dirigido, donde los vértices sean las personas, y las aristas aparezcan si un sujeto A habla con B, aparecería la arista (A, B). No dirigido, porque se pueden hablar mutuamente, sin importar si uno no le quiere contar al otro, pueden hacerlo. 
Supongamos que tenemos un sujeto A, el denunciante, que quiere denunciar a B porque anda en cosas ilegales. Pero A también le contó a X, su vecina, que anduvo en algo raro hace unos meses. A no se puede arriesgar a que de alguna forma, lo que sabe X le llegue a B, porque lo puede usar en su contra. Y bueno, si yo tengo esto modelado como un grafo, me interesaría saber si el denunciante, o sea Aes punto de articulación, es decir, su remoción implica que aumenta la cantidad de componente conexas del grafo (grupo de personas en este caso). 

- VER ESQUEMA EN FOTO 1 -

Vemos en la imagen como podemos modelar un ejemplo de 6 personas en el barrio, y vemos un caso donde solo una le cuenta a la otra. 
Si quitaramos a A, podemos ver que salen dos grupos de personas, por una lado queda B (el denunciado), C y D, y por otro, X y H. Estas personas no se podrían comunicar entre sí, por ejemplo, X no podría ir a decirle a B que A le contó de sus macanas. 

Para ver si es punto de articulación: recorremos con la técnica de DFS, si el vértice es raíz y tiene más de 1 hijo o si alguno de sus hijos no tiene forma de llegar a los vértices "superiores" de la raíz, entonces es punto de articulación. 
Complejidad de hallar si un vértice en un grafo es punto de articulación: O(V+E) (V: vértices, E: aristas), ya que es básicamente un DFS con algunas condiciones sobre los resultados. 
'''

'''
5) Indicar si las siguientes afirmaciones son verdaderas o falsas. Justificar.
a. Al resolver el problema de maximización de flujo buscamos caminos entre la fuente y el sumidero en la red residual. Si
en dicho camino se utiliza una arista que no existe en el grafo original, significa que no podemos considerar ese camino
para aumentar el flujo total.
b. En un grafo no dirigido con pesos negativos, podemos aplicar el algoritmo de Bellman-Ford para obtener el camino
mínimo desde un vértice hacia todos los demás.
c. Podemos calcular el Árbol de tendido mínimo de un grafo no dirigido que tenga pesos negativos.


SOLUCION:

a) FALSO. Si hallamos un ciclo entre dos vértices, podemos agregar un vértice intermedio (por ende, agregamos también nuevas aristas) y son válidas en el cálculo de maximización.

b) FALSO. El algoritmo de Bellman-Ford solo funciona si el grafo es dirigido, y no interesa si hay pesos negativos. 

c) VERDADERO. Para calcular un arbol de tendido mínimo, y más si utilizamos Prim o Kruskal, no vamos a tener problemas con pesos negativos. Estos se basan en los pesos para, por ejemplo en Kruskal, ordena las aristas de menor a mayor. 
'''


