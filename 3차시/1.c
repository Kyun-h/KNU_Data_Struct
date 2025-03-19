//2024004060 황상균
#include <stdio.h>
#include <stdlib.h>

void free3DArray(int***, int, int, int); //동적할당해제 함수
void print3DArray(int***, int, int, int); //3차원 배열 출력 함수

int main(void) {
    int ***arr;
    int i, j, k;

    printf("A[I][J][K]\n");
    printf("Input I:");
    scanf("%d", &i);
    printf("Input J:");
    scanf("%d", &j);
    printf("Input K:");
    scanf("%d", &k);

    puts("");
    
    arr = (int***)malloc(i * sizeof(int**)); //동적할당
    if (arr == NULL) {
        printf("Memory Allocation failed.");
        exit(EXIT_FAILURE);
    }

    for (int m = 0; m < i; m++) {
        arr[m] = (int**)malloc(j * sizeof(int*));
        for (int n = 0; n < j; n++) {
            arr[m][n] = (int*)malloc(k * sizeof(int)); //3차원 모두 할당 완료
        }
    }

    for (int m = 0; m < i; m++) {
        for (int n = 0; n < j; n++) {
            for (int v = 0; v < k; v++) {
                arr[m][n][v] = 100 * m + 10 * n + v;
            }
        }
    }

    print3DArray(arr, i, j, k);
    free3DArray(arr, i, j, k);

    return 0;
}

void free3DArray(int*** ary, int i, int j, int k) { //동적할당해제 함수
    for (int m = 0; m < i; m++) {
        for (int n = 0; n < j; n++) {
            free(ary[m][n]);
        }
        free(ary[m]);
    }
    free(ary);
}

void print3DArray(int*** ary, int i, int j, int k) { //3차원 배열 출력함수
    for (int m = 0; m < i; m++) {
        for (int n = 0; n < j; n++) {
            for (int v = 0; v < k; v++) {
                printf("A[%d][%d][%d]=%d ", m, n, v, ary[m][n][v]);
            }
            puts("");
        }
        puts("");
    }
}
