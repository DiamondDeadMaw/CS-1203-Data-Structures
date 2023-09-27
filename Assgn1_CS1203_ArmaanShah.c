#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
    struct node* prev;
} NODE;


typedef struct queue{
 NODE* front;
 NODE* rear;
} QUEUE;

void initQ(QUEUE* q) {
    q->front = NULL;
    q-> rear = NULL;
}

void insert(QUEUE* q, int elm) {

    NODE* newNode = (NODE*)malloc(sizeof(NODE));

    newNode-> data = elm;

    if (q-> rear == NULL) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

void delete(QUEUE* q) {

    if (q->front == NULL) {
        printf("Queue is empty");
    } else {

        NODE* temp = q-> front;
        q->front = temp->next;
        free(temp);

        if (q->front == NULL) {
            q->rear = NULL;
        }

    }
}

void printQueue(QUEUE* q) {

    NODE* current;
    current = q->front;
    printf("CURRENT QUEUE: ");

    bool f = true;
    if (q-> front == NULL) {
        printf("Queue is empty");
        f = false;
    }

    while (f) {

        if (current->next == NULL) {
            printf("%d", current->data);
            printf("\n");
            break;
        }
        printf("%d", current->data);
        printf(",");
        current = current->next;
    }
}


int main () {

    bool flag = true;
    QUEUE queue;
    initQ(&queue);

    int ans;
    int ans2;
    while (flag)
    {
        printf("Choose from the following: \n 1. Insert  \n 2. Delete \n 3.Print \n 4.Exit \n");
        scanf("%d", &ans);

        switch (ans)
        {
        case 1:
            printf("Enter new element \n");
            scanf("%d", &ans2);
            insert(&queue, ans2);
            break;
        case 2:
            delete(&queue);
            break;
        case 3:
            printQueue(&queue);
            break;
        case 4:
            flag = false;
            break;
        default:
            break;
        }

    }
    


    return 0;
}