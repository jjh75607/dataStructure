//
//  2week.c
//  데구실습
//
//  Created by 정순재 on 2023/03/14.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct people {
    char name[10];
    int gender; // 1남성 0여성
    int age;
};

void menu(void);
void textCheck(void);
void genderCheck(void);
void maxValue(void);
int findMaxValue(int arr[], int n);
void binarySearch(void);
int binarySearchRe(int arr[], int fisrt, int last, int n);

int main() {
    
    while(1) {
        menu();
        
        int n;
        scanf("%d", &n);
        
        if(n == 1) {
            textCheck();
        } else if(n == 2) {
            genderCheck();
        } else if(n == 3) {
            maxValue();
        } else if(n == 4) {
            binarySearch();
        } else {
            break;
        }
    }
    
    return 0;
}

void menu() {
    printf("\n--1~4가 아닌 숫자를 입력시 종료.--\n");
    printf("1. 입력된 문자열이 소문자,대문자,특수문자,숫자가 포함된 10자리 이상의 문자열인지 판별\n");
    printf("2. 20세이상 여성과 남성의 숫자 판별\n");
    printf("3. 배열에서 최대값을 찾는 재귀함수\n");
    printf("4. 이진탐색\n>>");
}

void textCheck() { // 1번문제
    int check[4] = {0,}; //소문자 대문자 특수문자 숫자
    int temp = 0;
    
    printf("\n소문자, 대문자, 특수문자, 숫자가 포함된 10자리 이상의 문자열을 입력해주세요 : ");
    
    char text[100];
    scanf("%s", text);
    
    if(strlen(text) >= 10) {
        for (int i = 0; i < strlen(text); i++) {
            if((text[i] >= 'a' && text[i] <= 'z') && check[0] == 0) { // 소문자 판별
                check[0] = 1;
                continue;
            }
            if((text[i] >= 'A' && text[i] <= 'Z') && check[1] == 0) { // 대문자 판별
                check[1] = 1;
                continue;
            }
            if((text[i] == '!' || text[i] == '#' || text[i] == '$' || text[i] == '*' || text[i] == '?') && check[2] == 0) { // 특스문자 판별
                check[2] = 1;
                continue;
            }
            if ((text[i] >= 48 && text[i] <= 57) && check[3] == 0) { //숫자판별
                check[3] = 1;
                continue;
            }
        }
        
        for (int i = 0; i < 4; i++) {
            temp += check[i];
        }
        
        if(temp == 4) {
            printf("%s는 소문자, 대문자, 특수문자, 숫자가 포함된 10자리 이상의 문자열 입니다.\n", text);
        } else {
            printf("%s는 모든 조건이 충족되지 않았습니다.\n", text);
        }
        
    } else {
        printf("10자리 이상으로 입력해주세요.\n");
    }
}

void genderCheck() { //2번문제
    struct people peoples[10] = {
        {"가가", 1, 12}, {"나가", 0, 23}, {"다가", 1, 35}, {"라가", 0, 41}, {"마가", 1, 5}, {"바가", 0, 19}, {"사가", 1, 20}, {"아가", 0, 11}, {"자가", 1, 24}, {"차가", 0, 21},
    };
    int girlCount = 0;
    int manCount = 0;
    
    for (int i = 0; i < 10; i++) {
        if(peoples[i].age >= 20) {
            (peoples[i].gender == 0) ? girlCount++ : manCount++;
        }
    }
    printf("\n20살 이상의 남성은 %d명, 여성은 %d명 입니다.\n", manCount, girlCount);
}

void maxValue() { // 3번
    int n;
    
    printf("몇자리의 숫자를 입력할지 정해주세요 : ");
    scanf("%d", &n);
    
    int* arr = (int*)malloc(sizeof(int) * n);
    
    printf("\n띄어쓰기로 구분해서 입력해주세요.>>");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    printf("입력하신 숫자 중 가장 큰 수는 %d입니다.\n", findMaxValue(arr, n));
}

int findMaxValue(int arr[], int n) {
    if(n == 0){
        return arr[0];
    }
    
    int max = findMaxValue(arr, n - 1); // 1
    
    if(max > arr[n]) {
        return max;
    } else {
        return arr[n];
    }
}

void binarySearch() { //4번
    int arr[5] = {1, 2, 5, 9, 11};
    int n;
    
    printf("찾을 값을 입력해주세요 : ");
    scanf("%d", &n);
    
    int temp = binarySearchRe(arr, 0, 4, n);
    
    if(temp == -1) {
        printf("%d는 존재하지 않는 값 입니다.\n", n);
    } else {
        printf("%d값은 arr[%d]에 있습니다.\n", n, temp);
    }
}

int binarySearchRe(int arr[], int fisrt, int last, int n) {
    int mid;
    
    if(fisrt > last) {
        return -1;
    }
    
    mid = (fisrt + last) / 2;
    printf("\n범위 [%d] ~~ [%d] 에서 중간 위치 [%d]의 값 [%d]와 찾는 값 %d를 비교\n", fisrt, last, mid, arr[mid], n);
    
    if(n == arr[mid]) {
        return mid;
    } else if(n < arr[mid]) {
        return binarySearchRe(arr, fisrt, mid - 1, n);
    } else {
        return binarySearchRe(arr, mid + 1, last, n);
    }
    
    return 0;
}
