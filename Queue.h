#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef Queue_h
#define Queue_h

typedef struct Day {
	int ngay;
	int thang;
	int nam;
}DATE;

typedef struct KhachHang {
	char maKH[10];
	char tenKH[50];
	char diaChi[100];
	char sdt[15];
}KHACHHANG;

typedef struct truyen {
    char tacGia[100];
    char theLoai[20];
    char nxb[100];
    char id[10];
    char name[50];
    int year;
    int soLuong;
}TRUYEN;

typedef struct NodeMuon { // NODE chưa thông tin truyện và khách hàng để thêm vào queue
	TRUYEN data;
	KhachHang kh;
	DATE ngayMuon;
	NodeMuon* pNext;
}NODEMUON;

typedef struct Queue {
	int NumItems;
	NODEMUON* front;
	NODEMUON* rear;	
}QUEUE;

#endif

//Khoi tao Queue
bool initQueue(QUEUE &q) {
	q.NumItems = 0;
	q.front = q.rear = NULL;
	return true;
}

// Ki?m tra hàng ð?i r?ng
bool isEmpty(QUEUE q) {
	
    return (q.NumItems == 0);
}

// Thêm vào cu?i hàng ð?i
bool enQueue(QUEUE &q, NODEMUON x) {
    NODEMUON* p = new NODEMUON;
    if(p == NULL) {
        return false;
    }
    p->data = x.data;
	p->kh = x.kh;
	p->ngayMuon = x.ngayMuon;
    p->pNext = NULL;
    if(isEmpty(q)) {
        q.front = q.rear = p;
    }
    else{
	    q.rear->pNext = p;
	    q.rear = p;
	}
	q.NumItems++;
    return true;
}


// L?y ra ð?u hàng ð?i
bool deQueue(QUEUE &q, NODEMUON &itemout) {
    if (isEmpty(q)) {
        return false;
    }
    NODEMUON* p = q.front;
    q.front = q.front->pNext;
    itemout.data = p->data;
    q.NumItems--;
    delete p;
    if(q.NumItems==0)
		initQueue(q);
    return true;
}

// kích thý?c hàng ð?i
int size(QUEUE q) {
    int count = 0;
    NODEMUON* p = q.front;
    while (p != NULL) {
        count++;
        p = p->pNext;
    }
    return count;
}

