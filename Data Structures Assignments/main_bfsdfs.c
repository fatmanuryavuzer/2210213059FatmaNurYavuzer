#include <stdio.h>

#define MAX 50

/* --------- Grafik Yapýsý (Adjacency List) ----------- */

int adj[MAX][MAX];   /* komþuluk matrisi gibi tutacaðýz */
int n;               /* düðüm sayýsý */

int visited[MAX];

/* ---------------- DFS (Recursive) ------------------- */

void DFS(int v) {
    int i;

    visited[v] = 1;
    printf("%d ", v);

    for (i = 0; i < n; i++) {
        if (adj[v][i] == 1 && !visited[i]) {
            DFS(i);
        }
    }
}

/* ---------------- BFS (Queue ile) ------------------- */

void BFS(int start) {
    int queue[MAX];
    int front = 0, rear = 0;
    int i, v;

    for (i = 0; i < n; i++)
        visited[i] = 0;

    visited[start] = 1;
    queue[rear++] = start;

    while (front < rear) {
        v = queue[front++];
        printf("%d ", v);

        for (i = 0; i < n; i++) {
            if (adj[v][i] == 1 && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }
}

/* -------------------- MAIN ------------------------- */

int main() {
    int e;
    int i, u, v;
    int start;

    printf("Kac dugum (0..n-1): ");
    scanf("%d", &n);

    printf("Kac edge (baglanti): ");
    scanf("%d", &e);

    for (i = 0; i < n; i++) {
        int j;
        for (j = 0; j < n; j++)
            adj[i][j] = 0;
    }

    printf("\nEdge'leri gir (u v):\n");
    for (i = 0; i < e; i++) {
        scanf("%d %d", &u, &v);
        adj[u][v] = 1;
        adj[v][u] = 1;   /* yönsüz grafik */
    }

    printf("\nBaslangic dugumu: ");
    scanf("%d", &start);

    /* DFS */
    for (i = 0; i < n; i++)
        visited[i] = 0;

    printf("\nDFS: ");
    DFS(start);

    /* BFS */
    printf("\nBFS: ");
    BFS(start);

    printf("\n");
    return 0;
}

