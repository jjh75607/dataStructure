#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define MAXLENGTH 10
#define MAXRANGE 100

struct coordinate {
    int x;
    int y;
};

struct Birthday {
    int year;
    int month;
    int day;
};

double Distance(int x, int y);
void findCoordinate(void);
void findFastBirthday(void);
void findFastBirthday2(void);
void findSlowBirthday(void);
void findPrimeNumber(void);
void menu(void);

int main() {
    while(1) {
        menu();
        
        int n;
        scanf("%d", &n);
        
        if(n == 1) { // 1번 문제
            findCoordinate();
        } else if(n == 2) { // 2번문제
            findFastBirthday();
        } else if(n == 3) { // 3번
            findFastBirthday2();
        } else if(n == 4) { //4
            findSlowBirthday();
        } else if(n == 5) { //5
            findPrimeNumber();
        } else {
            break;
        }
    }
} // --------
 

double Distance(int x, int y) {
    return sqrt(pow(x, 2) + pow(y, 2));
}

void findCoordinate() { // 1번
    struct coordinate coordinate[MAXLENGTH] = {{1, 2}, {6, 2}, {4, 2}, {5, 6}, {3, 7}, {1, -3}, {-2, 1}, {2, 2}, {3, 2}, {6, 3} };
    double distance[MAXLENGTH] = {0};
    double max = 0;
    double min = MAXRANGE;
    int maxX = 0, maxY = 0;
    int minX = 0, minY = 0;
    
    for (int i = 0; i < MAXLENGTH; i++) {
        distance[i] = Distance(coordinate[i].x, coordinate[i].y);
        
        if (distance[i] > max) {
            max = distance[i];
            maxX = coordinate[i].x;
            maxY = coordinate[i].y;
            
        }
        if (distance[i] < min) {
            min = distance[i];
            minX = coordinate[i].x;
            minY = coordinate[i].y;
        }
    }
    
    printf("가장 먼 거리는 (%d, %d)이며 거리는 %lf입니다.\n가장 가까운 거리는 (%d, %d)이며 거리는 %lf입니다\n", maxX, maxY, max, minX, minY, min);
}

void findFastBirthday(void) { // 2번
    char birthdays[MAXLENGTH][9] = {"19660819", "20000115", "19651213", "20100204", "20010304", "19990902", "19970203", "20201112", "20121210", "20300401"};
    struct Birthday birthday[MAXLENGTH];
    
    for(int i = 0; i < MAXLENGTH; i++) {
        birthday[i].year = atoi(birthdays[i]) * 0.0001;
        birthday[i].month = (int)(atoi(birthdays[i]) * 0.01) % 100;
        birthday[i].day = atoi(birthdays[i]) % 100;
    }
    
    int fastYear = birthday[0].year;
    int fastMonth = birthday[0].month;
    int fastDay = birthday[0].day;
    
    for(int i = 1; i < MAXLENGTH; i++) {
        if(fastYear > birthday[i].year) {
            fastYear = birthday[i].year;
            fastMonth = birthday[i].month;
            fastDay = birthday[i].day;
        } else if(fastYear == birthday[i].year && fastMonth > birthday[i].month) {
            fastMonth = birthday[i].month;
            fastDay = birthday[i].day;
        } else if(fastYear == birthday[i].year && fastMonth == birthday[i].month && fastDay > birthday[i].day) {
            fastDay = birthday[i].day;
        }
    }
    printf("가장 빠른 생년월일 %d-%02d-%02d\n", fastYear, fastMonth, fastDay);
}

void findSlowBirthday(void) { //4번
    struct Birthday birthday[MAXLENGTH] = { //구조체
        {1923, 02, 01},
        {2001, 05, 04},
        {2003, 01, 12},
        {1971, 03, 14},
        {2003, 01, 15},
        {2003, 01, 15},
        {1902, 07, 31},
        {1999, 06, 24},
        {1902, 07, 22},
        {1901, 02, 05}
    };
    
    int slowYear = birthday[0].year;
    int slowMonth = birthday[0].month;
    int slowDay = birthday[0].day;
    
    for(int i = 1; i < MAXLENGTH; i++) {
        if(slowYear < birthday[i].year) {
            slowYear = birthday[i].year;
            slowMonth = birthday[i].month;
            slowDay = birthday[i].day;
        } else if(slowYear == birthday[i].year && slowMonth < birthday[i].month) {
            slowMonth = birthday[i].month;
            slowDay = birthday[i].day;
        } else if(slowYear == birthday[i].year && slowMonth == birthday[i].month && slowDay < birthday[i].day) {
            slowDay = birthday[i].day;
        }
    }
    printf("가장 느린 생년월일 %d-%02d-%02d\n", slowYear, slowMonth, slowDay);
}

void findFastBirthday2(void) { //3번
    char birthdays[MAXLENGTH][9] = {"19650819", "20000115", "19650213", "20100204", "20010304", "19990902", "19970203", "20201112", "20121210", "20300401"};
    int year[MAXLENGTH], month[MAXLENGTH], day[MAXLENGTH];
    
    for(int i = 0; i < MAXLENGTH; i++) {
        char strYear[5], strMonth[3], strDay[3];// 문자열의 마지막 NULL 문자를 포함하기 위해 +1을 한 사이즈
        
        strncpy(strYear, birthdays[i], 4); //문자열의 해당 인덱스까지만 복사
        strncpy(strMonth, birthdays[i] + 4, 2); //year에 해당하는 4자리는 복사했기에 복사할 범위에 +4후 2만큼만 복사
        strncpy(strDay, birthdays[i] + 6, 2);
        
        year[i] = atoi(strYear); // 정수로 바꿔서 저장
        month[i] = atoi(strMonth);
        day[i] = atoi(strDay);
    }
    
    int fastYear = year[0];
    int fastMonth = month[0];
    int fastDay = day[0];
    
    for(int i = 1; i < MAXLENGTH; i++) { //바꾼 정수로 대소비교
        if(fastYear > year[i]) {
            fastYear = year[i];
            fastMonth = month[i];
            fastDay = day[i];
        } else if(fastYear == year[i] && fastMonth > month[i]) {
            fastMonth = month[i];
            fastDay = day[i];
        } else if(fastYear == year[i] && fastMonth == month[i] && fastDay > day[i]) {
            fastDay = day[i];
        }
    }
    printf("가장 빠른 생년월일 %d-%02d-%02d\n", fastYear, fastMonth, fastDay);
}

void findPrimeNumber() { //5번
    int n1, n2;
    
    printf("숫자 두개를 입력하세요 / n1 < n2(n1은 2이상) -->");
    scanf("%d %d", &n1, &n2);
    
    while(1) {
        if(n1 < 2) {
            printf("숫자 두개를 입력하세요 / n1은 2보다 커야합니다. -->");
            scanf("%d %d", &n1, &n2);
        } else if(n2 <= n1) {
            printf("숫자 두개를 입력하세요 / n2는 n1보다 커야합니다. -->");
            scanf("%d %d", &n1, &n2);
        } else {
            break;
        }
    }
    
    for(int i = n1; i <= n2; i++) {
        int flag = 0;
        for(int j = 2; j < i; j++) {
            if(i % j == 0) {
                flag = 1; //만약 소수가 아니라면 flag를 1로 변경
                break;
            }
        }
        if(flag != 1) { //falg가 0이면 소수라는 뜻 이므로 출력.
            printf("%d ", i);
        }
    }
    printf("\n");
}

void menu(void) {
    printf("\n--1~5가 아닌 숫자를 입력시 종료.--\n");
    printf("1. 좌표간 거리 구하기(최대 100까지)\n");
    printf("2. 문자열을 사용한 가장 빠른 생년월일 찾기\n");
    printf("3. 2차원배열을 사용한 가장 빠른 생년월일 찾기\n");
    printf("4. 구조체를 사용한 가장 늦은 생년월일 찾기\n");
    printf("5. 소수찾기\n --> : ");
}
