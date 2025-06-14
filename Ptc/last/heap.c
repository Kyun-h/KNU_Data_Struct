#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
typedef struct element{
    int key;
} element;
element heap[MAX_SIZE];


void preorder(int index, int size);
void addHeap(element item, int *size);
element pop(int* size);
void inorder(int idx, int size);

int main(void){
    int size = 0;
    element e;

    int keys[] = {50, 30, 20, 15, 10, 8, 16};
    for (int i = 0; i < 7; i++) {
        e.key = keys[i];
        addHeap(e, &size);
    }

    pop(&size);
    pop(&size);

    printf("Preorder traversal : ");
    preorder(1, size);
    printf("\n");

    printf("inorder traversal : ");
    inorder(1, size);
    printf("\n");

    return 0;
}

void inorder(int idx, int size){
    if(idx>size) return;
    inorder(idx*2, size);
    printf("%d ", heap[idx].key);
    inorder(idx*2+1, size);
}

void preorder(int index, int size) {
    if(index>size) return;
    printf("%d ", heap[index].key);             // (1) 현재 노드
    preorder(index * 2, size);                  // (2) 왼쪽 자식
    preorder(index * 2 + 1, size);              // (3) 오른쪽 자식
}


void addHeap(element item, int *size){
    int i;
    i = ++(*size);
    while((i!=1) && (item.key)>(heap[i/2].key)){ // heap[i/2] -> 부모노드 자리
        heap[i] = heap[i/2]; // 부모 노드를 내리고
        i/=2; // 부모 노드 자리로 이동
    }
    heap[i] = item; // 부모 자리에 item 끼워넣기
}

element pop(int* size){
    int parent, child;
    element item, temp;

    item = heap[1];
    temp = heap[(*size)--];
    parent=1, child = 2;

    while(child<=*size){
        if ((child<*size) && (heap[child].key < heap[child+1].key)) child++;

        if(temp.key >= heap[child].key) break;

        heap[parent] = heap[child]; // 위에서 자식중 더 큰 값 찾았으니 부모 노드로 올림
        parent = child; // 한 단계씩 내려감
        child *= 2;  // 한 단계씩 내려감
    }
    heap[parent] = temp; // 마지막에 temp를 빈 자리에 끼워넣음
    return item;
}