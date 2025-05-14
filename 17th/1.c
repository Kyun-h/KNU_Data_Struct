//2024004060 황상균
//unweighted undirected graph
#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 100
#define N 30

typedef struct node* nodePoint;
typedef struct node{
    int vertex;
    nodePoint next;
} Node;

int queue[MAX_QUEUE_SIZE];
int parent[N];
int front = 0, rear = 0;

nodePoint addlist(Node** list,int from, int to); //list 추가
void bfs(int v,int* visited,Node** list); //BFS 변환
void dfs(int v, int* visited, Node** list); //DFS 변환
void addq(int v); //Queue에 추가
int deleteq(); //Queue에서 pop
void DFS_connected(int n,int* visited,Node** list); //DFS_connected component 출력 함수
void BFS_connected(int n,int* visited,Node** list); //BFS_connected component 출력 함수
void BFS_Path(int from, int to); //BFS_Path 출력

int main(void){
    FILE *f = fopen("in.txt","r");
    if(f==NULL){
        fprintf(stderr,"CANNOT OPEN THE FILE.");
        exit(EXIT_FAILURE);
    }
    int from, to, ver_num, edge_num;
    fscanf(f,"%d %d",&ver_num, &edge_num);
    
    Node** list = (Node**)malloc((ver_num+1)*sizeof(Node*));
    for (int i = 0; i <= ver_num; i++) list[i] = NULL;

    int* visited = (int*)malloc((ver_num+1)*sizeof(int));
    for (int i = 0; i <= ver_num; i++) visited[i] = 0;

    for(int i=0; i<edge_num; i++){
        fscanf(f,"%d %d", &from, &to);
        addlist(list,from,to);
        addlist(list,to,from);
    }

    printf("DFS connected component\n");
    DFS_connected(ver_num, visited, list);
    puts("");

    for (int i = 0; i <= ver_num; i++) visited[i] = 0;

    printf("BFS connected component\n");
    BFS_connected(ver_num, visited, list);
    puts("");

    while(1){
        printf("Input (from to): ");
        scanf("%d %d", &from, &to);
        if(from<0 || to<0) break;

        printf("BFS Path(%d==>%d):\n",from,to);
        BFS_Path(from,to);
        puts("\n");
    }

    fclose(f);
    return 0;

}

void BFS_Path(int from, int to){
    if(from==to){
        printf("%d",from);
        return;
    }

    if (parent[to] == -1) {
        printf("No Path");
        return;
    }

    printf("%d ", to);
    BFS_Path(from, parent[to]);  
}

void addq(int v){ //Queue에 추가
    queue[rear++] = v;
}

int deleteq(){ //Queue에서 pop
    return queue[front++];
}

void dfs(int v, int* visited, Node** list) { //DFS 변환
    visited[v] = 1;
    printf("%4d", v);

    nodePoint cur = list[v];
    while (cur != NULL) {
        int next = cur->vertex;
        if (!visited[next]) {
            dfs(next, visited, list);
        }
        cur = cur->next;
    }
}


void bfs(int v,int* visited,Node** list){ //BFS 변환
    nodePoint w;
    front = rear = 0;
    printf("%4d",v);
    visited[v] = 1;
    parent[v] = -1;
    addq(v);
    while(front<rear){
        v = deleteq();
        for(w=list[v]; w; w=w->next){
            if(!visited[w->vertex]){
                printf("%5d",w->vertex);
                visited[w->vertex] = 1;
                parent[w->vertex] = v;
                addq(w->vertex);
            }
        }
    }

}

void DFS_connected(int n,int* visited,Node** list){ //DFS_connected component 출력 함수
    int cnt=0;
    for(int i=0; i<=n; i++){
        if(!visited[i]){
            printf("Componenet %d:",cnt++);
            dfs(i,visited,list);
            puts("");
        }
    }
}

void BFS_connected(int n,int* visited,Node** list){ //BFS_connected component 출력 함수
    int cnt=0;
    for(int i=0; i<=n; i++){
        if(!visited[i]){
            printf("Componenet %d:",cnt++);
            bfs(i,visited,list);
            puts("");
        }
    }
}

nodePoint addlist(Node** list,int from, int to){ //list 앞에 추가
    nodePoint temp = (Node*)malloc(sizeof(Node));
    temp->vertex = to;
    temp->next = list[from];
    list[from] = temp;
    return temp;
}