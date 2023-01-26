#ifndef QUEUE_H_
#define QUEUE_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FULL 100 /*Gia tri nay thuoc vao gioi han cua QUEUE ma ban muon cai dat*/
#ifndef STRUCT_DT
#define STRUCT_DT
typedef struct DT
{
    int point;
} DataType;
typedef DataType ElementType;
// const ElementType NotFound = {"Not Found", "Not Found", "Not Found"};
#endif
#ifndef STRUCT_LKD
#define STRUCT_LKD
typedef struct LKD
{
    ElementType data;
    struct LKD *next;
} LinkList;
#endif
typedef struct QUEUE
{
    LinkList *Front;
    LinkList *Rear;
} QUEUE;
QUEUE *MakeNullQueue(void);         /*Khoi tao mot QUEUE rong*/
int sizeQ(QUEUE *);                 /*Tra ve so phan tu trong QUEUE*/
int isEmptyQ(QUEUE *);              /*Kiem tra QUEUE co rong khong*/
int isFullQ(QUEUE *);               /*Kiem tra QUEUE co day khong*/
LinkList *front(QUEUE *);           /*Tra ve con tro cua phan tu FRONT*/
void EnQueue(QUEUE *, ElementType); /*Them phan tu vao phia sau QUEUE*/
ElementType DeQueue(QUEUE *);       /*Xoa phan tu o phia truoc QUEUE va tra ve data cua phan tu do*/
void PrintQ(QUEUE *);               /*In ra danh sach cua cac phan tu trong QUEUE*/
#endif