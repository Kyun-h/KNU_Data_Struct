//2024004060 황상균
#include <stdio.h>
#include <time.h>
#define MAX_SIZE 1001
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))
void sort(int [], int); //정렬 함수
void main(void){
    int i,n,step=10;
    int a[MAX_SIZE];
    double duration;

    printf("    n   repetitions    time\n");
    for(n=0;n<=1000;n+= step){ //n을 step만큼 더함
        long repetitions = 0;
        clock_t start = clock();
        do{
            repetitions++; //반복횟수 
            for(i=0;i<n;i++) a[i] = n-i;
            sort (a,n);
        }while(clock() - start < 1000);

        duration = ((double)(clock()-start))/CLOCKS_PER_SEC; //duration에 time 저장 
        duration /= repetitions;
        printf("%6d    %9d     %f\n",n,repetitions,duration); //출력 
        if(n==100) step = 100;
    }
}

void sort(int list[], int n){ //정렬 함수 코드
    int i,j,min,temp;
    for(i=0; i<n-1;i++){
        min = i;
        for(j=i+1; j<n;j++){
            if(list[j]<list[min]) min = j;
        SWAP(list[i], list[min],temp);
        }
    }
}