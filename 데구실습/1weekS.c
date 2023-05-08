//
//  1weekS.c
//  데구실습
//
//  Created by 정순재 on 2023/04/11.
//

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 10
#define MAX_RANGE 0
#define MIN_RANGE 999

typedef struct coordinate {
    int x;
    int y;
}coordinate;

typedef struct birthDay {
    int year;
    int month;
    int day;
}birthDay;

double distance(int x, int y);
void findCoordinate(coordinate c[]);
birthDay findBirthday(char arr[][9], birthDay b[]);
void fastOrSlowBirthday(birthDay b[]);

int main() {
    //좌표간 거리
    coordinate coordinate[MAX_SIZE] = {{1, 2}, {6, 2}, {4, 2}, {5, 6}, {3, 7}, {1, -3}, {-2, 1}, {2, 2}, {3, 2}, {6, 3} };
    findCoordinate(coordinate);
    
    //가장 빠른 생년월일
    char birthdayList[10][9] = {"19660819", "20000115", "19651213", "20100204", "20010304", "19990902", "19970203", "20201112", "20121210", "20300401"};
    birthDay birthdays[10];
    
    findBirthday(birthdayList, birthdays);
    fastOrSlowBirthday(birthdays);
    
    int n, m;
    scanf("%d %d", &m, &n);
    
    
    for (int i = m; i <= n; i++) {
        int flag = 0;
        for (int j = 2; j < i; j++) {
            if(i % j == 0) {
                flag = 1;
                continue;
            }
        }
        if(flag == 0) {
            printf("%d ", i);
        }
    }
    
    
    return 0;
}

double distance(int x, int y) {
    return sqrt(pow(x, 2) + pow(y, 2));
}

void findCoordinate(coordinate c[]) {
    double max = MAX_RANGE, min = MIN_RANGE;
    int maxX = 0, maxY = 0;
    int minX = 0, minY = 0;
    
    for (int i = 0; i < MAX_SIZE; i++) {
        double temp = distance(c[i].x, c[i].y);
        
        if(temp > max) {
            maxX = c[i].x;
            maxY = c[i].y;
            max = temp;
        }
        
        if(temp < min) {
            minX = c[i].x;
            minY = c[i].y;
            min = temp;
            
        }
    }
    
    printf("가장 먼 거리는 %lf이고 좌표는 (%d, %d)입니다.\n", max, maxX, maxY);
    printf("가장 가까운 거리는 %lf이고 좌표는 (%d, %d)입니다.\n", min, minX, minY);
}

birthDay findBirthday(char arr[][9], birthDay b[]) {
    for (int i = 0; i < 10; i++) {
        b[i].year = atoi(arr[i]) / 10000;
        b[i].month = (atoi(arr[i]) / 100) % 100;
        b[i].day = atoi(arr[i]) % 100;
    }
    
    return *b;
}

void fastOrSlowBirthday(birthDay b[]) {
    int fastYear = b[0].year;
    int fastMonth = b[0].month;
    int fastDay = b[0].day;

    for (int i = 1; i < 10; i++) {
        if(fastYear > b[i].year) {
            fastYear = b[i].year;
            fastMonth = b[i].month;
            fastDay = b[i].day;
            
        } else if(fastYear == b[i].year && fastMonth > b[i].month) {
            fastMonth = b[i].month;
            fastDay = b[i].day;
        } else if(fastYear == b[i].year && fastMonth == b[i].month && fastDay > b[i].day) {
            fastDay = b[i].day;
        }
    }
    
    printf("%d %02d %02d\n", fastYear, fastMonth, fastDay);
}


