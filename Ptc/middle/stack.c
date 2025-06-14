//stack 구조체 구현
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int data;
} element;


int top = -1, capacity = 1;

void stackFull();
void push(element item);
element pop();
element *stack;

int main(void){
    FILE *f;
    if((f=fopen("stack.txt","r"))==NULL){
        fprintf(stderr,"ERROR");
        exit(EXIT_FAILURE);
    }

    stack = (element*)malloc(sizeof(element));
    element data,ans;

    int iteration;
    char dic[10];

    fscanf(f,"%d", &iteration);
    for(int i=0; i<iteration; i++){
        fscanf(f,"%s",&dic);
        if(!strcmp(dic,"push")){
            fscanf(f,"%d", &data.data);
            push(data);
            printf("push :: %d\n",data.data);
        }
        else if(!strcmp(dic,"pop")){
            ans = pop();
            printf("pop :: %d\n",ans.data);
        }
    }
    
    free(stack);
    fclose(f);
    return 0;
}

void stackFull(){
    capacity *= 2;
    stack = realloc(stack, capacity*sizeof(element));
}

void push(element item){
    if(top>=capacity-1) stackFull();
    stack[++top] = item;
}

element pop(){
    if(top==-1){
        printf("stack is Empty");
        exit(EXIT_FAILURE);
    }
    return stack[top--];
}