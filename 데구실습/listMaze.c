//
//  7week.c
//  데구실습
//
//  Created by 정순재 on 2023/04/18.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100
#define MAZE_SIZE 10

typedef struct {        // 교체!
    short r;
    short c;
} element;

typedef struct {
    element data[MAX_STACK_SIZE];
    int top;
} StackType;

// 스택 초기화 함수
void init_stack(StackType *s) {
    s->top = -1;
}

// 공백 상태 검출 함수
int is_empty(StackType *s) {
    return (s->top == -1);
}
// 포화 상태 검출 함수
int is_full(StackType *s) {
    return (s->top == (MAX_STACK_SIZE - 1));
}
// 삽입함수
void push(StackType *s, element item) {
    if (is_full(s)) {
        fprintf(stderr, "스택 포화 에러\n");
        return;
    }
    else s->data[++(s->top)] = item;
}
// 삭제함수
element pop(StackType *s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    else return s->data[(s->top)--];
}
// 피크함수
element peek(StackType *s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    else return s->data[s->top];
}
// ===== 스택 코드의 끝 =====


element here = { 1,0 }, entry = { 1,0 };

char maze[MAZE_SIZE][MAZE_SIZE] = {
    { '1', '1', '1', '1', '1', '1', '1', '1', '1', '1' },
    { 'e', '0', '1', '0', '0', '0', '0', '0', '1', '1' },
    { '1', '0', '0', '0', '1', '0', '1', '0', '0', '1' },
    { '1', '0', '1', '0', '1', '1', '1', '0', '1', '1' },
    { '1', '0', '1', '0', '0', '1', '1', '0', '0', 'x' },
    { '1', '0', '1', '1', '1', '0', '0', '0', '0', '0' },
    { '1', '0', '0', '0', '0', '0', '1', '1', '1', '1' },
    { '1', '1', '1', '1', '1', '0', '1', '1', '1', '1' },
    { '1', '1', '1', '1', '1', '1', '1', '1', '1', '1' },
    { '1', '1', '1', '1', '1', '1', '1', '1', '1', '1' },
};

// 위치를 스택에 삽입
void push_loc(StackType *s, int r, int c) {
    if (r < 0 || c < 0) return;
    if (maze[r][c] != '1' && maze[r][c] != '.') {
        element tmp;
        tmp.r = r;
        tmp.c = c;
        push(s, tmp);
    }
}
// 미로를 화면에 출력한다.
void maze_print(char maze[MAZE_SIZE][MAZE_SIZE]) {
    printf("\n");
    for (int r = 0; r < MAZE_SIZE; r++) {
        for (int c = 0; c < MAZE_SIZE; c++) {
            if(maze[r][c] == '.') { //이미 지나 온 길을 0으로 변경
                maze[r][c] = '0';
            }
            
            printf("%c", maze[r][c]);
        }
        printf("\n");
    }
}

int main(void) {
    int r, c;
    StackType s, h, p;

    init_stack(&s);
    init_stack(&h); // 스택 2개를 더 선언
    init_stack(&p);
    
    here = entry;
    
    while (maze[here.r][here.c] != 'x') {
        r = here.r;
        c = here.c;
        
        push(&h, here); //지나가는 지점들 push if문 조건에 따라 막힌 길이라면 실패이기 떄문에
        
        maze[r][c] = '.';
        
        push_loc(&s, r - 1, c);
        push_loc(&s, r + 1, c);
        push_loc(&s, r, c - 1);
        push_loc(&s, r, c + 1);
        
        if (is_empty(&s)) {
            printf("실패\n");
            return 0;
        }
        else
            here = pop(&s);
        
    }
    
    while(!is_empty(&h)) { //h 스택이 비어있지 않다면
        element tmp = pop(&h); //하나하나 팝한 값을 tmp에 할당
        
        //현재위치의 왼,오,위,아래 중 어디인지 비교하여 해당하는 방향으로 이동 dfs방식 사용
        if(tmp.r == here.r && tmp.c == here.c - 1) { //왼쪽
            push(&p, tmp);
            here = tmp;
        } else if(tmp.r == here.r && tmp.c == here.c + 1) { //오른쪽
            push(&p, tmp);
            here = tmp;
        } else if(tmp.r == here.r - 1 && tmp.c == here.c) { //위
            push(&p, tmp);
            here = tmp;
        } else if(tmp.r == here.r + 1 && tmp.c == here.c) { //아래
            push(&p, tmp);
            here = tmp;
        }
    }
    
    maze[entry.r][entry.c] = '+'; //출발 지점
    for (int i = 0; i < p.top; i++) { // 해당 경로를 +로 바꿔줌
        maze[p.data[i].r][p.data[i].c] = '+';
    }
    
    
    maze_print(maze);
    printf("성공\n");
    
    return 0;
}
