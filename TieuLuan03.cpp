#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include "NhapXuat.h"

void initList(LIST &l);
void nhapVaoDanhSachTruyen(LIST &l);
NODE* timKiemT(LIST l, char maTruyen[]);
NODEMUON* timKiemKH(QUEUE q, char maKhachHang[]);
void themTruyen(QUEUE &q, LIST l, char maTruyen[], char maKhachHang[]);
int xoaTruyen(QUEUE &q, char maTruyen[]);
int soLuongQuyenTruyen(QUEUE q);
bool suaTruyen(LIST &L, char maTruyen[]);
NODEMUON* timTheoTen(QUEUE q, char tenKhachHang[]);
QUEUE danhSachKHTheoDiaChi(QUEUE q, char diaChi[]);
void xuatDanhSachTruyen1KHDaMuon(QUEUE q, char maKhachHang[]);
void xuatTruyenTheoTheLoai(LIST l, char theLoai[]);
void xuatTruyenTheoNgayMuon(QUEUE q, DATE ngayMuon);
void danhSachTruyenMuonQuaHan(QUEUE q, DATE ngayMuon);
void readBooksFromFile(const char* filePath, LIST& bookList);
void writeBooksToFile(const char* filePath, LIST bookList);

int main() {
	LIST danhSachTruyen;
	QUEUE danhSachMuon;
	initList(danhSachTruyen);
	initQueue(danhSachMuon);
	int choice;
	char maTruyen[20];
	char theLoai[20];
	char maKhachHang[20];
	char tenKhachHang[50];
	char diaChi[100];
	DATE ngayMuon;
	do {
		printf("========== MENU ==========\n");
		printf("1. Nhap danh sach truyen\n");
		printf("2. Them truyen vao danh sach muon\n");
		printf("3. Xoa truyen khoi danh sach muon\n");
		printf("4. Hien thi so luong quyen truyen trong danh sach muon\n");
		printf("5. Sua thong tin truyen\n");
		printf("6. Tim kiem khach hang theo ten\n");
		printf("7. Hien thi danh sach khach hang theo dia chi\n");
		printf("8. Hien thi danh sach truyen da muon cua mot khach hang\n");
		printf("9. Hien thi danh sach truyen theo the loai\n");
		printf("10. Hien thi danh sach truyen theo ngay muon\n");
		printf("11. Hien thi danh sach truyen muon qua han\n");
		printf("12. Doc danh sach truyen tu file\n");
		printf("13. Ghi danh sach truyen vao file\n"); // Modified: Changed the menu option
		printf("0. Thoat chuong trinh\n");
		printf("==========================\n");
		printf("Nhap lua chon cua ban: ");
		scanf("%d", &choice);
		fflush(stdin);
		switch(choice) {
			case 1:
				nhapVaoDanhSachTruyen(danhSachTruyen);
				break;
			case 2:
				printf("Nhap ma truyen: ");
				gets(maTruyen);
				fflush(stdin);
				printf("Nhap ma khach hang: ");
				gets(maKhachHang);
				fflush(stdin);
				themTruyen(danhSachMuon, danhSachTruyen, maTruyen, maKhachHang);
				break;
			case 3:
				printf("Nhap ma truyen: ");
				gets(maTruyen);
				fflush(stdin);
				if(xoaTruyen(danhSachMuon, maTruyen))
					printf("Xoa thanh cong.\n");
				else
					printf("Khong tim thay truyen.\n");
				break;
			case 4:
				printf("So luong quyen truyen trong danh sach muon: %d\n", soLuongQuyenTruyen(danhSachMuon));
				break;
			case 5:
				printf("Nhap ma truyen: ");
				gets(maTruyen);
				fflush(stdin);
				if(suaTruyen(danhSachTruyen, maTruyen))
					printf("Sua thong tin truyen thanh cong.\n");
				else
					printf("Khong tim thay truyen.\n");
				break;
			case 6: {
				printf("Nhap ten khach hang: ");
				gets(tenKhachHang);
				fflush(stdin);
				NODEMUON* khachHang = timTheoTen(danhSachMuon, tenKhachHang);
				if(khachHang != NULL) {
					printf("Thong tin khach hang:\n");
					xuatKH(khachHang->kh);
				}
				else {
					printf("Khong tim thay khach hang.\n");
				}
				break;
			}
			case 7: {
				printf("Nhap dia chi: ");
				scanf("%s", diaChi);
				fflush(stdin);
				QUEUE dsKHTheoDiaChi = danhSachKHTheoDiaChi(danhSachMuon, diaChi);
				if(isEmpty(dsKHTheoDiaChi)) {
					printf("Khong tim thay khach hang nao o dia chi nay.\n");
				}
				else {
					printf("Danh sach khach hang theo dia chi %s:\n", diaChi);
					for(NODEMUON* p = dsKHTheoDiaChi.front; p != NULL; p = p->pNext) {
						xuatKH(p->kh);
					}
				}
				break;
			}
			case 8:
				printf("Nhap ma khach hang: ");
				gets(maKhachHang);
				fflush(stdin);
				xuatDanhSachTruyen1KHDaMuon(danhSachMuon, maKhachHang);
				break;
			case 9:
				printf("Nhap the loai: ");
				gets(theLoai);
				fflush(stdin);
				xuatTruyenTheoTheLoai(danhSachTruyen, theLoai);
				break;
			case 10:
				printf("Nhap ngay muon (dd/mm/yyyy): ");
				scanf("%d/%d/%d", &ngayMuon.ngay, &ngayMuon.thang, &ngayMuon.nam);
				fflush(stdin);
				xuatTruyenTheoNgayMuon(danhSachMuon, ngayMuon);
				break;
			case 11:
				danhSachTruyenMuonQuaHan(danhSachMuon, ngayMuon);
				break;
			case 12: 
				readBooksFromFile("T:/books.txt", danhSachTruyen);
				break;
			case 13:
				printf("Nhap duong dan file: ");
				char filePath[100];
				scanf("%s", filePath);
				fflush(stdin);
				writeBooksToFile(filePath, danhSachTruyen);
				break;
			case 0:
				printf("Thoat chuong trinh.\n");
				break;
			default:
				printf("Lua chon khong hop le. Vui long chon lai.\n");
				break;
		}
	} while(choice != 0);
	return 0;
}

void initList(LIST &l) {
	l.pHead = l.pTail = NULL;
}

void nhapVaoDanhSachTruyen(LIST &l) {
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
		printf("Them thanh cong quyen truyen co ma %s vao cua hang.\n", x.id);
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
		printf("Khong co phieu muon trong danh sach.\n");
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
		if(stricmp(p->kh.tenKH, tenKhachHang) == 0)
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
		if(stricmp(p->kh.diaChi, diaChi) == 0)
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
		if(stricmp(p->data.theLoai, theLoai) == 0) {
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

void readBooksFromFile(const char* filePath, LIST& bookList) {
	FILE* file = fopen(filePath, "r");
	if (file == NULL) {
		printf("Cannot open file.\n");
		return;
	}
	initList(bookList);
	char line[256];
	while (fgets(line, sizeof(line), file)) {
		TRUYEN book;
		char* token = strtok(line, "|");
		strcpy(book.id, token);
		token = strtok(NULL, "|");
		strcpy(book.name, token);
		token = strtok(NULL, "|");
		strcpy(book.tacGia, token);
		token = strtok(NULL, "|");
		strcpy(book.theLoai, token);
		token = strtok(NULL, "|");
		strcpy(book.nxb, token);
		token = strtok(NULL, "|");
		book.year = atoi(token);
		token = strtok(NULL, "|");
		book.soLuong = atoi(token);

		NODE* newNode = (NODE*)malloc(sizeof(NODE));
		newNode->data = book;
		newNode->pNext = NULL;

		if (bookList.pHead == NULL) {
			bookList.pHead = newNode;
			bookList.pTail = newNode;
		} else {
			bookList.pTail->pNext = newNode;
			bookList.pTail = newNode;
		}
		printf("Them thanh cong quyen truyen co ma %s vao cua hang.\n", book.id);
	}

	fclose(file);
}

void writeBooksToFile(const char* filePath, LIST bookList) {
	FILE* file = fopen(filePath, "w");
	if (file == NULL) {
		printf("Error opening file.\n");
		return;
	}

	NODE* currentNode = bookList.pHead;
	while (currentNode != NULL) {
		TRUYEN book = currentNode->data;
		fprintf(file, "%s|%s|%s|%s|%s|%d|%d\n", book.id, book.name, book.tacGia, book.theLoai, book.nxb, book.year, book.soLuong);
		printf("Ghi thanh cong quyen truyen co ma %s vao file.\n", book.id);
		currentNode = currentNode->pNext;
	}

	fclose(file);
}