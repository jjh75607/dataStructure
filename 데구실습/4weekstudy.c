//
//  4weekstudy.c
//  데구실습
//
//  Created by 정순재 on 2023/04/22.
//

#include <stdio.h>

#define MAX_TERMS 100
#define ROW 8
#define COL 10

typedef struct {
    int row;
    int col;
    int value;
} element;

typedef struct SparseMatrix {
    element data[MAX_TERMS];
    int rows; // 행의 개수
    int cols; // 열의 개수
    int terms; // 항의 개수
} SparseMatrix;

int a[8][10] = {
    { 0, 0, 0, 0, 2, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0,-3, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0,-1, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

int b[8][10] = {
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0,-1, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 2, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 2, 0, 0, 0 }
};

int c[8][10] = {
    { 0, 0, 0, 0,-2, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 3 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0,-2, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 4, 0, 0, 0 }
};

SparseMatrix changeSparseMatrix(int arr[ROW][COL]) {
    SparseMatrix s;
    s.rows = ROW;
    s.cols = COL;
    s.terms = 0;
    
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            if(arr[i][j] != 0) {
                s.data[s.terms].value = arr[i][j];
                s.data[s.terms].row = i;
                s.data[s.terms].col = j;
                s.terms++;
            }
        }
    }
    
    return s;
}

SparseMatrix addSparseMatrix(SparseMatrix s1, SparseMatrix s2) {
    int aTerm = 0;
    int bTerm = 0;
    int term = 0;
    
    SparseMatrix result;
    result.rows = ROW;
    result.cols = COL;
    
    while(aTerm < s1.terms && bTerm < s2.terms) {
        if(s1.data[aTerm].row < s2.data[bTerm].row) {
            result.data[term].value = s1.data[aTerm].value;
            result.data[term].row = s1.data[aTerm].row;
            result.data[term].col = s1.data[aTerm].col;
            aTerm++;
        } else if(s1.data[aTerm].row > s2.data[bTerm].row) {
            result.data[term].value = s2.data[bTerm].value;
            result.data[term].row = s2.data[bTerm].row;
            result.data[term].col = s2.data[bTerm].col;
            bTerm++;
        } else {//s1 == s2
            if(s1.data[aTerm].col < s2.data[bTerm].col) {
                result.data[term].value = s1.data[aTerm].value;
                result.data[term].row = s1.data[aTerm].row;
                result.data[term].col = s1.data[aTerm].col;
                aTerm++;
            } else if(s1.data[aTerm].col > s2.data[bTerm].col) {
                result.data[term].value = s2.data[bTerm].value;
                result.data[term].row = s2.data[bTerm].row;
                result.data[term].col = s2.data[bTerm].col;
                bTerm++;
            } else {
                result.data[term].value = s1.data[aTerm].value + s2.data[bTerm].value;
                result.data[term].row = s2.data[bTerm].row;
                result.data[term].col = s2.data[bTerm].col;
                bTerm++;
                aTerm++;
            }
        }
        term++;
    }
    
    while(aTerm < s1.terms) {
        result.data[term++] = s1.data[aTerm++];
    }
    
    while(bTerm < s2.terms) {
        result.data[term++] = s2.data[bTerm++];
    }
    
    result.terms = term;
    
    return result;
}

void printSparseMatrix(SparseMatrix s) {
    int cnt = 0;
    for (int i = 0; i < s.rows; i++) {
        for (int j = 0; j < s.cols; j++) {
            if(cnt < s.terms && i == s.data[cnt].row && j == s.data[cnt].col) {
                printf("%3d", s.data[cnt++].value);
            } else {
                printf("%3d", 0);
            }
        }
        printf("\n");
    }
}

SparseMatrix test(SparseMatrix s) {
    SparseMatrix result;
    result.rows = s.cols;
    result.cols = s.rows;
    result.terms = s.terms;
    
    int cnt = 0;
    for (int i = 0; i < result.cols; i++) {//가로를 기준으로 찍으니까 col, 그리고 위에랑 인덱스가 안 맞아서 cnt추가,
        for (int j = 0; j < result.terms; j++) {
            if(s.data[j].col == i) {
                result.data[cnt].value = s.data[j].value;
                result.data[cnt].row = s.data[j].col;
                result.data[cnt++].col = s.data[j].row;
            }
        }
    }
    
    return result;
}


int main() {
    SparseMatrix s1 = changeSparseMatrix(a);
//    SparseMatrix s2 = changeSparseMatrix(b);
//    SparseMatrix s3 = changeSparseMatrix(c);
//    SparseMatrix s4 = addSparseMatrix(s1, s2);
    printSparseMatrix(test(s1));

    return 0;
}
