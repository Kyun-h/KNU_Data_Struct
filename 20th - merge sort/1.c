//2024004060 황상균
//merge sort
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

typedef struct element{
    char name[20];
    int key;
} PERSON;
void mergeSort(PERSON a[], int); //Merge Sort 알고리즘 전체 실행
void mergePass(PERSON initList[], PERSON mergedList[],int n, int s); // 현재 단계의 부분 리스트들 병합
void merge(PERSON initList[], PERSON mergedList[], int i, int m, int n); //하나의 정렬된 리스트로 병합
void printlist(PERSON *list, int n); //list 출력

int main(void){
    FILE *f = fopen("in.txt","r");
    if(f==NULL){
        printf("CANNOT OPEN THE FILE.");
        exit(EXIT_FAILURE);
    }

    int size;
    PERSON item;
    fscanf(f,"%d",&size);
    PERSON *list = (PERSON*)malloc((size+1)*sizeof(PERSON));

    for(int i=1; i<=size; i++){
        fscanf(f,"%s %d",&item.name, &item.key);
        list[i] = item;
    }

    printf("[Merge sort 진행중]\n");
    mergeSort(list,size);
    printf("[Merge sort 완료]\n");
    printlist(list,size);

    fclose(f);
    return 0;
}
void printlist(PERSON *list, int n){ //리스트 출력
    for(int i=1; i<=n; i++){
        printf("%8s:%5d\n",list[i].name, list[i].key);
    }
}

void mergeSort(PERSON* list, int n){ //Merge Sort 알고리즘 전체 실행
    PERSON* extra = (PERSON*)malloc((n+1)*sizeof(PERSON));
    int s = 1;

    while(s<n){
        mergePass(list,extra,n,s);
        printf("s: %d\n",s);
        printlist(list,n);
        puts("");

        s *= 2;
        mergePass(extra,list,n,s);
        printf("s: %d\n",s);
        printlist(list,n);
        puts("");

        s *= 2;
    }
}

void mergePass(PERSON initList[], PERSON mergedList[],int n, int s){ // 현재 단계의 부분 리스트들을 병합
    int i,j;
    for(i=1;i<=n-2*s+1;i+=2*s) merge(initList,mergedList,i,i+s-1,i+2*s-1);
    if(i+s-1<n) merge(initList,mergedList,i,i+s-1,n);
    else for(j=i;j<=n;j++) mergedList[j] = initList[j];
}

void merge(PERSON initList[], PERSON mergedList[], int i, int m, int n) //하나의 정렬된 리스트로 병합
 {
    int j,k,t;
    j = m+1;
    k = i; 
    while (i <= m && j <= n) {
        if (initList[i].key<= initList[j].key) mergedList[k++] = initList[i++];
        else mergedList[k++] = initList[j++];
    }
    if (i > m) for (t = j; t <= n; t++) mergedList[t] = initList[t];
    else for (t = i; t <= m; t++) mergedList[k+t-i] = initList[t];  
}