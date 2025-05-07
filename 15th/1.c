//2024004060 황상균
//BST 구현
#include <stdio.h>
#include <stdlib.h>
#define MAX_STRING 100

typedef struct{
    int ID;
    char name[MAX_STRING];
} element;

typedef struct tree* treePointer;
typedef struct tree{
    treePointer leftchild;
    element data;
    treePointer rightchild;
} tree;
element* search(treePointer root, int key); //key값 해당하는 node가 있는 지 확인
treePointer insert(treePointer root, element item); //tree에 node insert하는 함수
void InorderTrav(treePointer root); //InorderTraversal 출력하는 함수
treePointer findInorder(treePointer root, int k, int* count); //K번째 노드 찾는 함수

int main(void){
    FILE *f=fopen("in.txt","r");
    FILE *f2=fopen("search.txt","r");
    if(f2==NULL){
        fprintf(stderr,"CANNOT OPEN THE FILE.");
        exit(EXIT_FAILURE);
    }
    if(f==NULL){
        fprintf(stderr,"CANNOT OPEN THE FILE.");
        exit(EXIT_FAILURE);
    }

    int iter,size;
    fscanf(f,"%d",&iter);
    int num;
    char str[MAX_STRING];

    treePointer root = NULL;

    for(int i=0; i<iter; i++){
        element temp;
        fscanf(f,"%d %s", &temp.ID, &temp.name);
        root = insert(root,temp);
    }

    printf("[Inorder traversal]\n");
    InorderTrav(root);
    puts("\n");

    fscanf(f2,"%d",&size);
    int key;
    for(int i=0; i<size;i++){
        fscanf(f2,"%d",&key);
        if(search(root,key)==NULL) printf(" %d: 없음\n",key);
        else printf(" %d: 있음\n",key);
    }

    int k;
    printf("\nk번째 노드 찾기:\n");
    while (1) {
        printf("Input K: ");
        scanf("%d", &k);
        if (k < 0) break;

        int count = 0;
        treePointer kthNode = findInorder(root, k, &count);
        if (kthNode != NULL)
            printf("%d번째 노드: (%d, %s)\n", k, kthNode->data.ID, kthNode->data.name);
    }


    free(root);
    fclose(f);
    fclose(f2);
    return 0;
}

//K번째 노드 찾는 함수
treePointer findInorder(treePointer root, int k, int* count) { 
    if (root == NULL) return NULL;

    treePointer left = findInorder(root->leftchild, k, count);
    if (left != NULL) return left;

    (*count)++;
    if (*count == k) return root;

    return findInorder(root->rightchild, k, count);
}

//Inorder 출력 함수
void InorderTrav(treePointer root){
    if(root){
        InorderTrav(root->leftchild);
        printf("(%d, %s) ",root->data.ID,root->data.name);
        InorderTrav(root->rightchild);
    }
}

//tree에 node 하는 함수
treePointer insert(treePointer root, element item) {
    if (root == NULL) {
        treePointer newNode = (treePointer)malloc(sizeof(tree));
        newNode->data = item;
        newNode->leftchild = newNode->rightchild = NULL;
        return newNode;
    }

    if (item.ID < root->data.ID)
        root->leftchild = insert(root->leftchild, item);
    else if (item.ID > root->data.ID)
        root->rightchild = insert(root->rightchild, item);
    return root;
}

//tree에 key에 해당하는 ID를 가진 노드가 존재하는 지 검증하는 함수
element* search(treePointer root, int key){
    if(!root) return NULL;
    if(key==root->data.ID) return &(root->data);
    else if(key<root->data.ID) return search(root->leftchild,key);
    else return search(root->rightchild,key);
}