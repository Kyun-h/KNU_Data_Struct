//2024004060 황상균
//recursive merge sort
#include <stdio.h>
#include <stdlib.h>

typedef struct person{
    char name[20];
    int key;
} PERSON;

int listMerge(PERSON* a, int* link, int start1, int start2); // 두 정렬된 연결 리스트를 병합
int rmergeSort(PERSON a[], int link[], int left, int right); // merge sort를 재귀적으로 수행
void printList(PERSON *list, int *link, int head); // 리스트 출력

int main(void){
    FILE *f = fopen("in.txt","r");
    if(f==NULL){
        printf("CANNOT OPEN THE FILE.");
        exit(EXIT_FAILURE);
    }

    int size;
    fscanf(f,"%d",&size);
    PERSON item;
    PERSON* list = (PERSON*)malloc((size+1)*sizeof(PERSON));
    for(int i=1; i<=size; i++){
        fscanf(f,"%s %d", &item.name, &item.key);
        list[i] = item;
    }
    
    int* link = (int*)malloc((size+1)*sizeof(int));
    for (int i = 1; i <= size; i++) link[i] = 0;
    
    printf("[Recursive merge sort]\n\n");
    int head = rmergeSort(list, link, 1, size);
    printList(list, link, head);
    
    fclose(f);
    free(list);
    free(link);
    return 0;
}

void printList(PERSON *list, int *link, int head) { // list 출력
    for (int i = head; i != 0; i = link[i]) {
        printf("%5s:%5d\n", list[i].name, list[i].key);
    }
}

int rmergeSort(PERSON *a, int *link, int left, int right){ // merge sort를 재귀적으로 수행
    if (left >= right) return left;
    int mid = (left + right)/2;
    return listMerge(a, link, rmergeSort(a, link, left, mid),
    rmergeSort(a, link, mid+ 1, right));
}

int listMerge(PERSON* a, int* link, int start1, int start2){ // 두 정렬된 연결 리스트를 병합
    int last1, last2, lastResult=0;
    for(last1 = start1, last2 = start2; last1 && last2; ){
        if(a[last1].key>=a[last2].key){
            link[lastResult] = last1;
            lastResult = last1; last1 = link[last1];
        }
        else{
            link[lastResult] = last2;
            lastResult = last2; last2 = link[last2];
        }
    }
    if(last1 == 0) link[lastResult] = last2;
    else link[lastResult] = last1;
    return link[0];
}