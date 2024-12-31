#include <stdio.h>
#include <stdlib.h>

// Structure to represent an adjacency list node
typedef struct AdjListNode {
    int dest;
    struct AdjListNode* next;
} AdjListNode;

// Structure to represent an adjacency list
typedef struct AdjList {
    AdjListNode* head;
} AdjList;

// Structure to represent a graph
typedef struct Graph {
    int V;
    AdjList* array;
} Graph;

// Function to create a new adjacency list node
AdjListNode* createNode(int dest) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with V vertices
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->array = (AdjList*)malloc(V * sizeof(AdjList));
    for (int i = 0; i < V; ++i) {
        graph->array[i].head = NULL;
    }
    return graph;
}

// Function to add an edge to a directed graph
void addEdge(Graph* graph, int src, int dest) {
    AdjListNode* newNode = createNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}

// A utility function to perform DFS traversal
int DFSUtil(Graph* graph, int v, int visited[], int recStack[]) {
    // If the node is in the current recursion stack, a cycle is found
    if (recStack[v]) {
        return 1;
    }
    
    // If already visited and processed, no need to check again
    if (visited[v]) {
        return 0;
    }

    // Mark the current node as visited and in the recursion stack
    visited[v] = 1;
    recStack[v] = 1;

    // Recur for all the vertices adjacent to this vertex
    AdjListNode* temp = graph->array[v].head;
    while (temp) {
        int connectedVertex = temp->dest;
        if (DFSUtil(graph, connectedVertex, visited, recStack)) {
            return 1; // Cycle detected
        }
        temp = temp->next;
    }

    // Remove the vertex from the recursion stack
    recStack[v] = 0;
    return 0;
}

// Function to check if the graph contains a cycle
int isCyclic(Graph* graph) {
    int* visited = (int*)malloc(graph->V * sizeof(int));
    int* recStack = (int*)malloc(graph->V * sizeof(int));
    
    for (int i = 0; i < graph->V; i++) {
        visited[i] = 0;   // Mark all nodes as unvisited
        recStack[i] = 0;  // Mark all nodes as not in recursion stack
    }

    // Call DFS for all vertices
    for (int i = 0; i < graph->V; i++) {
        if (!visited[i]) {
            if (DFSUtil(graph, i, visited, recStack)) {
                free(visited);
                free(recStack);
                return 1; // Cycle detected
            }
        }
    }

    free(visited);
    free(recStack);
    return 0; // No cycle detected
}

// Function to perform topological sort
void topologicalSortUtil(Graph* graph, int v, int visited[], int* stack, int* stackIndex) {
    visited[v] = 1;
    AdjListNode* temp = graph->array[v].head;
    while (temp) {
        if (!visited[temp->dest]) {
            topologicalSortUtil(graph, temp->dest, visited, stack, stackIndex);
        }
        temp = temp->next;
    }
    stack[(*stackIndex)++] = v;
}

void topologicalSort(Graph* graph) {
    int* stack = (int*)malloc(graph->V * sizeof(int));
    int stackIndex = 0;
    int* visited = (int*)malloc(graph->V * sizeof(int));
    for (int i = 0; i < graph->V; i++) {
        visited[i] = 0;
    }

    // Perform DFS for all vertices to generate topological sort
    for (int i = 0; i < graph->V; i++) {
        if (!visited[i]) {
            topologicalSortUtil(graph, i, visited, stack, &stackIndex);
        }
    }

    // Print the topological sort
    printf("Topological Sort: ");
    for (int i = stackIndex - 1; i >= 0; i--) {
        printf("%d ", stack[i]);
    }
    printf("\n");

    free(stack);
    free(visited);
}

// Main function to demonstrate the graph operations
int main() {
    int V, E, src, dest;

    printf("Enter the number of vertices: ");
    scanf("%d", &V);

    Graph* graph = createGraph(V);

    printf("Enter the number of edges: ");
    scanf("%d", &E);

    for (int i = 0; i < E; i++) {
        printf("Enter edge (source and destination): ");
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    printf("Following is a Topological Sort of the given graph:\n");
    topologicalSort(graph);

    if (isCyclic(graph)) {
        printf("Graph contains a cycle.\n");
    } else {
        printf("Graph does not contain a cycle.\n");
    }

    // Free dynamically allocated memory
    for (int i = 0; i < V; ++i) {
        AdjListNode* temp = graph->array[i].head;
        while (temp) {
            AdjListNode* next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(graph->array);
    free(graph);

    return 0;
}
