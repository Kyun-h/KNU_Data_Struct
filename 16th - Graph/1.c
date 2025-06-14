//2024004060 황상균
//directed graph - vertex & edge
#include <stdio.h>
#include <stdlib.h>

typedef struct node* nodePoint;
typedef struct node{
    int vertex;
    nodePoint next;
} Node;

nodePoint addlist(Node** list,int , int ); //list 앞에 추가
void printList(Node** list,int size); //List 출력
void printIndgree(Node** list,int vt,int*); //Indegree 출력
void printOutdgree(Node** list,int vt,int* indegree); //Outdegree 출력
void search(Node** list,int from, int to,int vt,int* indegree, int* outdegree); //insert or Delete 결정 함수
void delete(Node** list,int from,int to,int,int* indegree, int* outdegree); //delete 함수
nodePoint addLast(Node** list, int from, int to,int,int* indegree, int* outdegree); //list 뒤에 추가(insert)

int main(void){
    FILE *f=fopen("in.txt","r");
    if(f==NULL){
        fprintf(stderr,"CANNOT OPEN THE FILE.");
        exit(EXIT_FAILURE);
    }
    int vt,from,to, eg;
    fscanf(f,"%d %d", &vt, &eg);

    Node** list = (Node**)malloc((vt+1)*sizeof(Node*));
    Node** inverse_list = (Node**)malloc((vt+1)*sizeof(Node*));
    int* indegree = (int*)calloc(vt + 1, sizeof(int));
    int* outdegree = (int*)calloc(vt + 1, sizeof(int));

    for(int i = 0; i <= vt; i++) {
        list[i] = NULL;
        inverse_list[i] = NULL;
    }

    for(int idx=0; idx<eg; idx++){
        fscanf(f,"%d %d", &from, &to);
        addlist(list,from,to);
        indegree[to]++;
        outdegree[from]++;
        addlist(inverse_list,to,from);
    }
    printf("Linked adjacency list\n");
    printList(list,vt);
    puts("");

    printf("Inverse adjacency list\n");
    printList(inverse_list,vt);
    puts("");

    printf("Indgree\n");
    printIndgree(list,vt,indegree);
    puts("");

    printf("Outdgree\n");
    printOutdgree(list,vt,outdegree);
    puts("");

    int in_from, in_to;
    while(1){
        printf("Input (from to): ");
        scanf("%d %d",&in_from,&in_to);
        if(in_from < 0 || in_to < 0) break;
        search(list,in_from,in_to,vt,indegree,outdegree);
    }

    fclose(f);
    return 0;
}

void search(Node** list,int from, int to,int vt,int* indegree, int* outdegree){ //insert or delete 결정 
    nodePoint temp = list[from];
    int found=0;
    while(temp != NULL){
        if(temp->vertex == to){
            found=1;
            break;
        }
        else temp = temp->next;
    }

    if(found==1) delete(list,from,to,vt,indegree,outdegree);
    else addLast(list,from,to,vt,indegree,outdegree);
    
}

void delete(Node** list,int from,int to,int vt,int* indegree, int* outdegree){ //delete 해줌
    nodePoint cur = list[from]; 
    nodePoint prev = NULL;

    while (cur != NULL) {
        if (cur->vertex == to) {
            if (prev == NULL) {
                list[from] = cur->next;
            } else {
                prev->next = cur->next;
            }
            free(cur);
            indegree[to]--;
            outdegree[from]--;
            printf("Delete (%d %d)...\n",from,to);
            printList(list,vt);
            puts("");
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}

nodePoint addLast(Node** list, int from, int to,int vt,int* indegree, int* outdegree) { //insert (뒤에 추가)
    nodePoint newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = to;
    newNode->next = NULL;
    indegree[to]++;
    outdegree[from]++;

    if (list[from] == NULL) {
        list[from] = newNode;
        printf("Insert (%d %d)...\n",from,to);
        printList(list,vt);
        puts("");
        return newNode;
    }

    nodePoint cur = list[from];
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = newNode;

    printf("Insert (%d %d)...\n",from,to);
    printList(list,vt);
    puts("");
    return newNode;
}

void printOutdgree(Node** list,int vt,int* outdegree){ //outdegree 출력
    for(int i=0; i<=vt; i++){
        printf("[ %d] %d\n",i,outdegree[i]);
    }
}

void printIndgree(Node** list,int vt,int* indegree){ //indegree 출력
    for(int i=0; i<=vt; i++){
        printf("[ %d] %d\n",i,indegree[i]);
    }
}

nodePoint addlist(Node** list,int from, int to){ //list 앞에 추가
    nodePoint temp = (Node*)malloc(sizeof(Node));
    temp->vertex = to;
    temp->next = list[from];
    list[from] = temp;
    return temp;
}

void printList(Node** list,int vt){ //list 출력
    for(int i=0; i<=vt; i++){
        nodePoint cur = list[i];
        printf("[ %d]",i);
        while(cur != NULL){
            printf("%3d",cur->vertex);
            cur = cur->next;
        }
        puts("");
    }

}