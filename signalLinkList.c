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

/*判断链表是否为空*/
static  int isEmptyList(Node *pHead)
{
    if(pHead == NULL)
    {
        printf("链表为空\n");
        return 1;
    }
    printf("链表非空\n");
    return 0;
}

/*获取链表某个位置的值*/
static elemType getelement(Node *pHead, int pos)
{
    int i=0;

    if(pos < 1)
    {
        printf("pos值非法.\n");
        return 0;
    }
    if(NULL == pHead)
    {
        printf("链表为空.\n");
        return 0;
    }
    while(NULL != pHead)
    {
        ++i;
        if(i == pos)
        {
            break;
        }
        pHead = pHead->next;
    }
    if(i < pos)
    {
        printf("pos值超过链表的最大长度.\n");
        return 0;
    }
    return pHead->element;
}

/*从单链表中查找具有给定值x的第一个元素，若查找成功则返回该结点data域的存储地址，否则返回NULL*/
elemType *getElemAddr(Node *pHead, elemType x)
{

    elemType icount=1; 
    if(NULL == pHead)
    {
        printf("链表为空\n");
        return NULL;
    }
    if(x < 0)
    {
        printf("x值不合法\n");
    }

    while(pHead->element != x && NULL != pHead->next)
    {
        ++ icount ;
        pHead=pHead->next;
    }
    if(pHead->element != x && NULL != pHead)
    {
        printf("链表中不存在 %d\n", x);
        return NULL;
    }
    if(pHead->element == x)
    {
        printf("getElement函数执行, 元素 %d 的地址为 0x%x, 在链表中的位置: %d\n", x, &(pHead->element), icount);
    }

    return &(pHead->element);
}


/*把单链表中第pos个结点的值修改为x的值，若修改成功返回１，否则返回０*/
static int modifyElem(Node *pHead, int pos, elemType x)
{
    int i = 0;

    if(NULL == pHead)
    {
        printf("链表为空\n");
        return 0;
    }
    if(pos < 1)
    {
        printf("pos值非法\n");
        return 0;
    }

    while(pHead != NULL)
    {
        ++ i;
        if(i == pos)
        {
            break; 
        }
        pHead=pHead->next;
    }
    if(i<pos)
    {
        printf("pos值非法\n");
        return 0;
    }
    pHead->element = x;   //指针的位置没有改变, 只修改了存储内容
    return 1;
}

/*向单链表的表头插入一个元素*/
static int insertHeadList(Node **pNode, elemType insertElem)
{
    Node *pInsert;
    pInsert = (Node *)malloc(sizeof(Node));
    memset(pInsert, 0x00, sizeof(Node));
    pInsert->element=insertElem;
    pInsert->next=*pNode;
    *pNode = pInsert;        
    printf("表头插入节点成功.\n");
    
    return 1;
}

/*向单链表的末尾添加一个元素*/
static int insertLastList(Node **pNode, elemType insertElem)
{
    Node  *pInsert;
    Node  *pHead;
    Node  *pTemp;     //定义一个临时链表用来存放第一个节点地址

    pHead = *pNode;
    pTemp = pHead;
    pInsert = (Node *)malloc(sizeof(Node));
    memset(pInsert, 0x00, sizeof(Node));
    pInsert->element=insertElem;

    while(NULL != pHead->next)
    {
        pHead=pHead->next;
    }
    pHead->next=pInsert;
    *pNode = pTemp;
    printf("向链表尾部插入节点成功.\n");

    return 1;
}

/*向单链表中第pos个结点位置插入元素为x的结点，若插入成功返回１，否则返回０*/
static int insertPosList(Node **pNode, int pos,  elemType insertElem) 
{
    Node *pInsert;
    Node *pHead;
    Node *pTemp;
    int  i=0;

    pHead = *pNode;
    pTemp = pHead;
    pInsert = (Node *)malloc(sizeof(Node));
    memset(pInsert, 0x00, sizeof(Node));
    pInsert->element=insertElem;

    if(NULL == pHead)
    {
        printf("链表为空\n");
        return 0;
    }
    if(pos < 1)
    {
        printf("pos值非法\n");
        return 0;
    }

    while(pHead != NULL)
    {
        ++ i;
        if(i == pos)
            break;
        pHead=pHead->next;
    }
    if(i<pos)
    {
        printf("pos值无效.\n");
        return 0;
    }
    pInsert->next = pHead->next;
    pHead->next = pInsert;
    *pNode = pTemp;

    return 1;
}



int main(int argc, char *argv[])
{
    
    Node *pList=NULL;
    int length=0;

    elemType posElem;

    printf("********初始化链表**********\n");
    initList(&pList);
    printList(pList);

    printf("\n********创建链表**********\n");

    pList = createList(pList);
    printList(pList);
   
    isEmptyList(pList);
    sizeList(pList);

    printf("\n********获取链表某个位置的值**********\n");
    posElem = getelement(pList, 3);
    printf("在链表位置3的地方存放的数据是: %d\n", posElem);

    
    printf("\n********获取链表中某个值的地址**********\n");
    getElemAddr(pList, 8);


    printf("\n*********修改某个节点的值*********\n");
    modifyElem(pList, 5, 99);
    printList(pList);

    printf("\n*********链表头插入节点*********\n");
    insertHeadList(&pList, 22);
    printList(pList);


    printf("\n*********链表尾部插入节点*********\n");
    insertLastList(&pList, 33); 
    printList(pList);

    printf("\n*********在pos的位置插入新节点*********\n");
    insertPosList(&pList, 2, 44);
    printList(pList);

    

    printf("\n*********清空链表*********\n");
    display_linkList(pList);
    pList=NULL;
    printList(pList);

    return 0;
}
