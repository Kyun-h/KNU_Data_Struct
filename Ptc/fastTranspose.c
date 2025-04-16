#include <stdio.h>
#include <stdlib.h>

typedef struct term{
    int row,col,val;
} term;

void fastTranspose(term a[], term b[]);

int main(void){
    FILE *f;
    term *a,*b;

    if((f=fopen("fast.txt","r"))==NULL){
        fprintf(stderr,"ERROR.");
        exit(EXIT_FAILURE);
    }
    int MAX_ROW , MAX_COL,MAX_TERM;
    fscanf(f,"%d %d", &MAX_ROW, &MAX_COL);
    MAX_TERM = MAX_COL * MAX_ROW;

    a=(term*)malloc((MAX_TERM+1)*sizeof(term));
    b=(term*)malloc((MAX_TERM+1)*sizeof(term));
    int term_cnt=0, data;

    for(int i=0; i<MAX_ROW; i++){
        for(int j=0; j<MAX_COL;j++){
            fscanf(f,"%d",&data);
            if(data){
                a[++term_cnt].row = i;
                a[term_cnt].col = j;
                a[term_cnt].val = data;
            }
        }
    }
    a[0].row = MAX_ROW;
    a[0].col = MAX_COL;
    a[0].val = term_cnt;
    
    printf("  [Before Traspose]\n");
    printf("   ROW   COL   VAL\n");
    for(int i=0; i<term_cnt+1; i++){
        printf(" %4d  %4d  %4d\n", a[i].row, a[i].col, a[i].val);
    }
    puts("");

    int found = 0;

    for(int i=0; i<MAX_ROW; i++){
        for(int j=0; j<MAX_COL; j++){
            found=0;
            for(int k=0; k<=a[0].val; k++){
                if(a[k].row == i && a[k].col == j){
                    printf("* ");
                    found = 1;
                    break;
                }
            }
            if(!found){
                printf("  ");
            }
        }
        puts("");
    }

    puts("");

    fastTranspose(a,b);

    printf("  [After Traspose]\n");
    printf("   ROW   COL   VAL\n");
    for(int i=0; i<term_cnt+1; i++){
        printf(" %4d  %4d  %4d\n", b[i].row, b[i].col, b[i].val);
    }
    puts("");

    for(int i=0; i<b[0].row; i++){
        for(int j=0; j<b[0].col; j++){
            found=0;
            for(int k=0; k<=b[0].val; k++){
                if(b[k].row == i && b[k].col == j){
                    printf("* ");
                    found = 1;
                    break;
                }
            }
            if(!found){
                printf("  ");
            }
        }
        puts("");
    }

    free(a);
    free(b);
    fclose(f);
    return 0;
}

void fastTranspose(term a[], term b[]){
    int *rowterms, *startingPos;
    int numCols = a[0].col, numTerms = a[0].val;
    int j;

    rowterms = (int*)malloc(numCols*sizeof(int));
    startingPos = (int*)malloc(numCols*sizeof(int));
    startingPos[0] = 1;

    b[0].row = a[0].col;
    b[0].col = a[0].row;
    b[0].val = a[0].val;

    if(numTerms>0){
        for(int i=0; i<numCols; i++){
            rowterms[i] = 0; //rowterm 초기화
        }
        for(int i=1; i<=numTerms; i++){
            rowterms[a[i].col]++; //col에 해당하는 row 추가
        }
        for(int i=1; i<=numCols; i++){ //startingPos 할당
            startingPos[i] = startingPos[i-1] + rowterms[i-1];
        }
        for(int i=1; i<=numTerms; i++){
            j = startingPos[a[i].col]++;
            b[j].row = a[i].col;
            b[j].col = a[i].row;
            b[j].val = a[i].val;
        }
    }
}