#include <stdio.h>
#include <stdlib.h>


struct node
{
int key;
struct node *left;
struct node *right;
int height;
};

int getHeight (struct node *n) {
    if (n == NULL) {
        return 0;
    } else {
        return n->height;
    }
}

struct node* createNode(int key) {
    struct node* node = (struct node*) malloc (sizeof(struct node));

    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

int max(int a, int b) {
    return (a>b)? a:b;
}

int getBalanceFactor(struct node* n) {
    if (n==NULL) {
        return 0;
    } else {
        return (getHeight(n->left) - getHeight(n->right));
    }
}

// y is the topmost
struct node* rightRotate(struct node* y) {
    struct node* x = y->left;
    struct node* T2 = x->right;

    x->right = y;
    y->left = T2;

    x->height = 1 + max(getHeight(x->right), getHeight(x->left));
    y->height = 1+ max(getHeight(y->left), getHeight(y->right));

    return x;
}

struct node* leftRotate(struct node* x) {
    struct node* y = x->right;
    struct node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1+ max(getHeight(x->left), getHeight(x->right));
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));

    return y;
}


struct node* insert(struct node* node, int key) {
    if (node == NULL) {
        return createNode(key);
    }

    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    }

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    int bf = getBalanceFactor(node);

    if (bf > 1) {
        int k = node->left->key;
        //LL Case
        if (key < k) {
            return rightRotate(node);

            //LR Case
        } else if (key > k) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    } else if (bf <-1) {

        int k = node->right->key;
        //RR Case
        if (key > k) {
            return leftRotate(node);

            //RL Case
        } else if (key < k) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }
    return node;
}

void printTree(struct node* r, int space) {
    if (r==NULL) {
        return;
    }
    space += 10;

    printTree(r->right, space);

    printf("\n");
    for (int i = 10; i< space; i++) {
        printf(" ");
    }
    printf("%d\n", r->key);

    printTree(r->left, space);
}

struct node* minVal(struct node* n) {
    struct node* current = n;

    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

struct node* delete(struct node* node, int key) {
    if (node == NULL) {
        return node;
    }

    if (key < node->key) {
        node->left = delete(node->left, key);
    } else if (key > node->key) {
        node->right = delete(node->right, key);
    } else {


        // one child or no children
        if ( (node->left == NULL) || (node->right == NULL)) {
            struct node* temp = node->left ? node->left : node->right;
            
            // no children
            if (temp == NULL) {
                temp = node;
                node = NULL;
            } else {
                *node = *temp;
            }
            free(temp);
        } else {

            // get inorder successor
            struct node* temp = minVal(node->right);

            node->key = temp->key;

            // delete that node
            node->right = delete(node->right, temp->key);
        }
    }

    if (node == NULL) {
        return node;
    }

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    int bf = getBalanceFactor(node);

    //LL Case
    if (bf > 1 && getBalanceFactor(node->left)  >= 0) {
        return rightRotate(node);
    }
    //LR Case
    if (bf > 1 && getBalanceFactor(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    //RR Case
    if (bf < -1 && getBalanceFactor(node->right) <=0) {
        return rightRotate(node);
    }

    //RL Case
    if (bf < -1 && getBalanceFactor(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void initTree(struct node* r, int data[], int size) {

    for (int i = 1; i< size; i++) {
        r = insert(r, data[i]);
    }

}

int main() {

    struct node* root = createNode(50);
    int nodes[] = {40, 30, 50, 90, 70, 30,10, 20, 40,100,120,150,5};
    int size = sizeof(nodes) / sizeof(nodes[0]);
    initTree(root, nodes, size);

    printf("Full tree: \n");
    printTree(root, 0);

    printf("Deleting node 90: \n");
    delete(root, 90);
    printf("New tree: \n");
    printTree(root, 0);

    printf("Deleting node 20: \n");
    delete(root, 20);
    printf("New tree: \n");
    printTree(root, 0);


    return 0;
}