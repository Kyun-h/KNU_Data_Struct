#include <stdio.h>
#include <stdlib.h>

typedef struct poly{
    int coef;
    int expon;
}Polynomial;

void padd(int sa, int fa, int sb, int fb, int* sd, int* fd, Polynomial *term);
void attach(int coef, int expon, Polynomial* term);
int compare(int a, int b);

int avail=0,cnt=0;
int size_a,size_b;

int main(void){
    Polynomial *temp;

    int sa=0,fa,sb,fb,sd,fd;

    FILE *f;
    if((f=fopen("pol.txt","r"))==NULL){
        fprintf(stderr,"CANNOT OPEN THE FILE.");
        exit(EXIT_FAILURE);
    }
    
    fscanf(f,"%d",&size_a);

    
    temp = (Polynomial*)malloc(size_a*sizeof(Polynomial));
    for(int i=0; i<size_a; i++){
        fscanf(f,"%d", &temp[i].coef);
        fscanf(f,"%d", &temp[i].expon);
    }
    
    fscanf(f,"%d",&size_b);
    temp = realloc(temp,(2*size_a+2*size_b)*sizeof(Polynomial));
    fa = size_a-1;
    sb = size_a;
    fb = size_a + size_b -1;
    sd = size_a + size_b;
    avail = size_a + size_b;
    fd = (size_a*2 + size_b*2);

    for(int i=size_a; i<size_a+size_b; i++){
        fscanf(f,"%d", &temp[i].coef);
        fscanf(f,"%d", &temp[i].expon);
    }

    padd(sa,fa,sb,fb,&sd,&fd,temp);

    printf("%d ", cnt);
    for(int i=sd; i<=fd; i++){
        printf("%d %d ", temp[i].coef, temp[i].expon);
    }

    free(temp);
    fclose(f);
    return 0;
}

void padd(int sa, int fa, int sb, int fb, int* sd, int* fd, Polynomial *term){
    *sd = avail;
    int coefficient;
    while(sa<=fa && sb<=fb){
        switch(compare(term[sa].expon,term[sb].expon)){
            case 1: //a의 차수가 더 클 때 
                attach(term[sa].coef,term[sa].expon,term);
                sa++;
                break;
            case 0: //두 차수가 같을 때 
                coefficient = term[sa].coef - term[sb].coef;
                if(coefficient!=0){
                    attach(coefficient,term[sa].expon,term);
                }
                sa++;
                sb++;
                break;
            case -1: //b의 차수가 더 클 때
                attach(-term[sb].coef,term[sb].expon,term);
                sb++;
                break;
        }
    }
    for(; sa<=fa; sa++){
        attach(term[sa].coef,term[sa].expon,term);
    }
    for(; sb<=fb; sb++){
        attach(-term[sb].coef,term[sb].expon,term);
    }
    *fd = avail-1;
}

void attach(int coef, int expon, Polynomial* term){
    if(avail>= (2*size_a + 2*size_b)){
        printf("Over.");
        exit(EXIT_FAILURE);
    }
    term[avail].coef = coef;
    term[avail++].expon = expon;
    cnt++;
}

int compare(int a, int b){
    if(a>b) return 1;
    else if(a==b) return 0;
    else if(a<b) return -1;
}