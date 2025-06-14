// 2024004060 황상균
// radix sort
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct element{
    char suit;
    int face;
} element;

int radixSort(element a[], int link[], int d, int r1, int r2, int n); // radix sort 실행 함수

int main(void){
    FILE *f = fopen("in.txt","r");
    element a[MAX];
    int link[MAX];
    int n;

    if(f == NULL){
        printf("CANNOT OPEN THE FILE.\n");
        exit(EXIT_FAILURE);
    }

    fscanf(f, "%d", &n);
    for (int i = 1; i <= n; i++) {
        fscanf(f, " %c %d", &a[i].suit, &a[i].face);
    }
    
    int start;
    start = radixSort(a, link, 2, 13, 4, n); 
    
    for (int i = start; i != 0; i = link[i]) {
        char *suit_str;
        switch (a[i].suit) {
            case 'C': suit_str = "club"; break;
            case 'D': suit_str = "dia"; break;
            case 'H': suit_str = "heart"; break;
            case 'S': suit_str = "spade"; break;
            default: suit_str = "unknown";
        }

        printf("(%5s, ", suit_str);
        switch (a[i].face) {
            case 11: printf("  J"); break;
            case 12: printf("  Q"); break;
            case 13: printf("  K"); break;
            default: printf("  %d", a[i].face); break;
        }
        printf(")\n");
    }


    fclose(f);
    return 0;
}

// radix sort 실행 함수
int radixSort(element a[], int link[], int d, int r1, int r2, int n) {
    int *front = (int *)malloc(sizeof(int) * (r1 > r2 ? r1 : r2));
    int *rear = (int *)malloc(sizeof(int) * (r1 > r2 ? r1 : r2));
    
    int i, bin, current, first, last;

    first = 1;
    for (i = 1; i <= n; i++) link[i] = i + 1;
    link[n] = 0;

    // r1 -> face 기반 정렬
    for (bin = 0; bin < r1; bin++) front[bin] = 0;

    for (current = first; current; current = link[current]) {
        if (a[current].face == 1) bin = 12;
            else bin = a[current].face - 2;
        if (front[bin] == 0) front[bin] = current;
        else link[rear[bin]] = current;
        rear[bin] = current;
    }

    for (bin = 0; bin < r1 && front[bin] == 0; bin++);
    first = front[bin];
    last = rear[bin];

    for (bin++; bin < r1; bin++) {
        if (front[bin]) {
            link[last] = front[bin];
            last = rear[bin];
        }
    }
    link[last] = 0;

    // r2 -> suit 기반 정렬
    for (i = 0; i < r2; i++) front[i] = 0;

    for (current = first; current; current = link[current]) {
        switch (a[current].suit) {
            case 'C': bin = 0; break;
            case 'D': bin = 1; break;
            case 'H': bin = 2; break;
            case 'S': bin = 3; break;
            default: bin = 0; break;
        }

        if (front[bin] == 0) front[bin] = current;
        else link[rear[bin]] = current;
        rear[bin] = current;
    }

    for (bin = 0; bin < r2 && front[bin] == 0; bin++);
    first = front[bin];
    last = rear[bin];

    for (bin++; bin < r2; bin++) {
        if (front[bin]) {
            link[last] = front[bin];
            last = rear[bin];
        }
    }
    link[last] = 0;

    free(front);
    free(rear);
    return first;
}