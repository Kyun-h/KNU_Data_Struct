//다른 로직으로 구현 
#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)

typedef struct stack* stackPoint;
typedef struct stack{
    int data;
    stackPoint next;
} stack;

typedef struct{
    int count;
    stackPoint top;
} Stack;

void printStack(Stack *s);
void push(Stack *s, int item);
int pop(Stack *s);

int main(void){
    FILE *f;
    if((f=fopen("in.txt","r"))==NULL){
        fprintf(stderr,"CANNOT OPEN THE FILE.");
        exit(EXIT_FAILURE);
    }
    char ch;
    int num,idx;
    char alpa;

    Stack stacks[3] = {0}; //index 0부터 순서대로 A, B, C 

    while(fscanf(f,"%c ",&ch)==1 && ch != 'q'){
        if(ch=='a'){
            fscanf(f,"%c %d", &alpa, &num);
            idx = alpa - 'A';
            printf("(%c %c %3d) ",ch,alpa,num);
            if(stacks[idx].count >= 4){
                printf("보관함 %c가 가득 찼음: 보관불가.\n",alpa);
                continue;
            }
            else{
                push(&stacks[idx],num);
                printf("[%c] ", alpa);
                printStack(&stacks[idx]);
                puts("");
            }
        }
        else if(ch=='d'){
            fscanf(f,"%c",&alpa);
            idx = alpa - 'A';
            printf("(%c %c)     ",ch,alpa);
            if(stacks[idx].count == 0){
                printf("보관함 %c가 비어있음: 반환불가.\n",alpa);
                continue;
            }
            else{
                printf("[%c] ", alpa);
                pop(&stacks[idx]);
                printStack(&stacks[idx]);
                puts("");
            }
        }
    }

    fclose(f);
    return 0;
}

void push(Stack *s, int item){
    stackPoint temp;
    temp = (stack*)malloc(sizeof(stack));
    temp->data = item;
    temp->next = s->top;
    s->top = temp;
    s->count++;
}

int pop(Stack *s){
    if(s->top == NULL) return 0;

    stackPoint temp;
    temp = (stack*)malloc(sizeof(stack));
    temp = s->top;
    s->top = temp->next;
    free(temp);
    s->count--;
    return 1;
}

void printStack(Stack *s){
    stackPoint cur = s->top;
    while(cur){
        printf("%d ", cur->data);
        cur = cur->next;
    }
}
