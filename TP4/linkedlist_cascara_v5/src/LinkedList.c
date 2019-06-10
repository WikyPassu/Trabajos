#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/LinkedList.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this;
    this = (LinkedList *)malloc(sizeof(LinkedList));
    if(this != NULL)
    {
        this->size=0;
        this->pFirstNode = NULL;
    }
    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL) ///Si la lista es diferente de NULL
    {
        returnAux = this->size; ///Mi retorno sera el tamaño actual de mi lista
    }

    return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
    Node* pNode = NULL; ///Creo un puntero pNode a NULL
    int i;

    if(this != NULL && nodeIndex >= 0 && nodeIndex < ll_len(this)) ///Si la lista es diferente de NULL y el indice del nodo pasado como parametro esta entre 0 y el tamaño de mi lista
    {
        pNode = this->pFirstNode; ///pNode apuntara al primer nodo de la lista
        for(i=0; i<nodeIndex; i++) ///Con el bucle for recorrere hasta llegar al indice del nodo pasado como parametro
        {
            pNode = pNode->pNextNode; ///Entonces, en cada iteracion, pNode se ira moviendo igualandolo al puntero del siguiente nodo. La ultima iteracion me permite obtener el nodo en el indice especificado
        }
    }

    return pNode;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex, void* pElement)
{
    int returnAux = -1;

    Node* pNewNode = (Node*) malloc(sizeof(Node)); ///Reservo espacio en memoria para un nuevo nodo
    Node* pAuxNode = NULL; ///Creo un nodo auxiliar que guardara la direccion de memoria del nodo anterior al pedido como parametro

    if(this != NULL && nodeIndex <= ll_len(this) && nodeIndex >= 0) ///Evaluo la lista y que el nodeIndex este entre 0 y el tamaño de la lista
    {
        if(pNewNode != NULL) ///Si se pudo reservar memoria para el nuevo nodo...
        {
            pNewNode->pElement = pElement; ///Al nuevo nodo le guardo el pElement del parametro
            pAuxNode = getNode(this, nodeIndex-1); ///Obtengo el nodo anterior al nodeIndex con getNode();

            if(nodeIndex == 0) ///En caso de que nodeIndex sea 0, me estaria refiriendo a la primer posicion de la lista
            {
                pNewNode->pNextNode = this->pFirstNode; ///Por lo tanto, el nuevo nodo apuntara al mismo nodo que la cabecera para no perder la referencia al resto de nodos
                this->pFirstNode = pNewNode; ///Y la cabecera apuntara a la direccion de memoria del nuevo nodo
            }
            else if(nodeIndex > 0 && nodeIndex < ll_len(this)) ///En caso de que nodeIndex no sea 0 ni el final de la lista, se trata de una adicion en el medio de los los nodos
            {
                pNewNode->pNextNode = pAuxNode->pNextNode; ///El nuevo nodo apuntara a donde apunta el nodo anterior al nodeIndex
                pAuxNode->pNextNode = pNewNode; ///Y el nodo anterior apuntara ahora a la direccion de memoria del nuevo nodo
            }
            else ///Si el nodeIndex es el ultimo nodo de la lista
            {
                pNewNode->pNextNode = NULL; ///Debe apuntar a NULL
                pAuxNode->pNextNode = pNewNode; ///Y el nodo anterior apuntara ahora a la direccion de memoria del nuevo nodo
            }

            this->size++; ///Aumento el tamaño de la lista, pues se añadio un nuevo nodo
            returnAux = 0; ///Retorno 0, se pudo añadir un nuevo nodo a la lista
        }
    }

    return returnAux;
}


/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int returnAux = -1;

    if(this != NULL) ///Evaluo que no me pasen NULL como lista
    {
        addNode(this, ll_len(this), pElement); ///Utilizo addNode para añadir un nuevo nodo a la lista. En este caso se añadira un nuevo nodo junto con su pElement asociado al final de la lista
        returnAux = 0; ///Retorno 0 si se pudo añadir el nuevo nodo
    }

    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;

    Node* pNode = NULL; ///Creo puntero de tipo nodo

    if(this != NULL && index >= 0 && index < ll_len(this)) ///Evaluo la lista y que el index pasado como parametro este entre 0 y el tamaño de la lista
    {
        pNode = getNode(this, index); ///Con getNode(); obtengo el nodo del index especificado
        returnAux = pNode->pElement; ///En returnAux voy a guardar el pElement que tenga el nodo
    }

    return returnAux; ///Retorno ese elemento
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;

    Node* pNode = NULL;

    if(this != NULL && index >= 0 && index < ll_len(this)) ///Evaluo la lista y que el index pasado como parametro este entre 0 y el tamaño de la lista
    {
        pNode = getNode(this, index); ///Con getNode(); obtengo el nodo del index especificado
        pNode->pElement = pElement; ///Reemplazo el pElement que tenia el nodo por el nuevo que se paso como parametro
        returnAux = 0; ///Se pudo hacer la modificacion
    }

    return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this, int index)
{
    int returnAux = -1;

    Node* pNode = NULL;
    Node* pAuxNode = NULL;

    if(this != NULL && index < ll_len(this) && index >= 0)
    {
        if(index == 0) ///Si el index pasado como parametro es 0, entonces se desea eliminar el primer nodo
        {
            pAuxNode = getNode(this, index); ///Primero obtengo el primer nodo con getNode();
            pNode = pAuxNode; ///pNode va a guardar la direccion de memoria de ese primer nodo para no perder referencia

            pAuxNode = pAuxNode->pNextNode; ///Entonces el que era mi primer nodo ahora apuntara al proximo nodo
        }
        else if(index > 0 && index < ll_len(this)) ///Si el index pasado como parametro no es 0 o el tamaño de la lista, se desea eliminar alguno nodo del centro
        {
            pAuxNode = getNode(this, index-1); ///Guardo el nodo anterior con index-1
            pNode = getNode(this, index); ///Guardo el nodo a eliminar

            pAuxNode->pNextNode = pNode->pNextNode; ///Hago que el nodo anterior apunte a lo que apunta el nodo a eliminar
            free(pNode); ///Hago free(); del nodo que quiero eliminar y lo libero
        }
        else ///Se quiere eliminar el ultimo nodo
        {
            pAuxNode = getNode(this, index-1); ///Guardo el nodo anterior con index-1
            pNode = getNode(this, index); ///Guardo el ultimo nodo de la lista que quiero eliminar

            pAuxNode->pNextNode = NULL; ///Hago que el nodo anterior apunte a NULL y pasa a ser el ultimo nodo de la lista
            free(pNode); ///Hago free(); del que era el ultimo nodo y lo libero
        }

        this->size--; ///Actualizo el tamaño de la lista pues se elimino un nodo
        returnAux = 0; ///Retorno 0, se pudo eliminar el nodo deseado
    }

    return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int i, returnAux = -1;

    if(this != NULL) ///Verifico que la lista no sea NULL
    {
        for(i=0; i<ll_len(this); i++) ///Con un bucle for que vaya desde 0 a uno menos del tamaño de la lista, voy removiendo todos los nodos
        {
            ll_remove(this, i); ///Hago ll_remove() de cada index, uso el iterador i
        }

        returnAux = 0; ///Retorno 0, pues todos los nodos fueron eliminados
    }

    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL) ///Verifico que la lista no sea NULL
    {
        ll_clear(this); ///Hago ll_clear() para eliminar todos los nodos
        free(this); ///Libero con free() a la lista
        returnAux = 0; ///Retorno 0, pues la lista con todos sus nodos fueron eliminados de memoria
    }

    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int i, returnAux = -1;

    Node* pNode = NULL; ///Creo un puntero a nodo

    if(this != NULL) ///Evaluo que la lista no sea NULL
    {
        for(i=0; i<ll_len(this); i++) ///Con un bucle for voy recorriendo los nodos
        {
            pNode = getNode(this, i); ///Obtengo el nodo en el index del iterador i
            if(pNode->pElement == pElement) ///Si existe coincidencia entre el pElement del nodo y el pElement pasado como parametro...
            {
                returnAux = i; ///Retornare el index del nodo en el que hubo coincidencia
                break; ///Rompo for, pues deseo saber la primer ocurrencia
            }
        }
    }

    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL) ///Evaluo que la lista no sea NULL
    {
        if(this->size > 0) ///Basta con fijarme si el tamaño de la lista es mayor a 0
        {
            returnAux = 0; ///Entonces hay elementos
        }
        else
        {
            returnAux = 1; ///Caso contrario, la lista esta vacia
        }
    }

    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;

    if(this != NULL && index <= ll_len(this) && index >= 0) ///Verifico que la lista no sea NULL y que index este entre 0 y el tamaño de la lista
    {
        if(addNode(this, index, pElement) == 0) ///Dentro de un if evaluo el retorno de addNode(), si es 0 se pudo agregar un nuevo nodo en el index y con ese elemento
        {
            returnAux = 0; ///Por lo tanto, retorno 0. Caso contrario -1
        }
    }

    return returnAux;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this, int index)
{
    void* returnAux = NULL;

    Node* pNode = NULL; ///Creo un nodo a NULL

    if(this != NULL && index >= 0 && index < ll_len(this)) ///Evaluo que la lista no sea NULL y que index este entre 0 y el tamaño de la lista
    {
        pNode = getNode(this, index); ///Con getNode() obtengo el nodo del index deseado
        returnAux = pNode->pElement; ///Antes de eliminarlo, guardo la direccion del pElement que tiene asociado
        ll_remove(this, index); ///Elimino el nodo
    }

    return returnAux; ///Retorno la direccion de memoria de ese pElement
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;

    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this, LinkedList* this2)
{
    int returnAux = -1;

    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this, int from, int to)
{
    LinkedList* cloneArray = NULL;

    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;

    return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
    int returnAux =-1;

    return returnAux;

}

