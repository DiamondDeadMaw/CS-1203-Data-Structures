#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define t 3

struct node {
    int keys[2*t - 1];
    struct node* links[2*t];
    bool isLeaf;
    int numKeys;
    int numLinks;
};

typedef struct node Node;

Node* getNode() {
    Node *n = (Node*)malloc(sizeof(Node));
    n->numKeys = 0;
    n->numLinks = 0;
    n->isLeaf = 0;

    for (int i = 0; i<(2*t-1); i++) {
        n->keys[i] = -1;
    }
    for (int i = 0; i< (2*t); i++) {
        n->links[i] = NULL;
    }
    return n;
}

void setKeys(Node* n, int num, int a[]) {
    // not checking for num < t-1 as described in Q2, to accomodate Q3s requirement of a single key in the parent
    if (num > 2*t - 1) {
        printf("Wrong number of keys\n");
        return;
    }

    for (int i = 0; i< num; i++) {
        n->keys[i] = a[i];
    }
    n->numKeys = num;
}

void insertVal2Node(Node* n, int k) {
    if (n->numKeys  == 2*t -1) {
        printf("Too many keys\n");
        return;
    }

    int i = 0;
    if (n->numKeys > 0) {
        while (n->keys[i] < k && i < n->numKeys) {
        i++;
    }
    }
    int temp = n->keys[i];
    n->keys[i] = k;
    n->numKeys = n->numKeys + 1;

    for (int j = i+1; j < n->numKeys; j++) {
        int temp2 = n->keys[j];
        n->keys[j] = temp;
        temp = temp2;
    }

}

void insertVal2NodeBreak(Node* n, int k) {
    // if node already has max amount of keys, will create a new node w/ left and right children. left child is the first
    // element of links array, while right child is the second.
    if (n->numKeys == 2*t -1) {
        
        //since t = 3, the new array will always have an even number of elements
        int tempArray[2*t];
        int j = 0;
        int flag = 0;
        //copying all values to a larger array
        for (int i = 0; i< 2*t-1; i++) {
            if (n->keys[i] > k && flag == 0) {
                tempArray[j++] = k;
                flag = 1;
            }
            tempArray[j++] = n->keys[i];

        }


        //setting current node to median key
        int newKey[1];
        // 3 is median since size is known
        newKey[0] = tempArray[3];
        setKeys(n, 1, newKey);
        Node* left =  getNode();
        //setting left child keys to first t keys
        for (int i = 0; i<3;i++) {
            insertVal2Node(left, tempArray[i]);
        }

        Node* right = getNode();

        for (int i = 4; i<6; i++) {
            insertVal2Node(right, tempArray[i]);
        }

        //adding children to pointers list
        n->numLinks = n->numLinks + 2;
        n->links[0] = left;
        n->links[1] = right;


            //if not a max, can use this function as normal. can replace the above function call with a recursive one
    } else {
        int i = 0;
    while (n->keys[i] < k) {
        i++;
    }
    int temp = n->keys[i];
    n->keys[i] = k;
    n->numKeys++;
    for (int j = i+1; j < n->numKeys - 1; j++) {
        int temp2 = n->keys[j];
        n->keys[j] = temp;
        temp = temp2;
    }
    }
}

Node* initTree() {
    Node* root = getNode();
    int rootKeys[] = {20, 30, 48, 70};

    setKeys(root, 4, rootKeys);
    return root;
}


void printNode(Node* n) {
    printf("Values of node: \n");
    for (int i = 0; i< n->numKeys-1;i++) {
        printf("%d", n->keys[i]);
        printf(", ");
    }
    printf("%d\n", n->keys[n->numKeys-1]);
    

    printf("Links from node: \n");
    if (n->numLinks == 0) {
        printf("No links\n");
    } else {
        for (int i = 0; i< n->numLinks-1;i++) {
        printf("%p", (void*)n->links[i]);
        printf(", ");
    }
    printf("%p\n", (void*)n->links[n->numLinks-1]);
    }
}


// QUESTION 4: SEARCH TREE FUNCTIONS
// using the same node struct from above

Node* initSearchTree() {
    Node* root = getNode();
    // since the links can be in arbitrary positions, we must initialize numLinks to max and check for nulls later
    root->numLinks = 2*t;

    return root;
}

bool isKeyInNode(Node* n, int k) {
    if (n->numKeys ==0) {
        return false;
    }
    for (int i = 0; i< n->numKeys; i++) {
        if (n->keys[i] == k) {
            return true;
        }
    }
    return false;
}

void insert(Node *n, int k);


void placeKeyInNewNode(Node* parent, int k) {
    //assuming keys of parent are sorted


    int largerIndex = 0;
    while (parent->keys[largerIndex] < k) {
        largerIndex++;
        if (largerIndex == 2*t-1 || largerIndex == parent->numKeys) {
            break;
        }
    }

    int linkIndex = largerIndex;

    if (parent->links[largerIndex] == NULL) {
        parent->links[largerIndex] = initSearchTree(); //this performs same func as getNode, but initializes numLinks correctly
    }

    insert(parent->links[largerIndex], k);


}

void insert(Node* n, int k) {
    if (n->numKeys >= 2*t-1 || isKeyInNode(n, k)) {
        placeKeyInNewNode(n, k);
    } else {
     if (k < n->keys[0]) {
        n->numKeys = n->numKeys + 1;
        int temp = n->keys[0];
        n->keys[0] = k;
        int i = 1;
        while (i < n->numKeys) {
            int temp2 = n->keys[i];
    n->keys[i++] = temp;
    temp = temp2;
        }
     } else {
           int largerIndex = 0;
    if (n->numKeys != 0) {
        while(n->keys[largerIndex] < k) {
        largerIndex++;
        if (largerIndex == n->numKeys-1) {
            break;
        }
    }
    }

    if (largerIndex == n->numKeys-1) {
    if (n->keys[largerIndex] < k) {
        n->keys[largerIndex + 1] = k;
    n->numKeys = n->numKeys + 1;
    } else {
       int temp = n->keys[largerIndex];
       n->keys[largerIndex+1] = temp;
       n->keys[largerIndex] = k;
       n->numKeys= n->numKeys + 1;
    }
} else {
    int temp = n->keys[largerIndex];
    n->keys[largerIndex] = k;
    n->numKeys = n->numKeys + 1;
    for (int i = n->numKeys - 1; i > largerIndex + 1; i--) {
        n->keys[i] = n->keys[i - 1];
    }
    n->keys[largerIndex + 1] = temp;
}
     }
    }

    
}

// returns parent if exists, returns null if doesnt exist
Node* search(Node* n, int k) {
    if (n == NULL) {
        return NULL;
    }
    int smallIndex = 0;

    //search leftmost subtree
    if (k < n->keys[0]) {
        return search(n->links[0], k);
    }

    //search rightmost subtree
    if (k > n->keys[n->numKeys-1]) {
        int i = n->numLinks - 1;
        return search(n->links[i], k);
    }
    // if in the middle
    for (int i = 0; i< n->numKeys-1; i++) {
        if (n->keys[i] == k) {
            return n;
        }

        if (k > n->keys[i] && k < n->keys[i+1]) {
            smallIndex = i;
            break;
        } 
    }

    return search(n->links[smallIndex+1], k);
}


int main() {

    printf("Name: Armaan Shah \n");
    printf("Course Name: Data Structures\n");
    printf("Year: 2023\n");
    printf("Roll number: 6\n");
    printf("Email: armaan.shah_ug25@ashoka.edu.in\n");
    printf("Phone number: 8130047572\n");
    
    printf("Testing the initialization of node with given values, showing keys in node: \n");
    Node* root1= initTree();
    printNode(root1);

    printf("Adding key 52 to the same node, and displaying new values:\n");
    insertVal2Node(root1, 52);
    printNode(root1);


    printf("Program 6: Testing the keys of the root node after insertion and breaking into 3 nodes:\n");
    printNode(root1);
    insertVal2NodeBreak(root1, 64);
    printNode(root1);

    printf("Checking values of left child: \n");
    printNode(root1->links[0]);
    printf("Checking values of right child: \n");
    printNode(root1->links[1]);




    printf("Program 7,8,9: Testing the functionality of the search tree insertion by printing the root nodes keys and links, and also searching for required values:\n");
    Node* root2 = initSearchTree();
    int keys[] = {70, 20, 30, 48, 52, 64, 11, 98, 77, 82, 89, 15};
    
    for (int i = 0; i<12; i++) {
        printf("%d", i);
        printNode(root2);
        insert(root2, keys[i]);

        if (i == 11) {

            if (search(root2, 48) != NULL) {
                printf("48 exists\n");
            } else {
                printf("48 does not exist\n");
            }

            if (search(root2, 99) != NULL) {
                printf("99 exists\n");
            } else {
                printf("99 doesnt exist\n");
            }
        }
    }

    return 0;
}