#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void reverse(char str[],int);

int main(void){
    char str[100];
    int size;
    while(1){
        printf("Input str: ");
        scanf("%s",str);
        size = strlen(str);

        if(!strcmp(str,"q")){
            break;
        }
        else{
            reverse(str,size);
        }
        puts("");
    }

    return 0;
}

void reverse(char str[],int size){
    if(size>0){
        printf("%c",str[size-1]);
        reverse(str,size-1);
    }
}