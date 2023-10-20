#include <stdio.h>
#include <string.h> 
#include <stdlib.h>

typedef struct truyen {
    char tacGia[100];
    char theLoai[20];
    char nxb[100];
    char id[10];
    char name[50];
    int year;
    int soLuong;
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
void themTruyen(QUEUE &q);
int xoaTruyen(QUEUE &q, char maTruyen[]);
int soLuongQuyenTruyen(QUEUE q);
bool suaTruyen(QUEUE q, char maTruyen[]);
void sapXepTheoSLGiam(QUEUE q);

int main() {
	QUEUE q;
	TRUYEN x;
	nhapVaoDanhSachTruyen(q);
	//themTruyen(q);
	//xoaTruyen(q, "13");
	//suaTruyen(q, "13");
	sapXepTheoSLGiam(q);
	xuatDanhSachCacQuyenTruyen(q);
}

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


// L?y ra ð?u hàng ð?i
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

// kích thý?c hàng ð?i
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
	printf("Nhap so luong quyen truyen: ");scanf("%d", &x.soLuong);
	fflush(stdin);
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
		do {
			x = nhap1QuyenTruyen();
			if(timKiem(q, x.id) != NULL) {
					printf("Loi. Ma quyen truyen khong duoc trung. Nhap lai!\n");
			}
		}while(timKiem(q, x.id) != NULL);
		if(enQueue(q, x))
			printf("Nhap thanh cong.\n");
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
		printf("So luong: %d\n", p->data.soLuong);
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

void themTruyen(QUEUE &q) {
	TRUYEN x;
	do {
		x = nhap1QuyenTruyen();
		if(timKiem(q, x.id) != NULL)
			printf("Loi. Ma quyen truyen khong duoc trung. Nhap lai!\n");
	}while(timKiem(q, x.id) != NULL);
	if(enQueue(q, x)){
		printf("Them thanh cong.\n");
	}
	else
		printf("Loi.\n");
}

int xoaTruyen(QUEUE &q, char maTruyen[]){
	NODE *pDel = q.front;
	NODE *pPre = NULL;
	if(q.front == NULL){
		printf("Mang khong co sinh vien nao.\n");
		exit(0);
	}
	while (pDel != NULL){
		if(stricmp(pDel->data.id, maTruyen) == 0){
			if(pDel == q.front){
				q.front = q.front->pNext;
				pDel->pNext = NULL;
				q.NumItems--;
				delete pDel;
				return 1;
			}
			else if(pDel->pNext == NULL){
				q.rear = pPre;
				pPre->pNext = NULL;
				q.NumItems--;
				delete pDel;
				return 1;
			}
			else{
				pPre->pNext = pDel->pNext;
				pDel->pNext = NULL;
				q.NumItems--;
				delete pDel;
				return 1;
			}
		}
		pPre = pDel;
		pDel = pDel->pNext;
	}
	
	return 0;
}

int soLuongQuyenTruyen(QUEUE q) {
	
	return q.NumItems;
}

bool suaTruyen(QUEUE q, char maTruyen[]) {
	NODE* p = timKiem(q, maTruyen);
	if(p == NULL)
		return false;
	printf("Nhap ten quyen truyen: ");gets(p->data.name);
	printf("Nhap ten tac gia: ");gets(p->data.tacGia);
	printf("Nhap the loai truyen: ");gets(p->data.theLoai);
	printf("Nhap ten nha xuat ban: "); gets(p->data.nxb);
	printf("Nhap nam xuat ban cua quyen truyen: ");scanf("%d", &p->data.year);
	printf("Nhap so luong quyen truyen: ");scanf("%d", &p->data.soLuong);
	return true;
}

void sapXepTheoSLGiam(QUEUE q) {
	for(NODE* p = q.front;p != NULL; p = p->pNext)
		for(NODE* k = p->pNext;k != NULL; k = k->pNext) {
			if(k > p){
				TRUYEN tmp = p->data;p->data = k->data;k->data = tmp;
			}
		}
}
