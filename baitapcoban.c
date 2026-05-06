#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Ngay
{
    int ngay, thang, nam;
};

struct SinhVien
{
    char maSV[20];
    char hoTen[50];
    int gioiTinh;
    struct Ngay ngaySinh;
    char diaChi[100];
    char lop[20];
    char khoa[20];
};

struct Node
{
    struct SinhVien data;
    struct Node *link;
};

struct List
{
    struct Node *first;
    struct Node *last;
};

void xoaXuongDong(char s[])
{
    s[strcspn(s, "\n")] = '\0';
}

int nhapSoNguyen()
{
    char temp[100];
    fgets(temp, sizeof(temp), stdin);
    return atoi(temp);
}

void init(struct List *l)
{
    l->first = NULL;
    l->last = NULL;
}

struct Node* createNode(struct SinhVien sv)
{
    struct Node *p = (struct Node*)malloc(sizeof(struct Node));

    if (p == NULL)
    {
        printf("Khong du bo nho!\n");
        exit(1);
    }

    p->data = sv;
    p->link = NULL;

    return p;
}

void nhapSV(struct SinhVien *sv)
{
    printf("Nhap ma sinh vien: ");
    fgets(sv->maSV, sizeof(sv->maSV), stdin);
    xoaXuongDong(sv->maSV);

    printf("Nhap ho ten: ");
    fgets(sv->hoTen, sizeof(sv->hoTen), stdin);
    xoaXuongDong(sv->hoTen);

    printf("Nhap gioi tinh (1-Nam, 0-Nu): ");
    sv->gioiTinh = nhapSoNguyen();

    printf("Nhap ngay sinh: ");
    sv->ngaySinh.ngay = nhapSoNguyen();

    printf("Nhap thang sinh: ");
    sv->ngaySinh.thang = nhapSoNguyen();

    printf("Nhap nam sinh: ");
    sv->ngaySinh.nam = nhapSoNguyen();

    printf("Nhap dia chi: ");
    fgets(sv->diaChi, sizeof(sv->diaChi), stdin);
    xoaXuongDong(sv->diaChi);

    printf("Nhap lop: ");
    fgets(sv->lop, sizeof(sv->lop), stdin);
    xoaXuongDong(sv->lop);

    printf("Nhap khoa: ");
    fgets(sv->khoa, sizeof(sv->khoa), stdin);
    xoaXuongDong(sv->khoa);
}

void xuatSV(struct SinhVien sv)
{
    printf("%-10s %-25s ", sv.maSV, sv.hoTen);

    if (sv.gioiTinh == 1)
        printf("%-5s ", "Nam");
    else
        printf("%-5s ", "Nu");

    printf("%02d/%02d/%04d   ",
           sv.ngaySinh.ngay,
           sv.ngaySinh.thang,
           sv.ngaySinh.nam);

    printf("%-20s %-10s %-10s\n",
           sv.diaChi,
           sv.lop,
           sv.khoa);
}

void xuatDS(struct List l)
{
    struct Node *p = l.first;

    if (p == NULL)
    {
        printf("Danh sach rong!\n");
        return;
    }

    printf("%-10s %-25s %-5s %-12s %-20s %-10s %-10s\n",
           "MaSV", "Ho ten", "GT", "Ngay sinh", "Dia chi", "Lop", "Khoa");

    while (p != NULL)
    {
        xuatSV(p->data);
        p = p->link;
    }
}

int cungNgaySinh(struct Ngay a, struct Ngay b)
{
    return a.ngay == b.ngay &&
           a.thang == b.thang &&
           a.nam == b.nam;
}

void themSVTangTheoMa(struct List *l, struct SinhVien sv)
{
    struct Node *p = createNode(sv);

    if (l->first == NULL)
    {
        l->first = l->last = p;
        return;
    }

    if (strcmp(sv.maSV, l->first->data.maSV) < 0)
    {
        p->link = l->first;
        l->first = p;
        return;
    }

    struct Node *q = l->first;

    while (q->link != NULL &&
           strcmp(q->link->data.maSV, sv.maSV) < 0)
    {
        q = q->link;
    }

    p->link = q->link;
    q->link = p;

    if (p->link == NULL)
    {
        l->last = p;
    }
}

void inSVCungNgaySinh(struct List l, struct Ngay ns)
{
    struct Node *p = l.first;
    int timThay = 0;

    while (p != NULL)
    {
        if (cungNgaySinh(p->data.ngaySinh, ns))
        {
            xuatSV(p->data);
            timThay = 1;
        }

        p = p->link;
    }

    if (timThay == 0)
    {
        printf("Khong tim thay sinh vien cung ngay sinh\n");
    }
}

void xoaSVCungNgaySinh(struct List *l, struct Ngay ns)
{
    struct Node *p;
    struct Node *q;

    while (l->first != NULL &&
           cungNgaySinh(l->first->data.ngaySinh, ns))
    {
        p = l->first;
        l->first = l->first->link;
        free(p);
    }

    if (l->first == NULL)
    {
        l->last = NULL;
        return;
    }

    q = l->first;

    while (q->link != NULL)
    {
        if (cungNgaySinh(q->link->data.ngaySinh, ns))
        {
            p = q->link;
            q->link = p->link;

            if (p == l->last)
            {
                l->last = q;
            }

            free(p);
        }
        else
        {
            q = q->link;
        }
    }
}

void giaiPhongDS(struct List *l)
{
    struct Node *p;

    while (l->first != NULL)
    {
        p = l->first;
        l->first = l->first->link;
        free(p);
    }

    l->last = NULL;
}

int main()
{
    struct List l;
    struct SinhVien sv;
    struct SinhVien svMoi;
    struct Ngay ns;

    int n;
    int i;

    init(&l);

    printf("Nhap so luong sinh vien: ");
    n = nhapSoNguyen();

    for (i = 0; i < n; i++)
    {
        printf("\nNhap sinh vien thu %d\n", i + 1);
        nhapSV(&sv);
        themSVTangTheoMa(&l, sv);
    }

    printf("\n===== DANH SACH SINH VIEN DA SAP XEP THEO MA =====\n");
    xuatDS(l);

    printf("\n===== THEM SINH VIEN MOI =====\n");
    nhapSV(&svMoi);
    themSVTangTheoMa(&l, svMoi);

    printf("\n===== DANH SACH SAU KHI THEM =====\n");
    xuatDS(l);

    printf("\nNhap ngay sinh can tim:\n");

    printf("Ngay: ");
    ns.ngay = nhapSoNguyen();

    printf("Thang: ");
    ns.thang = nhapSoNguyen();

    printf("Nam: ");
    ns.nam = nhapSoNguyen();

    printf("\n===== CAC SINH VIEN CUNG NGAY SINH =====\n");
    inSVCungNgaySinh(l, ns);

    printf("\n===== XOA SINH VIEN CUNG NGAY SINH =====\n");
    xoaSVCungNgaySinh(&l, ns);

    printf("\n===== DANH SACH SAU KHI XOA =====\n");
    xuatDS(l);

    giaiPhongDS(&l);

    return 0;
}