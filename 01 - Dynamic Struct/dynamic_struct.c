/*------------------------------------------------------
* Filename: dynamic_struct.c
* Description: Calculate times of day using dynamic allocation.
* Author: Gershon Levy
-------------------------------------------------------*/

#include <stdio.h>
#include <malloc.h>

#define MAX_SECS (60)
#define MAX_MINS (60)
#define MAX_HRS (24)

#define BAD_INPUT_ERR (-1)
#define MEM_ALLOCATION_ERR (-2)

struct Time
{

    int hrs;
    int mins;
    int secs;
};

/*------------------------------------------------------
* Function Name - add_time
*
* Function Purpose - Add 2 times together.
*
* Parameters –  [IN time1 - The first time we are adding.]
*               [IN time2 - The second time we are adding.]
*
* Return Values - The sum of the times.
*
* Author - Gershon Levy
-------------------------------------------------------*/

struct Time *add_time(struct Time *time1, struct Time *time2)
{
    /*init dynamically*/
    struct Time *time3 = (struct Time *)malloc(sizeof(struct Time));

    if (time3 == NULL)
    {
        printf("memory allocation err");
        return NULL;
    }

    /*make time 0:0:0*/
    time3->hrs = 0;
    time3->mins = 0;
    time3->secs = 0;

    time3->secs += (time1->secs) + (time2->secs);
    /*check if overflow on secs*/
    if ((time3->secs) >= MAX_SECS)
    {
        /*dont do +1 just in case we went over 120 secs. e.g. 12:01:100+12:01:21*/
        time3->mins += (time3->secs) / MAX_SECS;
        time3->secs %= MAX_SECS;
    }

    time3->mins += (time1->mins) + (time2->mins);
    /*check if overflow on mins*/
    if ((time3->mins) >= MAX_MINS)
    {
        /*dont do +1 like i said before*/
        time3->hrs += (time3->mins) / MAX_MINS;
        time3->mins %= MAX_MINS;
    }

    time3->hrs += (time1->hrs) + (time2->hrs);
    /*check if overflow on hrs*/
    if ((time3->hrs) >= MAX_HRS)
    {
        time3->hrs %= MAX_HRS;
    }

    return time3;
}

/*------------------------------------------------------
* Function Name - free_3_ptrs
*
* Function Purpose - Free the memory from 3 pointers.
*
* Parameters –  [IN time1 - The first pointer we are freeing.]
*               [IN time2 - The second pointer we are freeing.]
*               [IN time3 - The third pointer we are freeing.]
*
* Return Values - None.
*
* Author - Gershon Levy
-------------------------------------------------------*/

void free_3_ptrs(struct Time *time1, struct Time *time2, struct Time *time3)
{
    free(time1);
    free(time2);
    free(time3);
}

/*------------------------------------------------------
* Function Name - free_2_ptrs
*
* Function Purpose - Free the memory from 2 pointers.
*
* Parameters –  [IN time1 - The first pointer we are freeing.]
*               [IN time2 - The second pointer we are freeing.]
*
* Return Values - None.
*
* Author - Gershon Levy
-------------------------------------------------------*/

void free_2_ptrs(struct Time *time1, struct Time *time2)
{
    free(time1);
    free(time2);
}

int main()
{
    /*init dynamically*/
    struct Time *time1 = (struct Time *)malloc(sizeof(struct Time));

    if (time1 == NULL)
    {
        printf("memory allocation err");
        return MEM_ALLOCATION_ERR;
    }

    struct Time *time2 = (struct Time *)malloc(sizeof(struct Time));

    if (time2 == NULL)
    {
        printf("memory allocation err");
        free(time1);
        return MEM_ALLOCATION_ERR;
    }

    /*get info for the structs*/
    printf("Enter hours for first time: ");
    if (scanf("%d", &time1->hrs) != 1)
    {
        printf("bad input\n");
        free_2_ptrs(time1, time2);
        return BAD_INPUT_ERR;
    }

    printf("Enter minutes for first time: ");
    if (scanf("%d", &time1->mins) != 1)
    {
        printf("bad input\n");
        free_2_ptrs(time1, time2);
        return BAD_INPUT_ERR;
    }

    printf("Enter seconds for first time: ");
    if (scanf("%d", &time1->secs) != 1)
    {
        printf("bad input\n");
        free_2_ptrs(time1, time2);
        return BAD_INPUT_ERR;
    }

    printf("Enter hours for second time: ");
    if (scanf("%d", &time2->hrs) != 1)
    {
        printf("bad input\n");
        free_2_ptrs(time1, time2);
        return BAD_INPUT_ERR;
    }

    printf("Enter minutes for second time: ");
    if (scanf("%d", &time2->mins) != 1)
    {
        printf("bad input\n");
        free_2_ptrs(time1, time2);
        return BAD_INPUT_ERR;
    }

    printf("Enter seconds for second time: ");
    if (scanf("%d", &time2->secs) != 1)
    {
        printf("bad input\n");
        free_2_ptrs(time1, time2);
        return BAD_INPUT_ERR;
    }

    /*add them and print result*/
    struct Time *result = add_time(time1, time2);

    if (result == NULL)
    {
        printf("memory allocation err");
        free_2_ptrs(time1, time2);
        return MEM_ALLOCATION_ERR;
    }

    printf("The sum is: %d:%d:%d", result->hrs, result->mins, result->secs);

    /*free mem*/
    free_3_ptrs(time1, time2, result);

    return 0;
}