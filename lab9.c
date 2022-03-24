#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int readGraph (int n, int m, int *adjMatrix) {
    for (int i = 0; i < m; i++) {
        int from, to, len;
        if (scanf("%d%d%d", &from, &to, &len) != 3) {
            printf("bad number of lines\n");
            return 0;
        }
        if (from < 1 || from > n || to < 1 || to > n) {
            printf("bad vertex\n");
            return 0;
        }
        if (len < 0 || len > INT_MAX) {
            printf("bad length\n");
            return 0;
        }
        adjMatrix[(from-1)*n + (to-1)] = len;
        adjMatrix[(to-1)*n + (from-1)] = len;
    }
    return 1;
}

int findNextVertex (int *isVisited, unsigned *marks, int n, int start) {
    int minVertex = -1;
    if (!isVisited[start]) {
        isVisited[start]++;
        return start;
    }
    for (int k = 0; k < n; k++) {
        if (!isVisited[k] && (minVertex == -1 || marks[k] < marks[minVertex])) {
            minVertex = k;
        }
    }
    isVisited[minVertex]++;
    return minVertex;
}

void findWays (int n, int *adjMatrix, int *isVisited, unsigned *marks, int *bigWays, int start) {
    for (int i = 0; i < n; i++) {
        int vertex = findNextVertex(isVisited, marks, n, start);
        if (start == vertex) {
            marks[start] = 0;
        }
        for (int j = 0; j < n; j++) {
            if (adjMatrix[vertex * n + j] != 0) {
                if (adjMatrix[vertex * n + j] == INT_MAX){
                    bigWays[j] += bigWays[vertex];
                }
                unsigned check = marks[vertex] + adjMatrix[vertex * n + j];
                if (check == INT_MAX - 2 || check == INT_MAX - 1) {
                    break;
                }
                if (check < marks[j]) {
                    marks[j] = check;
                }
            }
        }
    }
}

int findPath (int n, int *path, int *adjMatrix, unsigned *marks, int start, int end, int *bigWays) {
    if (start == end) {
        return -3;
    }
    unsigned weight = marks[end]; //вес вершины
    if (weight == UINT_MAX) {
        return -1;
    }
    if (weight > INT_MAX && bigWays[end] >= 2) {
        return -2;
    }
    path[0] = end + 1;
    int k = 1;
    while (end != start) {
        for (int i = 0; i < n; i++) {
            if (adjMatrix[i * n + end] != 0) {
                unsigned temp = weight - adjMatrix[i * n + end];
                if (temp == marks[i]) {
                    weight = temp;
                    end = i;
                    path[k] = i+1;
                    k++;
                }
            }
        }
    }
    return k;
}

void freeEverything (int *adjMatrix, int *isVisited, unsigned *marks, int *path, int *bigWays) {
    free(adjMatrix);
    free(isVisited);
    free(marks);
    free(path);
    free(bigWays);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m, start, end;
    if (!scanf("%d%d%d%d", &n, &start, &end, &m)) {
        return 0;
    }
    if (n < 0 || n > 5000) {
        printf("bad number of vertices\n");
        return 0;
    }
    if (m < 0 || m > (n * ((n + 1) / 2))) {
        printf("bad number of edges\n");
        return 0;
    }
    if (start < 1 || start > n || end < 1 || end > n) {
        printf("bad vertex\n");
        return 0;
    }

    int *adjMatrix = calloc(n*n, sizeof(int));
    if (!readGraph(n, m, adjMatrix)) {
        free(adjMatrix);
        return 0;
    }

    int *bigWays = calloc(n, sizeof(int));
    bigWays[start-1] = 1;
    int *isVisited = calloc(n, sizeof(int));
    unsigned *marks = calloc(n, sizeof(unsigned));
    for (int i = 0; i < n; i++) {
        marks[i] = UINT_MAX;
    }

    findWays(n, adjMatrix, isVisited, marks, bigWays, start - 1);
    for (int i = 0; i < n; i++) {
        if (marks[i] >= (unsigned) INT_MAX + 1 && marks[i] < UINT_MAX) {
            printf("INT_MAX+ ");
        } 
        else if (marks[i] == UINT_MAX) {
            printf("oo ");
        }  
        else {
            printf("%u ", marks[i]);
        }
    }
    printf("\n");

    int *path = calloc(n, sizeof(int));
    int t = findPath(n, path, adjMatrix, marks, start-1, end-1, bigWays);
    if (t == -1) {
        printf("no path\n");
    }
    else if (t == -2) {
        printf("overflow\n");
    }
    else if (t == -3) {
        printf("%d\n", start);
    }

    else {
        for (int i = 0; i < t; i++) {
            printf("%d ", path[i]);
        }
        printf("\n");
    }
    freeEverything(adjMatrix, isVisited, marks, path, bigWays);
    return 0;
}
