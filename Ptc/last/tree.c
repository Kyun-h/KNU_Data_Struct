#include <stdio.h>
#include <stdlib.h>

typedef struct tree* treePoint;
typedef struct tree{
    treePoint left;
    int data;
    treePoint right;
} Tree;

treePoint addNode(treePoint t, int data);
void inorder(treePoint ptr);
void preorder(treePoint ptr);
void postorder(treePoint ptr);
treePoint searchNode(treePoint t, int target);
treePoint getMaxNode(treePoint t);
treePoint getMinNode(treePoint t);
treePoint removeNode(treePoint t, int target);

int main(void){
    int choice=1,data;
    treePoint root = NULL;
    treePoint findNode = NULL;

    printf("-------- [BST] ---------\n");
    printf("1. Insert Node. \n");
    printf("2. Delete Node.\n");
    printf("3. Search Node.\n");
    printf("4. MAX 구하기.\n");
    printf("5. MIN 구하기.\n");
    printf("6. Tree 출력.\n");
    printf("------------------\n");
    while(choice>0){
        printf(">>> ");
        scanf("%d",&choice);

        switch(choice){
            case 1: 
                printf("삽입할 정수 입력 >> ");
                scanf("%d",&data);

                root = addNode(root,data);
                break;
            case 2: 
                printf("삭제할 노드의 값 입력 : ");
                scanf("%d",&data);

                root = removeNode(root,data);
                break;
            case 3:
                printf("\n검색할 정수 입력 : ");
                scanf("%d", &data);

                findNode = searchNode(root,data);
                if(findNode == NULL) printf("검색한 값이 존재하지 않습니다.\n");
                else printf("검색한 값이 존재합니다.\n");
                break;
            case 4: 
                findNode = getMaxNode(root);
                if(findNode!=NULL) printf("최댓값은 %d입니다.\n",findNode->data);
                break;
            case 5:
                findNode = getMinNode(root);
                if(findNode!=NULL) printf("최솟값은 %d입니다.\n",findNode->data);
                break;
            case 6:
                printf("1. preorder 2. inorder 3. postorder.\n");
                scanf("%d",&choice);
                switch(choice){
                    case 1: preorder(root); puts(""); break;
                    case 2: inorder(root); puts(""); break;
                    case 3: postorder(root); puts(""); break;
                }
        }
    }

    return 0;
}

treePoint removeNode(treePoint t, int target){
    treePoint temp;
    if(t->data == target){
        if(t->left == NULL && t->right == NULL){ //자식 X
            free(t);
            return NULL;
        }
        else if(t->left == NULL){ //왼쪽 자식 X
            temp = t->right;
            free(t);
            return temp;
        }
        else if(t->right == NULL){ //오른쪽 자식 X
            temp = t->left;
            free(t);
            return temp;
        }
        else{
            temp = getMaxNode(t->left);
            t->data = temp->data;
            removeNode(t->left,temp->data);
        }
    }
    else if(t->data > target) t->left = removeNode(t->left, target);
    else t->right = removeNode(t->right, target);
}

treePoint getMinNode(treePoint t){
    if(t==NULL) return NULL;
    if(t->left != NULL) return getMinNode(t->left);
    return t;
}

treePoint getMaxNode(treePoint t){
    if(t==NULL) return NULL;
    if(t->right != NULL) return getMaxNode(t->right);
    return t;
}

treePoint searchNode(treePoint t, int target){
    if(t==NULL) return NULL;

    if(t->data == target) return t;
    else if(t->data > target) return searchNode(t->left,target);
    else return searchNode(t->right, target);
}

treePoint addNode(treePoint t, int data){
    if(t==NULL){
        t = (Tree*)malloc(sizeof(Tree));
        t->data = data;
        t->left = NULL;
        t->right = NULL;
    }
    else{
        if(t->data > data) t->left = addNode(t->left, data);
        else if(t->data < data) t->right = addNode(t->right, data);
    }

    return t;
}

void inorder(treePoint ptr){
    if(ptr){
        inorder(ptr->left);
        printf("%d ",ptr->data);
        inorder(ptr->right);
    }
}

void preorder(treePoint ptr){
    if(ptr){
        printf("%d ",ptr->data);
        preorder(ptr->left);
        preorder(ptr->right);
    }
}

void postorder(treePoint ptr){
    if(ptr){
        postorder(ptr->left);
        postorder(ptr->right);
        printf("%d ",ptr->data);
    }
}