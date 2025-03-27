#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100

int top = -1;

typedef struct{
    short int row;
    short int col;
    short int dir;
} element;

typedef struct{
    short int vert;
    short int horiz;
} offsets;

void MoveSet(offsets move[8]);
void push(element item);
element pop();
void stackFull();
void path(FILE *f);

element stack[MAX_STACK_SIZE];

int main(void){
    FILE *f1,*f2,*f3;
    if((f1=fopen("maze1.txt","r"))==NULL){
        fprintf(stderr,"File Cannot Open");
        exit(EXIT_FAILURE);
    }

    if((f2=fopen("maze2.txt","r"))==NULL){
        fprintf(stderr,"File Cannot Open");
        exit(EXIT_FAILURE);
    }

    if((f3=fopen("maze3.txt","r"))==NULL){
        fprintf(stderr,"File Cannot Open");
        exit(EXIT_FAILURE);
    }

    path(f1);
    path(f2);
    path(f3);

    fclose(f1);
    fclose(f2);
    fclose(f3);
    return 0;
}

void MoveSet(offsets move[8]){ //offset 설정하는 함수 
    move[0].vert = -1; move[0].horiz = 0; //북 
    move[1].vert = -1 , move[1].horiz = 1; //북동 
    move[2].vert = 0 , move[2].horiz = 1; //동 
    move[3].vert = 1 , move[3].horiz = 1; //남동 
    move[4].vert = 1 , move[4].horiz = 0; //남 
    move[5].vert = 1 , move[5].horiz = -1; //남서 
    move[6].vert = 0, move[6].horiz = -1; //서 
    move[7].vert = -1 , move[7].horiz = -1; //북서 
}

void push(element item){
    if(top>=MAX_STACK_SIZE-1)
        stackFull();
    stack[++top] = item;
}

element pop(){
    if(top==-1) {
        fprintf(stderr, "Stack is Empty");
        exit(EXIT_FAILURE);
    };
    return stack[top--];
}

void stackFull(){
    fprintf(stderr,"Stack is Full.");
    exit(EXIT_FAILURE);
}

void path(FILE *f){
    
    int row , col, dir=0;
    int initial_row , initial_col;
    int next_row , next_col;
    int found = 0;

    element position;
    offsets move[8];
    MoveSet(move); //offset 설정 

    int **maze , **mark;
    int EXIT_ROW, EXIT_COL;
    
    //row col 입력받기 
    fscanf(f,"%d", &row);
    initial_row = row;
    fscanf(f,"%d", &col);
    initial_col = col;
    maze = (int**)malloc((row+2)*sizeof(int*));
    mark = (int**)malloc((row+2)*sizeof(int*));
    
    for(int i=0; i<row+2; i++){ //2차원 동적할당 
        maze[i] = (int *)malloc((col+2)*sizeof(int));
        mark[i] = (int *)malloc((col+2)*sizeof(int));
    }

    for(int i=0; i<row+2; i++){ //mark 초기화 
        for(int j=0; j<col+2; j++){
            mark[i][j] = 0;
        }
    }

    for(int i=0; i<row+2; i++){ //미로 초기화 (boundary를 위해 1로 초기화)
        for(int j=0; j<col+2; j++){
            maze[i][j] = 1;
        }
    }

    for(int i=1; i<row+1; i++){ //미로 세팅 
        for(int j=1; j<col+1; j++){
            fscanf(f,"%d",&maze[i][j]);
        }
    }
    
    element start , end;
    
    //시작 지점과 끝 지점 받기 
    fscanf(f,"%d", &start.row);
    fscanf(f,"%d", &start.col);
    fscanf(f,"%d", &end.row);
    fscanf(f,"%d", &end.col);
    start.row++; start.col++; end.row++; end.col++;

    printf("[MAZE]\n");

    for(int i=1; i<initial_row+1; i++){
        for(int j=1; j<initial_col+1;j++){
            if(i==start.row && j == start.col) printf("S ");
            else if(i==end.row && j == end.col) printf("F ");
            else printf("%d ",maze[i][j]);
        }
        puts("");
    }
    puts("");

    mark[start.row][start.col] = 1;
    EXIT_ROW = end.row; EXIT_COL = end.col;
    
    stack[0].row = start.row; stack[0].col = start.col; stack[0].dir = 0; top = 0;
    
    while (top>-1 && !found) {
        position = pop(); //stack에 저장된 현재 위치 받아서 position에 넣기 
        row = position.row;      
        col = position.col;
        dir = position.dir;
        
        while (dir<8 && !found) {
            next_row = row + move[dir].vert; 
            next_col = col + move[dir].horiz;
            if (next_row==EXIT_ROW && next_col==EXIT_COL) found = 1;
            
            else if(!maze[next_row][next_col] && !mark[next_row][next_col]) {
                mark[next_row][next_col] = 1;
                position.row = row; position.col = col;
                position.dir = ++dir;  
                push(position);             
                row = next_row; col = next_col; dir = 0;
            }    
            else ++dir;  
        }
    } 
    int k=0;

    if(found){
        printf("[PATH]\n");
        for(int i=1; i<initial_row+1; i++){
            for(int j=1; j<initial_col+1;j++){
                if(i==start.row && j == start.col)printf("S "); //시작점 출력 
                else if(i==end.row && j == end.col) printf("F "); //끝점 출력 
                else {
                    int is_path = 0;
                    for(k=0; k<=top; k++){
                        if(i == stack[k].row && j == stack[k].col){
                            is_path++;
                            break;
                        }
                    }
                    if(i==row && j == col) is_path++;
                    if(is_path) printf("X ");
                    else printf("%d ",maze[i][j]);
                }
            }
            puts("");
        }
    }
    else printf("No Path.\n");

    for(int i=0; i<row; i++){ //행 할당해제  
        free(maze[i]);
        free(mark[i]);
    }
    puts("");

    free(maze); //할당 해제 
    free(mark); //할당 해제 
}