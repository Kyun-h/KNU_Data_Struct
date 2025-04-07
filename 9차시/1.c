//2024004060 황상균 
//linked list - insert & delete 
#include <stdio.h>
#include <stdlib.h>

typedef struct node* Link;
typedef struct node{
    int data;
    Link next;
} Node;

void printList(Link); //list 출력 함수 
Link appendNode(Link,Link); //list 마지막에 node 추가하는 함수 
Link createNode(int); //node 생성 함수 
Link inf_appendNode(Link head,int item,Link); //짝수일 경우 list 앞에 node 추가하는 함수 
Link insert(Link head,int num); //list 중간에 node 추가하는 함수 
Link delete(Link head,int num); //list의 num에 해당하는 node 제거하는 함수 
int DupCheck(Link head,int key); //list에 node가 중복으로 존재하는 지 체크하는 함수 

int flag = 0; //delete 함수의 flag -> main에서도 사용해서 전역으로 선언 
int main(void){
    Link head = NULL,cur;

    FILE *f1,*f2;
    if((f1=fopen("in.txt","r"))==NULL){
        printf("CANNOT OPEN THE FILE.");
        exit(EXIT_FAILURE);
    }
    if((f2=fopen("op.txt","r"))==NULL){
        printf("CANNOT OPEN THE FILE.");
        exit(EXIT_FAILURE);
    }

    int size,num;
    fscanf(f1,"%d",&size);

    for(int i=0; i<size; i++){
        fscanf(f1,"%d",&num);
        cur = createNode(num);
        if(num%2==0){ //짝수의 경우 
            head = inf_appendNode(head,num,cur);
        }
        else{ //홀수일 때 
            head = appendNode(head,cur);
        }
    }
    printList(head);
    puts("");
    puts("");

    char ch;
    fscanf(f2,"%d",&size);
    fgetc(f2); //개행문자 제거 
    for(int i=0; i<size;i++){
        flag=0;
        ch = fgetc(f2);
        if(ch=='a'){
            fscanf(f2,"%d",&num);
            fgetc(f2); //개행문자 삭제 

            printf("Insert %d: ",num);
            if(DupCheck(head,num)){
                continue;
            }
            else{
                head = insert(head,num);
                printList(head);
                puts("");
            }
        }
        else if(ch=='d'){
            fscanf(f2,"%d",&num);
            fgetc(f2); //개행문자 삭제 
            head = delete(head,num);
            printf("Delete %d: ",num);

            if(flag){
                printf("삭제할 노드 없음.\n");
                continue;
            }
            else{
                printList(head);
                puts("");
            }
        }
    }
    
    fclose(f1);
    fclose(f2);
    return 0;
}

int DupCheck(Link head,int key){ //중복 체크 함수 
    Link temp = head;
    while(temp->next){
        if(temp->data == key){
            printf("중복노드.\n");
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

Link insert(Link head, int num) { //node를 중간에 삽입하는 함수 
    Link temp = (Node*)malloc(sizeof(Node));
    temp->data = num;
    temp->next = NULL;

    if (!head) { //head가 empty일 때 head 추가 
        head = temp;
    } else {
        Link nextNode = head;
        while (((nextNode->next)->data)%2==0) { //next가 홀수면 멈춤 
            nextNode = nextNode->next;
        }
        temp->next = nextNode->next;
        nextNode->next = temp;
    }
    return head;
}

Link delete(Link head,int key){ //key에 해당하는 node 삭제 함수 
    Link temp = head,prev=NULL; //처음 값을 delete하기 위해 검사 
    if(temp->data==key){
        head = temp->next;
        free(temp);
        return head;
    }

    temp=head->next,prev=head; //처음 값(head) 제외하고 검사 
    int found=0;
    while(temp){
        if(temp->data==key){
            prev->next = temp->next;
            free(temp);
            found=1;
            break;
        }   
        prev = temp;
        temp = temp->next;
    }
    if(!found){
        flag++; //delete할 node가 존재하지 않으면 flag 반환 
    }
    return head;
}

Link inf_appendNode(Link head,int item,Link cur){ //짝수일 때 앞에다가 추가하는 함수 
    Link temp;
    temp = (Node*)malloc(sizeof(Node));

    if(head){
        cur->next = head;
        head = cur;
        
        return head;
    }
    else{
        cur->next = NULL;
        head = cur;
        return head;
    }
}

Link appendNode(Link head, Link cur){ //홀수 append 
    Link nextnode = head;
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

void printList(Link head){ //List 출력 
    Link nextNode = head;
    while(nextNode){
        printf("%d ",nextNode->data);
        nextNode = nextNode->next;
    }
}

Link createNode(int num){ //Node 생성 함수 
    Link cur = (Node*)malloc(sizeof(Node));
    cur->data = num;
    cur->next = NULL;
    return cur;
}