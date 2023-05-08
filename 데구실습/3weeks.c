#include <stdio.h>
#include <math.h>

#define MAX(a,b) (((a)>(b))?(a):(b))
#define MAX_DEGREE 101

typedef struct { // 다항식 구조체 타입 선언
    int degree; // 다항식의 차수
    float coef[MAX_DEGREE]; // 다항식의 계수
} polynomial;

// C = A+B 여기서 A와 B는 다항식이다. 구조체가 반환된다.
polynomial poly_add1(polynomial A, polynomial B) {
    polynomial C; // 결과 다항식
    int Apos = 0, Bpos = 0, Cpos = 0; // 배열 인덱스 변수
    int degree_a = A.degree;
    int degree_b = B.degree;

    C.degree = MAX(A.degree, B.degree); // 결과 다항식 차수

    while (Apos <= A.degree && Bpos <= B.degree) {
        if (degree_a > degree_b) {  // A항 > B항
            C.coef[Cpos++] = A.coef[Apos++];
            degree_a--;
        } else if (degree_a == degree_b) {  // A항 == B항
            C.coef[Cpos++] = A.coef[Apos++] + B.coef[Bpos++];
            degree_a--; degree_b--;
        } else { // B항 > A항
            C.coef[Cpos++] = B.coef[Bpos++];
            degree_b--;
        }
    }
    return C;
}

polynomial poly_mul(polynomial p1, polynomial p2) {
    polynomial result;
    result.degree = p1.degree + p2.degree;
    
    for (int i = 0; i < result.degree + 1; i++) {
        result.coef[i] = 0;
    }
    
    for (int i = 0; i < p1.degree + 1; i++) {
        for (int j = 0; j < p2.degree + 1; j++) {
            result.coef[i + j] += p1.coef[i] * p2.coef[j];
        }
    }
    
    return result;
}

polynomial userInputPolynomial(void) {
    polynomial tmp;
    
    printf("degree : ");
    scanf("%d", &tmp.degree);
    
    for (int i = 0; i < tmp.degree + 1; i++) {
        scanf("%f", &tmp.coef[i]);
    }
    
    return tmp;
}

void printPolynomial(polynomial p) {//4x^7-3x^4+2x^3-1
    for (int i = 0; i < p.degree + 1; i++) {
        if(p.coef[i] != 0) {
            if (p.coef[i] == 1) {
                printf("x^%d", p.degree - i);
            } else if(p.degree - i == 0) {
                printf("%.0f", p.coef[i]);
            } else if(p.degree - i == 1){
                printf("%.0fx", p.coef[i]);
            } else {
                printf("%.0fx^%d", p.coef[i], p.degree - i);
            }
            
            if(p.degree - i != 0) {
                printf(" + ");
            }
        }
    }
    
    printf("\n");
}

int poly_eval(int x) {
    int result = 0;
    polynomial p1 = {3, {3, 2, 1, 4}};

    for (int i = 0; i < p1.degree + 1; i++) {
        result += p1.coef[i] * pow(x, p1.degree - i);
    }
    return result;
}

int main() {
    polynomial a = {3, {3, 2, 1, 4}};
    polynomial b = {3, {1, 5, 4, 3}};
    printPolynomial(poly_mul(a, b));
    
    printf(" : %d : \n", poly_eval(3));
    
    return 0;
}
