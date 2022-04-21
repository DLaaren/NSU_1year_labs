#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    int height;
    struct Node *left, *right;
} Node;

static Node *allocator;

void initAllocator (int n) {
    allocator = malloc(n * sizeof(Node));
}

Node *nodeAllocator () {
    static int block = 0;
    return &allocator[block++];
}

void freeAllocator () {
    free(allocator);
}


Node *createNode (int key) {
    Node *root = nodeAllocator();
    
    root->key = key;
    root->left = NULL;
    root->right = NULL;
    root->height = 1;

    return root;
}

int findHeight (Node *node) {
    return (node ? node->height : 0); //node could be NULL -> height = 0
}

inline static int max (int a, int b) {
    return a > b ? a : b;
}

void updateHeight (Node *node) {
    int leftHeight = findHeight(node->left);
    int rightHeight = findHeight(node->right);
    node->height = max(leftHeight, rightHeight) + 1;
}

Node *rightRotation (Node *x) {
    Node *y = x->left;
    Node *T = y->right;
    y->right = x;
    x->left = T;

    updateHeight(x);
    updateHeight(y);

    return y;
}

Node *leftRotation (Node *x) {
    Node *y = x->right;
    Node *T = y->left;
    y->left = x;
    x->right = T;

    updateHeight(x);
    updateHeight(y);

    return y;
}

int balanceFactor (Node *node) {
    if (!node) 
        return 0;
    return findHeight(node->left) - findHeight(node->right);
}

Node *balance (Node *node) {
    updateHeight(node);
    if (balanceFactor(node) == 2) { //левое поддерево намного ниже правого
        if (balanceFactor(node->left) < 0) {
            node->left = leftRotation(node->left);
        }
        return rightRotation(node);
    }
    else if (balanceFactor(node) == -2) { // правое поддерево намного ниже левого
        if (balanceFactor(node->right) > 0) {
            node->right = rightRotation(node->right);
        }
        return leftRotation(node);
    }
    return node; //если балансировка не нужна
}

Node *insert (Node *node, int key) {
    if (!node) { 
        return createNode(key);
    }
    else if (key <= node->key) {
        node->left = insert(node->left, key);
    }
    else {
        node->right = insert(node->right, key);
    }
    return balance(node); //прежде чем вставить новый узел - его нужно сбалансировать
}

void freeAVL () {
    freeAllocator ();
}

void printfAVL (Node *root) {
    if (root) {
        printfAVL(root->left);
        printf("%d ", root->key);
        printfAVL(root->right);
    }
}

int main () {
    freopen("input.txt", "r", stdin); 
    freopen("output.txt", "w", stdout);

    int n;
    if (!scanf("%d", &n)) return 0;

    initAllocator(n); // выделили блок память под N узлов

    Node *root = NULL;
    for (int i = 0; i < n; i++) {
        int key;
        if (!scanf("%d", &key)) {
            freeAVL();
            return 0;
        }
        root = insert(root, key);
    }
    //printfAVL(root);
    //printf("\n");
    printf("%d\n", findHeight(root));
    freeAVL();
    return 0; 
}
