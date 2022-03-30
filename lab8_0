#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

typedef struct s_Edges {
    int from, to, len;
} Edges;

typedef struct s_Graph {
    int start, end;
} newGraph;

int readGraph (int n, int m, Edges *arr) {
    for (int i = 0; i < m; i++) {
        if (scanf("%d%d%d", &arr[i].from, &arr[i].to, &arr[i].len) != 3) {
            printf("bad number of lines\n");
            return 0;
        }
        if (arr[i].from < 1 || arr[i].from > n || arr[i].to < 1 || arr[i].to > n) {
            printf("bad vertex\n");
            return 0;
        }
        if (arr[i].len < 0 || arr[i].len > INT_MAX) {
            printf("bad length\n");
            return 0;
        }

    }
    return 1;
}

void buildGraph(int *max, int m, int *colour, Edges *arr, newGraph *graph) {
    for (int i = 0; i < m; i++) {
        if (colour[ arr[i].from ] != colour[ arr[i].to ]) {
            colour[ arr[i].from ] = colour[ arr[i].to ];
            graph[i].start = arr[i].from;
            graph[i].end = arr[i].to;

            if (graph[i].start > graph[i].end && graph[i].start > (*max)) {
                *max = graph[i].start;
            }
            else if (graph[i].end > graph[i].start && graph[i].end > (*max)) {
                *max = graph[i].end;
            }
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
    if (m < 0 || m > (n*(n+1)) / 2) {
        printf("bad number of edges\n");
        return 0;
    }
    if (n == 1 && m == 0) return 0;
        
    Edges *arr = calloc(m, sizeof(Edges));
    if (!readGraph(n, m, arr)) {
        free(arr);
        return 0;
    }

    qsort(arr, m, sizeof(Edges), compare);

    int *colour = calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        colour[i] = i;
    }
    newGraph *graph = calloc(n, sizeof(newGraph));
    int max = -1;
    buildGraph(&max, m, colour, arr, graph);
    if (n != max) {
        printf("no spanning tree\n");
        free(arr);
        free(colour);
        free(graph);
        return 0;
    }

    for (int i = n-2; i >= 0; i--) {
        printf("%d %d\n", graph[i].start, graph[i].end);
    }

    free(arr);
    free(colour);
    free(graph);
    return 0;
}
