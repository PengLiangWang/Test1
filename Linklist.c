/* http://www.cnblogs.com/renyuan/archive/2013/05/21/3091506.html */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int elemType;

typedef struct Node{
    elemType element;
    struct Node *next;
}Node;


/* 1.初始化线性表，即置单链表的表头指针为空 */
static void initList(Node **pNode)
{
    *pNode = NULL;
    printf("initList函数执行, 初始化成功\n");
}

/* 2.创建线性表，此函数输入负数终止读取数据*/
static Node *createList(Node *pHead)
{
    Node *p1;
    Node *p2;

    printf("创建链表,请输入整数值(<0退出)\n");
    p1=p2=(Node *)malloc(sizeof(Node));  //申请新节点
    if(p1 == NULL || p2 == NULL)
    {
        printf("内存分配失败\n");
        exit(0);
    }
    memset(p1, 0x00, sizeof(Node));
    scanf("%d", &p1->element);

    p1->next = NULL;   //(head)节点指向为空
    while(p1->element > 0) 
    {
        if(pHead == NULL)    //空表, 接入表头
        {
             pHead = p1;    //链表头指向 p1 的位置
        }
        else
        {
            p2->next = p1;
        }
        p2 = p1;   //将p2指向p1的位置，而p1去做其他事情
        p1 = (Node *)malloc(sizeof(Node));
        if(p1 == NULL || p2 == NULL)
        {
             printf("内存分配失败\n");
             exit(0);
        }
        memset(p1, 0x00, sizeof(Node));
        scanf("%d", &p1->element);
        p1->next = NULL;   //(head)节点指向为空
    }
    printf("链表创建成功\n");
    return pHead;
}

/*打印列表*/
static void printList(Node *pHead)
{
     if(NULL == pHead)
     {
         printf("PrintList执行成功, 链表为空\n");
     }
     else
     {
         printf("链表内容:\n");
         while(NULL != pHead)
         {
             if(NULL != pHead->next)
                 printf("%d->", pHead->element);
             else
                 printf("%d", pHead->element);
             pHead = pHead->next;
         }
         printf("\n");
     }

}

static void delete_linkList(Node *pHead)
{
    Node *p = pHead->next;
    if(p == NULL)
        return;
    pHead->next = p->next;  //相当于pHead->next 指向 pHead->next->next
    free(p);
    p=NULL;
    return;
}


static void clear_linkList(Node *pHead)
{
    while(pHead->next)
        delete_linkList(pHead);
    return;
}

static void display_linkList(Node *pHead)
{
    clear_linkList(pHead);
    free(pHead);    //先清空链表,再释放头结点
    pHead=NULL;
    return;
}

/*打印链表的长度*/
static int sizeList(Node *pHead)
{
    int size=0;

    while(NULL != pHead)
    {
        size ++;
        pHead = pHead->next;
    }
    printf("sizeList函数执行, 链表长度: %d\n", size);
    return 0;
}

static isEmptyList(Node *pHead)
{
    if(pHead == NULL)
    {
        printf("链表为空\n");
        return 1;
    }
    printf("链表非空\n");
    return 0;
}

int main(int argc, char *argv[])
{
    
    Node *pList=NULL;
    int length=0;

    elemType posElem;

    printf("\n********初始化链表**********\n");
    initList(&pList);
    printList(pList);

    printf("\n********创建链表**********\n");

    pList = createList(pList);
    printList(pList);
   
    isEmptyList(pList);
    sizeList(pList);

    printf("\n*********清空链表*********\n");
    display_linkList(pList);
    pList=NULL;
    printList(pList);

    


    return 0;
}
