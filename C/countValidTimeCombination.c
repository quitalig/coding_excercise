// Online C compiler to run C program online
#include <stdio.h>

#define THOUSANDTHS 1000
#define HUNDREDTHS  100
#define TENTHS      10
#define MAX_TIME    2359

void swap(int *first, int *second)
{
    int temp = *first;
    *first = *second;
    *second = temp;
}

unsigned int validateTime(int *inputArr)
{
    if( ((2 > inputArr[0]) || \
        ((2 == inputArr[0]) && (3 >= inputArr[1]))) && \
        (5 >= inputArr[2]) )
    {
        if (MAX_TIME >= ((inputArr[0])*THOUSANDTHS) + ((inputArr[1]) * HUNDREDTHS) + ((inputArr[2]) * TENTHS) + (inputArr[3]))
        {
            return 1;
        }  
    }
    
    return 0;
}

void printArr(int *inputArr)
{
    for(int ctr = 0; ctr < 4; ctr++)
    {
        printf("%d", inputArr[ctr]);
    }
    printf("\n");
}

int count(short A, short B, short C, short D)
{
    int result = 0;
    int input[] = {A, B, C, D};
    
    for(int ctr = 0; ctr < 4; ctr++)
    {
        if(ctr != 0)
        {
            swap(&input[0], &input[ctr]);
        }
        
        for(int x = 0; x < 3; x++)
        {
            printArr(input);
            result += validateTime(input);
            swap(&input[2], &input[3]);
            
            printArr(input);
            result += validateTime(input);
            swap(&input[1], &input[2]);
        }
        
        if(ctr != 0)
        {
            swap(&input[0], &input[ctr]);
        }
    }
    
    return result;
}

int main() {
    printf("result: %d\n", count(1, 7, 8, 4));
    printf("result: %d\n", count(1, 2, 5, 0));
    printf("result: %d\n", count(2, 3, 5, 9));
    printf("result: %d\n", count(0, 9, 0, 4));
    return 0;
}