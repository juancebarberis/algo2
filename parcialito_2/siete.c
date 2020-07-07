/*
(★★) Implementar el TDA MultiConjunto. Este es un Conjunto que permite más de una aparición de un elemento, por lo que eliminando una aparición, el elemento puede seguir perteneciendo. Dicho TDA debe tener como primitivas:

- multiconj_t* multiconj_crear(): crea un multiconjunto. A fines del parcialito, no es necesario implementar la primitiva de destruir.

- bool multiconj_guardar(multiconj_t* multiconj, char* elem): guarda un elemento en el multiconjunto. Devuelve true si se pudo guardar el elemento correctamente, false en caso contrario.

- bool multiconj_pertenece(multiconj_t* multiconj, char* elem): devuelve true si el elemento aparece al menos una vez en el conjunto.

- bool multiconj_borrar(multiconj_t* multiconj, char* elem): elimina una aparición del elemento dentro del conjunto. Devuelve true si se eliminó una aparición del elemento.

Dar la estructura del TDA y la implementación de las 4 primitivas marcadas, de forma tal que todas sean \mathcal{O}(1)O(1).
*/

typedef struct multiconj
{
  hash_t* hash;
} multiconj_t;


multiconj_t* multiconj_crear()
{
  multiconj_t* multiconj = malloc(sizeof(multiconj_t));

  if(!multiconj) return NULL;

  multiconj->hash = hash_crear();

  if(!multiconj->hash) {
    free(multiconj);
    return NULL; 
  }

  return multiconj;
}

bool multiconj_guardar(multiconj_t* multiconj, char* elem)
{
  if(!elem) return false;

  if(hash_pertenece(multiconj->hash, elem)) 
    hash_guardar(multiconj->hash, elem, hash_obtener(multiconj->hash, elem) + 1);
  else
    hash_guardar(multiconj->hash, elem, 1);

  return true;
}

bool multiconj_pertenece(multiconj_t* multiconj, char* elem)
{
  return hash_pertenece(multiconj->hash, elem);
}

bool multiconj_borrar(multiconj_t* multiconj, char* elem)
{
  if(!elem) return false;

  int valor;

  if(hash_pertenece(multiconj->hash, elem)) {
    valor = hash_obtener(multiconj->hash, elem);
    if(valor == 1)  // Si solo hay una aparición, tenemos que borrar definitivamente la clave del hash.
      hash_borrar(multiconj->hash, elem);
    else
      hash_guardar(multiconj->hash, elem, valor - 1);
  }
  else
    return false;

  return true;
}

/**
 * Todo esto es O(1) porque está implementado con un Hash.
 * */