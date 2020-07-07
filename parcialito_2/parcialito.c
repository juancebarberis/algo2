/**********************************
 * Nombre: Barberis, Juan Celestino
 * Padrón: 105147
 * */

/*************************************************************************************************************************************
2. Decidir si las siguientes afirmaciones son verdaderas o falsas, y justificar. 
a. Para implementar una primitiva que permita cambiar la función de prioridad de un Heap, la única implementación viable es en O(nlogn), sacando todos los elementos de dicho heap, cambiando la función, y volviendo a guardarlos (encolarlos). 
b. Si en un heap cuyo estado inicial es [10, 7, 5, 5, 6, 3, 4, 3, 2] se encola un 8, su estado final será [10, 8, 5, 
5, 7, 3, 4, 3, 2, 6]. 
c. Me convendría tener una implementación de Cola de Prioridad cuyo encolar sea O(1) aunque el desencolar sea O(n), 
en vez de la implementación usando Heaps. 

*/

/**
 * a. FALSO. Se puede hacer downheap desde la raiz, cambiando la funcion de comparación. Veo el actual, lo comparo con sus hijos, y
 * hago swap con el menor. De forma recursiva, haciendo esto para todos los elementos del arreglo, llegamos a una complejidad de 
 * O(n log n) (Hacemos n veces lo que cuesta downheap). Todo se puede hacer in-place, sin necesidad de sacar los elementos y volverlos a encolar.
 * 
 * b. VERDADERO.
 * 
 * c. FALSO. Conviene el Heap: al encolar tenemos una complejidad de O(log n), ya que debemos hacer upheap hasta dejar el 
 * heap balanceado. Y desencolar de un Heap, sale el elemento más prioritario, y lo que queda es hacer un swap con el último 
 * elemento del arreglo y hacer downheap para balancear el Heap, lo cual tiene también una complejidad de O(log n). 
 * Si bien el O(1) suena muy tentador, el O(log n) es mucho (mucho) mejor que un O(n).
 * */


/*************************************************************************************************************************************
3. Nu Tree es una conocida empresa de productos de botánica que adquirió su fama por ser pantalla de una estafa piramidal. La empresa vende fertilizantes que aseguran que tu huerta crecerá en pocos días. Para poder entrar a su red de ventas, tenés que sumar a 2 personas a la red. Cada una de ellas tiene a su vez 24hs para incluir a otras 2, y así sucesivamente. 
Los laboratorios de AlgoRW quieren analizar la red resultante, cuya información poseen en formato de un árbol binario que representa quién sumó a quién a la red. Se quiere, a través del nombre de una persona, obtener la lista de todos los contactos incorporados a partir de ella, ordenada por diferentes criterios (más abajo se distinguen). 
Implementar una primitiva lista_t* ab_debajo_de(ab_t* ab, const char* clave) que reciba una clave y devuelva todos los elementos debajo del nodo cuya clave es la indicada, en el orden que te corresponda según enunciado. Indicar y justificar la complejidad del algoritmo implementado. La estructura interna del árbol es: 
typedef struct ab { struct ab* izq; struct ab* der; char* clave; } ab_t; 
El orden debe ser: 

b. Niveles: Por ejemplo, llamando con la clave Jas en el árbol mostrado, la salida debe ser (exactamente): [Jas, Dato, 
Mile, Agus, Cami, Nacho]. 
*/

typedef struct ab { 
  struct ab* izq;
  struct ab* der;
  char* clave;
} ab_t; 

ab_t* buscar_ab(ab_t* actual, char* clave) 
{
  if(strcmp(actual->clave, clave) == 0) 
    return actual;

  buscar_ab(actual->izq, clave);
  buscar_ab(actual->der, clave);

  return NULL;  // No estoy seguro de este return. No logré comprender esta recursión en los casos donde no encuentro la clave.
}

lista_t* ab_debajo_de(ab_t* ab, const char* clave)
{
  lista_t* lista = lista_crear();

  if(!lista) return NULL;

  ab_t* nodo_buscado = buscar_ab(ab, clave);

  if(nodo_buscado) {
    lista_insertar_al_final(lista, nodo_buscado);
    _ab_insertar_hijos(nodo_buscado, lista);
  }

  return lista;
}

void _ab_insertar_hijos(ab_t* actual, lista_t* lista)
{
  if(!actual) return;

  if(actual->izq) lista_insertar_al_final(lista, actual->izq);

  if(actual->der) lista_insertar_al_final(lista, actual->der);

  _ab_insertar_hijos(actual->izq, lista);
  _ab_insertar_hijos(actual->der, lista);
}

/**
 * La complejidad de este algoritmo es O(n), con n la cantidad de elementos en el arbol.
 * Primero debemos buscar el ab_t correspondiente a nuestra clave, en el peor de los casos, recorremos todos los elementos del arbol. 
 * Y luego, tenemos que insertar en la lista, lo cual son operaciones de tiempo constante.
 * Contando todo el recorrido que podemos llegar a hacer, siempre recorremos todos los elementos, ya sea para buscar la clave, o para
 * insertarlas porque están por debajo de la clave hallada.
 * */

/************************************************************************************************************************************
4. Implementar una primitiva del Hash Cerrado que permita obtener una lista con las claves y valores existentes dentro del Hash. A fines del ejercicio, pueden suponer que en hash.h ya se encuentra definida una estructura typedef struct {const char* clave; void* dato; } hash_par_t;, y la lista debe ser de punteros a dicha estructura. Indicar y justificar la complejidad del algoritmo implementado. 
*/

typedef struct {
  const char* clave;
  void* dato; 
} hash_par_t;

hash_par_t* crear_par(hash_t* hash, char* clave) 
{
  hash_par_t* par = malloc(sizeof(hash_par_t));

  if(!par) return NULL;

  par->clave = clave;
  par->dato = hash_obtener(hash, clave);

  return par;
}

lista_t* lista_con_claves(hash_t* hash) 
{
  lista_t* lista = lista_crear();

  if(!lista) return NULL;

  hash_iter_t* iter = hash_iter_crear(hash);

  if(!iter) {
    lista_destruir(lista);
    return NULL;
  }

  while(hash_iter_avanzar(iter))
  {
    lista_insertar_al_final(lista, crear_par(hash, hash_iter_ver_actual(iter)));
  }

  return lista;
}

/**
 * La complejidad del algoritmo es O(n), n -> capacidad del hash. Ya que el iterador debe pasar por todas las claves. 
 * Cuando encontramos una clave, y no un espacio vacío/borrado, las operaciones son O(1), ya que solo alojamos memoria para el par y insertamos al final de la lista.
 * */