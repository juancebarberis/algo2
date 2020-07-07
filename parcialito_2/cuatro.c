/*
4. Implementar una primitiva para el ABB, que devuelva una lista con las claves del
mismo, ordenadas tal que si insertáramos las claves en un ABB vacío, dicho ABB
tendría la misma estructura que el árbol original.
*/

lista_t* claves_abb(abb_t* abb) 
{
  lista_t* resultado = lista_crear();

  if(!resultado) return NULL;

  _claves_abb(abb->raiz, lista);

  return resultado;
}

void _claves_abb(nodo_t* actual, lista_t* lista)
{
  if(!actual) return;

  lista_insertar_al_final(lista, actual);

  _claves_abb(actual->izq, lista);
  _claves_abb(actual->der, lista);
}