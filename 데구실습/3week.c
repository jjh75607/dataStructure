//
//  3week.c
//  데구실습
//
//  Created by 정순재 on 2023/03/21.
//

#define MAX_DEGREE 101

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int degree; //다항식의 차수
    float coef[MAX_DEGREE]; //다항식의 계수
} polynomial;

void menu(void);
void polynomialMultiplication(void);
polynomial mult_poly(polynomial p1, polynomial p2);
void printPolynomial(polynomial p);
polynomial inputPolynomial(void);
float poly_eval(int x);

int main() {
    while(1) {
        menu();
        
        int n;
        scanf("%d", &n);
        
        if(n == 1) {
            polynomialMultiplication();
        } else if(n == 2) {
            int x;
            
            printf("특정한 X값을 입력해주세요 : ");
            scanf("%d", &x);
            printf(" = %.0f\n", poly_eval(x));
        } else {
            break;
        }
    }
    
    return 0;
}

void menu() {
    printf("\n--1~2가 아닌 숫자를 입력시 종료.--\n");
    printf("1. 두 다항식의 곱셈 + 다항식 두개 입력 + 출력\n");
    printf("2. 입력한 X값에 대한 다항식의 값계산\n");
    printf(">>>");
}

void polynomialMultiplication() { //1번문제
    polynomial p1 = inputPolynomial();//다항식 구조체 두개 선언
    polynomial p2 = inputPolynomial();
    
    printPolynomial(mult_poly(p1, p2)); //출력함수 호출 시 매게변수로 곱셈함수의 리턴값
}

polynomial mult_poly(polynomial p1, polynomial p2) { //곱셈부분 (1번문제)
    polynomial result; // 결과를 담아줄 구조체

    for(int i = 0; i < p1.degree + p2.degree + 1; i++) { //초기화
        result.coef[i] = 0;
    }
    result.degree = p1.degree + p2.degree + 1;

    for (int i = 0; i < p1.degree + 1; i++) {//각 지수를 나타내며  두 지수를 더한 값에 해당 계수룰 넣어줌
        for (int j = 0; j < p2.degree + 1; j++) {
            result.coef[i + j] += p1.coef[i] * p2.coef[j];
        }
    }
        
    return result;
}

polynomial inputPolynomial(void) {//2번문제
    polynomial p;
    
    printf("차수를 입력해주세요 : ");
    scanf("%d", &p.degree);
    printf("%d만큼의 계수를 입력해주세요\n", p.degree + 1);// 3이라면 3 2 1 0
    
    for (int i = 0; i < p.degree + 1; i++) {
        printf("%d : ", p.degree - i);
        scanf("%f", &p.coef[i]);
    }
    
    return p;
}

void printPolynomial(polynomial p) {
    for (int i = 0; i < p.degree; i++) {
        if(p.coef[i] != 0) {
            //값이 0 보다 크고 제일 앞에 +를 출력하지 않기위해.
            if(p.coef[i] > 0 && i != 0) {
                printf(" + ");
            }
            //지수가 1이라면 ^%d부분 제거후 출력
            if(p.degree - i == 1) {
                printf("%.0fx", p.coef[i]);
            }//지수가 0이라면 x도 제거
            else if (p.degree - i == 0) {
                printf("%.0f", p.coef[i]);
            }
            else {
                printf("%.0fx^%d", p.coef[i], p.degree - i);
            }
        }
    }
    if(p.coef[p.degree] != 0) {
        // 마지막 항이 양수일때만 + 를출력하기위해 그리고 0일경우는 출력하지 않기위해
        if(p.coef[p.degree] > 0 && p.degree != 0) {
            printf("+");
        }
        printf("%.0f", p.coef[p.degree]);
    }
}

float poly_eval(int x) { // 4번문제
    polynomial p = inputPolynomial();
    float result = 0;
    
    for (int i = 0; i < p.degree + 1; i++) {
        result += p.coef[i] * pow(x, p.degree - i);
    }
    printf("P(%d) = ", x);
    printPolynomial(p);
    
    return result;
}
