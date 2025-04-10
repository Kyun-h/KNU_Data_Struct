//2024004060 황상균 
#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)

typedef struct {
    int key;
} element;

int rear = 0; //C-queue rear
int front = 0; //C-queue front

int l_rear=-1, l_front=-1; //L-queue rear & front 
element *queue,*Lqueue;
element item;
element set,Lset; //flag 

int Laddq(element *Lqueue,element item,int Queue_size); //L-queue add 함수 
element Ldeleteq(element *Lqueue,int Queue_size); //L-queue delete 함수 
element queueFull(); //Queue-Full 
element queueEmpty(); //Queue-Empty 
int Caddq(element *queue,element item, int Queue_size); //C-queue add 
element Cdeleteq(element *queue,int Queue_size);  //C-queue delete 
void Queue(FILE *f1); //전체적인 실행 함수 
void setup(); //rear & front reset 

int main(void){
    FILE *f1,*f2,*f3;
    if((f1=fopen("in1.txt","r"))==NULL){
        printf("CANNOT OPEN THE FILE.");
        exit(EXIT_FAILURE);
    }

    if((f2=fopen("in2.txt","r"))==NULL){
        printf("CANNOT OPEN THE FILE.");
        exit(EXIT_FAILURE);
    }

    if((f3=fopen("in3.txt","r"))==NULL){
        printf("CANNOT OPEN THE FILE.");
        exit(EXIT_FAILURE);
    }

    Queue(f1);
    setup();

    Queue(f2);
    setup();

    Queue(f3);

    fclose(f1);
    fclose(f2);
    fclose(f3);
    return 0;
}

void Queue(FILE *f1){
    int Queue_size;

    fscanf(f1,"%d",&Queue_size);
    queue = (element*)malloc(Queue_size*sizeof(element));
    Lqueue = (element*)malloc(Queue_size*sizeof(element));

    printf("Queue size: %d\n\n",Queue_size);
    char command;
    int cnt=1;
    element num; //Queue size 저장 
    while((command = fgetc(f1))!='q'){
        if(command == 'a'){ //a일 경우 add 
            fscanf(f1,"%d",&num.key);

            printf("add (%d)\n",cnt++);
            printf("[Cqueue] ");
            int check = Caddq(queue,num,Queue_size); //flag 
            if (check != -1) {
                if(rear != front){
                    int i = (front + 1) % Queue_size;
                    do {
                        printf("%d ", queue[i].key);
                        i = (i + 1) % Queue_size;
                    } while (i != (rear + 1) % Queue_size);
                }
                puts("");
            }

            printf("[Lqueue] ");
            check = Laddq(Lqueue,num,Queue_size); //flag
            if (check != -1) {
                if(l_rear != Queue_size){
                    int i = l_front+1;
                    while (i <= l_rear) {
                        printf("%d ", Lqueue[i].key);
                        i++;
                    }
                }
                puts("");
            }
        }
        else if(command =='d'){ //d일 경우 delete
            
            printf("Delete \n");
            printf("[Cqueue] ");
            set.key = 0;
            Lset.key=0;
            if(rear == front){
                printf("Empty. Not delete.\n"); //Not delete 이후에 더 실행하면 안되므로 flag 생성 
                set.key=-1;
            }
            
            if (set.key != -1) {
                Cdeleteq(queue,Queue_size);
                if (rear != front) {
                    int i = (front + 1) % Queue_size;
                    do {
                        printf("%d ", queue[i].key);
                        i = (i + 1) % Queue_size;
                    } while (i != (rear+1) % Queue_size);
                }
                puts("");
            }

            
            printf("[Lqueue] ");
            if(l_rear == l_front){
                printf("Empty. Not delete.\n"); //Not delete 이후에 더 실행하면 안되므로 flag 생성 
                Lset.key=-1;
            }
            if (Lset.key != -1) {
                Ldeleteq(Lqueue,Queue_size);
                if (l_rear != l_front) {
                    int i = l_front+1;
                    while (i <= l_rear) {
                        printf("%d ", Lqueue[i].key);
                        i++;
                    }
                }
                puts("");
            }

            
        }
    }
    puts("");

    free(queue);
    free(Lqueue);
}
void setup(){ //reset
    rear = 0, front=0;
    l_rear=-1,l_front=-1;
}

element queueFull(){ //Queue-FUll
    printf("Full. Not Add.\n");
}

element queueEmpty(){ //Queue-Empty
    printf("Empty.");
}

int Caddq(element *queue,element item,int Queue_size) { //Circular Queue - add
    if ((rear+1)%Queue_size == front) {
        queueFull();
        return -1;
    }
    rear = (rear+1) % Queue_size;
    queue[rear] =item;
    return 0;
 }

element Cdeleteq(element *queue,int Queue_size) { //Circular Queue - delete
    if ((front+1)%Queue_size == rear) {
        queueEmpty();
        front = (front+1) % Queue_size;
        set.key = -1;

        return set;
    }
    front = (front+1) % Queue_size;
    return queue[front];
}

int Laddq(element *Lqueue,element item,int Queue_size) { //List Queue - add
    if (l_rear == Queue_size-1) {
        queueFull();
        return -1;
    }
    Lqueue[++l_rear] =item;
    return 0;
 }

 element Ldeleteq(element *Lqueue,int Queue_size) { //List Queue - delete
    if (l_front == l_rear-1) {
        queueEmpty();
        l_front++;
        Lset.key = -1;
        return set;
    }
    l_front ++;

    return Lqueue[l_front];
}
