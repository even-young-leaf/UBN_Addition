#include <stdio.h>
#include"UBigNumber.h"
int main(void)
{
    struct UBigNumber A,B,C;
    A=InputUBN();
    B=InputUBN();
    C=AddUBN(&A,&B);
    PrintUBN(A);
    printf("+");
    PrintUBN(B);
    printf("=");
    PrintUBN(C);
    DestoryUBN(&A);
    DestoryUBN(&B);
    DestoryUBN(&C);
    return 0;
}
