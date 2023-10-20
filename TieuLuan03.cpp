#include <stdio.h>
#include <queue>


typedef struct Sach {
    char tacGia[100];
    char theLoai[20];
    char nxb[100];
    char id[10];
    char name[50];
    int year;
};

typedef struct QNode {
    Sach data;
    QNode* next;
};

typedef struct Queue {
    QNode* front;
    QNode* rear;
};

QNode* newNode(Sach x) {
    QNode* p = new QNode;
    p->data = x;
    p->next = NULL;
    return p;
}

void enQueue(Queue* q, Sach x) {
    QNode* p = newNode(x);
    if (q->front == NULL) {
        q->front = q->rear = p;
        return;
    }
    q->rear->next = p;
    q->rear = p;
}

void deQueue(Queue* q) {
    if (q->front == NULL) {
        return;
    }
    QNode* p = q->front;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    delete p;
}

int size(Queue* q) {
    int count = 0;
    QNode* p = q->front;
    while (p != NULL) {
        count++;
        p = p->next;
    }
    return count;
}

bool isEmpty(Queue* q) {
    return q->front == NULL;
}



