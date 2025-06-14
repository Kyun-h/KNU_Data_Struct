//2024004060 황상균
//tree 구현

#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 100
typedef struct tree* treePointer;
typedef struct tree{
    treePointer leftChild;
    int data;
    treePointer rightChild;
} Tree;

int countHeight(treePointer ptr); //height 구하기
void MakeTree(treePointer ptr,int value); //트리 생성
void countleaf(treePointer ptr); //leaf node 개수 구하기
int countNode(treePointer ptr); //전체 node 개수 구하기

treePointer queue[MAX_QUEUE_SIZE];
int front=0,rear=0;
int leaf=0;
int level_cnt=1; //input level에 해당하는 level을 찾기 위한 cnt

void levelOrder(treePointer ptr, int level); //input level에 해당하는 level 노드 출력
void addq(treePointer ptr); //queue에 추가
treePointer deleteq(); //queue에서 꺼내기
void levelOrdertrav(treePointer ptr); //levelorder traversal 출력
void Postorder(treePointer ptr); //postorder 출력

int main(void){
    int num,height=0,level,node;
    printf("Input number: ");
    scanf("%d", &num);
    puts("");

    treePointer head_tree;
    head_tree = (Tree*)malloc(sizeof(Tree));
    head_tree->rightChild = NULL;
    head_tree->leftChild = NULL;

    MakeTree(head_tree, num);
    height = countHeight(head_tree);
    countleaf(head_tree);
    node = countNode(head_tree);

    printf("height : %d\n",height);
    printf("Node의 개수: %d\n",node);
    printf("leaf node개수: %d\n\n",leaf);
    
    printf("Input level: ");
    scanf("%d", &level);

    levelOrder(head_tree,level);
    puts("");
    puts("");

    printf("Postorder travelsal: ");
    Postorder(head_tree);
    puts("");

    printf("Levelorder travelsal: ");
    levelOrdertrav(head_tree);

    return 0;
}
int countNode(treePointer ptr) { //전체 node 개수 구하기 
    if (ptr == NULL) return 0;
    return 1 + countNode(ptr->leftChild) + countNode(ptr->rightChild);
}

void Postorder(treePointer ptr){ //postorder traversal 출력
    if(ptr){
        Postorder(ptr->leftChild);
        Postorder(ptr->rightChild);
        printf("(%d) ", ptr->data);
    }
}

void levelOrdertrav(treePointer ptr){ //levelorder traversal 출력
    front = rear = 0;
    if(!ptr) return;
    addq(ptr);
    for(;;){
        level_cnt++;
        ptr = deleteq();
        if(ptr){
            printf("(%d) ",ptr->data);
            if(ptr->leftChild) addq(ptr->leftChild);
            if(ptr->rightChild) addq(ptr->rightChild);
        }
        else break;
    }

}
void levelOrder(treePointer ptr,int level){ //input level에 해당하는 level node 출력
    if (ptr == NULL) return;

    if (level == 1) {
        printf("%d ", ptr->data);
    } else if (level > 1) {
        levelOrder(ptr->leftChild, level - 1);
        levelOrder(ptr->rightChild, level - 1);
    }
}

void addq(treePointer ptr){ //queue에 add
    if(rear==MAX_QUEUE_SIZE-1){
        printf("Queue Full");
        exit(EXIT_FAILURE);
    }
    queue[rear++] = ptr;
}

treePointer deleteq(){ //queue에서 꺼내기
    if(front==rear) return NULL;
    return queue[front++];
}

void countleaf(treePointer ptr){ //leaf cound하는 함수
    if(ptr==NULL) return;

    if(!(ptr->leftChild) && !(ptr->rightChild)) leaf++;

    countleaf(ptr->leftChild);
    countleaf(ptr->rightChild);
}

int countHeight(treePointer ptr) { //height 구하는 함수
    if (ptr == NULL) return 0;
    
    int leftHeight = countHeight(ptr->leftChild);
    int rightHeight = countHeight(ptr->rightChild);
    
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

void MakeTree(treePointer ptr,int value){ //Tree 생성
    ptr->data = value;

    if(2*value < 100){
        ptr->leftChild = (treePointer)malloc(sizeof(Tree));
        MakeTree(ptr->leftChild,2*value);

    }
    else ptr->leftChild = NULL;

    if(3*value < 100){
        ptr->rightChild = (treePointer)malloc(sizeof(Tree));
        MakeTree(ptr->rightChild,3*value);
    }
    else ptr->rightChild = NULL;
}