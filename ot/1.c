//2024004060 황상균

#include <stdio.h>
#include <stdlib.h>
#include <Math.h>
#pragma warning (disable:4996)
#define MAX 50

int Max(int price[],int size); //최고 가격 찾아주는 함수 
int Min(int price[],int size); //최소 가격 찾아주는 함수 


int main(){
    FILE* fp1 = fopen("in.txt","r");
    FILE* fp2 = fopen("out.txt","w");
    char name[MAX][MAX];
    int price[MAX], year[MAX];

    if(!fp1 || !fp2){
        printf("CANNOT OPEN THE FILE");
        exit(1);
    }

    int i=0;
    while (fscanf(fp1, "%s %d %d", &name[i], &year[i], &price[i]) != EOF) { //in.txt 파일의 내용을 name , price , year 배열에 넣기 
        i++;
    }

    int size = 6;

    Max(price, size);
    Min(price , size);

    printf("Max price:\n");

    for(int m=0; m<size; m++){ //Max Price에 해당하는 책 출력
        if(price[m] == Max(price, size)){
            printf("%s\n", name[m]);
        }
    }
    puts("");
    puts("");
    
    printf("Min price:\n");  
    for(int m=0; m<size; m++){ //Min Price에 해당하는 책 출력
        if(price[m] == Min(price, size)){
            printf("%s\n", name[m]);
        }
    }
    fprintf(fp2,"Book list in 2023~2024\n");

    for(int i=0; i<size; i++){
        if(year[i]==2023 || year[i] == 2024){
            fprintf(fp2,"%s\n",name[i]);
        }
    }
    fclose(fp1); //파일 누수 방지를 위한 파일닫기 
    fclose(fp2); //파일 누수 방지를 위한 닫기 
    return 0;
}

int Max(int price[], int size){ //Max Price를 찾는 함수 
    int max=price[0];
    for(int i=0; i<size; i++){
        if (price[i] > max) { 
            max = price[i];
        }
    }
    return max;
}

int Min(int price[], int size){ //Min Price를 찾는 함수
    int min=price[0];
    for(int i=0; i<size; i++){
        if (price[i] < min) {
            min = price[i];
        }
    }
    return min;
}