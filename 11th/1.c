//2024004060 황상균
//Polynomial - Linked list 구현
#include <stdio.h>
#include <stdlib.h>

typedef struct poly* Polynomial;
typedef struct poly{
    int coefficient;
    int exponent;
    Polynomial next;
} Poly;

void execution(FILE *f);  //실행 함수 
void printList(Polynomial); //List 출력 
Polynomial appendNode(Polynomial,Polynomial); //List에 추가 
Polynomial createNode(int, int); //Node 생성 
Polynomial pmult(Polynomial a, Polynomial b); //두 리스트의 노드 곱하는 함수 
void attach(int coefficient, int exponent, Polynomial *ptr); //곱한 노드를 ptr 노드에 추가함 
void freeList(Polynomial head); //실행예 2를 위한 초기화 

int main(void){
    FILE *f1, *f2;
    FILE *f3, *f4;
    if((f1=fopen("in1.txt","r"))==NULL || (f2=fopen("in2.txt","r"))==NULL){
        fprintf(stderr,"CANNOT OPEN THE FILE.");
        exit(EXIT_FAILURE);
    }
    if((f3=fopen("in3.txt","r"))==NULL || (f4=fopen("in4.txt","r"))==NULL){
        fprintf(stderr,"CANNOT OPEN THE FILE.");
        exit(EXIT_FAILURE);
    }
    Polynomial a=NULL,b=NULL,c=NULL,cur_a,cur_b;

    int num1,num2;
    int a_coef, a_expon,b_coef,b_expon;
    fscanf(f1,"%d",&num1); 

    for(int i=0; i<num1; i++){
        fscanf(f1,"%d %d",&a_coef,&a_expon);
        
        cur_a = createNode(a_coef,a_expon); //노드 생성 
        a = appendNode(a,cur_a); // head 노드에 cur을 추가 
    }
    fscanf(f2,"%d",&num2);
    for(int i=0; i<num2; i++){
        fscanf(f2,"%d %d",&b_coef,&b_expon);
        cur_b = createNode(b_coef,b_expon);
        b = appendNode(b,cur_b);
    }
    printf("[실행예 1]\n");
    printf("poly1: \n");
    printList(a);
    puts("");
    printf("poly2: \n");
    printList(b);
    puts("");

    c = pmult(a,b);
    printf("poly1 * poly2:\n");
    printList(c);

    puts("");
    puts("");

    //실행예 2
    freeList(a); //초기화 
    freeList(b);
    freeList(c);
    a = b = c = NULL;

    fscanf(f3,"%d",&num1);

    for(int i=0; i<num1; i++){
        fscanf(f3,"%d %d",&a_coef,&a_expon);
        
        cur_a = createNode(a_coef,a_expon);
        a = appendNode(a,cur_a);
    }
    fscanf(f4,"%d",&num2);
    for(int i=0; i<num2; i++){
        fscanf(f4,"%d %d",&b_coef,&b_expon);
        cur_b = createNode(b_coef,b_expon);
        b = appendNode(b,cur_b);
    }

    printf("[실행예 2]\n");
    printf("poly1: \n");
    printList(a);
    puts("");
    printf("poly2: \n");
    printList(b);
    puts("");

    c = pmult(a,b);
    printf("poly1 * poly2:\n");
    printList(c);


    free(a);
    free(b);
    free(c);
    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);
    return 0;
}

void freeList(Polynomial head){ //Linked list reset 
    Polynomial temp;
    while(head){
        temp = head;
        head = head->next;
        free(temp);
    }
}

Polynomial pmult(Polynomial a, Polynomial b){ //Mult two list's node
    Polynomial c, b_cur;
    c = createNode(0, -1);  

    for( ; a; a = a->next){
        for(b_cur = b; b_cur; b_cur = b_cur->next){
            int mult = a->coefficient * b_cur->coefficient;
            int ex_mult = a->exponent + b_cur->exponent;
            attach(mult, ex_mult, &c);
        }
    }

    Polynomial result = c->next;
    free(c); 
    return result;
}


void attach(int coefficient, int exponent, Polynomial *ptr){ //mult한 node를 저장 
    Polynomial newNode, prev = *ptr, cur = (*ptr)->next;
    newNode = (Poly*)malloc(sizeof(Poly));

    while(cur && cur->exponent>exponent){
        prev = cur;
        cur = cur->next;
    }

    if(cur && cur->exponent == exponent){
        cur->coefficient += coefficient;
        if(cur->coefficient==0){
            prev->next = cur->next;
            free(cur);
        }
        return;
    }

    newNode = createNode(coefficient,exponent);
    newNode->next = cur;
    prev->next = newNode;
}


void printList(Polynomial head){ //List 출력 
    Polynomial nextnode = head;
    while(nextnode){
        printf("[%d, %d] ",nextnode->coefficient,nextnode->exponent);
        nextnode = nextnode->next;
    }
}

Polynomial appendNode(Polynomial head, Polynomial cur){ //List의 제일 뒤에 추가 
    if(!head){
        cur->next = NULL;
        head = cur;
        return head;
    }
    else{
        Polynomial temp = head;
        while(temp->next){
            temp = temp->next;
        }
        temp->next = cur;
        return head;
        
    }

}

Polynomial createNode(int coef, int expon){ //노드 생성 
    Polynomial new_node;
    new_node = (Poly*)malloc(sizeof(Poly));
    new_node->coefficient = coef;
    new_node->exponent = expon;
    new_node->next = NULL;

    return new_node;
}