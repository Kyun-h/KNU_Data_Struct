//delete => free로 노드를 반환 
#include <stdio.h>
#include <stdlib.h>

typedef struct node* LINK;
typedef struct node{
    int data;
    LINK next;
} Node;

typedef struct {
    int key;
} element;  

typedef struct stack* stackPoint;
typedef struct stack{
    int top;
    int bottom;
    int cnt;
    element data;
    stackPoint next;
} stack;

void stack_reset(stackPoint s);
void printList(LINK); //stack에 내용 출력 
LINK appendNode(LINK head, LINK cur); 
LINK creatNode(int num); 
LINK delete(LINK head);
stackPoint push(int i, element item, stackPoint *top);

int found = 0;
int a_cnt =0, b_cnt=0, c_cnt=0;

int main(void){
    FILE *f;
    if((f=fopen("in.txt","r"))==NULL){
        fprintf(stderr,"CANNOT OPEN THE FILE.");
        exit(EXIT_FAILURE);
    }

    LINK A_head=NULL, A_cur;
    LINK B_head=NULL, B_cur;
    LINK C_head=NULL, C_cur;

    stackPoint A_top[4];
    stackPoint B_top[4];
    stackPoint C_top[4];
    
    char ch;
    int num;
    char PointName;
    
    while (fscanf(f, "%c ", &ch) == 1 && ch != 'q'){
        // fscanf(f,"%c ",&ch);
        if(ch == 'a'){
            fscanf(f,"%c ", &PointName);
            fscanf(f,"%d", &num);
            switch(PointName){
                case 'A' :
                    printf("(%c %c  %d)[A] ",ch,PointName,num);
                    if(a_cnt != 4){
                        A_cur = creatNode(num);
                        A_head = appendNode(A_head, A_cur);
                        a_cnt ++;
                        printList(A_head);
                        puts("");
                        continue;
                    }
                    else{
                        printf("보관함A가 가득 찼음: 보관불가\n");
                        continue;
                    }

                case 'B' :
                    printf("(%c %c  %d)[B] ",ch,PointName,num);
                    if(b_cnt != 4){
                        B_cur = creatNode(num);
                        B_head = appendNode(B_head, B_cur);
                        b_cnt++;
                        printList(B_head);
                        puts("");
                        continue;
                    }
                    else{
                        printf("보관함B가 가득 찼음: 보관불가\n");
                        continue;
                    }

                    case 'C' :
                        printf("(%c %c  %d)[C] ",ch,PointName,num);
                    if(c_cnt != 4){
                        C_cur = creatNode(num);
                        C_head = appendNode(C_head, C_cur);
                        c_cnt++;
                        printList(C_head);
                        puts("");
                        continue;
                    }
                    else{
                        printf("보관함C가 가득 찼음: 보관불가\n");
                        continue;
                    }
            }
        }
        else if(ch=='d'){
            fscanf(f,"%c ", &PointName);
            switch(PointName){
                case 'A':
                    A_head = delete(A_head);
                    a_cnt--;
                    if(a_cnt==-1){
                        printf("(d A)   보관함A가 비어있음: 반환불가\n");
                        continue;
                    }
                    printf("(%c %c)   [A] ",ch,PointName);
                    printList(A_head);
                    puts("");
                    continue;
                case 'B':
                    B_head = delete(B_head);
                    b_cnt--;
                    if(b_cnt==-1){
                        printf("(d B)   보관함B가 비어있음: 반환불가\n");
                        continue;
                    }
                    printf("(%c %c)   [B] ",ch,PointName);
                    printList(B_head);
                    puts("");
                    continue;
                case 'C': 
                    C_head = delete(C_head);
                    c_cnt--;
                    if(c_cnt==-1){
                        printf("(d C)   보관함C가 비어있음: 반환불가\n");
                        continue;
                    }
                    printf("(%c %c)   [C] ",ch,PointName);
                    printList(C_head);
                    puts("");
                    continue;
            }
        }
    }

    fclose(f);
    return 0;
}

stackPoint push(int i, element item, stackPoint *top){
    stackPoint temp;
    temp = (stack*)malloc(sizeof(stack));
    temp->data = item;
    temp->next = top[i];
    top[i] =temp;
}

element pop(int i,stackPoint *top){
    stackPoint temp = top[i];
    element item;
    if(!temp){
        // return stackEmpty();
    }
    item = temp->data;
    top[i] = temp->next;
    free(temp);
    return item;
}

LINK delete(LINK head){ //첫항 삭제 
    LINK cur, prev;
    if(!head) return head;
    if(!head->next){
        free(head);
        return NULL;
    }

    head = head->next;

    free(prev);
    return head;
}
LINK appendNode(LINK head, LINK cur){
    //list 앞에다가 추가해야함 
    LINK temp;
    temp = (Node*)malloc(sizeof(Node));
    
    if(!(head)){
        cur->next = NULL;
        head = cur;
        return head;
    }
    else{
        cur->next = head;
        head = cur;
        return head;
    }

}

// LINK appendNode(LINK head, LINK cur){
//     //list 앞에다가 추가해야함 
//     LINK temp;
//     temp = (Node*)malloc(sizeof(Node));
//     if(!(head)){
//         cur->next = NULL;
//         head = cur;
//         return head;
//     }
//     else{
//         cur->next = head;
//         head = cur;
//         return head;
//     }
// }

LINK creatNode(int num){
    LINK cur;
    cur = (Node*)malloc(sizeof(Node));

    cur->data = num;
    cur->next = NULL;
    return cur;
}

void printList(LINK head){
    LINK nextnode = head;
    while(nextnode){
        printf("%d ", nextnode->data);
        nextnode = nextnode->next;
    }
    if(!head){
        printf(" ");
    }
}

// void printList(stackPoint stack){
    
// }