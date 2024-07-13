#ifndef UBIGNUMBER_H_INCLUDE
#define UBIGNUMBER_H_INCLUDE

struct Node
{
    int digit;//数字
    struct Node *next,*prev;//前后结点指针
};

//无符号大数结构体
struct UBigNumber
{
    int digitCount;//位数
    struct Node*pHead,*pTail;//指向头结点和尾结点
};

//下列函数返回的大数占用的内存资源由函数调用者负责释放
//输入无符号大数
struct UBigNumber InputUBN();
//打印无符号大数
void PrintUBN(struct UBigNumber ubn);
//两个无符号大数相加
struct UBigNumber AddUBN(const struct UBigNumber *pA,const struct UBigNumber *pB);
//销毁无符号大数，释放空间
void DestoryUBN(struct UBigNumber *pA);

//下列函数是无符号大数处理辅助函数
//表示无符号大数用带头节点的双向链表
void _InitUBN(struct UBigNumber *pUBN);
//无符号大数尾部添加1位数字
void _AppendDigit(struct UBigNumber *pUBN,int digit);
//无符号大数尾部添加1位数字
void _AppendFrontDigit(struct UBigNumber *pUBN,int digit);
//无符号大数的规范表示，去除高位多余的0，至少含1位数字
void _Normalize(struct UBigNumber *pUBN);
//动态分配一个节点，返回节点指针
//分配失败时，简化程序，退出运行
struct Node*_NewNode();
#endif //UBIGNUMBER_H_INCLUDE




