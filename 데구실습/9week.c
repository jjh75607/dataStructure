//
//  9week.c
//  데구실습
//
//  Created by 정순재 on 2023/05/02.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
    char *title;
    char genre;
    int  year;
    int playTime;
}element; //제목, 장르, 개봉년도, 재생시간를 위한 구조체

typedef struct node{
    element data;
    struct node* pre;
    struct node* next;
}node; //이중 연결리스트 구조체

void init(node* phead) {
    phead->pre = phead;
    phead->next = phead;
} //이중연결리스트 초기화를 위한 함수

node* delete_node(node* head, char* title) {
    node* pre = NULL;
    
    if(head == NULL) { //비어있다면
        printf("비어있는 노드는 삭제할수 없습니다.");
        return NULL;
    } else if(strcmp(head->data.title, title) == 0) {
        pre = head;
        head = head->next;
        free(pre);
    } else {
        for (node* q = head; q != NULL; q = q->next) {
            if(strcmp(q->data.title, title) == 0) {
                pre->next = q->next;
                free(q);
                return head;
            }
            pre = q;
        }
    }
    
    return head;
}

void dDelete(node* head, node* remove) {
    if(head == remove)
        return;
    remove->pre->next = remove->next;
    remove->next->pre = remove->pre;
    free(remove);
} //이중연결리스트 삭제를 위한 함수

void insert_node(node* before, element value) {
    node* p = (node*)malloc(sizeof(node));
    p->data = value;
    p->pre = before;
    p->next = before->next;
    before->next->pre = p;
    before->next = p;
}

node* find_movieTitle(node *head, char *title) {
    for(node* p = head; p != NULL; p = p->next) { //루프를 돌려 같은 제목을 발견한다면 해당 구조체를 리턴
        if(strcmp(p->data.title, title) == 0) {
            return p;
        }
    }
    return NULL;
}

node* dFind_movieTitle(node *head, char *title) {
    for(node* p = head->next; p != head; p = p->next) { //루프를 돌려 같은 제목을 발견한다면 해당 구조체를 리턴
        if(strcmp(p->data.title, title) == 0) {
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

int get_lengthRe(node* head) {
    if(head == NULL) {
        return 0;
    }
    
    return get_lengthRe(head->next) + 1;
}

int dGetLength(node* head) {
    int cnt = 0;
    for(node* q = head->next; q != head; q = q->next) {
        cnt++;
    }
    return cnt;
}

node* displayRe(node* head) {
    if(head == NULL) {
        return NULL;
    }
    printf("제목 : %s, 장르 : %c, 개봉년도 : %d\n", head->data.title, head->data.genre, head->data.year);
    return displayRe(head->next);
}

void display(node *head) {
    node* p;
    for (p = head->next; p != head; p = p->next) {
        printf("<-| |%s %c %d %d| |->", p->data.title, p->data.genre, p->data.year, p->data.playTime);
    }
    printf("\n");
}

void reverseDisplay(node *head) {
    if(head != NULL) {
        reverseDisplay(head->next);
        printf("제목 : %s, 장르 : %c, 개봉년도 : %d\n", head->data.title, head->data.genre, head->data.year);
    }
}

node* findFastMovie(node* head) {
    node *p = head;
    int find = p->next->data.year;
    
    for (node* q = head->next; q != head; q = q->next) {
        if(find >= q->data.year) {
            find = q->data.year;
            p = q;
        }
    }
    
    return p;
}

void findGenrePrint(node* head, char genre) {
    for (node* q = head; q != NULL; q = q->next) {
        if(genre == q->data.genre) {
            printf("%s %c %d\n", q->data.title, q->data.genre, q->data.year);
        }
    }
}

void dFindGenrePrint(node* head, char genre) {
    for (node* q = head->next; q != head; q = q->next) {
        if(genre == q->data.genre) {
            printf("%s %c %d %d\n", q->data.title, q->data.genre, q->data.year, q->data.playTime);
        }
    }
}



void menu(void) {
    printf("\n================\n");
    printf("1. 데이터 입력(영화이름, 장르{a,c,f,r}, 개봉년도\n");
    printf("2. 가장 빠른 개봉년도\n");
    printf("3. 원하는 장르만 검색\n");
    printf("4. 노드의 갯수\n");
    printf("5. 순환 출력\n");
    printf("6. 역순 순환 출력\n");
    printf("7. 데이터 삭제\n");
    printf("8. 특정 영화 제목 검색\n");
    printf("9. 재생\n");
//    printf("3. 리스트의 노드 갯수\n");
//    printf("4. 리스트 전체 출력\n");
//    printf("5. 터미널 한글 입력 깨짐으로 미리 입력해둔 테스트\n");
    printf("================\n");
    printf(">>> ");
}

void loadingBar(node* p) {
    printf("제목->%s : ", p->data.title);
    for(int i = 0; i < p->data.playTime; i++) {
        printf(".");
        sleep(p->data.playTime);
    }
    
    printf("\n");
}

int main() {
    int n;
    node* temp = (node*)malloc(sizeof(node));
    node* current;
    init(temp);

    while(1) {
        menu();

        scanf("%d", &n);

        getchar();
        if(n == 1) {
            char *title = (char*)malloc(sizeof(char) * 100);
            char genre;
            int year, playTime;

            printf("제목 입력 >>");
            scanf("%s", title);
            getchar();
            printf("장르 입력 >>");
            scanf("%c", &genre);
            getchar();
            printf("개봉년도 입력 >>");
            scanf("%d", &year);
            getchar();
            printf("재생시간 입력 >>");
            scanf("%d", &playTime);
            getchar();

            element data = (element){title, genre, year, playTime};

            int t = 0;
            node* q = NULL;
            for (node* p = temp->next; p != temp; p = p->next) {
                if(strcmp(title, p->data.title) > 0) {//양수면 title이 더 큼
                    q = p;
                    t = 1;
                } else {
                    break;
                }
            }
            
            if(t) {
                insert_node(q, data);
            } else {
                insert_node(temp, data);
            }
            
        } else if(n == 2) {
            node *t = findFastMovie(temp);
            printf("가장 빠른 개봉년도를 가진 영화는 %s %c %d %d\n", t->data.title, t->data.genre, t->data.year, t->data.playTime);
        } else if(n == 3) {
            char genre;
            printf("장르 입력 >>");
            scanf("%c", &genre);
            dFindGenrePrint(temp, genre);
        }else if(n == 4) {
            printf("현재 노드의 갯수는 %d\n", dGetLength(temp));
        }else if(n == 5) {
            display(temp);
        }else if(n == 6) {
            reverseDisplay(temp);
        } else if(n == 7){
            char *title = (char*)malloc(sizeof(char) * 100);

            printf("삭제할 영화 제목 입력 >>");
            scanf("%s", title);
            
            for (node* p = temp->next; p != temp; p=p->next) {
                if(strcmp(title, p->data.title) == 0 ){
                    dDelete(temp, p);
                    break;
                }
            }
        } else if(n == 8){
            char *title = (char*)malloc(sizeof(char) * 100);

            printf("영화 제목 입력 >>");
            scanf("%s", title);

            node* t = dFind_movieTitle(temp, title);
            if(t == NULL) {
                printf("is empty\n");
            } else {
                printf("%s %c %d %d\n", t->data.title, t->data.genre, t->data.year, t->data.playTime);
            }
        } else if(n == 9){
            current = temp->next;
            char ch;
            
            do {
                printf(">(다음 노드), <(이전 노드), f(처음노드), l(마지막 노드), p(현재노드) q(종료)");
                printf("입력 : ");
                scanf("%c", &ch);
                getchar();
                if(ch == '>') {
                    if(current == temp->pre) {
                        current = temp->next;
                    } else {
                        current = current->next;
                    }
                    loadingBar(current);
                } else if(ch == '<') {
                    if(current == temp->next) {
                        current = temp->pre;
                    } else {
                        current = current->pre;
                    }
                    loadingBar(current);
                } else if(ch == 'f') {
                    current = temp->next;
                    loadingBar(current);
                } else if(ch == 'l') {
                    current = temp->pre;
                    loadingBar(current);
                } else if(ch == 'p'){
                    loadingBar(current);
                    if(current == temp->pre) {
                        current = temp->next;
                    } else {
                        current = current->next;
                    }
                }
            } while(ch != 'q');
        } else {
            break;
        }
    }
    
//    node* head = NULL;
//    int n;
    
    /*while(1) {
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
            
//            printf("fast movie %d\n", findFastMovie(temp)->data.year);
//            findGenrePrint(temp, 'a');

//            display(temp);
//
//            node* temp2 = find_movieTitle(temp, "고목");
//            if(temp2 == NULL) {
//                printf("is empty\n");
//            } else {
//                printf("%s %c %d\n", temp2->data.title, temp2->data.genre, temp2->data.year);
//            }
//
//            printf("%d\n", get_length(temp));
        } else {
            break;
        }
    }
    */
    return 0;
}
