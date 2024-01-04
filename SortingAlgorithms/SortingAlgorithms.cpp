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

void CountingSort(std::vector<int> input_array, int size, int max)
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
    for (int i = size - 1; i >= 0; i--)
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
    long bucket_range = max / bucket_count;
    for (int i = 0; i < size; i++)
    {
        buckets[(input_array[i] / bucket_range)].push_back(input_array[i]);
    }
    for (int i = 0; i < bucket_count; i++)
    {   
        // using bubble sort for sorting buckets; this implementation results in slow sorting
        if (buckets[i].size() > 1)
        {
           //CountingSort(buckets[i],buckets[i].size(),max);
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
    /*printf("\n\n");
    for (int i = 0; i < bucket_count; i++)
    {
        if (buckets[i].size() > 0)
        {
            for (int j = 0; j < buckets[i].size(); j++)
            {
                printf("bucket %i : %i ",i, buckets[i][j]);
            }
            printf("\n");
        }
    }
    printf("\n\n");*/
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


//struct Test
//{
//    double value;
//    int integer;
//    bool operator>(Test a)
//    {
//        return ((int)this->value + this->integer) > ((int)a.value + a.integer);
//    }
//};

//int range(Test element)
//{
//    return element.integer + (int)element.value;
//}

template<typename T>
bool greater(T data1, T data2)
{
    return data1 > data2;
}

bool compareTables(int* tab1, DynamicArray<int>* tab2, int* tab3, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (tab1[i] != tab3[i] || tab1[i] != tab2->values[i] || tab3[i] != tab2->values[i])
        {
            return false;
        }
    }
    return true;
}

bool compareTables(int* tab1, int* tab3, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (tab1[i] != tab3[i])
        {
            return false;
        }
    }
    return true;
}

bool compareTables(DynamicArray<int>* tab1, DynamicArray<int>* tab3, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (tab1->values[i] != tab3->values[i])
        {
            return false;
        }
    }
    return true;
}

// Countingsort works; heapsort works with upheap; Bucketsort works with integer as bucket count
void main_ints()
{
    srand(0);
    clock_t t1, t2;
    //int MAX_ORDER = 7; // m a k s y m a l n y rzad wielkosci s o r t o w a n y c h danych
    int MAX_ORDER = 7;
    int m = (int)pow(10, 7); // sortowane liczby ze zbioru {0 , ... , m - 1}
    for (int o = 1; o <= MAX_ORDER; o++)
    {
        int n = (int)pow(10, o); // rozmiar tablicy z danymi
        int* array1 = new int[n];
        DynamicArray<int>* array2 = new DynamicArray<int>;
        DynamicArray<int>* array22 = new DynamicArray<int>;
        for (int i = 0; i < n; i++)
        {
            int rand_val = abs((rand() * rand()) % m); // tu losowanie liczby c a l k o w i t e j
                array1[i] = rand_val;
                array2->Append(rand_val);
                array22->Append(rand_val);
        }
         // skrotowy wypis tablicy do p o s o r t o w a n i a ( np . pewna liczba p o c z a t k o w y c h elementow )
        printf("Input array:\n");
        for (int i = 0; i < 10; i++)
        {
            printf("{%i} ",array1[i]);
        }
        printf("\n");
        //int* array2 = new int[n];
        int* array3 = new int[n];
        //memcpy(array2, array1, n * sizeof(int)); // pierwsza kopia
        memcpy(array3, array1, n * sizeof(int)); // druga kopia
        if (compareTables(array1, array2, array3, n))
        {
            printf("--------Input Tables are equal--------\n");
        }
        else
        {
            printf("--------Input Tables are not equal--------\n");
        }
        // s o r t o w a n i e przez zliczanie ( do wykonania w miejscu )
        
        clock_t t1 = clock();
        CountingSort(array1, n, m);
        clock_t t2 = clock();
        std::cout << "Total time of Counting Sort = " << ((t2 - t1) / (double)CLOCKS_PER_SEC) * 1000 << "ms\n";
        for (int i = 0; i < 10; i++)
        {
            printf("{%i} ", array1[i]);
        }
        printf("\n");

        // wypis pomiaru czasu i skrotowej postaci wynikowej tablicy
        // s o r t o w a n i e przez k o p c o w a n i e ( do wykonania w miejscu )
        
        t1 = clock();
        BinaryHeap<int> bh(array2, n, true);
        /*BinaryHeap<int> bh2(array22, n, false);
        if (compareTables(array2, array22, n))
        {
            printf("+++Equal+++\n");
        }
        else
        {
            printf("---Not Equal---\n");
        }*/


        bh.Sort(n);
        t2 = clock();
        std::cout << "Total time of Heap Sort = " << ((t2 - t1) / (double)CLOCKS_PER_SEC) * 1000 << "ms\n";
        for (int i = 0; i < 10; i++)
        {
            printf("{%i} ", array2->values[i]);
        }
        printf("\n");

        // wypis pomiaru czasu i skrotowej postaci wynikowej tablicy
        // s o r t o w a n i e kubelkowe ( do wykonania w miejscu )

        t1 = clock();
        BucketSort(array3, n, m, n); // s z c z e g o l n a wersja bucket sort tylko dla liczb c a l k o w i t y c h
        t2 = clock();
        std::cout << "Total time of Bucket Sort = " << ((t2 - t1) / (double)CLOCKS_PER_SEC) * 1000 << "ms\n";
        for (int i = 0; i < 10; i++)
        {
            printf("{%i} ", array3[i]);
        }
        printf("\n");


        //array2->swap(0,1);

        if (compareTables(array1,array2,array3,n))
        //if (compareTables(array1,array3,n))
        {
            printf("========Output Tables are equal========\n\n");
        }
        else
        {
            printf("========Output Tables are not equal========\n\n");
        }
        // wypis pomiaru czasu i skrotowej postaci wynikowej tablicy
            // s p r a w d z e n i e zgodnosci tablic array1 , array2 , array3 i wypis i n f o r m a c j i o zgodnosci na ekran
        delete[] array1;
        //delete[] array2;
        delete[] array3;
    }
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

    /*DynamicArray<int>* array = new DynamicArray<int>;
    int size = 10;
    int max = 11;
    for (int i = 6; i < 11; i++)
    {
        array->Append(i);
    }
    for (int i = 1; i < 6; i++)
    {
        array->Append(i);
    }*/

    /*DynamicArray<int>* array = new DynamicArray<int>;
    int size = 10;
    int max = 11;
    for (int i = 1; i < 11; i++)
    {
        array->Append(i);
    }*/

    /*for (int i = 0; i < size; i++)
    {
        printf("{%i} ", array->values[i]);
    }
    BinaryHeap<int> bh(array, size, true);
    printf("\n");
    bh.Sort(size);
    for (int i = 0; i < size; i++)
    {
        printf("{%i} ",array->values[i]);
    }*/
    //printf("%s",bh.toString(size-1));
    main_ints();

}

