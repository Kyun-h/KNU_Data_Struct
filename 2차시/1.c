//2024004060 Ȳ��� 
#include <stdio.h>
#include <ctype.h>
#pragma warning (disable:4996)
#define Max_size 20

void hol_prt(char [],int size , int i); //Ȧ����° ���� ����ϴ� �Լ� 
void reverse(char[], int); //���ڿ� �Ųٷ� ����ϴ� �Լ� 

int main(void){
    char in_str[Max_size];
    int i=0,cnt=0;
    
    printf("Input str: ");
    scanf("%s",&in_str);
    
    int size = sizeof(in_str)/sizeof(in_str[0]);
    for(int j=0; j<size; j++){
        if(isalpha(in_str[j])!= 0)
            cnt++; //���ڿ� �ȿ��� ����� �Էµ� ���� Ȯ���Ͽ� cnt�� �־ ���ڿ��� �������� size�� ���ϱ� ���� cnt    
    }

    printf("Ȧ����° ���� ���: ");
    hol_prt(in_str,cnt, i);
    
    puts("");

    printf("���ڿ� �Ųٷ� ���: ");
    reverse(in_str,cnt);

    return 0;
}

void hol_prt(char str[],int size,int i){
    if(i<size){
        printf("%c", str[i]);
        hol_prt(str,size,i+=2); //����ϴ� ��Ʈ 
    }
}

void reverse(char str[], int size){
    if(size>0){
        printf("%c", str[size-1]);
        reverse(str, size-1); //����ϴ� ��Ʈ 
    }
}