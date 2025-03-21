//2024004060 Ȳ���

#include <stdio.h>
#include <stdlib.h>

typedef struct polynomial{ //����ü POLY ���� 
    int coef, expon;
}POLY;

int size_a;
int size_b=1;
int avail=0;
int cnt=0;

void padd(int startA, int finishA, int startB, int finishB, int *startD, int *finishD, POLY *terms); //A(x)���� B(x) ���� �Լ� 
void attach(float coefficient, int exponent,POLY *terms); //terms ������� coef�� expon ���̴� �Լ�
int COMPARE(int, int); //��� ���ؼ� ������ ũ�� 1 , ������ 0, ������ ũ�� -1 return �ϴ� �Լ�

int main(void){
    POLY *terms;
    int size_c = 100;

    FILE *f; //in1.txt ���� �Է� 
    FILE *fp; //in2.txt ���� �Է� 
    if((f=fopen("in1.txt","r"))==NULL){
        printf("CANNOT OPEN THE FILE.");
        exit(EXIT_FAILURE);
    }

    if((fp=fopen("in2.txt","r"))==NULL){
        printf("CANNOT OPEN THE FILE.");
        exit(EXIT_FAILURE);
    }

    //1��° ���� �����
    fscanf(f,"%d",&size_a); 
    terms = (POLY*)malloc((size_a)*sizeof(POLY)); //terms�� ���� �Ҵ� 
    
    for(int i=0; i<size_a; i++){ //A(x) �Լ� �ޱ� 
        fscanf(f,"%d",&terms[i].coef);
        fscanf(f,"%d",&terms[i].expon);
    }
    
    fscanf(f,"%d",&size_b);
    terms = (POLY*)realloc(terms,(size_a*2+size_b*2)*sizeof(POLY)); //size realloc 

    for(int i = size_a; i<size_a + size_b; i++){ //B(x) �Լ� �ޱ� 
        fscanf(f,"%d",&terms[i].coef);
        fscanf(f,"%d",&terms[i].expon);
    }

    int sa = 0, fa = size_a-1, sb=size_a , fb = size_a+size_b-1, sd, fd;
    avail = size_a + size_b; //terms �ȿ� ����� 
    padd(sa,fa,sb,fb,&sd,&fd,terms);
    
    printf("in1.txt ��°�� : \n");
    printf("%d ", cnt);
    for(int i=sd; i<=fd; i++){ //in1.txt���� C(x) ��� 
        printf("%d %d ",terms[i].coef,terms[i].expon);
    }
    puts("");

    //2��° �ؽ�Ʈ ���� �����
    cnt = 0;
    fscanf(fp,"%d", &size_a);
    for(int i=0; i<size_a; i++){ //in2.txt���� A(x) �ޱ� 
        fscanf(fp,"%d",&terms[i].coef);
        fscanf(fp,"%d",&terms[i].expon);
    }
    fscanf(fp,"%d",&size_b);
    terms = (POLY*)realloc(terms,(size_a*2+size_b*2)*sizeof(POLY)); //���� ���Ҵ� 

    for(int i = size_a; i<size_a + size_b; i++){ //in2.txt���� B(x) �ޱ� 
        fscanf(fp,"%d",&terms[i].coef);
        fscanf(fp,"%d",&terms[i].expon);
    }
    sa = 0, fa = size_a-1, sb=size_a , fb = size_a+size_b-1, sd, fd;
    avail = size_a + size_b; //terms�� ����� 
    padd(sa,fa,sb,fb,&sd,&fd,terms);
    
    printf("in2.txt ��°�� : \n");
    printf("%d ", cnt);
    for(int i=sd; i<=fd; i++){ //in2.txt���� C(x) ��� 
        printf("%d %d ",terms[i].coef,terms[i].expon);
    }

    free(terms);
    fclose(fp);
    fclose(f);
    return 0;
}

//A(x)���� B(x) ���� �Լ� -> ���� �� case�� ���� 
void padd(int startA, int finishA, int startB, int finishB, int *startD, int *finishD, POLY *terms){
    int coefficient;
    *startD= avail; //������� D�� �Ҵ� 
    while (startA<= finishA&& startB<= finishB){
        switch(COMPARE(terms[startA].expon, terms[startB].expon)){
            case -1: //B ������ ũ�� 
                attach(-terms[startB].coef, terms[startB].expon,terms); 
                startB++;
                break;
            case 0: //������ ������ 
                coefficient = terms[startA].coef - terms[startB].coef;
                if(coefficient!=0){
                    attach(coefficient, terms[startA].expon,terms);
                }
                startA++;
                startB++;
                break;
            case 1:  //A ������ ũ�� 
                attach(terms[startA].coef,terms[startA].expon,terms);
                startA++;
        }
    }   
    for( ; startA <= finishA; startA++){
        attach(terms[startA].coef, terms[startA].expon,terms);
    }
    for( ; startB <= finishB; startB++){  
        attach(terms[startB].coef, terms[startB].expon,terms);
    }    
    *finishD = avail -1; 
}

//terms�� D���� (avail)�� coef�� expon ���� 
void attach(float coefficient, int exponent,POLY *terms){ 
    if (avail >=2*size_a+2*size_b) {
        printf("ERROR\n");
        exit(EXIT_FAILURE);
    }
    terms[avail].coef = coefficient;
    terms[avail++].expon = exponent;
    cnt++;
}

//�� ��� �� 
int COMPARE(int a, int b){ 
    if(a<b) return  -1;
    else if(a==b) return 0;
    else if(a>b) return 1;
}