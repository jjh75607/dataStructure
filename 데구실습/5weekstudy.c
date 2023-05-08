#include <stdio.h>

int factorial(int n) {
    if(n == 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

void factorialFor(int n) {
    int result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    printf("factorialFor %d\n", result);
}

void powerFor(int n, int x) {
    int r = 1;
    for (int i = 0; i < x; i++) {
        r = r * n;
    }
    printf("powerFor %d\n", r);
}

int power(int n, int x) {
    if(x == 0) {
        return 1;
    }
    return n * power(n, x - 1);
}

int fibo(int n) {
    if(n < 2) {
        return n;
    }
    return fibo(n-1) + fibo(n-2);
}

void hanoi(int n, int a, int b, int c) {
    if(n == 1) {
        printf("%d -> %d\n", a, c);
    } else {
        hanoi(n - 1, a, c, b);//a의 제일 큰 원판을 제외하고 b로 모두 이동
        printf("%d -> %d\n", a, c);//제일 큰 원판 c로 이동
        hanoi(n - 1, b, a, c); //b에 있는 모든 원판 c로 이동
    }
}

int qustion13(int n) {
    if(n <= 1) {
        return n;
    }
    return n + qustion13(n - 1);
}

double qustion14(double n) {
    if(n == 1) {
        return n;
    }
    return (1 / n) + qustion14(n - 1);
}

void qustion16(int n) {
    int r = 0;
    for (int i = 1; i <= n; i++) {
        r += i;
    }
    printf("qustion16 %d\n", r);
}

int binomial(int n, int k) {
    if(k == 0 || n == k) {
        return 1;
    }
    return binomial(n - 1, k - 1) + binomial(n - 1, k);
}

int A(int m, int n) {
    if(m == 0) {
        return n+1;
    } else if(n == 0) {
        return A(m - 1, 1);
    } else {
        return A(m - 1, A(m, n - 1));
    }
}

int main() {
    printf("factorial %d\n", factorial(5));
    factorialFor(5);
    powerFor(3, 2);
    printf("power %d\n", power(3, 3));
    printf("fibo %d\n", fibo(5));
    hanoi(1, 1, 2, 3);
    printf("qustion13 %d\n", qustion13(3));
    printf("qustion14 %lf\n", qustion14(5.0));
    qustion16(5);
    printf("binomial %d\n", binomial(5, 2));
    printf("A %d\n", A(3, 2));
    
    return 0;
}
