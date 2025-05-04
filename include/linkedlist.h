#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#define SENITAL_TAIL_VALUE INT_MAX

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node Node;

struct Node
{
    Node *next;
    Node *prev;
    int data;
};

typedef struct Node *List;

List createList()
{
    List l = (List)malloc(sizeof(Node));

    l->next = l;
    l->prev = l;
    l->data = SENITAL_TAIL_VALUE;

    return l;
}

typedef struct CompareNodeContainer CompareNodeContainer;

struct CompareNodeContainer
{
    Node *target;
    Node *candidate;
};


Node *foreach (List list, void *compareTo, bool (*compareFunc)(Node *itr_ptr, void *input))
{
    Node *ptr_iter = list->next;
    do
    {
        if (compareFunc(ptr_iter, compareTo))
            return ptr_iter;

        ptr_iter = ptr_iter->next;
    } while (ptr_iter != list);

    return NULL;
}

bool isEmpty(List list)
{
    if (list == NULL)
        return true;

    if (list->next == list->prev)
        return true;

    return false;
}

void link(Node *a, Node *b)
{
    //  K<->A<->L
    //  B->L
    //  A<-B
    //  B<-L
    //  A->B  
    //   |
    //   v
    //  K<->A<->B<->L
    b->next = a->next;
    b->prev = a;
    a->next->prev = b;
    a->next = b;
}

bool insert(List list, Node *node)
{
    if (node == NULL)
        return false;

    // Link new node
    link(list, node);
    return true;
}

bool isEqual(Node *n_ptr, int data)
{
    return n_ptr->data == data;
}

Node *search(List list, int key)
{
    return foreach (list, key, isEqual);
}

Node *delete_(List list, Node *B)
{
    // Cant delete a empty list
    if (B == list)
        return NULL;
    //       A<->B<->C
    //       |       |
    //       A  <->  C
    Node *A = B->prev;
    Node *C = B->next;
    // Link next and previus together
    A->next = C;
    C->prev = A;

    return B;
}

typedef struct
{
    Node *node;
} NodeContainer;

bool setMaximum(Node *node_ptr, NodeContainer *current_max)
{
    if ((current_max->node == NULL || node_ptr->data > current_max->node->data))
    {
        current_max->node = node_ptr;
    }

    return false;
}

Node *maximum(List list)
{
    NodeContainer maxNode;
    maxNode.node = NULL;

    foreach (list, &maxNode, setMaximum)
        ;

    return maxNode.node;
}

bool setMinimum(Node *node_ptr, NodeContainer *current_min)
{
    if ((current_min->node == NULL || node_ptr->data < current_min->node->data))
    {
        current_min->node = node_ptr;
    }

    return false;
}

Node *minimum(List list)
{
    NodeContainer maxNode;
    maxNode.node = NULL;

    foreach (list, &maxNode, setMinimum)
        ;

    return maxNode.node;
}

bool setSuccessor(Node *node_ptr, CompareNodeContainer *current){
    if (node_ptr->data > current->target->data)
    {
        if (current->candidate == NULL || node_ptr->data < current->candidate->data)
        {
            current->candidate = node_ptr;
        }
    }
    return false; 
}

Node *successor(List list, Node *node)
{
    // key = 2
    // S->0->1->2->3->4->5->S
    //          |-----------|
    //                      v
    //                      5

    CompareNodeContainer container;
    container.target = node;
    container.candidate = NULL;

    foreach (list, &container, setSuccessor)
        ;

    return container.candidate;
}

bool setPredecessor(Node *node_ptr, CompareNodeContainer *current){
    if (node_ptr->data < current->target->data)
    {
        if (current->candidate == NULL || node_ptr->data > current->candidate->data)
        {
            current->candidate = node_ptr;
        }
    }
    return false; 
}

Node *predecessor(List list, Node *node)
{
    
    //    list: S->0->1->2->3->4->5->S
    //                      ^     ^ 
    //                      |     |
    //                  target   result: node with largest value < 2
    

    CompareNodeContainer container;
    container.target = node;
    container.candidate = NULL;

    foreach(list, &container, setPredecessor);

    return container.candidate;
}

void printList(List l)
{
    Node *ptr_iter = l;
    do
    {
        if (ptr_iter == l)
        {
            printf("S");
            printf("->");
        }
        else
        {
            printf("%d", ptr_iter->data);
            printf("->");
        }

        ptr_iter = ptr_iter->next;
    } while (ptr_iter != l);
}

#endif