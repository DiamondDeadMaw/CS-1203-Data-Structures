#include <stdio.h>
#include <stdbool.h>

typedef struct node {
    int data;
    struct node* next;
} NODE;


typedef struct queue{
 NODE* front;
 NODE* rear;
} QUEUE;


int main () {

    bool flag = true;
    QUEUE q;

    while (flag)
    {
        printf("Choose from the following: \n 1. Insert  \n 2. Delete \n 3.Print \n 4.Exit \n");

    }
    


    return 0;
}