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

// Done; working
void BucketSort(int* input_array, int size, int max, int bucket_count)
{
    std::vector<int>* buckets = new std::vector<int>[bucket_count];
    int min = max;
    for (int i = 0; i < size; i++)
    {
        if (input_array[i] < min)
        {
            min = input_array[i];
        }
    }
    for (int i = 0; i < size; i++)
    {
        buckets[(int)(bucket_count * input_array[i] / max)].push_back(input_array[i]);
    }
    for (int i = 0; i < bucket_count; i++)
    {
        if (buckets[i].size() > 1)
        {
            bool changed = true;
            while (changed)
            {
                changed = false;
                for (int j = 0; j < buckets[i].size() - 1; j++)
                {
                    if (buckets[i][j] > buckets[i][j+1])
                    {
                        int temp = buckets[i][j];
                        buckets[i][j] = buckets[i][j+1];
                        buckets[i][j + 1] = temp;
                        changed = true;
                    }
                }
            }
        }
    }

    for (int i = 0; i < bucket_count; i++)
    {
        printf("\n");
        for (int j = 0; j < buckets[i].size(); j++)
        {
            printf("%i ", buckets[i][j]);
        }
    }

    int index = 0;
    for (int i = 0; i < bucket_count; i++)
    {
        for (int j = 0; j < buckets[i].size(); j++)
        {
            input_array[index++] = buckets[i][j];
        }
    }
}

template <typename T>
void BucketSort(T* input_array, int size, int max, bool comp(), void func())
{

}

int main()
{
    /*int size = 20;
    int max = 544;
    int input2[20] = {2,32,543,6,1,3,2,5,7,3,1,65,1,23,57,12,75,12,61,32};
    CountingSort(input2, size, max);
    for (int i = 0; i < size; i++)
    {
        printf("%i ", input2[i]);
    }*/
    
    int size = 20;
    int max = 101;
    int input2[20] = { 2,32,100,6,1,3,2,5,7,3,1,65,1,23,57,12,75,12,61,32 };

    /*int size = 10;
    int max = 10+1;
    int input2[10] = { 2,1,5,6,8,9,3,4,7,10 };*/
    BucketSort(input2, size, max,5);
    printf("\n");
    for (int i = 0; i < size; i++)
    {
        printf("%i ", input2[i]);
    }
}

