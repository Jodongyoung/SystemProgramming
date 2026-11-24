#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void addq(struct node *head, struct node *tail, int data) {
    struct node *newNode = (struct node *) malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = NULL;

    if (head->next == NULL) {
        head->next = newNode;
    } else {
        tail->next->next = newNode;
    }
    tail->next = newNode;
}

int delete(struct node *head, struct node *tail) {
    if (head->next == NULL) {
        return -1;
    }
    struct node *temp = head->next;
    int data = temp->data;
    head->next = temp->next;
    if (head->next == NULL) {
        tail->next = NULL;
    }
    free(temp);
    return data;
}

int main() {
    // 더미 노드 head, tail 구성
    struct node head, tail;
    head.next = NULL;
    tail.next = NULL;

    int val;
    // 자연수 외의 문자(예: x) 입력 시 루프 종료
    while (scanf("%d", &val) == 1) {
        addq(&head, &tail, val);
    }

    printf("Print queue\n");
    while (head.next != NULL) {
        printf("%d\n", delete(&head, &tail));
    }

    return 0;
}
