#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    long long val;
    struct Node* next;
} node_t;

typedef struct Queue {
    node_t* head;
    node_t* tail;
    int size;
} queue_t;


long long inputNumber() {
    char input[100];
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Error reading input\n");
        exit(1);
    }

    if (input[0] == '\n') {
        printf("Empty input\n");
        exit(1);
    }

    int is_negative = 0;
    if (input[0] == '-') {
        is_negative = 1;
    }

    long long num = 0;
    for (int i = is_negative; input[i] != '\n'; i++) {
        if (input[i] < '0' || input[i] > '9') {
            printf("Invalid symbol: %c\n", input[i]);
            exit(1);
        }

        long long digit = input[i] - '0';
        num = num * 10 + digit;
    }

    if (is_negative) {
        return -num;
    }

    return num;
}

node_t* createNode(long long val) {
    node_t* node = (node_t*)malloc(sizeof(node_t));

    if (!node) {
        printf("Failed to create a node\n");
        exit(1);
    }

    node->val = val;
    node->next = NULL;

    return node;
}

queue_t* createQueue() {
    queue_t* queue = (queue_t*)malloc(sizeof(queue_t));

    if (!queue) {
        printf("Failed to create a queue\n");
        exit(1);
    }
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;

    return queue;
}

void push(queue_t* queue, long long val) {
    node_t* node = createNode(val);

    if (queue->head == NULL) {
        queue->head = node;
        queue->tail = node;
        queue->size++;
        return;
    }

    queue->tail->next = node;
    queue->tail = queue->tail->next;
    queue->size++;
}

long long pop(queue_t* queue) {
    if (queue->head == NULL) {
        printf("Queue is empty\n");
        exit(1);
    }

    node_t* temp = queue->head;
    queue->head = queue->head->next;

    if (queue->head == NULL) {
        queue->tail = NULL;

    }

    long long val = temp->val;
    free(temp);
    queue->size--;
    return val;
}


long long peek(queue_t* queue) {
    if (queue->head == NULL) {
        printf("List is empty\n");
        exit(1);
    }

    return queue->head->val;
}

int size(queue_t* queue) {
    return queue->size;
}

int isEmpty(queue_t* queue) {
    return queue->size == 0;
}


void print(queue_t* queue) {
    printf("[ ");
    node_t* temp = queue->head;
    while (temp != NULL) {
        printf("%lld ", temp->val);
        temp = temp->next;
    }
    printf("]\n");
}

void deleteQueue(queue_t* queue) {
    if (queue == NULL) return;

    node_t* temp = queue->head;
    while (temp != NULL) {
        node_t* next = temp->next;
        free(temp);
        temp = next;
    }

    free(queue);
}

int main() {
    queue_t* q = createQueue();

    printf("Type '1' to add, '2' to pop, '3' to get size, '4' to print, '5' to quit\n");
        
    while (1) {
        printf("Choice: ");
        long long c = inputNumber();

        if (c == 1) {
            printf("Input number: ");
            long long val = inputNumber();
            push(q, val);
        } else if (c == 2) {
            long long v = pop(q);
            printf("Removed: %lld\n", v);
        } else if (c == 3) {
            int s = size(q);
            printf("Size: %d\n", s);
        } else if (c == 4) {
            printf("Queue: ");
            print(q);
        } else if (c == 5) {
            printf("Quiting\n");
            break;
        } else {
            printf("Invalid input: %lld\n", c);
            break;
        }
    }

    deleteQueue(q);
    return 0;
}
