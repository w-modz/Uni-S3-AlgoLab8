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
        // using bubble sort for sorting buckets
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

    int index = 0;
    for (int i = 0; i < bucket_count; i++)
    {
        for (int j = 0; j < buckets[i].size(); j++)
        {
            input_array[index++] = buckets[i][j];
        }
    }
}

// Done; working?; unsure about implementation
template <typename T>
void BucketSort(T* input_array, int size, int max, int bucket_count, bool comp(T,T), int range(T))
{
    std::vector<T>* buckets = new std::vector<T>[bucket_count];
    /*int min = max;
    for (int i = 0; i < size; i++)
    {
        if (input_array[i] < min)
        {
            min = input_array[i];
        }
    }*/
    for (int i = 0; i < size; i++)
    {
        buckets[(int)(bucket_count * range(input_array[i]) / max)].push_back(input_array[i]);
    }
    for (int i = 0; i < bucket_count; i++)
    {
        // using bubble sort for sorting buckets
        if (buckets[i].size() > 1)
        {
            bool changed = true;
            while (changed)
            {
                changed = false;
                for (int j = 0; j < buckets[i].size() - 1; j++)
                {
                    if ( comp(buckets[i][j],buckets[i][j + 1]) )
                    {
                        T temp = buckets[i][j];
                        buckets[i][j] = buckets[i][j + 1];
                        buckets[i][j + 1] = temp;
                        changed = true;
                    }
                }
            }
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


struct Test
{
    double value;
    int integer;
    bool operator>(Test a)
    {
        return ((int)this->value + this->integer) > ((int)a.value + a.integer);
    }
};

int range(Test element)
{
    return element.integer + (int)element.value;
}

template<typename T>
bool greater(T data1, T data2)
{
    return data1 > data2;
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
    
    /*int size = 20;
    int max = 101;
    int input2[20] = { 2,32,100,6,1,3,2,5,7,3,1,65,1,23,57,12,75,12,61,32 };

    BucketSort(input2, size, max,5);
    printf("\n");
    for (int i = 0; i < size; i++)
    {
        printf("%i ", input2[i]);
    }*/

    /*int size = 20;
    int max = 40;
    Test input[20];
    Test a;
    for (int i = 0; i < 20; i++)
    {
        a.value = i;
        a.integer = i;
        input[i] = a;
    }
    BucketSort(input, size, max, 5, greater<Test>, range);
    printf("\n");
    for (int i = 0; i < size; i++)
    {
        printf("{%i %lf} ", input[i].integer, input[i].value);
    }*/

    DynamicArray<int>* array = new DynamicArray<int>;
    int size = 10;
    int max = 11;
    for (int i = 6; i < 11; i++)
    {
        array->Append(i);
    }
    for (int i = 1; i < 6; i++)
    {
        array->Append(i);
    }

    /*DynamicArray<int>* array = new DynamicArray<int>;
    int size = 10;
    int max = 11;
    for (int i = 1; i < 11; i++)
    {
        array->Append(i);
    }*/

    for (int i = 0; i < size; i++)
    {
        printf("{%i} ", array->values[i]);
    }
    BinaryHeap<int> bh(array, size, true);
    printf("\n");
    bh.Sort(size);
    for (int i = 0; i < size; i++)
    {
        printf("{%i} ",array->values[i]);
    }
    //printf("%s",bh.toString(size-1));
}

