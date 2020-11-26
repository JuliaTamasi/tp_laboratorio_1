/*
    utest example : Unit test examples.
    Copyright (C) <2018>  <Mauricio Davila>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __LINKEDLIST
#define __LINKEDLIST
struct Node
{
    void* pElement;
    struct Node* pNextNode;
}typedef Node;

struct LinkedList
{
    Node* pFirstNode;
    int size;
}typedef LinkedList;
#endif



//Publicas
LinkedList* ll_newLinkedList(void); //Crea una lista nueva con punteros a elementos de un tipo
int ll_len(LinkedList* this); //devuelve el tama�o de la lista. Lo necesito porque como es una lista dinamica el tama�o va variando
Node* test_getNode(LinkedList* this, int nodeIndex);
int test_addNode(LinkedList* this, int nodeIndex,void* pElement);
int ll_add(LinkedList* this, void* pElement); //agrega un puntero al final de la lista
void* ll_get(LinkedList* this, int index); //devuelve el elemento de un indice determinado de la lista
int ll_set(LinkedList* this, int index,void* pElement); //Pisa un elemento de la lista que esta en determinado index con el elemento que le paso (pElement)
int ll_remove(LinkedList* this,int index);
int ll_clear(LinkedList* this); //borra los elementos de la lista, la deja en tama�o 0, como si recien la hubiese creado
int ll_deleteLinkedList(LinkedList* this); //elimina la lista completamente, libera la memoria en donde estaba la lista.
int ll_indexOf(LinkedList* this, void* pElement);
int ll_isEmpty(LinkedList* this);
int ll_push(LinkedList* this, int index, void* pElement);
void* ll_pop(LinkedList* this,int index);
int ll_contains(LinkedList* this, void* pElement);
int ll_containsAll(LinkedList* this,LinkedList* this2);
LinkedList* ll_subList(LinkedList* this,int from,int to);
LinkedList* ll_clone(LinkedList* this);
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order);
