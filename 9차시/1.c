//2024004060 Ȳ��� 
//linked list - insert & delete 
#include <stdio.h>
#include <stdlib.h>

typedef struct node* Link;
typedef struct node{
    int data;
    Link next;
} Node;

void printList(Link); //list ��� �Լ� 
Link appendNode(Link,Link); //list �������� node �߰��ϴ� �Լ� 
Link createNode(int); //node ���� �Լ� 
Link inf_appendNode(Link head,int item,Link); //¦���� ��� list �տ� node �߰��ϴ� �Լ� 
Link insert(Link head,int num); //list �߰��� node �߰��ϴ� �Լ� 
Link delete(Link head,int num); //list�� num�� �ش��ϴ� node �����ϴ� �Լ� 
int DupCheck(Link head,int key); //list�� node�� �ߺ����� �����ϴ� �� üũ�ϴ� �Լ� 

int flag = 0; //delete �Լ��� flag -> main������ ����ؼ� �������� ���� 
int main(void){
    Link head = NULL,cur;

    FILE *f1,*f2;
    if((f1=fopen("in.txt","r"))==NULL){
        printf("CANNOT OPEN THE FILE.");
        exit(EXIT_FAILURE);
    }
    if((f2=fopen("op.txt","r"))==NULL){
        printf("CANNOT OPEN THE FILE.");
        exit(EXIT_FAILURE);
    }

    int size,num;
    fscanf(f1,"%d",&size);

    for(int i=0; i<size; i++){
        fscanf(f1,"%d",&num);
        cur = createNode(num);
        if(num%2==0){ //¦���� ��� 
            head = inf_appendNode(head,num,cur);
        }
        else{ //Ȧ���� �� 
            head = appendNode(head,cur);
        }
    }
    printList(head);
    puts("");
    puts("");

    char ch;
    fscanf(f2,"%d",&size);
    fgetc(f2); //���๮�� ���� 
    for(int i=0; i<size;i++){
        flag=0;
        ch = fgetc(f2);
        if(ch=='a'){
            fscanf(f2,"%d",&num);
            fgetc(f2); //���๮�� ���� 

            printf("Insert %d: ",num);
            if(DupCheck(head,num)){
                continue;
            }
            else{
                head = insert(head,num);
                printList(head);
                puts("");
            }
        }
        else if(ch=='d'){
            fscanf(f2,"%d",&num);
            fgetc(f2); //���๮�� ���� 
            head = delete(head,num);
            printf("Delete %d: ",num);

            if(flag){
                printf("������ ��� ����.\n");
                continue;
            }
            else{
                printList(head);
                puts("");
            }
        }
    }
    
    fclose(f1);
    fclose(f2);
    return 0;
}

int DupCheck(Link head,int key){ //�ߺ� üũ �Լ� 
    Link temp = head;
    while(temp->next){
        if(temp->data == key){
            printf("�ߺ����.\n");
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

Link insert(Link head, int num) { //node�� �߰��� �����ϴ� �Լ� 
    Link temp = (Node*)malloc(sizeof(Node));
    temp->data = num;
    temp->next = NULL;

    if (!head) { //head�� empty�� �� head �߰� 
        head = temp;
    } else {
        Link nextNode = head;
        while (((nextNode->next)->data)%2==0) { //next�� Ȧ���� ���� 
            nextNode = nextNode->next;
        }
        temp->next = nextNode->next;
        nextNode->next = temp;
    }
    return head;
}

Link delete(Link head,int key){ //key�� �ش��ϴ� node ���� �Լ� 
    Link temp = head,prev=NULL; //ó�� ���� delete�ϱ� ���� �˻� 
    if(temp->data==key){
        head = temp->next;
        free(temp);
        return head;
    }

    temp=head->next,prev=head; //ó�� ��(head) �����ϰ� �˻� 
    int found=0;
    while(temp){
        if(temp->data==key){
            prev->next = temp->next;
            free(temp);
            found=1;
            break;
        }   
        prev = temp;
        temp = temp->next;
    }
    if(!found){
        flag++; //delete�� node�� �������� ������ flag ��ȯ 
    }
    return head;
}

Link inf_appendNode(Link head,int item,Link cur){ //¦���� �� �տ��ٰ� �߰��ϴ� �Լ� 
    Link temp;
    temp = (Node*)malloc(sizeof(Node));

    if(head){
        cur->next = head;
        head = cur;
        
        return head;
    }
    else{
        cur->next = NULL;
        head = cur;
        return head;
    }
}

Link appendNode(Link head, Link cur){ //Ȧ�� append 
    Link nextnode = head;
    if(!head){
        head = cur;
        return head;
    }
    while(nextnode->next){
        nextnode = nextnode->next;
    }
    nextnode->next = cur;
    return head;
}

void printList(Link head){ //List ��� 
    Link nextNode = head;
    while(nextNode){
        printf("%d ",nextNode->data);
        nextNode = nextNode->next;
    }
}

Link createNode(int num){ //Node ���� �Լ� 
    Link cur = (Node*)malloc(sizeof(Node));
    cur->data = num;
    cur->next = NULL;
    return cur;
}