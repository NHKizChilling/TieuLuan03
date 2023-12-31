#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Queue.h"
//#pragma once

#ifndef NhapXuat_h
#define NhapXuat_h

typedef struct NodeT { // Node chỉ để chưa danh sách truyện
    TRUYEN data;
    NodeT* pNext;
}NODE;

typedef struct ListT { // Danh sách truyện
	NODE* pHead;
	NODE* pTail;
}LIST;



TRUYEN nhap1QuyenTruyen() {
	TRUYEN x;
	fflush(stdin);
	printf("Nhap ma truyen: ");gets(x.id);
	fflush(stdin);
	printf("Nhap ten quyen truyen: ");gets(x.name);
	printf("Nhap ten tac gia: ");gets(x.tacGia);
	printf("Nhap the loai truyen: ");gets(x.theLoai);
	printf("Nhap ten nha xuat ban: "); gets(x.nxb);
	printf("Nhap nam xuat ban cua quyen truyen: ");scanf("%d", &x.year);
	printf("Nhap so luong quyen truyen: ");scanf("%d", &x.soLuong);
	return x;
}

void xuatDanhSachCacQuyenTruyen(LIST l) {
	if(l.pHead == NULL)
		printf("Danh sach khong ton tai.\n");

	for(NODE* p = l.pHead; p != NULL; p = p->pNext) {
		printf("Ma truyen: %s\n", p->data.id);
		printf("Ten truyen: %s\n", p->data.name);
		printf("Tac gia: %s\n", p->data.tacGia);
		printf("The loai: %s\n", p->data.theLoai);
		printf("Nha xuat ban: %s\n", p->data.nxb);
		printf("Nam xuat ban: %d\n", p->data.year);
		printf("So luong: %d\n", p->data.soLuong);
		printf("\n");
	}
}

KHACHHANG nhapInfoKhachHang() {
	KHACHHANG tmp;
	fflush(stdin);
	printf("Nhap ma khach hang: ");gets(tmp.maKH);
	printf("Nhap ten khach hang: ");gets(tmp.tenKH);
	printf("Nhap dia chi khach hang: ");gets(tmp.diaChi);
	printf("Nhap so dien thoai khach hang: ");gets(tmp.sdt);
	return tmp;
}

void nhapNgayMuon(DATE &tmp) {
	printf("Nhap ngay muon: ");scanf("%d", &tmp.ngay);
	printf("Nhap thang muon: ");scanf("%d", &tmp.thang);
	printf("Nhap nam muon: ");scanf("%d", &tmp.nam);
}


void xuatKH(KHACHHANG tmp) {
    printf("Ma khach hang: %s\n", tmp.maKH);
    printf("Ten khach hang: %s\n", tmp.tenKH);
    printf("Dia chi khach hang: %s\n", tmp.diaChi);
    printf("So dien thoai khach hang: %s\n", tmp.sdt);
}

void xuatTruyen(TRUYEN tmp) {
    printf("Ma truyen: %s\n", tmp.id);
    printf("Ten truyen: %s\n", tmp.name);
    printf("Tac gia: %s\n", tmp.tacGia);
    printf("The loai: %s\n", tmp.theLoai);
    printf("Nha xuat ban: %s\n", tmp.nxb);
    printf("Nam xuat ban: %d\n", tmp.year);
    printf("So luong: %d\n", tmp.soLuong);
    printf("\n");
}

void xuatInfo(NODEMUON* p) {
    xuatKH(p->kh);
    xuatTruyen(p->data);
    printf("\n");
}

#endif
