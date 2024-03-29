#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
//*** user.cpp ***
#ifndef NULL
#define NULL 0
#endif

struct Node {
    char data;
    Node *front;
    Node *back;
};

struct List {
    Node* cursor;
    Node* head;
};

void initUser() {
    
}

void Insert(int len, char str[]) {
   
}

void Backspace(int len) {
   
}

void Delete(int len) {
    
}

void moveForward(int moveCnt) {
  
}

void moveBackward(int moveCnt) {
    
}

void Undo() {

}

void getString(int stPos, int len, char str[]) {

}

/// *** main.cpp ***

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <string.h>

#define MAXLENGTH 1024

extern void initUser();
extern void Insert(int len, char str[]);
extern void Backspace(int len);
extern void Delete(int len);
extern void moveForward(int moveCnt);
extern void moveBackward(int moveCnt);
extern void Undo();
extern void getString(int stPos, int len, char str[]);

enum CMD {
    CMD_INPUT = 1,
    CMD_BACKSPACE = 2,
    CMD_DELETE = 3,
    CMD_FORWARD = 4,
    CMD_BACKWARD = 5,
    CMD_UNDO = 6,
    CMD_GETSTRING = 7
};

static char str[MAXLENGTH + 5], ansStr[MAXLENGTH + 5];

int main() {
    //freopen("input.txt", "r", stdin);
    int N;
    int score;
    int cmd, stPos, len;
    int i, j;

    initUser();
    score = 100;

    scanf("%d", &N);

    for (i = 0; i < N; ++i) {
        scanf("%d", &cmd);
        switch (cmd) {
        case CMD_INPUT:
            scanf("%d %s", &len, str);
            Insert(len, str);
            break;
        case CMD_BACKSPACE:
            scanf("%d", &len);
            Backspace(len);
            break;
        case CMD_DELETE:
            scanf("%d", &len);
            Delete(len);
            break;
        case CMD_FORWARD:
            scanf("%d", &len);
            moveForward(len);
            break;
        case CMD_BACKWARD:
            scanf("%d", &len);
            moveBackward(len);
            break;
        case CMD_UNDO:
            Undo();
            break;
        case CMD_GETSTRING:
            for (j = 0; j <= MAXLENGTH; ++j) {
                str[j] = 0;
            }
            scanf("%d %d %s", &stPos, &len, ansStr);
            getString(stPos, len, str);
            if (strcmp(str, ansStr)) { score = 0;  break; }
        }
        if (score == 0) break;

        list.print();
    }
    printf("Score : %d \n", score);
    return 0;
}