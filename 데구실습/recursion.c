//
//  recursion.c
//  데구실습
//
//  Created by 정순재 on 2023/04/23.
//

#include <stdio.h>

int factorial(int n) {
    if(n == 0) {
        return 1;
    }
    return n * factorial(n - 1);
}

int fibo(int n) {
    if(n < 2) {
        return n;
    }
    return n + fibo(n - 1);
}

int power(int n, int x) {
    if(x == 0) {
        return 1;
    }
    
    return n * power(n, x - 1);
}

void hanoi(int n, int a, int b, int c) {
    if(n == 1) {
        printf("원판1을 %d -> %d\n", a, c);
    } else {
        hanoi(n - 1, a, c, b);
        printf("%d -> %d\n", a, c);
        hanoi(n - 1, b, a, c);
    }
}

int sum(int n) {
    printf("%d\n", n);
    if(n < 1) {
        return 1;
    }
    return n + sum(n - 1);
}

void r(int n) {
    if(n != 1) {
        r(n - 1);
    }
    printf("%d\n", n);
//    return 0;
}

void a(int i) {
    if(i > 1) {
        printf("=%d=", i);
        a(i / 2);
        a(i / 2);
    }
    printf("+%d+", i);
    printf("*");
}

double diva(int n) {
    if(n == 1){
        return 1;
    }
    printf("%d %lf %lf\n", n, (double)n-1, (double)1/n);
    return diva(n - 1) + (double)1/n;
}

int main() {
//    printf(">>%d\n", factorial(5));
    printf(">>%d\n", fibo(5));
//    printf("%d", power(2, 4));
//    hanoi(3, 1, 2, 3);
//    printf("%d\n", sum(5));
//    printf("%lf\n", diva(5));
    return 0;
}
