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
        if (len < 0) {
            printf("bad length\n");
            return 0;
        }
        adjMatrix[(from-1)*n + (to-1)] = len;
        adjMatrix[(to-1)*n + (from-1)] = len;
    }
    return 1;
}

int findNextVertex (int *isVisited, unsigned *dist, int n, int start) {
    int minVertex = -1;
    if (!isVisited[start]) {
        isVisited[start]++;
        return start;
    }
    for (int k = 0; k < n; k++) {
        if (!isVisited[k] && (minVertex == -1 || dist[k] < dist[minVertex])) {
            minVertex = k;
        }
    }
    isVisited[minVertex]++;
    return minVertex;
}

void findWays (int n, int *adjMatrix, int *isVisited, unsigned *dist, int *countWays, int start, int *path) {
    countWays[start] = 1;
    for (int i = 0; i < n; i++) {
        int vertex = findNextVertex(isVisited, dist, n, start);
        if (start == vertex) {
            dist[start] = 0;
        }
        for (int j = 0; j < n; j++) {
            if (adjMatrix[vertex * n + j] != 0) {
                if (countWays[j] == 0) {
                    countWays[j] == countWays[vertex];
                }
                else {
                    countWays[j] += countWays[vertex];
                }
                unsigned check = dist[vertex] + adjMatrix[vertex * n + j];
                if (check == INT_MAX - 2 || check == INT_MAX - 1) {
                    break;
                }
                if (check < dist[j]) {
                    dist[j] = check;
                    path[j] = vertex;
                }
            }
        }
    }
}


void freeEverything (int *adjMatrix, int *isVisited, unsigned *dist, int *path, int *countWays) {
    free(adjMatrix);
    free(isVisited);
    free(dist);
    free(path);
    free(countWays);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m, start, end;
    if (scanf("%d%d%d%d", &n, &start, &end, &m) != 4) {
        return 0;
    }
    if (n < 0 || n > 5000) {
        printf("bad number of vertices\n");
        return 0;
    }
    if (m < 0 || m > ((n * (n-1))/2)) {
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

    int *countWays = calloc(n, sizeof(int));
    int *isVisited = calloc(n, sizeof(int));
    unsigned *dist = calloc(n, sizeof(unsigned));
    int *path = calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        dist[i] = UINT_MAX;
    }

    findWays(n, adjMatrix, isVisited, dist, countWays, start - 1, path);
    for (int i = 0; i < n; i++) {
        if (dist[i] >= (unsigned) INT_MAX + 1 && dist[i] < UINT_MAX) {
            printf("INT_MAX+ ");
        } 
        else if (dist[i] == UINT_MAX) {
            printf("oo ");
        }  
        else {
            printf("%u ", dist[i]);
        }
    }
    printf("\n");

    if (dist[end-1] == UINT_MAX) {
        printf("no path\n");
    }
    else if (dist[end-1] > INT_MAX && countWays[end-1] > 1) {
        printf("overflow\n");
    }
    else if (start == end) {
        printf("%d\n", start);
    }

    else {
        printf("%d ", end);
        int p = end-1;
        while (p != start-1) {
            p = path[p]; 
            printf("%d ", p+1);
        }
        printf("\n");
    }
    freeEverything(adjMatrix, isVisited, dist, path, countWays);
    return 0;
}
