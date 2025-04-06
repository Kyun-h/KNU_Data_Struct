//2024004060 황상균
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable:4996)

#define MAX_STACK_SIZE 100  
#define MAX_EXPR_SIZE 100   

typedef enum { lparen, rparen, plus, minus, times, divide, mod, alpa, umul, eos, operand } precedence;
static int isp[] = { 0, 19, 12, 12, 13, 13, 13, 18, 1, 0 }; //@(18) , #(1)
static int icp[] = { 20, 19, 12, 12, 13, 13, 13, 18, 1, 0 };
int top = -1;

precedence stack[MAX_STACK_SIZE];
precedence get_token(char* symbol, int* n);

int eval(void);
void postfix(void); 
void push(int item); //stack push 함수 
char pop(); //stack pop 함수 
void stackFull(); //stack이 Full한 상태일 때 사용
void print_token(int pop);
char expr[MAX_EXPR_SIZE];

int valid_exp(const char* expr) { //괄호 수 맞는 지 확인하는 함수 
    int balance = 0;
    for (int i = 0; expr[i] != '\0'; i++) {
        if (expr[i] == '(') {
            balance++;
        }
        else if (expr[i] == ')') {
            balance--;
            if (balance < 0) {
                return 0; // 닫는 괄호가 많음
            }
        }
    }
    return balance == 0; // 괄호 수 확인 
}

int main(void) {
    FILE* f;
    int n;

    if ((f = fopen("infix.txt", "r")) == NULL) {
        printf("CANNOT OPEN THE FILE.");
        exit(EXIT_FAILURE);
    }

    fscanf(f, "%d", &n); // 수식의 개수 읽기
    fgetc(f); // 개행문자 제거

    for (int i = 0; i < n; i++) {
        memset(expr, 0, sizeof(expr)); // expr 배열 초기화

        if (fgets(expr, sizeof(expr), f) == NULL) {
            printf("Error reading expression.\n");
            break;
        }

        expr[strcspn(expr, "\n")] = '\0'; // 개행문자 제거  


        printf("Infix: %s\n", expr); //Infix 출력 

        // 괄호 오류 검사 
        if (!valid_exp(expr)) {
            printf("괄호 오류\n");
            puts("");
            continue;
        }

        printf("Postfix: ");
        postfix(); // 후위 표기법 변환
        puts("");
    }

    fclose(f);
    return 0;
}


void postfix(void) { //후위 표기법으로 변환해주는 함수 
    char symbol;
    precedence token;
    int n = 0;
    top = 0;
    stack[0] = eos;
    for (token = get_token(&symbol, &n); token != eos; token = get_token(&symbol, &n))
    {
        if (token == operand) 
            printf("%c", symbol);
        else if (token == rparen)
        {
            while (stack[top] != lparen) {
                print_token(pop());
            }
            pop();
        }
        else
        {
            while (isp[stack[top]] >= icp[token]) {
                print_token(pop());
            }
            push(token);
        }
    }
    while (((token = pop())) != eos) {
        print_token(token); //token을 출력해주는 함수 
    }
    printf("\n");
}

precedence get_token(char* symbol, int* n) { //token을 enum에 미리 정해놓은 정수로 변환 
    *symbol = expr[(*n)++];
    switch (*symbol) {
    case '(': return lparen;
    case ')': return rparen;
    case '+': return plus;
    case '-': return minus;
    case '/': return divide;
    case '*': return times;
    case '%': return mod;
    case '@': return alpa;
    case '#': return umul;
    case '\0': return eos;
    default: return operand;
    }
}

void push(int item) { //stack에 push 함수 
    if (top >= MAX_STACK_SIZE - 1)
        stackFull();
    stack[++top] = item;
}

char pop() { //stack에서 pop하는 함수 
    if (top == -1) {
        fprintf(stderr, "Stack is Empty");
        exit(EXIT_FAILURE);
    };
    return stack[top--];
}

void stackFull() { //stack이 Full한 상태일 때 오류 출력 
    fprintf(stderr, "Stack is Full.");
    exit(EXIT_FAILURE);
}

void print_token(int token) { //token을 enum에 사전에 정해놓은 규칙에 따라 출력 
    switch (token) {
    case plus: printf("+"); break;
    case minus: printf("-"); break;
    case times: printf("*"); break;
    case divide: printf("/"); break;
    case mod: printf("%%"); break;
    case alpa: printf("@"); break;
    case umul: printf("#"); break;
    default: printf("%d", token); break;
    }
}