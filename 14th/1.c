//2024004060 황상균
//min heap 구현
#include <stdio.h>
#include <stdlib.h>
#define HEAP_EMPTY(n)  (!n)

typedef struct{
    int id;
    int time;
} element;

int size;
void levelOrdertrav(element* heap,int size); //levelorder 출력
void push(element* heap, element item, int *n); //heap push
element pop(element* heap, int *front); //heap pop
void heapify_down(element* heap, int index, int size); //기존 time보다 커졌을 때 재정렬
void heapify_up(element* heap, int index); //기존 time보다 작아졌을 때 재정렬

int main(void){
    FILE *f=fopen("in.txt","r");
    if(!f){
        fprintf(stderr,"CANNOT OPEN THE FILE.");
        exit(EXIT_FAILURE);
    }
    fscanf(f,"%d",&size);
    size++;

    element* heap;
    element item;
    int n=0,fix_n=0;
    heap = (element*)malloc(sizeof(element)*size);
    for(int i=0; i<size; i++){
        fscanf(f,"%d %d", &item.id, &item.time);
        push(heap,item,&n);
    }

    printf("Min heap level order traversal:\n");
    levelOrdertrav(heap,n);
    puts("\n");

    printf("연속으로 2번 pop: ");
    element ans;
    for(int j=0; j<2; j++){
        ans = pop(heap,&n);
        printf("(%d, %d) ",ans.id, ans.time);
    }
    puts("\n");
    printf("2번 pop이후 level order travelsal:\n");
    levelOrdertrav(heap,n);
    puts("\n");

    int fix_id, fix_time;

    while(1){
        printf("변경할 task ID, time 입력: ");
        scanf("%d %d",&fix_id, &fix_time);

        if(fix_id<0 && fix_time<0) break;

        for(int i=1; i<=n; i++){
            if(heap[i].id == fix_id) {
                int old_time = heap[i].time;
                heap[i].time = fix_time;
                if(old_time<fix_time) heapify_down(heap,i,n);
                else if(old_time>fix_time) heapify_up(heap,i);
                break;
            }
        }

    printf("\ntask %d의 time을 %d로 변경 후 heap: \n",fix_id,fix_time);
    levelOrdertrav(heap,n);
    puts("\n");
    }

    free(heap);
    fclose(f);
    return 0;
}

void heapify_down(element* heap, int index, int size){ //시간이 커질 때 재정렬
    int parent = index, child;
    element temp = heap[parent];

    while ((child = 2 * parent) <= size) {
        if (child < size && heap[child].time > heap[child + 1].time)
            child++;
        if (temp.time <= heap[child].time)
            break;
        heap[parent] = heap[child];
        parent = child;
    }

    heap[parent] = temp;
}

void heapify_up(element* heap, int index){ //시간이 작아졌을 때 재정렬
    element temp = heap[index];
    int child = index, parent = child / 2;

    while (child > 1 && temp.time < heap[parent].time) {
        heap[child] = heap[parent];
        child = parent;
        parent = child / 2;
    }

    heap[child] = temp;
}


element pop(element* heap, int *n){ //heap에 pop
    int parent, child;
    element item, temp;
    if(HEAP_EMPTY(*n)) exit(EXIT_FAILURE);

    item = heap[1];
    temp = heap[(*n)--];

    parent = 1;
    child = 2;
    while(child<=*n){
        if((child<*n) && (heap[child].time > heap[child+1].time)) child++;
        if(temp.time <= heap[child].time) break;
        heap[parent]= heap[child];
        parent = child;
        child *= 2;
    }
    heap[parent] = temp;

    return item;
}

void levelOrdertrav(element* heap,int size){ //levelorder 출력
    for(int i=1; i<=size; i++){
        printf("%d ",heap[i].id);
    }
}

void push(element* heap, element item, int *n){ //heap에 push
    int i;
    if(*n==size-1) return;
    i = ++(*n);
    while((i!=1) && (item.time < heap[i/2].time)){
        heap[i] = heap[i/2];
        i/=2;
    }
    heap[i]=item;
}