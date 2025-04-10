//2024004060 황상균 
//입력받은 문자 홀수항 & reverse 출력 
#include <stdio.h>
#include <ctype.h>
#pragma warning (disable:4996)
#define Max_size 20

void hol_prt(char [],int size , int i); //홀수번째 문자 출력하는 함수 
void reverse(char[], int); //문자열 거꾸로 출력하는 함수 

int main(void){
    char in_str[Max_size];
    int i=0,cnt=0;
    
    printf("Input str: ");
    scanf("%s",&in_str);
    
    int size = sizeof(in_str)/sizeof(in_str[0]);
    for(int j=0; j<size; j++){
        if(isalpha(in_str[j])!= 0)
            cnt++; //문자열 안에서 영어로 입력된 값만 확인하여 cnt에 넣어서 문자열의 실질적인 size를 구하기 위한 cnt    
    }

    printf("홀수번째 문자 출력: ");
    hol_prt(in_str,cnt, i);
    
    puts("");

    printf("문자열 거꾸로 출력: ");
    reverse(in_str,cnt);

    return 0;
}

void hol_prt(char str[],int size,int i){
    if(i<size){
        printf("%c", str[i]);
        hol_prt(str,size,i+=2); //재귀하는 파트 
    }
}

void reverse(char str[], int size){
    if(size>0){
        printf("%c", str[size-1]);
        reverse(str, size-1); //재귀하는 파트 
    }
}