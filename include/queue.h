#ifndef QUEUE_HEADER
#define QUEUE_HEADER
#include "stack.h"

typedef Stack Queue;

bool enqueue(Queue queue, Node *node)
{
    return push(queue, node);
}

Node *dequeue(Queue queue)
{
    return delete_(queue, queue->prev);
}

Node *peek_queue(Queue queue)
{
    // S->A->B
    // ===> A->B->S 
    // ===> -->B
    return peek(queue->prev->prev);
}

#endif