#include <stdio.h>
#include <stdlib.h>

typedef struct s_Edges {
    int from, to, len;
} Edges;

int readGraph (int n, int m, Edges *arrEdges) {
    int from, to, len;
    for (int i = 0; i < m; i++) {
        if (scanf("%d%d%d", &from, &to, &len) != 3) {
            printf("bad number of lines\n");
            return 0;
        }
        if (from < 1 || from > n || to < 1 || to > n) {
            printf("bad vertex\n");
            return 0;
        }
        if (len < 0) {
            printf("bad length\n");
            return 0;
        }
        arrEdges[i].from = from-1;
        arrEdges[i].to = to-1;
        arrEdges[i].len = len;
    }
    return 1;
}

void makeSet (int v, int *parent) { //create set concluding only v
    parent[v] = v;
}

int findSet (int v, int *parent) { //find set with v (find the leader)
    if (v == parent[v]) return v;
    return parent[v] = findSet(parent[v], parent);
}

void uniteSets (int a, int b, int *parent) { //unite two sets with a and b
    a = findSet(a, parent);
    b = findSet(b, parent);
    if (a != b) parent[b] = a;
}

void KruskalAlgorithm (int m, int *frameLen, Edges *arrEdges, int *parent, int *frame) {
    for (int i = 0; i < m; i++) {
        if (findSet(arrEdges[i].from, parent) != findSet(arrEdges[i].to, parent)) { //if from and to from different sets
            uniteSets(arrEdges[i].from, arrEdges[i].to, parent);
            frame[*frameLen] = i; //the number of edge for frame
            (*frameLen)++; 
        }
    }
}

int compare (const void *x1_ptr, const void *x2_ptr) {
    Edges *x1 = (Edges*)x1_ptr;
    Edges *x2 = (Edges*)x2_ptr;

    int res = 0;
    if (x1->len < x2->len) {
        res = -1;
    }
    else if (x1->len == x2->len) {
        res = 0;
    }
    else if (x1->len > x2->len) {
        res = 1;
    }
    
    return res;
} 

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m;
    if (scanf("%d%d", &n, &m) != 2) return 0;
    if (n < 0 || n > 5000) {
        printf("bad number of vertices\n");
        return 0;
    }
    if (m < 0 || m > (n*(n-1)) / 2) {
        printf("bad number of edges\n");
        return 0;
    }

    Edges *arrEdges = calloc(m, sizeof(Edges));
    if (!readGraph(n, m, arrEdges)) {
        free(arrEdges);
        return 0;
    }

    qsort(arrEdges, m, sizeof(Edges), compare);

    int *parent = calloc(n, sizeof(int));
    int *frame = calloc(n , sizeof(int));
    
    for (int i = 0; i < n; i++) {
        makeSet(i, parent);
    } 

    int frameLen = 0;
    KruskalAlgorithm(m, &frameLen, arrEdges, parent, frame);  
    if (frameLen != n-1) {
        printf("no spanning tree\n");
        free(arrEdges);
        free(parent);
        free(frame);
        return 0;

    }

    for (int i = 0; i < frameLen; i++) {
        printf("%d %d\n", arrEdges[frame[i]].from + 1, arrEdges[frame[i]].to + 1);
    }

    free(arrEdges);
    free(parent);
    free(frame);
    return 0;
}
