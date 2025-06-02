//2024004060 황상균
//Insert & Quick sort
#include <stdio.h>
#include <stdlib.h>
#define SWAP(x,y) {element t=x;x=y;y=t;}

typedef struct element{
    char name[20];
    int score;
} element;

void insertionSort(element a[], int n); //전체적인 배열을 insert로 정렬
void insert(element e, element a[], int i); //insert 정렬 함수
void quickSort(element* a, int left, int right); //내림차순 quickSort 함수

int main(void){
    FILE *f = fopen("in.txt","r");
    if(f==NULL){
        fprintf(stderr,"CANNOT OPEN THE FILE.");
        exit(EXIT_FAILURE);
    }
    int size;
    fscanf(f,"%d",&size);

    element *list, *quick_list;
    element con;
    list = (element*)malloc((size+1)*sizeof(element));
    quick_list = (element*)malloc((size)*sizeof(element));
    for(int i=1; i<=size; i++){
        fscanf(f,"%s %d",&con.name, &con.score);
        list[i] = con;
        quick_list[i-1] = con;
    }

    insertionSort(list,size);

    printf("[Insert sort]\n");
    for(int i=1; i<=size; i++){
        printf("%10s%4d\n",list[i].name, list[i].score);
    }

    printf("\n[Quick sort]\n");
    quickSort(quick_list,0,size-1);

    for(int i=0; i<size; i++){
        printf("%10s%4d\n",quick_list[i].name, quick_list[i].score);
    }

    free(list);
    free(quick_list);
    return 0;
}

void quickSort(element* a, int left, int right){ //내림차순 quickSort
    int pivot,i,j;
    element temp;
    if (left < right) {
        i = left-1; j = right;
        pivot = a[right].score;
        printf("Pivot: %d\n",pivot);
        do {
            do i++; while (a[i].score > pivot);
            do j--; while (a[j].score < pivot);
            if (i < j) SWAP(a[i],a[j]);
        } while ( i < j) ;
        SWAP(a[right],a[i]);
        quickSort(a,left,i-1);
        quickSort(a,i+1,right);
    }
}

void insertionSort(element a[], int n){ //전체적으로 insert 정렬
    int j;
    for (j = 2; j <= n; j++){
        element temp= a[j];
        insert(temp, a, j-1);
    }
}

void insert(element e, element a[], int i){ //insert 정렬 논리 
    a[0] = e;
    while (e.score > a[i].score){
        a[i+1] = a[i];
        i--;
    }
    a[i+1] = e;
}