//2024004060 황상균
//heap Sort
#include <stdio.h>
#include <stdlib.h>
#define SWAP(a, b) {person tmp=a; a=b; b=tmp;}

typedef struct person{
    char name[20];
    int score; //긴급도
    int order; //입력 순서
} person;

void heapSort(person a[], int n); //heapSort 실행 함수
int compare(person p1, person p2); //p1 , p2 우선순위 비교 함수
void adjust(person a[], int root, int n); //max heap을 만족하도록 재정렬

int main(void){
    FILE *f = fopen("in.txt","r");
    if(f==NULL){
        printf("CANNOT OPEN THE FILE.");
        exit(EXIT_FAILURE);
    }
    int size;
    int idx = 1;
    fscanf(f,"%d",&size);

    person* ary = (person*)malloc((size+1)*sizeof(person));
    for(int i=1; i<=size; i++){
        fscanf(f,"%s %d", &ary[i].name, &ary[i].score);
        ary[i].order = idx++;
    }
    heapSort(ary,size);

    printf("[after heap sort]\n");
    for(int i=size; i>=1; i--) printf("%4s:%4d %2d \n", ary[i].name, ary[i].score, ary[i].order);

    free(ary);
    fclose(f);
    return 0;
}

void heapSort(person a[], int n){ //heapSort 실행 함수
    int i,j;
    person temp;
    
    for(i=n/2;i>0;i--) adjust(a,i,n);
    for(i=n-1;i>0;i--){
        SWAP(a[1],a[i+1]);
        adjust(a,1,i);
    }
}

void adjust(person a[], int root, int n) { //max heap을 만족하도록 재정렬
    int child;
    person temp;
    temp = a[root];
    child = 2 * root;

    while (child <= n) {
        if ((child < n) && (compare(a[child], a[child + 1]) < 0)) child++;  

        if (compare(temp, a[child]) >= 0) break;

        else {
            a[child / 2] = a[child];  
            child *= 2;
        }
    }
    a[child / 2] = temp;
}


int compare(person p1, person p2) { //p1, p2 우선순위 비교 함수
    if (p1.score > p2.score)
        return 1;
    else if (p1.score < p2.score)
        return -1;
    else {
        if (p1.order < p2.order)
            return 1;
        else
            return -1;
    }
}