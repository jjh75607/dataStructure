//
//  5week.c
//  데구실습
//
//  Created by 정순재 on 2023/04/04.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_STACK_SIZE 100

typedef int element;

//스택 구조체
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
    } else {
        s->data[++(s->top)] = item;
    }
}

// 삭제함수
element pop(StackType *s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    } else {
        return s->data[(s->top)--];
    }

}

// 피크함수
element peek(StackType *s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    } else {
        return s->data[s->top];
    }
}

int check_matching(const char *in) { // 1번문제
    StackType num;
    StackType s;
    char ch, open_ch;
    int i, n = (int)strlen(in);   // n= 문자열의 길이
    int temp = 0;
    
    init_stack(&s); // 스택의 초기화
    init_stack(&num);

    for (i = 0; i < n; i++) {
        ch = in[i]; // ch = 다음 문자
        
        switch (ch) {
            case '(':   case '[':    case '{':
                //괄호가 열렸을때 숫자를 Push해줌
                push(&s, ch);
                push(&num, ++temp);
                //스택에 넣었을때 맨위이기 때문에 peek를 출력
                printf("%d ", peek(&num));
                break;
            case ')':   case ']':    case '}':
                if (is_empty(&s)) { //스택이 비었다면
                    return 0;
                }
                else {
                    open_ch = pop(&s);
                    //닫히는 부분을 만났다면 지움
                    printf("%d ", pop(&num));
                    if ((open_ch == '(' && ch != ')') || (open_ch == '[' && ch != ']') ||(open_ch == '{' && ch != '}')) {
                        return 0;
                    }
                    break;
                }
        }
    }
    if (!is_empty(&s)) {
        return 0; // 스택에 남아있으면 오류
    }
    return 1;
}

int eval(char exp[]) { //2번
    int op1, op2, value;
    int len = (int)strlen(exp);
    char ch;
    StackType s;
    
    init_stack(&s);
    
    for (int i = 0; i < len; i++) {
        ch = exp[i];
        //연산자가 아니라면 정수로 변환후 저장
        if(ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != '^' && ch != '=' && ch != '&' && ch != '|' && ch != '>' && ch != '<') {
            value = ch - '0';
            push(&s, value);
        } else {
            op2 = pop(&s);
            op1 = pop(&s);
            //각 연산자에 맞는 연산 후 푸쉬
            switch(ch) {
                case '+':
                    push(&s, op1 + op2);
                    break;
                case '-':
                    push(&s, op1 - op2);
                    break;
                case '*':
                    push(&s, op1 * op2);
                    break;
                case '/':
                    push(&s, op1 / op2);
                    break;
                case '^':
                    push(&s, pow(op1, op2));
                    break;
                case '=':
                    push(&s, op1 == op2);
                    break;
                case '&':
                    push(&s, op1 & op2);
                    break;
                case '|':
                    push(&s, op1 | op2);
                    break;
                case '<':
                    push(&s, op1 < op2);
                    break;
                case '>':
                    push(&s, op1 > op2);
                    break;
            }
        }
    }
    return pop(&s);
}

void numLength(char arr[]) { //3번
    StackType string;
    StackType number;
    
    //초기화
    init_stack(&string);
    init_stack(&number);
    
    for (int i = 0; i < strlen(arr); i++) {
        //대소문자 상관 없기때문에 모두 소문자로 변경
        char ch = tolower(arr[i]);
        
        //string 스택이 비어있거나, ch와 string의 맨 위 값이 다르다면, 즉 새로운 값이라면 새로 push
        if(is_empty(&string) || ch != peek(&string)) {
            push(&string, ch);
            push(&number, 1);
        } else if(peek(&string) == ch) { // 연속되는 값이라면 number만 ++
            number.data[number.top] += 1;
        }
    }
    //출력
    printf("문자열 압축의 결과는 : ");
    for (int i = 0; i < number.top + 1; i++) {
        printf("%d%c", number.data[i], string.data[i]);
    }
}

void menu(void) {
    printf("\n1~3입력, 그 외의 숫자 입력시 종료\n");
    printf("1. 수식에 있는 괄호의 번호를 출력\n");
    printf("2. +,-,*,/,^(거듭제곱)>,<,=(EQ),&(AND),|(OR) 다음의 연산자를 포함하는 후위표기식\n");
    printf("3. 문자열 압축 프로그램\n");
    printf(">>> ");
}

int main() {
    int n;
    
    while(1) {
        menu();
        scanf("%d", &n);
        
        if(n == 1) {
            printf("입력 예:((())(()))\n>>>>");
            char brackets[MAX_STACK_SIZE];
            scanf("%s", brackets);
            check_matching(brackets);
        } else if(n == 2) {
            printf("+,-,*,/,^(거듭제곱)>,<,=(EQ),&(AND),|(OR)를 포함한 후위표현식 입력\n>>>");
            char notation[MAX_STACK_SIZE];
            scanf("%s", notation);
            printf("후위표기식의 결과는 %d입니다.", eval(notation));
        } else if(n == 3){
            printf("문자열 압축 프로그램 >>>");
            char text[MAX_STACK_SIZE];
            scanf("%s", text);
            numLength(text);
        } else {
            break;
        }
    }
    
    
    return 0;
}
