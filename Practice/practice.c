#include <stdio.h>
#include <math.h>
#include <stdlib.h>


void printTree(int arr[], int size, int index, int space) {
    if (index >= size) {
        return;
    }
    space += 10;

    printTree(arr, size, 2*index + 2, space);

    printf("\n");
    for (int i = 10; i< space; i++) {
        printf(" ");
    }
    printf("%d\n", arr[index]);

    printTree(arr, size, 2* index + 1, space);
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d",arr[i]);
        printf(", ");
    }
    printf("\n");
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int arr[], int n, int i) {
    int l = 2*i + 1;
    int r = 2*i + 2;

    int largest = i;
    
    if ( l < n && arr[l] > arr[i]) {
        largest = l;
    }

    if (r < n && arr[r] > arr[largest]) {
        largest = r;
    }

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }


}

void heapDelete(int arr[], int* n) {
    int lastElem = arr[*n - 1];

    arr[0] = lastElem;

    *n = *n - 1;
    heapify(arr, *n, 0);
}

void addSpace(int **arr, int* size, int elem) {
    int* temp = (int*)malloc((*size + 1) * sizeof(int));

    for (int i = 0; i < *size;i++ ) {
        temp[i] = (*arr)[i];
    }
    temp[*size] = elem;
    *size = *size + 1;
    free(*arr);
    *arr = temp;

}


void heapInsert(int **arr, int* size, int elem) {
    addSpace(arr, size, elem);
    int i = *size - 1;
    while (i != 0) {
        int parent =(int) (i-1)/2;
        if ((*arr)[parent] < (*arr)[i]) {
            swap(&(*arr)[i], &(*arr)[parent]);
        } else {
            break;
        }
        i = parent;
    }
}

void heapTest() {
 int a_Start[] = {1,2,6,10,15,19,3,22,25,31,30};

    int size = sizeof(a_Start) / sizeof(a_Start[0]);
    int* a = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        a[i] = a_Start[i];
    }
    
    for (int i = floor(size/2-1); i >=0; i--) {
        heapify(a, size, i);
    }
    printTree(a, size, 0,0);
    printf("Deleting");
    heapDelete(a, &size);
    printTree(a, size, 0, 0);

    printf("Inserting");
    heapInsert(&a, &size, 50);
    printTree(a, size, 0, 0);
}


//Stack and queue
struct node {
    int key;
    struct node* next;
};
typedef struct node* Node;

Node creatNode(int key) {
    Node t = (Node)malloc(sizeof(Node));
    t->key = key;
    return t;
}

struct queue {
    Node front;
    Node rear;
};
typedef struct queue* Queue;

void pushQueue(Queue q, int key) {
    printf("In push");
    if (q->front == NULL && q->rear == NULL) {
        q->front = creatNode(key);
        q->rear = q->front;
    } else if (q->rear == q->front) {
        q->rear = creatNode(key);
        q->front->next = q->rear;
    } else {
        q->rear->next = creatNode(key);
        q->rear = q->rear->next;
    }
}

int removeQueue(Queue q) {
    if (q->front == q->rear) {
        if (q->rear == NULL) {
            return -999;
        } else {
            int temp = q->front->key;
            free(q->front);
            free(q->rear);
            q->front = NULL;
            q->rear = NULL;
            return temp;
        }
    } else {
        int temp = q->front->key;
        Node t = q->front->next;
        free(q->front);
        q->front = t;
    }
}
void printQueue(Queue q) {
    if (q->front != NULL) {
        Node current= q->front;
        while (current != NULL) {
            printf("%d",current->key);
            current = current->next;
        }
    }
    printf("\n");
}

void queueTest() {
    Queue qu = (Queue)malloc(sizeof(Queue));
    pushQueue(qu, 1);
    pushQueue(qu, 2);
    pushQueue(qu, 3);
    pushQueue(qu, 4);
    printQueue(qu);
    printf("done");
}

// Binary search tree
struct bstNode {
    int key;
    struct bstNode* left;
    struct bstNode* right;
};

typedef struct bstNode* BNode;

BNode bstCreatNode(int key) {
    BNode temp = (BNode)malloc(sizeof(BNode));

    temp->key = key;
    temp->right = NULL;
    temp->left = NULL;

    return temp;
}

BNode bstInsert(BNode n, int key) {
    printf("Inserting %d \n", key);
    BNode parent, temp;
    int dir = 0;
    temp = n;
    printf("here");
    while (temp != NULL) {
        printf("inloop");
        if (temp->key == key) {
            printf("Key already exists");
            return temp;
        } else if ( key < temp->key ) {
            parent = temp;
            temp = temp->left;
            dir = 0;
        } else {
            parent = temp;
            temp= temp->right;
            dir = 1;
        }
    }

    temp = bstCreatNode(key);
    if (dir == 0) {
        parent->left = temp;
    } else {
        parent->right = temp;
    }
    return temp;
}
void printBST(BNode r, int space) {
    if (r==NULL) {
        return;
    }
    space += 10;

    printBST(r->right, space);

    printf("\n");
    for (int i = 10; i< space; i++) {
        printf(" ");
    }
    printf("%d\n", r->key);

    printBST(r->left, space);
}

void bstTest() {
    int a[] = {1,2,3,5,6};
    BNode root = bstCreatNode(4);
    for (int i = 0; i< 5; i++) {
        bstInsert(root, a[i]);
    }
    printBST(root, 0);
}
int main() {


    //heapTest();
   //queueTest();
   bstTest();

    return 0;
}