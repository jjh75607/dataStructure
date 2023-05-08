//
//  9week.c
//  데구실습
//
//  Created by 정순재 on 2023/05/02.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *title;
    char genre;
    int  year;
}element; //제목, 장르, 개봉년도를 위한 구조체

typedef struct node{
    element data;
    struct node* next;
}node;

node* insert_node(node* head, element value) {
    node *p = (node *)malloc(sizeof(node)); //새로운 구조체변수를 동적할당
    p->data = value; //value값은 어떤 장소에 삽입하더라도 들어가야 하기에 미리 삽입

    if(head == NULL) { //head가 null이라면 즉 노드가 비어있는 상태
        p->next = head;
        head = p;
        
        return head;//들어온 값을 head에 넣어주어 리턴
    } else {
        node* pre = NULL; //이전 값을 잠시 담기 위한 변수
        
        for (node* q = head; q != NULL; q = q->next) {
            int i = strcmp(q->data.title, value.title);
            if(i >= 0) { //기존값이 더 크다면
                break;
            }
            pre = q;//원래 있던 것의 뒤에 노드를 추가해야 하기에 q를 Pre에 할당
        }
        
        if(pre == NULL) {//pre가 null이라면 head보다 빠르다는 의미
            p->next = head;
            head = p;
        } else { //아니라면
            p->next = pre->next;
            pre->next = p;
        }
    }
    
    return head;
}

node* find_movieTitle(node *head, char *title) {
    for(node* p = head; p != NULL; p = p->next) { //루프를 돌려 같은 제목을 발견한다면 해당 구조체를 리턴
        if(p->data.title == title) {
            return p;
        }
    }
    return NULL;
}

int get_length(node *head) {
    int cnt = 0;
    for(node* p = head; p != NULL; p = p->next) { //null이 아닐동안 루프를 돌리며 카운트 변수를 +1
        cnt++;
    }
    
    return cnt;
}

void display(node *head) {
    if(head == NULL) { //head가 null이라면 비어있다는 뜻
        printf("node is empty\n");
    } else { //루프를 돌려 하나하나 출력
        for(node* p = head; p != NULL; p = p->next) {
            printf("제목 : %s, 장르 : %c, 개봉년도 : %d\n", p->data.title, p->data.genre, p->data.year);
        }
    }
}

void menu(void) {
    printf("\n================\n");
    printf("1. 데이터 입력(영화이름, 장르{a,c,f,r}, 개봉년도\n");
    printf("2. 특정 영화 제목 검색\n");
    printf("3. 리스트의 노드 갯수\n");
    printf("4. 리스트 전체 출력\n");
    printf("5. 터미널 한글 입력 깨짐으로 미리 입력해둔 테스트\n");
    printf("================\n");
    printf(">>> ");
}


int main() {
    node* head = NULL;
    
    int n;
    
    while(1) {
        menu();
        scanf("%d", &n);
        
        if(n == 1) {
            int year;
            char *title = (char*)malloc(sizeof(char) * 100), genre;
            
            printf("제목 입력 >>");
            scanf("%s", title);
            printf("장르 입력 >>");
            scanf(" %c", &genre);
            printf("개봉년도 입력 >>");
            scanf(" %d", &year);
            
            element data = {title, genre, year};
            head = insert_node(head, data);
        } else if(n == 2) {
            char title[100];
            scanf("%s", title);
            
            node* temp = find_movieTitle(head, title);
            if(temp == NULL) {
                printf("is empty\n");
            } else {
                printf("%s %c %d\n", temp->data.title, temp->data.genre, temp->data.year);
            }
        } else if(n == 3) {
            printf("%d\n", get_length(head));
        } else if(n == 4) {
            display(head);
        } else if(n == 5) {
            node* temp = NULL;
            temp = insert_node(temp, (element){"고목", 'a', 2000});
            temp = insert_node(temp, (element){"제목", 'f', 2001});
            temp = insert_node(temp, (element){"누목", 'r', 2002});
            temp = insert_node(temp, (element){"가나", 'f', 2003});
            temp = insert_node(temp, (element){"나목", 'a', 2004});
            
            display(temp);
            
            node* temp2 = find_movieTitle(temp, "고목");
            if(temp2 == NULL) {
                printf("is empty\n");
            } else {
                printf("%s %c %d\n", temp2->data.title, temp2->data.genre, temp2->data.year);
            }
            
            printf("%d\n", get_length(temp));
        } else {
            break;
        }
    }
    
    
    
    return 0;
}
