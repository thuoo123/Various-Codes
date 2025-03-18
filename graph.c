#include <stdio.h>
#include <stdlib.h>
#define INF 999999

void print_path(int* parent, int j);
int* dijkstra(int** graph, int src, int V, int* parent);
int path_choice(int* dist, int* spt, int V);

int main() {
    int V;
    int i, j;
    int** graph;
    char* labels;
    char src;
    int src_index;
    int* dist;
    int* parent;

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    labels = (char*)malloc(sizeof(char) * V);
    for (i = 0; i < V; i++) {
        labels[i] = 'a' + i;
    }

    graph = (int**)malloc(sizeof(int*) * V);
    for (i = 0; i < V; i++) {
        graph[i] = (int*)malloc(sizeof(int) * V);
    }

    printf("Enter the Adjacency Matrix:\n");
    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    // Clear input buffer
    while ((getchar()) != '\n' && getchar() != EOF);

    printf("Enter the source vertex: ");
    scanf(" %c", &src);

    for (i = 0; i < V; i++) {
        if (src == labels[i]) {
            src_index = i;
            break;
        }
    }
    
    if (i == V) {
        printf("Source vertex not found.\n");
        for (i = 0; i < V; i++) {
            free(graph[i]);
        }
        free(graph);
        free(labels);
        return 1;
    }

    parent = (int*)malloc(sizeof(int) * V);
    if (parent == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    dist = dijkstra(graph, src_index, V, parent);
    printf("The Results are as follows:\n");
    for (i = 0; i < V; i++) {
        printf("Shortest distance from %c to %c: %d\n", labels[src_index], labels[i], dist[i]);
        printf("Path: ");
        print_path(parent, i);
        printf("\n");
    }

    free(dist);
    free(parent);
    for (i = 0; i < V; i++) {
        free(graph[i]);
    }
    free(graph);
    free(labels);

    return 0;
}

int* dijkstra(int** graph, int src, int V, int* parent) {
    int i, v;
    int count;
    int* dist = (int*)malloc(sizeof(int) * V);
    int* spt_set = (int*)malloc(sizeof(int) * V);

    if (dist == NULL || spt_set == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    for (i = 0; i < V; i++) {
        dist[i] = INF;
        spt_set[i] = 0;
        parent[i] = -1; // Initialize parent array
    }
    dist[src] = 0;

    for (count = 0; count < V - 1; count++) {
        int u = path_choice(dist, spt_set, V);
        spt_set[u] = 1;

        for (v = 0; v < V; v++) {
            if ((!spt_set[v]) && (graph[u][v] > 0) && (dist[u] != INF) && (dist[u] + graph[u][v] < dist[v])) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u; // Update parent
            }
        }
    }

    free(spt_set);
    return dist;
}

int path_choice(int* dist, int* spt, int V) {
    int min = INF;
    int min_index = -1;
    int i;
    for (i = 0; i < V; i++) {
        if ((spt[i] == 0) && (dist[i] <= min)) {
            min = dist[i];
            min_index = i;
        }
    }
    return min_index;
}

void print_path(int* parent, int j) {
    if (parent[j] == -1) {
        printf("%c -> ", 'a' + j);
        return;
    }
    print_path(parent, parent[j]);
    printf("%c -> ", 'a' + j);
}
