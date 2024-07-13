#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"UBigNumber.h"

//输入无符号大数
struct UBigNumber InputUBN()
{
    struct UBigNumber result;
    _InitUBN(&result);
    char ch;
    //跳过非数字字符
    do
        ch=getchar();
    while(ch<'0'||ch>'9');
    while(ch>='0'&&ch<='9')
    {
        _AppendDigit(&result,ch-'0');//添加一位
        ch=getchar();
    }
    _Normalize(&result);
    return result;
}

//打印无符号大数
void PrintUBN(struct UBigNumber ubn)
{
    //断言：至少有1位数字
    assert(ubn.digitCount>0&&ubn.pHead->next!=NULL);
    struct Node *la=ubn.pHead->next;//头结点无数据，跳过
    while(la)
    {
        printf("%d",la->digit);
        la=la->next;
    }
}

//两个无符号大数相加
struct UBigNumber AddUBN(const struct UBigNumber *pA,const struct UBigNumber *pB)
{
    struct UBigNumber result,*pResult=&result;
    _InitUBN(pResult);
    int iCarry=0;//进位，初始0
    struct Node *p1=pA->pTail,*p2=pB->pTail;//从低位开始处理
    while(p1!=pA->pHead&&p2!=pB->pHead)//两数相同位处理
    {
        int digit=p1->digit+p2->digit+iCarry;
        iCarry=digit/10;//新进位
        digit%=10;//当前结果位
        _AppendFrontDigit(pResult,digit);//添加至结果最高位
        p1=p1->prev;//准备处理前一位
        p2=p2->prev;
    }
    while(p1!=pA->pHead)//第1大数剩余位处理
    {
        int digit=p1->digit+iCarry;
        iCarry=digit/10;
        digit%=10;
        _AppendFrontDigit(pResult,digit);
        p1=p1->prev;
    }
    while(p2!=pB->pHead)//第2大数剩余位处理
    {
        int digit=p2->digit+iCarry;
        iCarry=digit/10;
        digit%=10;
        _AppendFrontDigit(pResult,digit);
        p2=p2->prev;
    }
    if(iCarry!=0)//最后进位处理
        _AppendFrontDigit(pResult,iCarry);
    return result;
}

//销毁无符号大数，释放空间
void DestoryUBN(struct UBigNumber *pUBN)
{
    while (pUBN->pHead!=NULL)//晴空后应该只剩1个头结点
    {
        struct Node *p=pUBN->pHead;//待删除结点
        pUBN->pHead=p->next;//尾指针前移
        free(p);//释放结点
    }
}

//建立表示无符号大数用带头节点双向链表
void _InitUBN(struct UBigNumber *pUBN)
{
    struct Node*p=_NewNode();
    pUBN->pHead=pUBN->pTail=p;//建立头结点
    p->next=p->prev=NULL;
    pUBN->digitCount=0;//位数0
}

//在无符号大数尾部添加1位数字
void _AppendDigit(struct UBigNumber *pUBN,int digit)
{
    //原来只有一个高位0
    if(pUBN->digitCount==1&&pUBN->pTail->digit==0)
    {
        pUBN->pTail->digit=digit;
        return;
    }
    struct Node *p=_NewNode();
    p->digit=digit;
    p->next=NULL;
    p->prev=pUBN->pTail;
    pUBN->pTail->next=p;
    pUBN->pTail=p;
    ++pUBN->digitCount;//修改位数
}

//无符号大数前添加1位数字
void _AppendFrontDigit(struct UBigNumber *pUBN,int digit)
{
    struct Node *p=_NewNode();//申请新结点
    p->digit=digit;//设置结点数值
    p->next=pUBN->pHead->next;//修改双向链表，将新结点添加在头结点后
    if(p->next!=NULL)
        p->next->prev=p;
    p->prev=pUBN->pHead;
    pUBN->pHead->next=p;
    if(pUBN->pTail==pUBN->pHead)
        pUBN->pTail=p;//当原来只有头结点时，新结点也是尾结点
    ++pUBN->digitCount;//修改位数
}

//无符号大数的规范表示，去除高位多余的0，至少含1位数字
void _Normalize(struct UBigNumber *pUBN)
{
    if(pUBN->digitCount==0)
        _AppendFrontDigit(pUBN,0);
    while(pUBN->digitCount>1&&pUBN->pHead->next->digit==0)
    {
        struct Node *p=pUBN->pHead->next;//待删除的结点
        pUBN->pHead->next=p->next;//正向链表中删除
        p->next->prev=pUBN->pHead;//反向链表中删除
        free(p);//释放结点
        --pUBN->digitCount;//调整位数
    }
}

//动态分配1个节点，返回节点指针
//当分配内存失败时，简化程序，退出运行
struct Node *_NewNode()
{
    struct Node *p=(struct Node*)malloc(sizeof(struct Node));;
    if(p==NULL)
    {
        printf("Error:out of memory\n");
        exit(-1);
    }
    return p;
}

