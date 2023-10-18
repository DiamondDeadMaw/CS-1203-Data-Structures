#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* left;
    struct node* right;
} Node;


Node* createNode(int d) {
    Node* newNode = (Node*)malloc(sizeof(Node));

    newNode->data = d;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}


// recursive insertion into tree following property of BST
Node* insert(Node* n, int d) {

    if (n == NULL) {
        return createNode(d);
    }

    if (d < n->data) {
        n->left = insert(n->left, d);
    } else if (d > n->data) {
        n->right = insert(n->right, d);
    }

    return n;
}

// takes root, data array, and size of the array.
void initTree(Node* r, int d[], int size) {
    r->data = d[0];


    for (int i = 1; i< size; i++) {
        insert(r, d[i]);
    }
}

// helper func to print tree, to check validity of traversal
void printTree(Node* r, int space) {
    if (r==NULL) {
        return;
    }
    space += 10;

    printTree(r->right, space);

    printf("\n");
    for (int i = 10; i< space; i++) {
        printf(" ");
    }
    printf("%d\n", r->data);

    printTree(r->left, space);
}

// implementing stack of type Node pointer using a linked list
typedef struct s_node {
    Node* data;
    struct s_node* next;
} S_Node;

typedef struct stack {
    S_Node* top;
} Stack;


void push(Node* data, Stack* stk) {
    S_Node* newNode = (S_Node*)malloc(sizeof(S_Node));
    newNode->data = data;
    newNode-> next= stk->top;
    stk->top = newNode;
}

Node* pop(Stack* stk) {

    if (stk->top == NULL) {
        return NULL;
    }

    S_Node* temp = stk->top;
    Node* tempD = temp->data;
    stk->top = temp->next;
    free(temp);
    return tempD;
}


void inorder(Node* root) {

    Stack* stack = (Stack*)malloc(sizeof(Stack));
    
    Node* curr= root;

    int flag = 1;

    while (flag ==1) {
        if (curr != NULL) {
            push(curr, stack);
            curr = curr->left;
        }
        // will be called when we reach the leftmost leaf
        else  {
            // if the leftmost leaf doesnt have a right child, but has a parent
            
            if (stack->top != NULL) {
                curr = pop(stack);
                printf("%d", curr->data);
                printf(", ");

                curr = curr->right;
            } else {
                flag = 0;
            }
        }
    }

}

int main() {

    Node* root = createNode(50);

    int nodes[] = {40, 30, 50, 90, 70, 30,10, 20, 40,100,120,150,5};
    int size = sizeof(nodes) / sizeof(nodes[0]);
    initTree(root, nodes, size);
    printf("Full tree: \n");
    printTree(root, 0);

    printf("Inorder traversal: \n");
    inorder(root);
    return 0;
}