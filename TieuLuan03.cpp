#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include "Queue.h"
#include "NhapXuat.h"

void initList(LIST &l);
void nhapVaoDanhSachTruyen(LIST &l);
NODE* timKiemT(LIST l, char maTruyen[]);
NODEMUON* timKiemKH(QUEUE q, char maKhachHang[]);
void themTruyen(QUEUE &q, LIST l, char maTruyen[]);
int xoaTruyen(QUEUE &q, char maTruyen[]);
int soLuongQuyenTruyen(QUEUE q);
bool suaTruyen(LIST &L, char maTruyen[]);
NODEMUON* timTheoTen(QUEUE q, char tenKhachHang[]);
QUEUE danhSachKHTheoDiaChi(QUEUE q, char diaChi[]);
void xuatDanhSachTruyen1KHDaMuon(QUEUE q, char maKhachHang[]);
void xuatTruyenTheoTheLoai(LIST l, char theLoai[]);
void xuatTruyenTheoNgayMuon(QUEUE q, DATE ngayMuon);
void danhSachTruyenMuonQuaHan(QUEUE q);

int main() {
	// QUEUE q;
	// TRUYEN x;
	// nhapVaoDanhSachTruyen(q);
	// //themTruyen(q);
	// //xoaTruyen(q, "13");
	// //suaTruyen(q, "13");
	// xuatDanhSachCacQuyenTruyen(q);
}


void initList(LIST &l) {
	l.pHead = l.pTail = NULL;
}

void nhapVaoDanhSachTruyen(LIST &l) {
	initList(l);
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
		NODE* p = new NODE;
		p->data = x;
		p->pNext = NULL;
		if(l.pHead == NULL) {
			l.pHead = l.pTail = p;
		}
		else {
			l.pTail->pNext = p;
			l.pTail = p;
		}
		i++;
	}
}



NODEMUON* timKiemKH(QUEUE q, char maKhachHang[]) {
	if(isEmpty(q))
		return NULL;
	for(NODEMUON* p = q.front;p != NULL; p = p->pNext) {
		if(strcmp(p->data.id, maKhachHang) == 0)
			return p;
	}
	return NULL;
}

NODE* timKiemT(LIST l, char maTruyen[]) {
	if(l.pHead == NULL)
		return NULL;
	for(NODE* p = l.pHead;p != NULL; p = p->pNext) {
		if(strcmp(p->data.id, maTruyen) == 0)
			return p;
	}
	return NULL;
}

void themTruyen(QUEUE &q, LIST l, char maTruyen[], char maKhachHang[]) {
	NODE* truyen = timKiemT(l, maTruyen);
	if(truyen == NULL)
		return;
	NODEMUON* khachHang = timKiemKH(q, maKhachHang);
	if(khachHang->kh.maKH == NULL) {
		printf("Khong tim thay khach hang.\n");
		printf("Tao them khach hang moi?\n");
		printf("1. Co\n");
		printf("2. Khong\n");
		int choice;
		scanf("%d", &choice);
		fflush(stdin);
		if(choice == 1) {
			KHACHHANG tmp;
			nhapInfoKhachHang(tmp);
			khachHang->kh = tmp;
		}
		else
			return;
	}
	NODEMUON tmp;
	tmp.data = truyen->data;
	tmp.kh = khachHang->kh;
	nhapNgayMuon(tmp.ngayMuon);
	enQueue(q, tmp);
}

int xoaTruyen(QUEUE &q, char maTruyen[]){
	NODEMUON *pDel = q.front;
	NODEMUON *pPre = NULL;
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

bool suaTruyen(LIST &l, char maTruyen[]) {
	NODE* p = timKiemT(l, maTruyen);
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

NODEMUON* timTheoTen(QUEUE q, char tenKhachHang[]) {
	if(isEmpty(q))
		return NULL;
	for(NODEMUON* p = q.front;p != NULL; p = p->pNext) {
		if(strcmp(p->kh.tenKH, tenKhachHang) == 0)
			return p;
	}
	return NULL;
}

QUEUE danhSachKHTheoDiaChi(QUEUE q, char diaChi[]) {
	QUEUE tmp;
	initQueue(tmp);
	if(isEmpty(q))
		return tmp;
	for(NODEMUON* p = q.front;p != NULL; p = p->pNext) {
		if(strcmp(p->kh.diaChi, diaChi) == 0)
			enQueue(tmp, *p);
	}
	return tmp;
}

void xuatDanhSachTruyen1KHDaMuon(QUEUE q, char maKhachHang[]) {
	NODEMUON* p = q.front;
	while(p != NULL) {
		if(strcmp(p->kh.maKH, maKhachHang) == 0) {
			xuatTruyen(p->data);
		}
		p = p->pNext;
	}
}

void xuatTruyenTheoTheLoai(LIST l, char theLoai[]) {
	if(l.pHead == NULL)
		printf("Danh sach khong ton tai.\n");

	for(NODE* p = l.pHead; p != NULL; p = p->pNext) {
		if(strcmp(p->data.theLoai, theLoai) == 0) {
			xuatTruyen(p->data);
		}
	}
}

void xuatTruyenTheoNgayMuon(QUEUE q, DATE ngayMuon) {
	if(isEmpty(q))
		return;
	for(NODEMUON* p = q.front;p != NULL; p = p->pNext) {
		if(p->ngayMuon.ngay == ngayMuon.ngay && p->ngayMuon.thang == ngayMuon.thang && p->ngayMuon.nam == ngayMuon.nam) {
			xuatTruyen(p->data);
		}
	}
}

void danhSachTruyenMuonQuaHan(QUEUE q, DATE ngayMuon) {
	if(isEmpty(q))
		return;
	for(NODEMUON* p = q.front;p != NULL; p = p->pNext) {
		if(p->ngayMuon.ngay >= ngayMuon.ngay && p->ngayMuon.thang >= ngayMuon.thang && p->ngayMuon.nam >= ngayMuon.nam) {
			xuatTruyen(p->data);
		}
	}
}