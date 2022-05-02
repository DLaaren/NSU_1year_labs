#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    int height;
    struct Node *left, *right;
} Node;

Node *initAllocator (int n) {
    Node *allocator = malloc (n * sizeof(Node));
    return allocator;
}

Node *nodeAllocator (Node *allocator) {
    static int block = 0;
    return &allocator[block++];
}

Node *createNode (int key, Node *allocator) {
    Node *root = nodeAllocator(allocator);
    
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

Node *insert (Node *node, int key, Node *allocator) {
    if (!node) { 
        return createNode(key, allocator);
    }
    else if (key <= node->key) {
        node->left = insert(node->left, key, allocator);
    }
    else {
        node->right = insert(node->right, key, allocator);
    }
    updateHeight(node);
    return balance(node);
}

int main () {
    // freopen("input.txt", "r", stdin); 
    // freopen("output.txt", "w", stdout);

    int n;
    if (!scanf("%d", &n)) return 0;

    Node *allocator = initAllocator(n); // выделили блок память под N узлов

    Node *root = NULL;
    for (int i = 0; i < n; i++) {
        int key;
        if (!scanf("%d", &key)) {
            free(allocator);
            return 0;
        }
        root = insert(root, key, allocator);
    }

    printf("%d\n", findHeight(root));
    free(allocator);
    return 0; 
}
