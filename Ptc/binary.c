#include <stdio.h>
#include <stdlib.h>

int binarysearch(int list[], int key,int,int);

int main(void){
    int list[10] = {1,2,3,4,5,6,7,8,9,10};
    int flag=0;
    flag = binarysearch(list, 5,1,10);
    if(flag) printf("found");
    else printf("Failed.");

    return 0;
}

int binarysearch(int list[], int key,int left, int right){
    int middle;
    while(middle<=right){
        middle = (left+right)/2;
        if(list[middle]<key) return binarysearch(list,key,middle+1,right);
        else if(list[middle]==key) return middle;
        else if(list[middle]>key) return binarysearch(list,key,left,middle-1);
    }
}