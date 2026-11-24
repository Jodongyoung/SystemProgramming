#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void push(struct node *top, int data) {
    struct node *newNode = (struct node *) malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = top->next;
    top->next = newNode;
}

int pop(struct node *top) {
    if (top->next == NULL) {
        return -1;
    }
    struct node *temp = top->next;
    int data = temp->data;
    top->next = temp->next;
    free(temp);
    return data;
}

int main() {
    // top을 더미 헤드 노드로 활용
    struct node top;
    top.next = NULL;

    int val;
    // 자연수(정수) 외 문자(예: x 등) 입력 시 입력 종료
    while (scanf("%d", &val) == 1) {
        push(&top, val);
    }

    printf("Print stack\n");
    while (top.next != NULL) {
        printf("%d\n", pop(&top));
    }

    return 0;
}
