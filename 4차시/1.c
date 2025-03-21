//2024004060 황상균

#include <stdio.h>
#include <stdlib.h>

typedef struct polynomial{ //구조체 POLY 선언 
    int coef, expon;
}POLY;

int size_a;
int size_b=1;
int avail=0;
int cnt=0;

void padd(int startA, int finishA, int startB, int finishB, int *startD, int *finishD, POLY *terms); //A(x)에서 B(x) 빼는 함수 
void attach(float coefficient, int exponent,POLY *terms); //terms 빈공간에 coef와 expon 붙이는 함수
int COMPARE(int, int); //계수 비교해서 좌항이 크면 1 , 같으면 0, 우항이 크면 -1 return 하는 함수

int main(void){
    POLY *terms;
    int size_c = 100;

    FILE *f; //in1.txt 파일 입력 
    FILE *fp; //in2.txt 파일 입력 
    if((f=fopen("in1.txt","r"))==NULL){
        printf("CANNOT OPEN THE FILE.");
        exit(EXIT_FAILURE);
    }

    if((fp=fopen("in2.txt","r"))==NULL){
        printf("CANNOT OPEN THE FILE.");
        exit(EXIT_FAILURE);
    }

    //1번째 파일 입출력
    fscanf(f,"%d",&size_a); 
    terms = (POLY*)malloc((size_a)*sizeof(POLY)); //terms에 공간 할당 
    
    for(int i=0; i<size_a; i++){ //A(x) 함수 받기 
        fscanf(f,"%d",&terms[i].coef);
        fscanf(f,"%d",&terms[i].expon);
    }
    
    fscanf(f,"%d",&size_b);
    terms = (POLY*)realloc(terms,(size_a*2+size_b*2)*sizeof(POLY)); //size realloc 

    for(int i = size_a; i<size_a + size_b; i++){ //B(x) 함수 받기 
        fscanf(f,"%d",&terms[i].coef);
        fscanf(f,"%d",&terms[i].expon);
    }

    int sa = 0, fa = size_a-1, sb=size_a , fb = size_a+size_b-1, sd, fd;
    avail = size_a + size_b; //terms 안에 빈공간 
    padd(sa,fa,sb,fb,&sd,&fd,terms);
    
    printf("in1.txt 출력결과 : \n");
    printf("%d ", cnt);
    for(int i=sd; i<=fd; i++){ //in1.txt에서 C(x) 출력 
        printf("%d %d ",terms[i].coef,terms[i].expon);
    }
    puts("");

    //2번째 텍스트 파일 입출력
    cnt = 0;
    fscanf(fp,"%d", &size_a);
    for(int i=0; i<size_a; i++){ //in2.txt에서 A(x) 받기 
        fscanf(fp,"%d",&terms[i].coef);
        fscanf(fp,"%d",&terms[i].expon);
    }
    fscanf(fp,"%d",&size_b);
    terms = (POLY*)realloc(terms,(size_a*2+size_b*2)*sizeof(POLY)); //공간 재할당 

    for(int i = size_a; i<size_a + size_b; i++){ //in2.txt에서 B(x) 받기 
        fscanf(fp,"%d",&terms[i].coef);
        fscanf(fp,"%d",&terms[i].expon);
    }
    sa = 0, fa = size_a-1, sb=size_a , fb = size_a+size_b-1, sd, fd;
    avail = size_a + size_b; //terms에 빈공간 
    padd(sa,fa,sb,fb,&sd,&fd,terms);
    
    printf("in2.txt 출력결과 : \n");
    printf("%d ", cnt);
    for(int i=sd; i<=fd; i++){ //in2.txt에서 C(x) 출력 
        printf("%d %d ",terms[i].coef,terms[i].expon);
    }

    free(terms);
    fclose(fp);
    fclose(f);
    return 0;
}

//A(x)에서 B(x) 빼는 함수 -> 차수 비교 case로 나눔 
void padd(int startA, int finishA, int startB, int finishB, int *startD, int *finishD, POLY *terms){
    int coefficient;
    *startD= avail; //빈공간을 D로 할당 
    while (startA<= finishA&& startB<= finishB){
        switch(COMPARE(terms[startA].expon, terms[startB].expon)){
            case -1: //B 차수가 크면 
                attach(-terms[startB].coef, terms[startB].expon,terms); 
                startB++;
                break;
            case 0: //차수가 같으면 
                coefficient = terms[startA].coef - terms[startB].coef;
                if(coefficient!=0){
                    attach(coefficient, terms[startA].expon,terms);
                }
                startA++;
                startB++;
                break;
            case 1:  //A 차수가 크면 
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

//terms의 D공간 (avail)에 coef랑 expon 저장 
void attach(float coefficient, int exponent,POLY *terms){ 
    if (avail >=2*size_a+2*size_b) {
        printf("ERROR\n");
        exit(EXIT_FAILURE);
    }
    terms[avail].coef = coefficient;
    terms[avail++].expon = exponent;
    cnt++;
}

//두 계수 비교 
int COMPARE(int a, int b){ 
    if(a<b) return  -1;
    else if(a==b) return 0;
    else if(a>b) return 1;
}