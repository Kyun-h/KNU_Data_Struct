#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node* LINK;
typedef struct node{
    int data;
    LINK next;
} NODE;

void printList(LINK);
LINK appendNode(LINK,LINK);
LINK createNode(int);

int main(void){
    LINK head = NULL , cur;
    int cnt=0;
    srand(time(NULL));
    for(int i=0; i<10; i++){
        cur = createNode(rand()%21);
        head = appendNode(head,cur);
        cnt++;
    }
    printList(head);
    puts("");
    printf("The length of list : %d",cnt);

    return 0;
}

LINK appendNode(LINK head, LINK cur){
    LINK nextnode = head;
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
        printf("%4d",nextnode->data);
        nextnode = nextnode->next;
    }
}

LINK createNode(int number){
    LINK cur = (NODE*)malloc(sizeof(LINK));
    cur->data = number;
    cur->next = NULL;
    return cur;
}