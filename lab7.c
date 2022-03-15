#include <stdio.h>
#include <stdlib.h>

typedef unsigned char uchar;

int read_graph(int n, int m, uchar *adjMatrix) {
    for (int i = 0; i < m; i++) {
        int from, to;
        if (scanf("%d%d", &from, &to) != 2) {
            printf("bad number of lines\n");
            return 0;
        }
        if (from < 1 || from > n || to < 1 || to > n) {
            printf("bad vertex\n");
            return 0;
        }
        adjMatrix[(from-1)*n + (to-1)] = 1;
        
    }
    return 1;
}

int DFS(int n, uchar *adjMatrix, int vertex, char *colour, int *answer_stack, int *free_place) {

    if (colour[vertex] == 1) { //is grey
        printf("impossible to sort\n");
        return 0;
    }
    if (colour[vertex] == 2) { //is black
        return 1;
    }

    colour[vertex]++; // has been painted in grey
    for (int i = 0; i < n; i++) {
        if (adjMatrix[vertex*n + i] == 1) {
            if (!DFS(n, adjMatrix, i, colour, answer_stack, free_place)) {
                return 0;
            }
        }
    }
    colour[vertex]++; //has been painted in black
    answer_stack[(*free_place)++] = vertex + 1;
    return 1;
}

void free_everything(uchar *adjMatrix, char *colour, int *answer_stack) {
    free(adjMatrix);
    free(colour);
    free(answer_stack);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m;
    if (scanf("%d%d", &n, &m) != 2) {
        printf("bad number of lines\n");
        return 0;
    }
    if (n < 0 || n > 2000) {
        printf("bad number of vertices\n");
        return 0;
    }
    if (m < 0 || m > (n * ((n + 1) / 2))) {
        printf("bad number of edges\n");
        return 0;
    }

    char *colour = calloc(n, sizeof(char));
    uchar *adjMatrix = calloc(n * n,  sizeof(uchar));
    int *answer_stack = calloc(n, sizeof(int));
    int free_place = 0;

    if (!read_graph(n, m, adjMatrix)) {
        free_everything(adjMatrix, colour, answer_stack);
        return 0;
    }
    else {
        for (int vertex = 0; vertex < n; vertex++) {
            if (!DFS(n, adjMatrix, vertex, colour, answer_stack, &free_place)) {
                free_everything(adjMatrix, colour, answer_stack);
                return 0;
            }
        }
        for (int i = free_place - 1; i >= 0; i--) {
            printf("%d ", answer_stack[i]);
        }
    }

    free_everything(adjMatrix, colour, answer_stack);

    return 0;
}
