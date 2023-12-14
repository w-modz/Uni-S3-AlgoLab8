// ALGO2 IS1 221A LAB05
// Wiktor Modzelewski
// mw53766@zut.edu.pl
#include <iostream>
#include <string>
#include <array>
#include <ctime>
#include <random>
#include <sstream>

#define DEFAULT_SIZE 8
#define EXPANSION_MULTIPLIER 2

template<typename T>
class DynamicArray
{
private:
	uint32_t size = DEFAULT_SIZE;
public:
	uint32_t actual_size = 0;
	T* values;

	DynamicArray(void)
	{
		values = new T[DEFAULT_SIZE];
	}

	~DynamicArray()
	{
		delete[] values;
		values = nullptr;
	}

	uint32_t GetSize()
	{
		return size;
	}

	uint32_t GetActualSize()
	{
		return actual_size;
	}
	void Set(uint32_t index, T value)
	{
		if (index > actual_size)
		{
			throw std::out_of_range("Index out of bounds");
		}
		values[index] = value;
	}
	T Get(uint32_t index)
	{
		if (index >= actual_size)
		{
			throw std::out_of_range("Index out of bounds");
		}
		return values[index];
	}

	void Append(T value)
	{
		if (actual_size + 1 > size)
		{
			Expand();
		}
		Set(actual_size, value);
		actual_size++;
	}

	void Clear()
	{
		delete[] values;
		actual_size = 0;
		T* new_values = new T[size];
		values = new_values;
	}

	// The sorting method assumes existance of valid ">" operator overload for given datatype
	void Sort()
	{
		for (int i = 0; i < actual_size - 1; i++)
		{
			for (int j = 0; j < actual_size - i - 1; j++)
			{
				if (values[j] > values[j + 1])
				{
					int temp = values[j + 1];
					values[j + 1] = values[j];
					values[j] = temp;
				}
			}
		}
	}

	std::string ToString(uint32_t number_to_print)
	{
		if (number_to_print == 0)
		{
			return "[]";
		}
		else if (actual_size == 0)
		{
			return "[]";
		}
		else if (actual_size < number_to_print)
		{
			throw std::out_of_range("Index out of bounds");
		}
		std::ostringstream output_stream;
		output_stream << "[" << values[0];
		for (int i = 1; i < number_to_print; i++)
		{
			output_stream << ", " << values[i];
		}
		output_stream << "]\n";
		return output_stream.str();
	}

	void swap(int index1, int index2)
	{
		if (actual_size <= index1 || actual_size <= index2)
		{
			throw std::out_of_range("Index out of bounds");
		}
		T temp = values[index1];
		values[index1] = values[index2];
		values[index2] = temp;
	}

private:
	void Expand()
	{
		const uint32_t new_size = size * EXPANSION_MULTIPLIER;
		T* new_values = new T[new_size];
		for (int i = 0; i < actual_size; i++)
		{
			new_values[i] = values[i];
		}
		delete[] values;
		values = new_values;
		size = new_size;
	}
};

template <typename T>
class BinaryHeap
{
private:
	DynamicArray<T>* table;
public:
	BinaryHeap(void)
	{
		table = new DynamicArray<T>;
	}
	~BinaryHeap(void)
	{
		delete table;
		table = nullptr;
	}

	int parent(int i)
	{ 
		return (i - 1) / 2;
	}

	int left(int i)
	{ 
		return (2 * i + 1);
	}

	int right(int i) 
	{ 
		return (2 * i + 2);
	}

	void clear(void)
	{
		delete table;
		table = new DynamicArray<T>;
	}

	std::string toString(uint32_t number_to_print)
	{
		return table->ToString(number_to_print);
	}


	template<typename Comp>
	void insert(T data, Comp greaterEq)
	{
		table->Append(data);
		int current_element = table->GetActualSize() - 1;
		upHeap(current_element, greaterEq);
	}

	template<typename Comp>
	T getMax(Comp greaterEq)
	{
		T max;
		if (table->GetActualSize() == 0)
		{
			throw std::domain_error("err");
		}
		else if (table->GetActualSize() == 1)
		{
			max = table->values[0];
			clear();
			return max;
		}
		max = table->values[0];
		table->values[0] = table->values[table->GetActualSize() - 1];
		//table->values[table->GetActualSize() - 1];
		table->actual_size--;
		downHeap(0, greaterEq);
		return max;
	}

	template<typename Comp>
	void upHeap(int& current_element, Comp& greaterEq)
	{
		if (current_element != 0 && greaterEq(table->Get(current_element), table->Get(parent(current_element))))
		{
			table->swap(current_element, parent(current_element));
			current_element = parent(current_element);
			upHeap(current_element, greaterEq);
		}
	}

	template<typename Comp>
	void downHeap(int index, Comp greaterEq)
	{
		if (!greaterEq(table->values[index], table->values[left(index)]) || !greaterEq(table->values[index], table->values[right(index)]))
		{
			if (greaterEq(table->values[left(index)], table->values[right(index)]))
			{
				if (left(index) < table->actual_size)
				{
					table->swap(index, left(index));
					index = left(index);
				}
			}
			else
			{
				if (left(index) < table->actual_size)
				{
					table->swap(index, right(index));
					index = right(index);
				}
			}
			if (right(index) < table->actual_size && left(index) < table->actual_size)
			{
				downHeap(index, greaterEq);
			}
		}
	}
};

template<typename T>
bool greaterEq(const T data1, const T data2)
{
	return data1 >= data2;
}

int main()
{
	/*BinaryHeap<int>* heap = new BinaryHeap<int>;
	heap->insert(19, greaterEq<int>);
	heap->insert(36, greaterEq<int>);
	heap->insert(25, greaterEq<int>);
	heap->insert(1, greaterEq<int>);
	heap->insert(17, greaterEq<int>);
	heap->insert(3, greaterEq<int>);
	heap->insert(2, greaterEq<int>);
	heap->insert(7, greaterEq<int>);
	heap->insert(100, greaterEq<int>);

	for (size_t i = 9; i > 0; i--)
	{
		std::cout << heap->toString(i) << heap->getMax(greaterEq<int>) << '\n';
	}*/

	const int MAX_ORDER = 7;
	BinaryHeap<int>* bh = new BinaryHeap<int>();
	for (int o = 1; o <= MAX_ORDER; o++)
	{
		const int n = pow(10, o); // rozmiar danych
		// dodawanie do kopca
		clock_t t1 = clock();
		for (int i = 0; i < n; i++) {
			int so = rand() * rand() % 10000000 + 1; // losowe dane
			bh->insert(so, greaterEq<int>);
		}
		clock_t t2 = clock();
		std::cout << "Sample size = "<< n << "\n";
		std::cout << bh->toString(10);
		std::cout << "Total time of inserting = " << ((t2 - t1) / (double)CLOCKS_PER_SEC) * 1000 << "ms\n";
		std::cout << "Average time of inserting = " << ((t2 - t1) / (double)CLOCKS_PER_SEC) * 1000 / n << "ms\n";
		// wypis na ekran aktualnej postaci kopca ( skrotowej ) oraz pomiarow czasowych
		// p o b i e r a n i e ( i usuwanie ) elementu m a k s y m a l n e g o z kopca
			t1 = clock();
		for (int i = 0; i < n; i++) {
			int polled = bh->getMax(greaterEq<int>); // argument : wskaznik na k o m p a r a t o r
			// e w e n t u a l n y wypis na ekran danych elementu pobranego ( przy malym e k s p e r y m e n c i e )
		}
		t2 = clock();
		std::cout << "Total time of polling = " << ((t2 - t1) / (double)CLOCKS_PER_SEC) * 1000 << "ms\n";
		std::cout << "Average time of polling = " << ((t2 - t1) / (double)CLOCKS_PER_SEC) * 1000 / n << "ms\n\n";
		//std::cout << bh->toString(1);
		// wypis na ekran aktualnej postaci kopca ( kopiec pusty ) oraz pomiarow czasowych
		bh->clear(); // c z y s z c z e n i e kopca ( tak naprawde ,, z r e s e t o w a n i e ’’ tablicy d y n a m i c z n e j o p a k o w a n e j przez kopiec )
	}
	delete bh;

	return 0;
}