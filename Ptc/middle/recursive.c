#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void recursive(char str[100],int);

int main(void){
    char input;
    char str[100];
    int size;
    while(1){
        printf("문자열을 입력해주세요 (종료 : Q) >>> ");
        scanf("%s",str);
        size = strlen(str);
        if(!strcmp(str,"Q")){
            break;
        }
        else{
            recursive(str,size);
            puts("");
        }
    }

    return 0;
}

void recursive(char str[100], int size){
    if(size>=0){
        printf("%c",str[size--]);
        recursive(str,size);
    }
}