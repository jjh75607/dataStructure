#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_QUEUE_SIZE 100

// 프로그램 5.2에서 다음과 같은 부분을 복사한다.
// ================ 원형큐 코드 시작 =================
typedef struct { // 요소 타입
    int type; //추가
    int id;
    int arrival_time; //도착시간
    int service_time; //서비스시간
} element;            // 교체!

typedef struct {
    element data[MAX_QUEUE_SIZE];
    int front, real;
}QueueType;

void error(char *message) {
    fprintf(stderr, "%s\n", message);
}

void init_queue(QueueType *q) {
    q->front = q->real = 0;
}

int is_empty(QueueType *q) {
    return (q->front == q->real);
}

int is_full(QueueType *q) {
    return (q->real + 1) % MAX_QUEUE_SIZE == q->front;
}

void queue_print(QueueType *q) {
    printf("QUEUE(front=%d rear=%d) = ", q->front, q->real);
    if(!is_empty(q)) {
        int i = q->front;
        do {
            i = (i + 1) % MAX_QUEUE_SIZE;
            printf("%d %d %d | ", q->data[i].id, q->data[i].arrival_time, q->data[i].service_time);
            if(i != q->real)
                break;
        }while(i != q->front);
    }
    printf("\n");
}

void enqueue(QueueType *q, element item) {
    if(is_full(q))
        error("포화");
    q->real = (q->real + 1) % MAX_QUEUE_SIZE;
    q->data[q->real] = item;
}

element dequeue(QueueType *q) {
    if(is_empty(q)) {
        error("공백");
    }
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}
// ================ 원형큐 코드 종료 =================

int main(void) {
    
    int n;
    
    while(1) {
        scanf("%d", &n);
        
        if(n == 1) { //2번 문제
            int minutes = 60;
            int total_customers = 0;
            
            int service_time = 0;
            int service_customer = 0;
            
            int serviceTimeB = 0;
            int serviceCustomerB = 0;//2번 창구의 변수들 선언

            QueueType queue;
            init_queue(&queue);
            srand((unsigned int)time(NULL));

            for (int clock = 0; clock < minutes; clock++) {
                printf("현재시각=%d\n", clock);
                
                if ( (rand()%10) < 3) {
                    element customer;
                    customer.id = total_customers++;
                    customer.arrival_time = clock;
                    customer.service_time = rand() % 3+1;
                    customer.type = 1; //1번창구인지 2번창구인지 구분하기 위한 type
                    enqueue(&queue, customer);
                    printf("[1번 창구]고객 %d이 %d분에 들어옵니다. 업무처리시간= %d분\n", customer.id, customer.arrival_time, customer.service_time);
                }
                
                if ( (rand()%10) < 3) { //2번 창구의 손님
                    element customer;
                    customer.id = total_customers++;
                    customer.arrival_time = clock;
                    customer.service_time = rand() % 3+1;
                    customer.type = 2;
                    enqueue(&queue, customer);
                    printf("[2번 창구]고객 %d이 %d분에 들어옵니다. 업무처리시간= %d분\n", customer.id, customer.arrival_time, customer.service_time);
                }
                
                if (service_time > 0 && queue.data[queue.real].type == 1) { //1번 창구의 손님이 업무처리중이라면
                    printf("[1번 창구]고객 %d 업무처리중입니다. \n", service_customer);
                    service_time--;
                } else if(queue.data[queue.real].type == 1){
                    if (!is_empty(&queue)) {
                        element customer = dequeue(&queue);
                        service_customer = customer.id;
                        service_time = customer.service_time;
                        
                        if(customer.type == 1) { //타입이 1즉 1번창구의 손님에 대한 정보
                            printf("[1번 창구]고객 %d이 %d분에 업무를 시작합니다. 대기시간은 %d분이었습니다.\n", customer.id, clock, clock - customer.arrival_time);
                        }
                    }
                }
                
                if (serviceTimeB > 0 && queue.data[queue.real].type == 2) {
                    printf("[2번 창구]고객 %d 업무처리중입니다. \n", serviceCustomerB);
                    serviceTimeB--;
                } else if(queue.data[queue.real].type == 2){
                    if (!is_empty(&queue)) {
                        element customer = dequeue(&queue);
                        serviceCustomerB = customer.id;
                        serviceTimeB = customer.service_time;
                        
                        if(customer.type == 2) {
                            printf("[2번 창구]고객 %d이 %d분에 업무를 시작합니다. 대기시간은 %d분이었습니다.\n", customer.id, clock, clock - customer.arrival_time);
                        }
                    }
                }
            }
        } else if(n == 2) {
            int sex;
            int manCnt = 0;
            int girlCnt = 0;
            
            QueueType man, girl;
            
            init_queue(&man);
            init_queue(&girl);
            
            srand((unsigned int)time(NULL));
            
            for(int i = 0; i < MAX_QUEUE_SIZE; i++) { //0 ~ 99
                sex = rand() % MAX_QUEUE_SIZE;
                
                if(sex % 2 == 0) {//남 짝수라면
                    element data;
                    data.id = ++manCnt; //몇번째 남자인지 id에 할당
                    enqueue(&man, data);
                    
                    printf("남%d 입장 - ", manCnt);
                    if(!is_empty(&girl)) { //girl큐가 비어있지 않다면
                        printf("남%d/여%d 매칭\n", dequeue(&man).id, dequeue(&girl).id);
                    } else {
                        printf("대기\n");
                    }
                } else {
                    element data;
                    data.id = ++girlCnt;
                    enqueue(&girl, data);
                    
                    printf("여%d 입장 - ", girlCnt);
                    if(!is_empty(&man)) {
                        printf("여%d/남%d 매칭\n", dequeue(&girl).id, dequeue(&man).id);
                    } else {
                        printf("대기\n");
                    }
                }
            }
        } else {
            break;
        }
    }
    return 0;
}
