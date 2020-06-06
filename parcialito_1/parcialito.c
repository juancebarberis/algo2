/**************************************************************************************************************************************
 * 3. Implementar una primitiva para el TDA cola void** cola_multifondo(const cola_t* cola, size_t k) que reciba
una cola y devuelva un arreglo con los últimos k elementos que saldrían de la cola (los del fondo), en el orden que saldrían
de esta originalmente. En caso que la cola tenga menos de k elementos, rellenar con NULL al final de dicho arreglo. Por
ejemplo, si la cola tuviera [1, 2, 3, 4, 5] (primer elemento el 1), con k = 3 deberíamos obtener un arreglo [3, 4, 5].
La cola no puede ser modificada durante la ejecución de la primitiva. Indicar y justificar el orden de la primitiva. La
implementación del TDA es sobre un arreglo dinámico circular como la vista en clase, cuya estructura interna es:

typedef struct cola {
    void** datos;
    size_t capacidad;
    size_t inicio;
    size_t fin;
} cola_t;

*/

void **cola_multifondo(const cola_t *cola, size_t k)
{
    if(cola_esta_vacia(cola)) 
        return NULL;
    
    void** arreglo = calloc(k * sizeof(void*)); // Inicializa todos los valores en NULL por defecto

    if(!arreglo) 
        return NULL;

    if(cola->fin - k < 0) // Homologación de k, en caso de que sea mayor al tamaño de la cola
        k = k + (cola->fin - k);

    int j = 0;
    for(int i = cola->fin - k + 1; i < cola->fin + 1; i++)
    {
        arreglo[j] = cola->datos[i] ? cola->datos[i] : NULL;
        j++;
    }

    return arreglo;
}
/**
 * En este caso, la complejidad de esta primitiva es O(k) (en principio, sin contar con la llamada a calloc
 * ya que solo realizamos k operaciones, porque directamente vamos a la posición del arreglo datos donde queremos empezar a copiar los punteros.
 * */


/**************************************************************************************************************************************
 * 6. Se tiene un arreglo ordenado crecientemente en el que, para cada elemento, su siguiente está a una distancia K
(desconocida a priori). A dicho arreglo se le elimina un elemento del medio. Implementar un algoritmo que, por división y
conquista, obtenga en O(log n) el valor del elemento faltante. Justificar la complejidad del algoritmo implementado. Por
ejemplo, para [1,2,3,5,6] el faltante es el 4, y para [5,7,9,11,13,17] el faltante es 15.
*/

// Solución
int _hallar_faltante(int arreglo[], int inicio, int fin, int k)
{
    if(arreglo[inicio + 1] - arreglo[inicio] != k)
        return arreglo[inicio] + k;

    int medio = (inicio + fin) / 2;

    return _hallar_faltante(arreglo, medio, fin, k);
    /*
    int der = _hallar_faltante(arreglo, medio, fin, k);
    return der;
    */
}

//Wrapper function  
int hallar_faltante(int arreglo[], int largo)
{
    return _hallar_faltante(arreglo, 0, largo, arreglo[1] - arreglo[0]);
}

int main()
{
    int arreglo[] = {5, 7, 9, 11, 13, 17};
    hallar_faltante(arreglo, 5);
    int arreglo[] = {1, 2, 3, 5, 6};
    hallar_faltante(arreglo, 4);
    return 0;
}
/**
 * La complejidad de este algoritmo se podría explicar por medio del Teorema Maestro.
 * 
 * A: 1 -> llamados recursivos
 * B: 2 -> en cuántas partes se divide el arreglo
 * C: 0 -> costos extras de unir los resultados
 * 
 * Con esto, nos queda que el algoritmo es O(log n) ya que logaritmo en base 2 de 1 = 0, lo que confirma que el algoritmo es O(log n).
 * */

/************************************************************************************************************************************
 * 9. Implementar un algoritmo (en pseudocódigo) que ordene el padrón de alumnos de la facultad en O(n). Justificar la
complejidad del algoritmo implementado. Podés usar toda la información que conozcas de la realidad para que funcione lo
más rápido posible. Elegir 6 padrones de la planilla de asignación de ejercicios (incluyendo el tuyo) y hacerle un seguimiento
al algoritmo. Dicho seguimiento lo podés hacer como prefieras: sobre hojas de papel y adjuntando fotos al envío, escribiéndolo
sobre un archivo de texto, etc.

//Solución

/**
 * [104082, 104425, 105161, 105006, 105199, 105147]
 * 
 * Vamos a implementar una especie de Radix sort para ordenar los padrones. 
 * Sabemos que al menos la mayoría de los padrones tienen entre 5 y 6 dígitos.
 * 
 * Podemos empezar a realizar el ordenamiento por el último dígito (menos significativo) hasta el primero (más significativo):
 * 
 * Comenzando por el primer dígito, nos queda el siguiente arreglo: [105161, 104082, 104425, 105006, 105147, 105199] .
 * Analogamente avanzamos con el resto de los dígitos: [105006, 104425, 105147, 105161, 104082, 105199].
 * Continuando... [105006, 104082, 105147, 105161, 105199, 104425].
 * Continuando... [104082, 104425, 105006, 105147, 105161, 105199].
 * Continuando... [104082, 104425, 105006, 105147, 105161, 105199].
 * Finalmente nos queda así: [104082, 104425, 105006, 105147, 105161, 105199] queda ordenado de forma ascendente.
 * 
 * Pseudo-códido:

radix(padrones, 6);

pseudo_radix(arreglo, numero_elementos, numero_cifras_posibles)
{
    para cada numero_elementos:
        crear un arreglo con numero_cifras_posibles arreglos

    => cada arreglo dependiendo del numero_elementos sería: [0: {}, 1: {}, 2: {}, 3: {}... numero_cifras_posibles: {}]; 

    para cada elemento en el arreglo, realizar un slice sobre cada cifra (comenzando desde la menos significativa, en este caso el final)
    ubicar la cifra en el arreglo que le pertenece a la posición y dentro de la clave que le pertenece según la qué digito es y sobre qué cifra
    estamos mirando.

    => mirando el caso de un padrón en sus primeras dos pasadas: '105147' => [7: {'105147'}] y '105157' => [4: {'105147'}]
    así hasta llegar a el caso donde tenemos que ordenar utilizando un algoritmo auxiliar, cada arreglo que nos queda.
}

La complejidad de este algoritmo nos queda O(l(n+k)) donde n es la cantidad de elementos de nuestro arreglo, k la cantidad de digitos. 
*/