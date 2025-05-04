#ifndef STACK_HEADER
#define STACK_HEADER
#include "linkedlist.h"

typedef List Stack;

bool deleteStackNode(Node *itr_ptr, Stack stack)
{
    free(delete_(stack, itr_ptr->prev));
    return false;
}

Stack createStack()
{
    return createList();
}

Node *peek(Stack stack)
{
    if (stack->next == stack)
        return NULL;
        
    return stack->next;
}

void clear(Stack stack)
{
    foreach (stack, stack, deleteStackNode)
        ;
    // Because of the strucutre of the algortigm the second element has to be deleted manually
    delete_(stack, stack->next);
}

Node *pop(Stack stack)
{
    return delete_(stack, stack->next);
}

bool push(Stack stack, Node *node)
{
    return insert(stack, node);
}

void printStack(Stack stack)
{
    printf("Top|");
    printList(stack);
    printf("|Botttom");
}

#endif