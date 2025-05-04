#include <stdio.h>
#include "linkedlist.h"
#include "stack.h"
#include <assert.h>
#include "queue.h"

// Color codes for output
#define COLOR_RESET   "\033[0m"
#define COLOR_GREEN   "\033[0;32m"
#define COLOR_CYAN    "\033[0;36m"
#define COLOR_YELLOW  "\033[0;33m"

// Helper to get how many items are in an array
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

void testListOperations()
{
    printf(COLOR_CYAN "=== Exercise 1: Linked List ===\n" COLOR_RESET);

    List l = createList();
    assert(l != NULL);
    assert(l->next == l->prev);
    assert(isEmpty(l));

    printf(COLOR_GREEN "List creation passed.\n" COLOR_RESET);

    const int expected_data[] = {3, 1, 5, 10, 8, 7};

    // Insert numbers into the list
    for (int i = ARRAY_SIZE(expected_data) - 1; i >= 0; i--)
    {
        Node *n = malloc(sizeof(Node));
        assert(n);
        n->data = expected_data[i];
        assert(insert(l, n));
    }

    printList(l);
    printf("\n");

    // Verify correct order
    Node *iter = l->next;
    for (int i = 0; i < ARRAY_SIZE(expected_data); i++)
    {
        assert(iter->data == expected_data[i]);
        iter = iter->next;
    }

    printf(COLOR_GREEN "Insert order test passed.\n" COLOR_RESET);

    // Search tests
    for (int i = 0; i < ARRAY_SIZE(expected_data); i++)
        assert(search(l, expected_data[i]) != NULL);

    assert(search(l, 9999) == NULL);

    printf(COLOR_GREEN "Search test passed.\n" COLOR_RESET);

    // Max/min
    assert(maximum(l)->data == 10);
    assert(minimum(l)->data == 1);
    printf(COLOR_GREEN "Min/max test passed.\n" COLOR_RESET);

    // Successor/Predecessor
    assert(successor(l, search(l, 5))->data == 7);
    assert(predecessor(l, search(l, 10))->data == 8);
    printf(COLOR_GREEN "Successor/predecessor test passed.\n" COLOR_RESET);
}

void testStack()
{
    printf(COLOR_CYAN "\n=== Exercise 3: Stack ===\n" COLOR_RESET);

    Stack stack = createStack();
    assert(stack && isEmpty(stack));

    for (int i = 1; i <= 5; i++) {
        Node *n = malloc(sizeof(Node));
        n->data = i;
        assert(push(stack, n));
    }

    printf(COLOR_GREEN "Push test passed.\n" COLOR_RESET);
    printStack(stack);

    for (int i = 5; i >= 1; i--) {
        Node *p = pop(stack);
        assert(p && p->data == i);
        free(p);
    }

    assert(pop(stack) == NULL);
    assert(peek(stack) == NULL);
    printf(COLOR_GREEN "Pop/empty test passed.\n" COLOR_RESET);

    for (int i = 10; i <= 15; i++) {
        Node *n = malloc(sizeof(Node));
        n->data = i;
        push(stack, n);
    }

    printStack(stack);
    clear(stack);
    assert(peek(stack) == NULL);
    printf(COLOR_GREEN "Clear test passed.\n" COLOR_RESET);
}

void test_queue()
{
    printf(COLOR_CYAN "\n=== Exercise 4: Queue ===\n" COLOR_RESET);

    Queue queue = createStack(); 

    for (int i = 0; i < 5; i++) {
        Node *n = malloc(sizeof(Node));
        n->data = i;
        enqueue(queue, n);
    }

    printStack(queue);
    assert(peek_queue(queue)->data == 0);
    printf(COLOR_GREEN "Peek test passed.\n" COLOR_RESET);

    for (int i = 0; i < 5; i++) {
        Node *n = dequeue(queue);
        assert(n && n->data == i);
        free(n);
    }

    assert(dequeue(queue) == NULL);
    printf(COLOR_GREEN "Dequeue/empty test passed.\n" COLOR_RESET);

    Node *n = malloc(sizeof(Node));
    n->data = 42;
    enqueue(queue, n);
    assert(dequeue(queue)->data == 42);
    printf(COLOR_GREEN "Single value test passed.\n" COLOR_RESET);

    clear(queue);
}

void testExercise2()
{
    printf(COLOR_CYAN "\n=== Exercise 2: Linked List Testing ===\n" COLOR_RESET);

    List l1 = createList();
    const int l1_data[] = {3, 1, 5, 10, 8, 7};
    for (int i = 0; i < 6; i++) {
        Node *n = malloc(sizeof(Node));
        n->data = l1_data[i];
        insert(l1, n);
    }

    List l2 = createList();
    const int l2_data[] = {5, 2, 9, 6, 1, 2};
    for (int i = 0; i < 6; i++) {
        Node *n = malloc(sizeof(Node));
        n->data = l2_data[i];
        insert(l2, n);
    }

    printf(COLOR_YELLOW "Minimum of L1: %d\n" COLOR_RESET, minimum(l1)->data);
    printf(COLOR_YELLOW "Maximum of L1: %d\n" COLOR_RESET, maximum(l1)->data);
    printf(COLOR_YELLOW "Minimum of L2: %d\n" COLOR_RESET, minimum(l2)->data);
    printf(COLOR_YELLOW "Maximum of L2: %d\n" COLOR_RESET, maximum(l2)->data);

    printf(COLOR_YELLOW "Successor of 5 in L1: %d\n" COLOR_RESET, successor(l1, search(l1, 5))->data);
    printf(COLOR_YELLOW "Predecessor of 5 in L1: %d\n" COLOR_RESET, predecessor(l1, search(l1, 5))->data);
    printf(COLOR_YELLOW "Successor of 9 in L2: %s\n" COLOR_RESET,
           successor(l2, search(l2, 9)) ? "Exists" : "NULL");
    printf(COLOR_YELLOW "Predecessor of 9 in L2: %d\n" COLOR_RESET, predecessor(l2, search(l2, 9))->data);

    printf(COLOR_YELLOW "Predecessor of max in L1 (10): %d\n" COLOR_RESET, predecessor(l1, maximum(l1))->data);
    printf(COLOR_YELLOW "Successor of min in L2 (1): %d\n" COLOR_RESET, successor(l2, minimum(l2))->data);
}

int main()
{
    testListOperations();
    testStack();
    test_queue();
    testExercise2();

    return 0;
}
