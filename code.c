#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//구조체 선언
typedef struct Class {
    char name[100];
    char subject[200];
    int size;
    float score;
    struct Class* next;
}Class;

char data[100];
char* scan_data(void) {
    scanf("%s", data);
    return data;
}

//사용되는 함수
void menu(); //메뉴를 출력해주는 함수
char* scan_data(void); // 문자열을 입력값으로 받아 리턴해주는 함수
void printAll(Class* hp); // 노드에 연결된 정보를 출력해주는 함수
void add(Class* hp, char*(*fp) (void)); // 노드에 정보를 추가해주는 함수
void search(Class* hp); // 노드로 검색하는 함수
void del(Class* hp); // 노드를 삭제하는 함수
void loadfile(Class* hp); // 파일에서 데이터를 노드에 저장해주는 함수
void Exit(Class* hp); // 노드의 데이터를 파일에 저장해주는 함수

void main()
{
    Class* head = (Class*)malloc(sizeof(Class)); // head노드 생성
    head->next = NULL; // 노드 초기화
    int num; //메뉴에서 선택한 값 저장
    
    loadfile(head); // 파일의 정보 노드에 입력

    while (1) { // 실행
        menu();
        scanf("%d", &num);
        if (num == 5) { // 나가면서 파일에 데이터 저장
            Exit(head); 
            break;
        }
        switch (num) {
        case 1:
            printAll(head);
            break;
        case 2:
            add(head, scan_data);
            break;
        case 3:
            search(head);
            break;
        case 4:
            del(head);
            break;

        default:
            printf("잘못된 선택입니다.\n");
            break;
        }
    }
    //메모리해제
    Class* node = head;
    Class* del;
    while (node != NULL) {
        del = node;
        node = node->next;
        free(del);
    }
}

//메뉴창 띄우기
void menu()
{
    printf("============================================\n");
    printf("1. 출력\n");
    printf("2. 입력\n");
    printf("3. 검색\n");
    printf("4. 삭제\n");
    printf("5. 나가기\n");
    printf("============================================\n");
    printf("메뉴를 고르시오: ");
    return;
}

//전체 프린트
void printAll(Class* hp) {
    Class* temp = hp->next;
    while (temp != NULL) {
        printf("--------------------------------------------\n");
        printf("성함\t과목명\t\t학점\t평점\n");
        printf("%s\t", temp->name);
        printf("%s\t", temp->subject);
        printf("%d\t", temp->size);
        printf("%f\n", temp->score);
        temp = temp->next;
    }
    printf("--------------------------------------------\n");
}

//데이터 추가
void add(Class* hp, char*(*fp) (void)) {
    char* info; // 문자열을 입력받는 함수를 호출한다.
    Class* temp = (Class*)malloc(sizeof(Class)); // 입력받은 값을 저장할 노드를 생성한다.
    Class* last;
    last = hp;
    while (last->next != NULL) {
        last = last->next;
    }
    printf("--------------------추가--------------------\n");
    printf("교수님 성함: ");
    info = scan_data(); // 문자열을 입력받을때, 호출한 함수를 이용하여 노드의 값으로 넘긴다.
    strcpy(temp->name, info);
    printf("과목명: ");
    info = scan_data();
    strcpy(temp->subject, info);
    printf("학점: ");
    scanf("%d", &temp->size);
    printf("평점: ");
    scanf("%f", &temp->score);
    printf("추가되었습니다.\n");
    last->next = temp;
    temp->next = NULL;
}

//데이터 검색
void search(Class* hp) {
    int success = 0;
    int select;
    int searchsize;
    char searchname[50];
    char searchsubject[100];
    Class* temp = hp->next;
    Class* search = (Class*)malloc(sizeof(Class));
    search->size = 0;
    search->score = 0;
    printf("--------------------검색--------------------\n");
    printf("무엇으로 검색하시겠습니까?\n");
    printf("1. 교수님 성함\n");
    printf("2. 과목명\n");
    printf("3. 학점\n");
    printf("--------------------------------------------\n");
    printf("선택: ");
    scanf("%d", &select);
    switch (select) {
    case 1:
        printf("찾고자 하는 교수님 성함: ");
        scanf("%s", searchname);
        strcpy(search->name, searchname);
        while (temp != NULL) {
            if (!strcmp(temp->name, search->name)) {
                success = 1;
                printf("--------------------------------------------\n");
                printf("성함\t과목명\t\t학점\t평점\n");
                printf("%s\t", temp->name);
                printf("%s\t", temp->subject);
                printf("%d\t", temp->size);
                printf("%f\n", temp->score);
                printf("--------------------------------------------\n");

            }
            temp = temp->next;
        }
        if (success == 0) {
            printf("--------------------------------------------\n");
            printf("검색된 교수님은 존재하지 않습니다.\n");
            printf("--------------------------------------------\n");
        }
        free(search);
        break;
    case 2:
        printf("찾고자 하는 과목명: ");
        scanf("%s", searchsubject);
        strcpy(search->subject, searchsubject);
        while (temp != NULL) {
            if (!strcmp(temp->subject, search->subject)) {
                success = 1;
                printf("--------------------------------------------\n");
                printf("성함\t과목명\t\t학점\t평점\n");
                printf("%s\t", temp->name);
                printf("%s\t", temp->subject);
                printf("%d\t", temp->size);
                printf("%f\n", temp->score);
                printf("--------------------------------------------\n");
            }
            temp = temp->next;
        }
        if (success == 0) {
            printf("--------------------------------------------\n");
            printf("검색된 과목명은 존재하지 않습니다.\n");
            printf("--------------------------------------------\n");
        }
        free(search);
        break;
    case 3:
        printf("찾고자 하는 학점: ");
        scanf("%d", &searchsize);
        while (temp != NULL) {
            if (temp->size == searchsize) {
                success = 1;
                printf("--------------------------------------------\n");
                printf("성함\t과목명\t\t학점\t평점\n");
                printf("%s\t", temp->name);
                printf("%s\t", temp->subject);
                printf("%d\t", temp->size);
                printf("%f\n", temp->score);
                printf("--------------------------------------------\n");
            }
            temp = temp->next;
        }
        if (success == 0) {
            printf("--------------------------------------------\n");
            printf("검색된 학점은 존재하지 않습니다.\n");
            printf("--------------------------------------------\n");
        }
        break;
    }
}

//데이터 삭제
void del(Class* hp) {
    Class* temp = hp->next;
    Class* last = hp;
    Class* del;
    Class* data = (Class*)malloc(sizeof(Class));
    int dele = 0;
    char delname[100];
    char delsubject[200];
    printf("--------------------삭제--------------------\n");
    printf("삭제하고 싶은 교수님 성함: ");
    scanf("%s", delname);
    strcpy(data->name, delname);
    printf("삭제하고 싶은 과목명: ");
    scanf("%s", delsubject);
    strcpy(data->subject, delsubject);
    while (temp != NULL) {
        if ((!strcmp(temp->name, data->name)) && (!strcmp(temp->subject, data->subject))) {
            last->next = temp->next;
            del = temp;
            temp = temp->next;
            free(del);
            dele = 1;
            break;
        }
        temp = temp->next;
        last = last->next;
    }
    if (dele == 1) {
        printf("삭제되었습니다.\n");
    }
    else {
        printf("존재하지 않는 데이터입니다.\n");
    }
}

//파일에서 데이터 불러오기
void loadfile(Class* hp) {
    //파일 내용 연결리스트에 저장
    char names[50];
    char subjects[100];
    int size;
    float score;
    //파일 오픈
    FILE* fp;
    fp = fopen("info.dat", "a+");
    //파일 실행 실패
    if (fp == NULL) {
        printf("failed to open file\n");
        return;
    }
    //파일 실행 성공
    Class* temp;
    Class* last;
    temp = (Class*)malloc(sizeof(Class));
    fscanf(fp, "%s %s %d %f", names, subjects, &size, &score);
    //head뒤에 temp연결
    if (feof(fp) == 0) {
        temp->size = size;
        temp->score = score;
        strcpy(temp->name, names);
        strcpy(temp->subject, subjects);
        hp->next = temp;
        temp->next = NULL;
        last = temp;
    }
    else free(temp);
    //temp뒤에 temp생성
    while (1) {
        temp = (Class*)malloc(sizeof(Class));
        fscanf(fp, "%s %s %d %f", names, subjects, &size, &score);
        if (feof(fp) == 0) {
            temp->size = size;
            temp->score = score;
            strcpy(temp->name, names);
            strcpy(temp->subject, subjects);
            last->next = temp;
            temp->next = NULL;
            last = temp;
        }
        else {
            free(temp);
            break;
        }
    }
    fclose(fp);
}

//파일에 데이터 업데이트
void Exit(Class* hp)
{
    Class* temp = hp->next;
    FILE* fp = fopen("info.dat", "wt");
    if (temp == NULL)
        return;
    else
    {
        while (temp != NULL)
        {
            fputs(temp->name, fp); fputs(" ", fp);
            fputs(temp->subject, fp); fputs(" ", fp);
            fprintf(fp, "%d", temp->size); fputs(" ", fp);
            fprintf(fp, "%f", temp->score); fputs("\n", fp);
            temp = temp->next;
        }
    }
    fclose(fp);
    return;
}




