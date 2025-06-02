//2024004060 황상균
//minumum cost spanning tree
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int u, v, weight;
} Edge;

int parent[MAX];
Edge edges[MAX * MAX];
Edge mst[MAX];

int edgeCount = 0;
int mstCount = 0;

int find(int x) ; //root 찾는 함수
void unionSet(int a, int b); // 하나로 합침
int compare(const void* a, const void* b); //qsort를 위한 비교 함수

int main() {
    FILE *fp = fopen("in.txt", "r");
    if (!fp) {
        fprintf(stderr,"CANNOT OPEN THE FILE.");
        exit(EXIT_FAILURE);
    }
    
    int n;
    fscanf(fp, "%d", &n);
    
    int matrix[MAX][MAX];
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            fscanf(fp, "%d", &matrix[i][j]);
        }
    }
    
    for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
    if (matrix[i][j] != 0) {
        edges[edgeCount].u = i;
        edges[edgeCount].v = j;
        edges[edgeCount].weight = matrix[i][j];
        edgeCount++;
    }
    
    for (int i = 0; i < n; i++) parent[i] = i;
    
    qsort(edges, edgeCount, sizeof(Edge), compare); //정렬 함수 qsort
    
    int u,v,w;
    for (int i = 0; i < edgeCount; i++) {
        u = edges[i].u;
        v = edges[i].v;
        w = edges[i].weight;
        
        printf("try (%d, %d, %d)==> ", u, v, w);
        
        if (find(u) != find(v)) {
            printf("OK\n");
            unionSet(u, v);
            mst[mstCount++] = edges[i];
        } else {
            printf("cycle\n");
        }
        
        if (mstCount == n - 1) break;
    }
    
    printf("\n(edge):weight\n");
    for (int i = 0; i < mstCount; i++) {
        printf("(%3d, %3d) : %d\n", mst[i].u, mst[i].v, mst[i].weight);
    }
    
    fclose(fp);
    return 0;
}

int find(int x) { //root 찾기
    while (parent[x] != x) x = parent[x];
    return x;
}

void unionSet(int a, int b) { //하나로 합치기
    int rootA = find(a);
    int rootB = find(b);
    if (rootA != rootB)
    parent[rootB] = rootA;
}

int compare(const void* a, const void* b) { //qsort를 위한 비교 함수
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}