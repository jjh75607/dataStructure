//
//  6week.c
//  데구실습
//
//  Created by 정순재 on 2023/04/11.
//

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100

typedef int element;       // typedef char element;

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
    } else s->data[++(s->top)] = item;
}

// 삭제함수
element pop(StackType *s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    } else return s->data[(s->top)--];
}

// 피크함수
element peek(StackType *s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    } else return s->data[s->top];
}

// 연산자의 우선순위를 반환한다.
int prec(char op) {
    switch (op) {
        case '(': case ')':
            return 0;
        case '=':
            return 1;
        case '|':
            return 2;
        case '&':
            return 3;
        case '<': case '>':
            return 4;
        case '+': case '-':
            return 5;
        case '*': case '/': case '%':
            return 6;
        case '^':
            return 7;
    }
    return -1;
}

// 중위 표기 수식 -> 후위 표기 수식
StackType infix_to_postfix(char exp[]) {
    printf("\n=======<infix_to_postfix>=====\n");
    int i = 0;
    char ch, top_op;
    int len = (int)strlen(exp);
    StackType s, t;

    init_stack(&s); // 스택 초기화
    init_stack(&t);

    for (i = 0; i<len; i++) {
        ch = exp[i];
        switch (ch) {
            case '+': case '-': case '*': case '/': case '%': case '<': case '>': case '&': case '|': case '=':// 연산자를 만나면
                // 스택에 있는 연산자의 우선순위가 더 크거나 같으면 출력
                while (!is_empty(&s) && ((prec(ch) <= prec(peek(&s))))) {
                    push(&t, pop(&s));
                    printf("pop : %c\n", peek(&t));
                }
                push(&s, ch);
                printf("push : %c\n", ch);
                break;
            case '(': // 왼쪽 괄호를 만나면
                push(&s, ch);
                printf("push : %c\n", ch);
                break;
            case '^':
                push(&s, ch);
                printf("push : %c\n", ch);
                break;
            case ')': // 오른쪽 괄호를 만나면
                top_op = pop(&s);
                printf("pop : %c\n", top_op);
                // 왼쪽 괄호를 만날때까지 출력
                while (top_op != '(') {
                    printf("push : %c\n", top_op);
                    push(&t, top_op);
                    top_op = pop(&s);
                }
                break;
            default: // 피연산자를 만나면
                push(&t, ch);
                printf("push : %c\n", ch);
                break;
        }
    }
    
    
    // 스택에 남은 연산자들을  pop 순서대로 출력
    while (!is_empty(&s)) {
        push(&t, pop(&s));
        printf("pop : %c\n", peek(&t));
    }
    
    return t;
}

int eval(StackType exp) { //2번
    printf("=====<eval>=====\n");
    
    int op1, op2, value;
    int len = exp.top + 1;
    char ch;
    StackType s;
    
    init_stack(&s);
    
    
    for (int i = 0; i < len; i++) {
        ch = exp.data[i];
        //연산자가 아니라면 정수로 변환후 저장
        if(ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != '^' && ch != '=' && ch != '&' && ch != '|' && ch != '>' && ch != '<' && ch != '%') {
            value = ch - '0';
            push(&s, value);
        } else {
            op2 = pop(&s);
            op1 = pop(&s);
            //각 연산자에 맞는 연산 후 푸쉬
            switch(ch) {
                case '+':
                    push(&s, op1 + op2);
                    printf("push : %d\n", op1 + op2);
                    break;
                case '-':
                    push(&s, op1 - op2);
                    printf("push : %d\n", op1 - op2);
                    break;
                case '*':
                    push(&s, op1 * op2);
                    printf("push : %d\n", op1 * op2);
                    break;
                case '/':
                    push(&s, op1 / op2);
                    printf("push : %d\n", op1 / op2);
                    break;
                case '^': //2 ^ 3 ^ 2
                    push(&s, pow(op1, op2));
                    printf("push : %.0lf\n", pow(op1, op2));
                    break;
                case '=':
                    push(&s, op1 == op2);
                    printf("push : %d\n", op1 == op2);
                    break;
                case '&':
                    push(&s, op1 && op2);
                    printf("push : %d\n", op1 && op2);
                    break;
                case '|':
                    push(&s, op1 || op2);
                    printf("push : %d\n", op1 || op2);
                    break;
                case '<':
                    push(&s, op1 < op2);
                    printf("push : %d\n", op1 < op2);
                    break;
                case '>':
                    push(&s, op1 > op2);
                    printf("push : %d\n", op1 > op2);
                    break;
                case '%':
                    push(&s, op1 % op2);
                    printf("push : %d\n", op1 % op2);
                    break;
            }
        }
    }
    
    return pop(&s);
}

// main() 은
// 중위표기 문자열 입력하고,
// 후위표기로 변경해서 저장하고, 후위수식 문자열 출력
int main() {
    char text[MAX_STACK_SIZE];
    printf("input : ");
    scanf("%s", text);
    StackType s = infix_to_postfix(text);
    printf("\n결과 : %d\n", eval(s));
    
    return 0;
}


