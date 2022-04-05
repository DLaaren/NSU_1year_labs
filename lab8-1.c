#include <stdio.h>
#include <stdlib.h>

#define INF 2147483648

int readGraph (int n, int m, unsigned *adjMatrix) {
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
        adjMatrix[(from-1)*n + (to-1)] = len;
        adjMatrix[(to-1)*n + (from-1)] = len;
    }
    return 1;
}

int PrimaAlgorithm (int n, unsigned *adjMatrix, int *ansStack) {
    int last_ansStack = 0;
    int *used = calloc(n, sizeof(int)); //is included in frame or not
    unsigned *minEdge = calloc(n, sizeof(unsigned)); //the shortest possible vertex from vertex i
    int *endEdge = calloc(n, sizeof(int)); //the end of the edge from vertex i
    for (int i = 0; i < n; i++) {
        minEdge[i] = INF; //all vertexes are far away from the begin
        endEdge[i] = -1;  
    }
    minEdge[0] = 0;

    for (int i = 0; i < n; i++) {
        int v = -1;
        for (int j = 0; j < n; j++) {
            if (!used[j] && (v == -1 || minEdge[j] < minEdge[v])) v = j;
        } //searching the closest vertex from the vertex i 
        if (minEdge[v] == INF) { //if there is no one
            free(used);
            free(minEdge);
            free(endEdge);
            return 0;
        }
        used[v]++;
        if (endEdge[v] != -1) {
            ansStack[last_ansStack++] = v;
            ansStack[last_ansStack++] = endEdge[v];
        }
        for (int to = 0; to < n; to++) { //looking for all edges from vertex v
            if (adjMatrix[v*n + to] < minEdge[to]) {
                minEdge[to] = adjMatrix[v*n + to];
                endEdge[to] = v;
            }
        }
    }

    free(used);
    free(minEdge);
    free(endEdge);
    return 1;
}

int main () {
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

    if (n == 0) {
        printf("no spanning tree\n");
        return 0;
    }

    unsigned *adjMatrix = calloc(n*n, sizeof(unsigned));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adjMatrix[i*n + j] = INF;
        }
    }
    if (!readGraph(n, m, adjMatrix)) {
        free(adjMatrix);
        return 0;
    }

    int *ansStack = calloc(2*(n-1), sizeof(int));
    if (!PrimaAlgorithm(n, adjMatrix, ansStack)) {
        printf("no spanning tree\n");
    }
    else {
        for (int i = 0; i < 2*(n-1); i+=2) {
            printf("%d %d\n", ansStack[i]+1, ansStack[i+1]+1);
        }
    }

    free(ansStack);
    free(adjMatrix);
    return 0;
}
