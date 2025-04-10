#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node* LINK;
typedef struct node{
    int data;
    LINK next;
} Node;

LINK appendNode(LINK,LINK);
void printList(LINK);
LINK createNode(int);
void printgreatNum(LINK,int);
LINK deleteNode(LINK head, int key);
LINK insert(LINK head,int num); //중간에 삽입 -> 아직 미구현 

int flag = 0; //delete를 위한 flag 

int main(void){
    LINK head = NULL, cur;
    srand(time(NULL));
    int num;

    for(int i=0; i<10; i++){
        printf("List에 넣을 num 입력 >> ");
        scanf("%d", &num);
        cur = createNode(num);
        head = appendNode(head,cur);
    }
    
    printList(head);
    puts("");
    // printgreatNum(head,rand()%21);
    printf("삭제할 Node 입력 >> ");
    scanf("%d",&num);
    head = deleteNode(head,num);
    if(flag){
        printf("삭제할 노드 없음.\n");
    }
    else{
        printList(head);
    }

    return 0;
}

LINK insert(LINK head,int num){ 
    //중간에 삽입 구현하기
}

LINK deleteNode(LINK head, int key){
    //첫째항의 경우 삭제 code 
    LINK cur = head, prev = NULL;
    if(cur->data == key){
        head = cur->next;
        free(cur);
        return head;
    }

    //첫째항이 아닐 경우 삭제 code 
    prev = head, cur = head->next;
    int found = 0;
    while(cur){
        if(cur->data == key){
            prev->next = cur->next;
            found = 1;
            free(cur);
            break;
        }
        prev = cur;
        cur = cur->next;
    }
    if(!found){
        flag++;
    }
    return head;
}

void printgreatNum(LINK head,int num){
    LINK nextnode = head;
    int flag=0;
    while(nextnode->next){
        if(nextnode->data == num){
            printf("%d", nextnode->data);
            flag = 1;
            break;
        }
        nextnode = nextnode->next;
    }
    if(flag){
        printf("입니다.\n");
    }
    else{
        printf("없습니다.\n");
    }
}

LINK appendNode(LINK head, LINK cur){
    LINK nextnode = head;
    //head가 NULL일 때 고려
    if(!head){
        head = cur;
        return head;
    }
    while(nextnode->next){
        nextnode = nextnode->next;
    }
    nextnode->next = cur;
    return head;
}

void printList(LINK head){
    LINK nextnode = head;
    while(nextnode){
        printf("%d ",nextnode->data);
        nextnode = nextnode->next;
    }
}

LINK createNode(int num){
    LINK cur = (Node*)malloc(sizeof(Node));
    cur->data = num;
    cur->next = NULL;
    return cur;
}