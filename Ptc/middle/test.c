#include <stdio.h>

void printSpaces(int count) {
    if (count == 0) return;
    printf(" ");
    printSpaces(count - 1);
}

void printStars(int count) {
    if (count == 0) return;
    printf("*");
    printStars(count - 1);
}

void printUpperDiamond(int n, int current) {
    if (current > n) return;
    printSpaces(n - current);
    printStars(2 * current - 1);
    printf("\n");
    printUpperDiamond(n, current + 1);
}

void printLowerDiamond(int n, int current) {
    if (current == 0) return;
    printSpaces(n - current);
    printStars(2 * current - 1);
    printf("\n");
    printLowerDiamond(n, current - 1);
}

int main() {
    int n;
    printf("다이아몬드 반쪽 높이를 입력하세요: ");
    scanf("%d", &n);
    printUpperDiamond(n, 1);   // 위쪽 피라미드
    printLowerDiamond(n, n - 1); // 아래쪽 역삼각형 (맨 위 줄 제외)
    return 0;
}
