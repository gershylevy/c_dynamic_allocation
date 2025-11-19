/*------------------------------------------------------
* Filename: median.c
* Description: Find median of numbers given.
* Author: Gershon Levy
-------------------------------------------------------*/

// note that i considered \n to be a non number char

#include <stdio.h>
#include <stdlib.h>

#define START_SIZE (100)
#define SIZE_JUMP (10)

#define FALSE (0)
#define TRUE (1)

#define NO_INPUT_ERR (-1)
#define MEM_ALLOCATE_ERR (-2)

/*------------------------------------------------------
* Function Name -  insertion_sort
*
* Function Purpose - Sorts an array using insertion sort.
*
* Parameters –  [IN arr - Our array.]
*               [IN n - The size of our array]
*
* Return Values - The sorted array.
*
* Author - Gershon Levy
-------------------------------------------------------*/

int *insertion_sort(int arr[], int n)
{
    for (int i = 1; i < n; ++i)
    {
        int key = arr[i];
        int j = i - 1;

        /* Move elements of arr[0..i-1], that are
           greater than key, to one position ahead
           of their current position */
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }

    return arr;
}

float median(int nums[], int size)
{
    float median;
    // if size is odd then we want the middle element
    if (size % 2 != 0)
    {
        --size; // since size is 0 indexed
        return nums[(size + 1) / 2];
    }

    --size; // since size is 0 indexed
    // if size is even then we want the average of the 2 middle elements
    median = ((float)nums[size / 2] + nums[(size / 2) + 1]) / 2;

    return median;
}

int main()
{
    // init
    int max_size = START_SIZE; // note this can change in the future
    int size = 0;
    int minus = FALSE;
    int i = 0;
    float median_num;

    int *nums = (int *)malloc(max_size * sizeof(int));
    if (nums == NULL)
    {
        printf("memory allocation error\n");
        return MEM_ALLOCATE_ERR;
    }

    int temp = fgetc(stdin);

    nums[0] = 0;

    do
    {
        // if we ran outta space
        if (max_size == size)
        {
            max_size += SIZE_JUMP;
            nums = (int *)realloc(nums, max_size * sizeof(int)); // increase space allocated

            if (nums == NULL)
            {
                printf("memory allocation error\n");
                return MEM_ALLOCATE_ERR;
            }
        }

        if ((temp < '0' || temp > '9') && temp != '-' && temp != ' ')
        {
            // we shrink size by 2, 1 for this char and another because if size
            size--;
            break;
        }

        // end of number
        if (temp == ' ')
        {
            ++size;
            nums[size] = 0;
            temp = fgetc(stdin);
            minus = FALSE;
            continue;
        }

        // make space for next part of number (e.g turn 12 into 120 so we could make it into 123 easier)
        nums[size] *= 10;

        if (temp == '-')
        {
            minus = TRUE;
        }

        // add the last part of number
        if (temp != '-' && minus == FALSE)
        {
            nums[size] += temp - '0';
        }

        // number is negative so do opposite
        if (temp != '-' && minus == TRUE)
        {
            nums[size] -= temp - '0';
        }

        temp = fgetc(stdin);
    } while (temp != '\n');

    // we didnt grow size for last number
    ++size;

    // no nums were inputted
    if (size == 0)
    {
        printf("no nums inputted\n");
        return NO_INPUT_ERR;
    }

    nums = insertion_sort(nums, size);

    median_num = median(nums, size);

    printf("The median is: %.1f\n", median_num);

    // deallocate space
    free(nums);

    return 0;
}