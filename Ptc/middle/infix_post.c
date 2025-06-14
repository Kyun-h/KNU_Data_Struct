#include <stdio.h>

#define MAX 1000

int main() {
    FILE *fp = fopen("infix.txt", "r"); // 파일 열기
    int n, top = -1, idx = 0;
    char stack[MAX];
    char ch;

    fscanf(fp, "%d ", &n); // 첫 줄 수행 횟수 읽기

    for(int i=0; i<n;i++) { 
        fscanf(fp, "%c ", &ch);
         // " %c" : 공백, 줄바꿈 무시하고 문자 하나 읽기
        if (ch == '(') {
            stack[++top] = '('; // '('면 push
        } else if (ch == ')') {
            if (top >= 0) {
                top--; // '('가 있으면 pop
            } else {    
                printf("%d\n", idx); // 짝이 안 맞으면 현재 인덱스 출력
                fclose(fp);
                return 0;
            }
        }
        idx++; // 읽은 문자 수 (인덱스)
    }

    fclose(fp);
    return 0;
}
