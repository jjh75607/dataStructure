//
//  4week.c
//  데구실습
//
//  Created by 정순재 on 2023/03/28.
//

#define MAX_TERMS 100
#define ROW 8
#define COL 10

#include <stdio.h>

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

SparseMatrix saveSparesMatrix(int arr[][COL]);
SparseMatrix addSparseMatrix(SparseMatrix a, SparseMatrix b);
void printSparseMatrix(SparseMatrix a);
SparseMatrix initSparesMatrix(SparseMatrix *s);

int a[8][10] = { { 0, 0, 0, 0, 2, 0, 0, 0, 0, 0 },
                 { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
                 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                 { 0, 0, 0, 0, 0, 0, 0,-3, 0, 0 },
                 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                 { 0,-1, 0, 0, 0, 0, 0, 0, 0, 0 },
                 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }}; //2 1 -3 -1

int b[8][10] = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // -1 2 2
                 { 0, 0, 0,-1, 0, 0, 0, 0, 0, 0 },
                 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                 { 0, 0, 0, 0, 2, 0, 0, 0, 0, 0 },
                 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                 { 0, 0, 0, 0, 0, 0, 2, 0, 0, 0 }};

int c[8][10] = { { 0, 0, 0, 0,-2, 0, 0, 0, 0, 0 },
                 { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
                 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 3 },
                 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                 { 0, 0, 0, 0,-2, 0, 0, 0, 0, 0 },
                 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                 { 0, 0, 0, 0, 0, 0, 4, 0, 0, 0 }};

int main() {
    SparseMatrix s1 = saveSparesMatrix(a); //배열에 저장된 행렬을 구조체로 변경
    SparseMatrix s2 = saveSparesMatrix(b);
    SparseMatrix s3 = saveSparesMatrix(c);
    
    printf("a & b 덧셈\n");
    printSparseMatrix(addSparseMatrix(s1, s2)); //출력함수의 매게변수로 덧셈함수의 결과를 줌
    printf("====================\n");
    printf("b & c덧셈\n");
    printSparseMatrix(addSparseMatrix(s2, s3));
    printf("====================\n");
    printf("a & c덧셈\n");
    printSparseMatrix(addSparseMatrix(s1, s3));
    return 0;
}

SparseMatrix saveSparesMatrix(int arr[][COL]) { //구조체로 변경하는 함수
    SparseMatrix s;
    s.terms = 0;
    s.rows = ROW;
    s.cols = COL; //terms, rows, cols초기화
    int cnt = 0; //카운트 변수 선언
    
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) { //배열의 사이즈 만큼 루프 진행
            if(arr[i][j] == 0){ // 현재 값이 0이라면 건너뜀.
                continue;
            } else { //0이 ㅣ아니라면 cnt 인덱스에 value, row, col값 넣어줌
                s.data[cnt].value = arr[i][j];
                s.data[cnt].row = i;
                s.data[cnt].col = j;
                cnt++;
            }
        }
    }
    s.terms = cnt; //0이 아닌 값을 담는 terms에 반복횟수, 즉 0이 아닌 값의 수를 담아줌
    
    return s;
}

SparseMatrix addSparseMatrix(SparseMatrix a, SparseMatrix b) { //더하기 함수
    SparseMatrix result = initSparesMatrix(&result); //배열 초기화, 결과값을 담을 변수
    result.rows = a.rows;
    result.cols = a.cols;
    int aTemp = 0, bTemp = 0, cnt = 0; //인덱스를 표현하기 위한 변수와 카운트 변수
    
    while (aTemp < a.terms && bTemp < b.terms) { //a.terms와 b.terms만큼 루프를 돌리기 위해 temp변수를 인덱스로 사용
            if (a.data[aTemp].row < b.data[bTemp].row) { //temp변수를 인덱스로 사용하고, a의 row가 b의 row보다 작다면 result에 a의 값들을 넘겨줌
                result.data[cnt].value = a.data[aTemp].value;
                result.data[cnt].row = a.data[aTemp].row;
                result.data[cnt].col = a.data[aTemp].col;
                aTemp++; //a구조체의 0번 인덱스의 값들을 사용했기에 aTemp++
            } else if (a.data[aTemp].row > b.data[bTemp].row) { // b의 row가 더 클때 진행
                result.data[cnt].value = b.data[bTemp].value;
                result.data[cnt].row = b.data[bTemp].row;
                result.data[cnt].col = b.data[bTemp].col;
                bTemp++;
            } else { //a와 b의 row가 같을 경우 col비교
                if (a.data[aTemp].col < b.data[bTemp].col) { //a의 col이 더 작을경우, 즉 더 빠른 인덱스
                    result.data[cnt].value = a.data[aTemp].value;
                    result.data[cnt].row = a.data[aTemp].row;
                    result.data[cnt].col = a.data[aTemp].col;
                    aTemp++;
                } else if (a.data[aTemp].col > b.data[bTemp].col) { // b가 더 작은경우
                    result.data[cnt].value = b.data[bTemp].value;
                    result.data[cnt].row = b.data[bTemp].row;
                    result.data[cnt].col = b.data[bTemp].col;
                    bTemp++;
                } else {//col이 같은경우
                    result.data[cnt].value = a.data[aTemp].value + b.data[bTemp].value;
                    result.data[cnt].row = a.data[aTemp].row;
                    result.data[cnt].col = a.data[aTemp].col;
                    aTemp++;
                    bTemp++;
                }
            }
            cnt++; //한번 while문이 돌때마다 ++
        }
    
    for (; aTemp < a.terms; aTemp++) {//위의 while문의 조건은 하나의 인덱스만 넘어가도 멈추기때문에 남은 값들을 넣어주기 위한 for문
        result.data[cnt] = a.data[aTemp];
        cnt++;
    }
    
    for (; bTemp < b.terms; bTemp++) { // 위와 같으나 b구조체를 위한 포문
        result.data[cnt] = b.data[bTemp];
        cnt++;
    }
    
    result.terms = cnt;
    return result;
}

void printSparseMatrix(SparseMatrix a) { //출력 함수
    int cnt = 0;
    for(int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            //cnt변수가 매게변수로 받은 구조체의 terms보다 작고, row가 i와 같으며 col이 j와 같을 경우에만 사용 / 즉 0이 아닌 값
            if(cnt < a.terms && a.data[cnt].row == i && a.data[cnt].col == j) {
                printf("%3d", a.data[cnt].value);
                cnt++;
            } else { //값이 0일경우
                printf("%3d", 0);
            }
        }
        printf("\n");//한번의 row를 다 출력했을경우 줄바꿈
    }
}

SparseMatrix initSparesMatrix(SparseMatrix *s) { //초기화를 위해 매게변수를 포인터로 선언
    for (int i = 0; i < s->terms; i++) {
        s->data[i].value = 0;
    }
    return *s;
}
