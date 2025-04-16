//2024004060 황상균
//doubly linked circular list with header node
#include <stdio.h>
#include <stdlib.h>


typedef struct node* nodePoint;
typedef struct node{
    nodePoint llink;
    int data;
    nodePoint rlink;
} Node;

void insert(nodePoint head, int); //head 뒤에 오름차순으로 노드 삽입하는 함수 
void delete(nodePoint head, int); //노드의 data가 key에 해당하면 삭제시키는 함수 
void printList(nodePoint head); //List 출력 
nodePoint createNode(int); //노드 생성 
nodePoint createHeader(); //head 생성 
nodePoint findNode(nodePoint head, int key); //printLeft와 Right에 사용할 Node를 찾아주는 함수 
void printLeft(nodePoint head, int key); //좌측 리스트 출력 
void printRight(nodePoint head, int key); //우측 리스트 출력

int main(void){
    nodePoint head=NULL;
    FILE *f;
    if((f=fopen("in.txt","r"))==NULL){
        fprintf(stderr,"CANNOT OPEN THE FILE.");
        exit(EXIT_FAILURE);
    }
    
    head = createHeader(); //헤더 생성 

    int num;
    fscanf(f,"%d", &num);

    int element;
    for(int i=0; i<num; i++){
        fscanf(f,"%d",&element);
        insert(head,element); //리스트에 추가 
    }
    printf("리스트 출력:\n");
    printList(head);
    puts("");

    int ques;
    printf("Left/Right 출력 위한 숫자 입력 : ");
    scanf("%d",&ques);
    puts("");

    printf("%d 기준 좌측 리스트 출력:\n",ques);
    printLeft(head,ques);
    puts("");

    printf("%d 기준 우측 리스트 출력:\n",ques);
    printRight(head,ques);
    puts("");

    int input=0;
    while(input!=-1){
        printf("삭제할 숫자 입력: ");
        scanf("%d",&input);
        if(input==-1){
            printf("Quit\n");
            break;
        }
        else{
            delete(head,input);
            printList(head);
        }
    }

    fclose(f);
    return 0;
}

nodePoint findNode(nodePoint head, int key){ //list를 순회하며 data가 key에 해당하는 노드 return
    nodePoint cur = head->rlink;
    while(cur!=head){
        if(cur->data==key) return cur;
        cur = cur->rlink;
    }
    return NULL;
}

void printLeft(nodePoint head, int key){ //좌측 리스트 출력 
    nodePoint target = findNode(head,key);
    if(!target){
        return;
    }

    nodePoint cur = target;
    do{
        if(cur!=head)
            printf("%d ", cur->data);
        cur = cur->llink;
    }while(cur!=target);

    puts("");
}

void printRight(nodePoint head, int key){ //우측 리스트 출력 
    nodePoint target = findNode(head,key);
    if(!target){
        return;
    }

    nodePoint cur = target;
    do{
        if(cur!=head)
            printf("%d ", cur->data);
        cur = cur->rlink;
    }while(cur!=target);

    puts("");
}

nodePoint createHeader(){ //head 생성 
    nodePoint head = (Node*)malloc(sizeof(Node));
    head->llink = head;
    head->rlink = head;
    head->data = -1;
    return head;
}

nodePoint createNode(int data){ //Node 생성 
    nodePoint newnode;
    newnode = (Node*)malloc(sizeof(Node));
    newnode->data = data;
    newnode->llink = NULL;
    newnode->rlink = NULL;
    return newnode;
}

void printList(nodePoint head){ //List 출력 
    nodePoint cur=head->rlink;

    while(cur!=head){
        printf("%d ",cur->data);
        cur = cur->rlink;
    }
    puts("");
}

void insert(nodePoint head, int data){ //오름차순으로 노드 추가 
    nodePoint newnode = createNode(data);
    nodePoint cur = head->rlink;

    while(cur!=head && cur->data>data){
        cur=cur->rlink;
    }
    newnode->rlink = cur;
    newnode->llink = cur->llink;
    cur->llink->rlink = newnode;
    cur->llink = newnode;
}

void delete(nodePoint head, int key){ //data가 key에 해당하는 노드 제거 
    nodePoint cur = head->rlink;

    while(cur!=head){
        if(cur->data == key){
            cur->llink->rlink = cur->rlink;
            cur->rlink->llink = cur->llink;
            free(cur);
            return;
        }
        cur = cur->rlink;
    }
    printf("삭제할 노드%d 없음.\n",key);
}