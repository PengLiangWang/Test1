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


int main(int argc, char *argv[])
{
    
    Node *pList=NULL;
    int length=0;

    elemType posElem;

    initList(&pList);
    printList(pList);

    printf("\n**********************\n");

    pList = createList(pList);
    printList(pList);

    return 0;
}