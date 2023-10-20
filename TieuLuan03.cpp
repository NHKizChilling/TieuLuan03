#include <stdio.h>
#include <conio.h> 
#include <stdlib.h>

typedef struct truyen {
    char tacGia[100];
    char theLoai[20];
    char nxb[100];
    char id[10];
    char name[50];
    int year;
}TRUYEN;

typedef struct QNode {
    TRUYEN data;
    QNode* pNext;
}NODE;

typedef struct Queue {
	int NumItems;
    NODE* front;
    NODE* rear;
}QUEUE;

bool initQueue(QUEUE &q);
bool isEmpty(QUEUE q);
bool enQueue(QUEUE &q, TRUYEN x);
bool deQueue(QUEUE &q, TRUYEN &itemout);
int size(QUEUE q);
TRUYEN nhap1QuyenTruyen();
void nhapVaoDanhSachTruyen(QUEUE &q);
void xuatDanhSachCacQuyenTruyen(QUEUE q);
NODE* timKiem(QUEUE q, char maTruyen[]);

int main() {
	QUEUE q;
	TRUYEN x;
	nhapVaoDanhSachTruyen(q);
	xuatDanhSachCacQuyenTruyen(q);
}

//Khoi tao Queue
bool initQueue(QUEUE &q) {
	q.NumItems = 0;
	q.front = q.rear = NULL;
	return true;
}

// Ki?m tra hàng đ?i r?ng
bool isEmpty(QUEUE q) {
	
    return (q.NumItems == 0);
}

// Thêm vào cu?i hàng đ?i
bool enQueue(QUEUE &q, TRUYEN x) {
    NODE* p = new NODE;
    if(p == NULL) {
        return false;
    }
    p->data = x;
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


// L?y ra đ?u hàng đ?i
bool deQueue(QUEUE &q, TRUYEN &itemout) {
    if (isEmpty(q)) {
        return false;
    }
    NODE* p = q.front;
    q.front = q.front->pNext;
    itemout = p->data;
    q.NumItems--;
    delete p;
    if(q.NumItems==0)
		initQueue(q);
    return true;
}

// kích thư?c hàng đ?i
int size(QUEUE q) {
    int count = 0;
    NODE* p = q.front;
    while (p != NULL) {
        count++;
        p = p->pNext;
    }
    return count;
}

TRUYEN nhap1QuyenTruyen() {
	TRUYEN x;
	fflush(stdin);
	printf("Nhap ma truyen: ");gets(x.id);
	printf("Nhap ten quyen truyen: ");gets(x.name);
	printf("Nhap ten tac gia: ");gets(x.tacGia);
	printf("Nhap the loai truyen: ");gets(x.theLoai);
	printf("Nhap ten nha xuat ban: "); gets(x.nxb);
	printf("Nhap nam xuat ban cua quyen truyen: ");scanf("%d", &x.year);
	return x;
}

void nhapVaoDanhSachTruyen(QUEUE &q) {
	initQueue(q);
	TRUYEN x;
	int n;
	do {
		printf("Nhap so luong quyen truyen: ");
		scanf("%d", &n);
		if(n <= 0)
			printf("So luong da nhap khong hop le. Vui long nhap lai!\n");
	}while(n <= 0);
	int i = 0;
	while(i < n) {
		x = nhap1QuyenTruyen();
		if(enQueue(q, x)){
			if(timKiem(q, x.id) == NULL)
				printf("Them thanh cong.\n");
			else {
				do {
					printf("Loi. Ma quyen truyen khong duoc trung. Nhap lai!\n");
					x = nhap1QuyenTruyen();
				}while(timKiem(q, x.id) != NULL);
				
			}
		}
		else
			printf("Loi. Khong the tao noi luu tru truyen\n");
		i++;
	}
}

void xuatDanhSachCacQuyenTruyen(QUEUE q) {
	NODE* p = q.front;
	if(isEmpty(q))
		printf("Danh sach khong ton tai.\n");
	while(p != NULL) {
		printf("Ma quyen truyen: %s\n", p->data.id);
		printf("Ten quyen truyen: %s\n", p->data.name);
		printf("Ten tac gia cua truyen: %s\n", p->data.tacGia);
		printf("The loai truyen: %s\n", p->data.theLoai);
		printf("Nha xuat ban: %s\n", p->data.nxb);
		printf("Nam xuat ban: %d\n", p->data.year);
		p = p->pNext;
	}
}

NODE* timKiem(QUEUE q, char maTruyen[]) {
	if(isEmpty(q))
		return NULL;
	for(NODE* p = q.front;p != NULL; p = p->pNext) {
		if(strcmp(p->data.id, maTruyen) == 0)
			return p;
	}
	
	return NULL;
}
