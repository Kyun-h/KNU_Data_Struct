#include <stdio.h>
#include <stdlib.h>

int main(void){
    FILE *f;
    if((f=fopen("isin.txt","r"))==NULL){
        fprintf(stderr,"ERROR");
        exit(EXIT_FAILURE);
    }

    int size;
    fscanf(f,"%d ", &size);

    int *ary;
    ary = (int*)malloc(size*sizeof(int));
    for(int i=0; i<size; i++){
        fscanf(f,"%d ", &ary[i]);
    }

    int ans,cnt;

    while(1){
        cnt=0;
        printf("존재 검증할 숫자 하나 입력 >>> ");
        scanf("%d",&ans);
        if(ans == -1) break;
        for(int i=0; i<size; i++){
            if(ary[i] == ans){
                cnt++;
            }
        }
        printf("숫자 %d는 %d개 존재합니다.\n", ans,cnt);
    }


    free(ary);
    return 0;
}