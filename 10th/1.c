//2024004060 황상균 
//linked list - multiple stack 
#include <stdio.h>
#include <stdlib.h>

typedef struct stack* stackPoint;
typedef struct stack {
    int data;
    stackPoint next;
} stack;

typedef struct{
    int count;
    stackPoint top;
} Stack;

// 스택 관련 함수
void push(int item, Stack *s);
int pop(Stack *s, int *popped_value);
void printStack(stackPoint top);

int main(void) {
    FILE *f;
    if ((f = fopen("in.txt", "r")) == NULL) {
        fprintf(stderr, "CANNOT OPEN FILE.\n");
        exit(EXIT_FAILURE);
    }

    stackPoint top[3] = {NULL, NULL, NULL}; // 처음부터 A,B,C
    int count[3] = {0, 0, 0};               // 각 스택의 현재 아이템 수
    char cmd, box;
    int num;

    while (fscanf(f, " %c", &cmd) == 1 && cmd != 'q') {
        if (cmd == 'a') {
            fscanf(f, " %c %d", &box, &num);
            int idx = box - 'A';

            printf("(%c %c %3d) ", cmd, box, num);

            if (count[idx] >= 4) {
                printf("보관함%c가 가득 찼음: 보관불가\n", box);
                continue;
            }

            printf("[%c] ", box);
            push(idx, num, top);
            count[idx]++;
            printStack(top[idx]);
            printf("\n");
        } 
        else if (cmd == 'd') {
            fscanf(f, " %c", &box);
            int idx = box - 'A';
            int val;

            if (count[idx] == 0) {
                printf("(%c %c)     보관함%c가 비어있음: 반환불가\n", cmd, box, box);
                continue;
            }

            pop(idx, top, &val);
            count[idx]--;

            printf("(%c %c)     [%c] ", cmd, box, box);
            printStack(top[idx]);
            printf("\n");
        }
    }

    fclose(f);
    return 0;
}

//stack에 push
void push(int idx, int item, stackPoint top[]) {
    stackPoint newNode = (stackPoint)malloc(sizeof(stack));
    newNode->data = item;
    newNode->next = top[idx];
    top[idx] = newNode;
}

//stack에서 pop
int pop(int idx, stackPoint top[], int *popped_value) {
    if (top[idx] == NULL) return 0;

    stackPoint temp = top[idx];
    *popped_value = temp->data;
    top[idx] = temp->next;
    free(temp);
    return 1;
}

// 스택 내용 출력
void printStack(stackPoint top) {
    stackPoint curr = top;
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
}