//2024004060 Ȳ���
#include <stdio.h>
#include <stdlib.h>
int MAX_ROWS;
int MAX_COLS;

typedef struct {
    int row;
    int col;    
    int value;
} terms;

void fastTranspose(terms *a, terms *b); //matrix ���� �Լ�

int main(void){
    FILE *f;
    if((f=fopen("in.txt", "r"))==NULL){
        printf("CANNOT OPEN THE FILE");
        exit(EXIT_FAILURE);
    }
    
    fscanf(f,"%d",&MAX_ROWS);
    fscanf(f,"%d",&MAX_COLS);
    
    int MAX_TERMS = MAX_COLS * MAX_ROWS; //�迭 �ִ� ũ�� 

    terms *a, *b;

    a = (terms*)malloc(sizeof(terms)*(MAX_TERMS+1));
    b = (terms*)malloc(sizeof(terms)*(MAX_TERMS+1));

    int termCount = 0;

    for(int v = 0; v<MAX_TERMS; v++){ //a �迭 �ʱ�ȭ 
        a[v].value = 0;
    }

    int value;
    
    for (int m = 0; m < MAX_ROWS; m++) { 
        for (int n = 0; n < MAX_COLS; n++) {
            fscanf(f, "%d", &value); //������ ������ �޾Ƽ� 1�̸� �ֱ� 
            if(value==1){
                a[++termCount].row = m;
                a[termCount].col = n;
                a[termCount].value = value;
            }
        }
    }
    a[0].row = MAX_ROWS;
    a[0].col = MAX_COLS;
    a[0].value = termCount; 

    int k=0;
    termCount = 1;
    printf("\t[Before Transpose]\n"); //Trans ���� ��� 
    printf("\tROW\tCOL\tVAL\n");
    
    for (int i = 0; i <= a[0].value; i++) {
        printf("\t%d\t%d\t%d\n", a[i].row, a[i].col, a[i].value);
    }

    puts("");

    termCount = 1;
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            int found = 0;
            for (int k = 1; k <= a[0].value; k++) {
                if (a[k].row == i && a[k].col == j) { //�ϳ��� �˻��ؼ� �ش��ϴ� row col�� a�� �����Ѵٸ� * ��� 
                    printf("*");
                    found = 1;
                    break;
                }
            }
            if (!found) { //�ش��ϴ� a �迭�� ������ ���� ��� 
                printf(" ");
            }
        }
        puts("");
    }

    puts("");

    fastTranspose(a,b); //b�� row�� a�� col , col�� a�� row �־ row ��� ���� 
    
    termCount=0;
    
    printf("\t[After Transpose]\n"); //��ȯ �� b ��� 
    printf("\tROW\tCOL\tVAL\n");
    for (int i = 0; i <= b[0].value; i++) {
        printf("\t%d\t%d\t%d\n", b[i].row, b[i].col, b[i].value);
    }

    puts("");

    termCount = 0;
    for (int i = 0; i < b[0].row; i++) { //a�� ������ ��Ŀ���� 
        for (int j = 0; j < b[0].col; j++) {
            int found = 0;
            for (int k = 1; k <= b[0].value; k++) {
                if (b[k].row == i && b[k].col == j) {
                    printf("*");
                    found = 1;
                    break;
                }
            }
            if (!found) {
                printf(" ");
            }
        }
        puts("");
    }
    free(a); //�Ҵ� ���� 
    free(b);
    fclose(f);
    return 0;
}

void fastTranspose(terms* a, terms* b){ 
    int *rowTerms, *startingPos;
    int i,j,numCols = a[0].col, numTerms = a[0].value; //numCols = 10, numTerms = 28;

    rowTerms = (int*)malloc(sizeof(int)*numCols);
    startingPos = (int*)malloc(sizeof(int)*numCols);
    b[0].row = numCols; 
    b[0].col = a[0].row;
    b[0].value = numTerms;

    if(numTerms > 0){
        for (i=0; i<numCols; i++){
            rowTerms[i] = 0; //�ʱ�ȭ 
        }
        for(i=1; i<= numTerms; i++){
            rowTerms[a[i].col]++; 
        }
        startingPos[0] = 1; //�������� ���� 
        
        for(i=1; i <numCols; i++){
            startingPos[i] = startingPos[i-1] + rowTerms[i-1];
        }
        for(i=1; i<=numTerms; i++){ //a �迭�� ���� ���� b�� ���� 
            j = startingPos[a[i].col]++;
            b[j].row = a[i].col; 
            b[j].col = a[i].row;
            b[j].value = a[i].value;
        }
    }
    free(rowTerms);
    free(startingPos);
}