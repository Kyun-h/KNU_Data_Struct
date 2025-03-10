//2024004060 Ȳ���

#include <stdio.h>
#include <stdlib.h>
#include <Math.h>
#pragma warning (disable:4996)
#define MAX 50

int Max(int price[],int size); //�ְ� ���� ã���ִ� �Լ� 
int Min(int price[],int size); //�ּ� ���� ã���ִ� �Լ� 


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
    while (fscanf(fp1, "%s %d %d", &name[i], &year[i], &price[i]) != EOF) { //in.txt ������ ������ name , price , year �迭�� �ֱ� 
        i++;
    }

    int size = 6;

    Max(price, size);
    Min(price , size);

    printf("Max price:\n");

    for(int m=0; m<size; m++){ //Max Price�� �ش��ϴ� å ���
        if(price[m] == Max(price, size)){
            printf("%s\n", name[m]);
        }
    }
    puts("");
    puts("");
    
    printf("Min price:\n");  
    for(int m=0; m<size; m++){ //Min Price�� �ش��ϴ� å ���
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
    fclose(fp1); //���� ���� ������ ���� ���ϴݱ� 
    fclose(fp2); //���� ���� ������ ���� �ݱ� 
    return 0;
}

int Max(int price[], int size){ //Max Price�� ã�� �Լ� 
    int max=price[0];
    for(int i=0; i<size; i++){
        if (price[i] > max) { 
            max = price[i];
        }
    }
    return max;
}

int Min(int price[], int size){ //Min Price�� ã�� �Լ�
    int min=price[0];
    for(int i=0; i<size; i++){
        if (price[i] < min) {
            min = price[i];
        }
    }
    return min;
}