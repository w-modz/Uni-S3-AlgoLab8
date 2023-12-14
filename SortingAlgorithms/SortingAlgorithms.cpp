#include <iostream>
#include "BinaryHeap.cpp"

// Done; working
void CountingSort(int* input_array, int size, int max)
{
    int* counting_array = new int[max];
    int* helper_array = new int[size];
    for (int i = 0; i < max; i++)
    {
        counting_array[i] = 0;
    }
    for (int i = 0; i < size; i++)
    {
        counting_array[input_array[i]]++;
        helper_array[i] = input_array[i];
    }
    for (int i = 1; i < max; i++)
    {
        counting_array[i] += counting_array[i - 1];
    }
    for (int i = size-1; i >= 0; i--)
    {
        counting_array[helper_array[i]]--;
        input_array[counting_array[helper_array[i]]] = helper_array[i];
    }

    delete[] counting_array;
    delete[] helper_array;
}

int main()
{
    int size = 20;
    int max = 544;
    int input2[20] = {2,32,543,6,1,3,2,5,7,3,1,65,1,23,57,12,75,12,61,32};
    CountingSort(input2, size, max);
    for (int i = 0; i < size; i++)
    {
        printf("%i ", input2[i]);
    }
}

