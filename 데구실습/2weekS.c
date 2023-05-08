//
//  2weekS.c
//  데구실습
//
//  Created by 정순재 on 2023/04/21.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char name[10];
    int sex;
    int age;
}people;

void checkString(char text[]) {
    int size = (int)strlen(text);
    int check[4] = {0, };
    int flag = 0;
    
    if(size >= 10) {
        for (int i = 0; i < size; i++) {
            if(isupper(text[i])) {
                check[0] = 1;
                continue;
            }
            if(islower(text[i])) {
                check[1] = 1;
                continue;
            }
            if(isdigit(text[i])) {
                check[2] = 1;
                continue;
            }
            if(text[i] == '!' || text[i] == '?' || text[i] == '*' || text[i] == '#' || text[i] == '$') {
                check[3] = 1;
                continue;
            }
        }
        
        for (int i = 0; i < 4; i++) {
            if(check[i] == 0) {
                flag = 0;
                break;
            }
        }
        
        (flag) ? printf("success\n") : printf("fall\n");
    } else {
        printf("짧다\n");
    }
}

void ageCheck(people *p) {
    int girlCnt = 0;
    int manCnt = 0;
    
    for (int i = 0; i < 10; i++) {
        if(p[i].sex == 1 && p[i].age >= 20) {
            manCnt++;
            continue;
        }
        if(p[i].sex == 0 && p[i].age >= 20) {
            girlCnt++;
            continue;
        }
    }
    printf("girl : %d man : %d\n", girlCnt, manCnt);
}

int findMaxValue(int arr[], int n) {
    if(n == 0) {
        return arr[n];
    }
    
    int max = findMaxValue(arr, n - 1);
    
    if(max > arr[n]) {
        return max;
    } else {
        return arr[n];
    }
}

int binarySearch(int arr[], int first, int last, int n) {
    int mid = (first + last) / 2;
    
    if(first > last) {
        return -1;
    }
    
    printf("중간위치 = %d의 값 %d와 찾는값 %d를 비교\n", mid, arr[mid], n);
    
    if(n == arr[mid]) {
        return mid;
    } else if(arr[mid] > n) {
        return binarySearch(arr, first, mid - 1, n);
    } else {
        return binarySearch(arr, mid + 1, last, n);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    
    if(n == 1) {
        char text[100];
        scanf("%s", text);
        
        checkString(text);
    } else if(n == 2) {
        people peoples[10] =  { {"가가", 1, 12}, {"나가", 0, 23}, {"다가", 1, 35}, {"라가", 0, 41}, {"마가", 1, 5}, {"바가", 0, 19}, {"사가", 1, 20}, {"아가", 0, 11}, {"자가", 1, 24}, {"차가", 0, 21}
        };
        
        ageCheck(peoples);
    } else if(n == 3) {
        int arr[5] = {44, 77, 33, 99, 121};
        int size = 5;
        printf("%d", findMaxValue(arr, size));
    } else if(n == 4) {
        int arr[7] = { 17, 28, 43, 67, 88, 92, 100 };
        int findValue;
        
        scanf("%d", &findValue);
        printf("%d\n", binarySearch(arr, 0, 6, findValue));
    }
    
    return 0;
}
