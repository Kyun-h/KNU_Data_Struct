//2024004060 Ȳ���
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
void push(int item); //stack push �Լ� 
char pop(); //stack pop �Լ� 
void stackFull(); //stack�� Full�� ������ �� ���
void print_token(int pop);
char expr[MAX_EXPR_SIZE];

int valid_exp(const char* expr) { //��ȣ �� �´� �� Ȯ���ϴ� �Լ� 
    int balance = 0;
    for (int i = 0; expr[i] != '\0'; i++) {
        if (expr[i] == '(') {
            balance++;
        }
        else if (expr[i] == ')') {
            balance--;
            if (balance < 0) {
                return 0; // �ݴ� ��ȣ�� ����
            }
        }
    }
    return balance == 0; // ��ȣ �� Ȯ�� 
}

int main(void) {
    FILE* f;
    int n;

    if ((f = fopen("infix.txt", "r")) == NULL) {
        printf("CANNOT OPEN THE FILE.");
        exit(EXIT_FAILURE);
    }

    fscanf(f, "%d", &n); // ������ ���� �б�
    fgetc(f); // ���๮�� ����

    for (int i = 0; i < n; i++) {
        memset(expr, 0, sizeof(expr)); // expr �迭 �ʱ�ȭ

        if (fgets(expr, sizeof(expr), f) == NULL) {
            printf("Error reading expression.\n");
            break;
        }

        expr[strcspn(expr, "\n")] = '\0'; // ���๮�� ����  


        printf("Infix: %s\n", expr); //Infix ��� 

        // ��ȣ ���� �˻� 
        if (!valid_exp(expr)) {
            printf("��ȣ ����\n");
            puts("");
            continue;
        }

        printf("Postfix: ");
        postfix(); // ���� ǥ��� ��ȯ
        puts("");
    }

    fclose(f);
    return 0;
}


void postfix(void) { //���� ǥ������� ��ȯ���ִ� �Լ� 
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
        print_token(token); //token�� ������ִ� �Լ� 
    }
    printf("\n");
}

precedence get_token(char* symbol, int* n) { //token�� enum�� �̸� ���س��� ������ ��ȯ 
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

void push(int item) { //stack�� push �Լ� 
    if (top >= MAX_STACK_SIZE - 1)
        stackFull();
    stack[++top] = item;
}

char pop() { //stack���� pop�ϴ� �Լ� 
    if (top == -1) {
        fprintf(stderr, "Stack is Empty");
        exit(EXIT_FAILURE);
    };
    return stack[top--];
}

void stackFull() { //stack�� Full�� ������ �� ���� ��� 
    fprintf(stderr, "Stack is Full.");
    exit(EXIT_FAILURE);
}

void print_token(int token) { //token�� enum�� ������ ���س��� ��Ģ�� ���� ��� 
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