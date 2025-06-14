// 2024004060 황상균
// static hashing
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUCKET_SIZE 29
#define SLOT_SIZE 2
#define MAX_LEN 100

typedef struct Slot* SlotPointer;
typedef struct Slot{
    char word[MAX_LEN];
    int count;
    SlotPointer next;
} Slot;

Slot ht[BUCKET_SIZE][SLOT_SIZE]; //hash table
SlotPointer ht2[BUCKET_SIZE]; // chaining - hash table

void printHashTable(); // 문제1 hash table 출력
SlotPointer search(char* word); // 문제1 search
void insert(char* word); // 문제1 insert
int hash(char* key); // hash function (문제 1,2 공용 사용)

SlotPointer search_chain(char* word); // 문제2 - chain search
void insert_chaning(char* word); // 문제 2 - insert for chaining
void printht_chain(); // 문제 2 print 함수

int main() {
    FILE* f = fopen("in.txt", "r");
    if (f==NULL) {
        printf("CANNOT OPEN THE FILE.");
        exit(1);
    }

    char buf[1000];
    char* delimiters = " .,!?\n";

    while (fgets(buf, sizeof(buf), f)) {
        char* token = strtok(buf, delimiters);
        while (token != NULL) {
            if (strcmp(token, "eof") == 0) {
                break;
            }
            insert(token);
            token = strtok(NULL, delimiters);
        }
    }
    
    printf("[실행예 1]\n\n");
    printHashTable();
    puts("\n");

    char query[MAX_LEN];
    SlotPointer result;
    while (1) {
        printf("Input string (Q for quit): ");
        scanf("%s", query);
        if (strcmp(query, "Q") == 0){
            printf("EXIT");
            break;
        }
        result = search(query);
        if(result!=NULL)  printf("[%s, %d]\n", result->word, result->count);
    }
    fclose(f);

    // chaining

    printf("\n\n[실행예 2]\n\n");
    f = fopen("in.txt", "r");
    if (f == NULL) {
        printf("CANNOT OPEN FILE.");
        exit(1);
    }

    while (fgets(buf, sizeof(buf), f)) {
        char* token = strtok(buf, delimiters);
        while (token != NULL) {
            if (strcmp(token, "eof") == 0) {
                break;
            }
            insert_chaning(token);
            token = strtok(NULL, delimiters);
        }
    }
    
    printht_chain();
    puts("\n");

    while (1) {
        printf("Input string (Q for quit): ");
        scanf("%s", query);
        if (strcmp(query, "Q") == 0){
            printf("EXIT");
            break;
        }
        result = search_chain(query);
        if (result != NULL)
            printf("[%s, %d]\n", result->word, result->count);
        else
            printf("%s가 없음.\n", query);
    }

    fclose(f);
    return 0;
}

//chain 함수들

SlotPointer search_chain(char* word) { // 문제2 - chain search
    SlotPointer current;
    int homeBucket = hash(word);
    current = ht2[homeBucket];

    while (current != NULL) {
        if (strcmp(current->word, word) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}

void insert_chaning(char* word) { // 문제 2 - insert for chaining
    int h = hash(word);
    SlotPointer current = ht2[h];

    while (current != NULL) {
        if (strcmp(current->word, word) == 0) {
            current->count++;
            return;
        }
        current = current->next;
    }

    SlotPointer newSlot = (SlotPointer)malloc(sizeof(Slot));
    strcpy(newSlot->word, word);
    newSlot->count = 1;
    newSlot->next = NULL;

    if (ht2[h] == NULL) {
        ht2[h] = newSlot;
    } else {
        current = ht2[h];
        while (current->next != NULL)
            current = current->next;
        current->next = newSlot;
    }
}

void printht_chain() { // 문제 2 print 함수
    for (int i = 0; i < BUCKET_SIZE; i++) {
        printf("[%2d]: ", i);
        SlotPointer current = ht2[i];
        if (!current) {
            printf("");
        } else {
            while (current) {
                printf("[%6s, %2d] ", current->word, current->count);
                current = current->next;
            }
        }
        printf("\n");
    }
}

// static hashing 함수 + 공용 함수

int hash(char* key) { // hash function (문제 1,2 공용 사용)
    int number = 0;
    while(*key) number += *key++;
    return number % BUCKET_SIZE;
}

void insert(char* word) { // 문제1 insert
    int h = hash(word);
    int org = h;

    while (1) {
        for (int i = 0; i < SLOT_SIZE; i++) {
            if (ht[h][i].count) {
                if (strcmp(ht[h][i].word, word) == 0) {
                    ht[h][i].count++;
                    return;
                }
            } else {
                strcpy(ht[h][i].word, word);
                ht[h][i].count = 1;
                return;
            }
        }
        h = (h + 1) % BUCKET_SIZE;
    }
}

SlotPointer search(char* word) { // 문제1 search
    int homeBucket, currentBucket;
    homeBucket = hash(word);

    for (currentBucket = homeBucket;
         ht[currentBucket][0].count != 0 || ht[currentBucket][1].count != 0;
         currentBucket = (currentBucket + 1) % BUCKET_SIZE) {

        for (int i = 0; i < SLOT_SIZE; i++) {
            if (ht[currentBucket][i].count > 0 &&
                strcmp(ht[currentBucket][i].word, word) == 0) {
                return &ht[currentBucket][i];
            }
        }
        if (currentBucket == homeBucket) break;
    }
    printf("%s가 없음.\n", word);
    return NULL;
}

void printHashTable() { // 문제1 hash table 출력
    for (int i = 0; i < BUCKET_SIZE; i++) {
        printf("[%2d]: ", i);
        int empty = 1;
        for (int j = 0; j < SLOT_SIZE; j++) {
            if (ht[i][j].count) {
                printf("[%s, %d] ", ht[i][j].word, ht[i][j].count);
                empty = 0;
            }
        }
        if (empty) printf("");
        printf("\n");
    }
}