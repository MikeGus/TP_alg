#include <iostream>
#include <assert.h>

//2_4. Скользящий максимум.
//Дан массив натуральных чисел A[0..n), n не превосходит 10^8. Так же задан размер некотрого окна
//(последовательно расположенных элементов массива) в этом массиве k, k<=n. Требуется для
//каждого положения окна (от 0 и до n-k) вывести значение максимума в окне. Скорость работы O(n
//log n), память O(k).
//Формат входных данных. Вначале вводится n - количество элементов массива. Затем вводится n
//строк со значением каждого элемента. Затем вводится k - размер окна.
//Формат выходных данных. Разделенные пробелом значения максимумов для каждого положения
//окна.

//functions for work w/ array
namespace my {

template<class T>
void copy(T* dest, T* src, size_t size)
{
    for (size_t i = 0; i < size; ++i) {
        dest[i] = src[i];
    }
}

template<class T>
void swap(T& dest, T& src)
{
    T tmp = src;
    src = dest;
    dest = tmp;
}

template<class T>
void resize(T*& array, size_t size, const float mult)
{
    size_t new_size = size * mult;
    T* new_array = new T[new_size];

    my::copy(new_array, array, size);
    delete[] array;

    array = new_array;
}

}

template<class T>
class Heap {

public:
    Heap();
    ~Heap();

    T& get_elem(size_t pos);
    size_t get_size();

    void sift_up(int pos);
    void sift_down(size_t pos);

    void build(T* array, size_t arr_size);
    void add(T& elem);

    bool is_empty();
    T extract_max();

private:

    T* data;
    size_t capacity;
    size_t size;

    const size_t init_capacity = 10;
    const float mult = 2;
};

template<class T>
Heap<T>::Heap()
{
    data = new T[init_capacity];
    size = 0;
    capacity = init_capacity;
}

template<class T>
Heap<T>::~Heap()
{
    delete[] data;
    size = 0;
    capacity = 0;
}

template<class T>
T& Heap<T>::get_elem(size_t pos)
{
    assert(pos < size);
    return data[pos];
}

template<class T>
size_t Heap<T>::get_size()
{
    return size;
}

template<class T>
void Heap<T>::sift_down(size_t pos)
{
    size_t left = 2 * pos + 1;
    size_t right = 2 * pos + 2;

    size_t largest = pos;
    if (left < size && data[left] > data[pos]) {
        largest = left;
    }
    if (right < size && data[right] > data[largest])
    {
        largest = right;
    }
    if (largest != pos) {
        my::swap(data[pos], data[largest]);
        sift_down(largest);
    }
}

template<class T>
void Heap<T>::sift_up(int pos)
{
    while (pos > 0) {
        int parent = (pos - 1) / 2;
        if (data[pos] <= data[parent]) {
            return;
        }
        my::swap(data[pos], data[parent]);
        pos = parent;
    }
}

template<class T>
void Heap<T>::build(T* array, size_t arr_size)
{
    delete[] data;
    data = new T[arr_size];
    size = arr_size;

    my::copy(data, array, arr_size);

    for (int i = (int)size / 2 - 1; i >= 0; --i) {
        sift_down(i);
    }
}

template<class T>
void Heap<T>::add(T &elem)
{
    if (size <= capacity) {
        my::resize(data, size, mult);
    }
    data[size] = elem;
    sift_up(size);
    size++;
}

template<class T>
bool Heap<T>::is_empty()
{
    return size == 0;
}

template<class T>
T Heap<T>::extract_max()
{
    assert(!is_empty());
    T result = data[0];

    data[0] = data[size - 1];
    size--;

    if (!is_empty()) {
        sift_down(0);
    }

    return result;
}

void get_result(int* result_array, size_t window_size, int* array, size_t size)
{
    Heap<int> heap;

    for (size_t pos = 0; pos < (size - window_size + 1); ++pos) {
        heap.build(array + pos, window_size);
        result_array[pos] = heap.extract_max();
    }

}

int main(void)
{
    size_t size = 0;
    std::cin >> size;

    int* array = new int[size];

    for (size_t i = 0; i < size; ++i) {
        std::cin >> array[i];
    }

    size_t window = 0;
    std::cin >> window;

    int* result_array = new int[size - window + 1];

    get_result(result_array, window, array, size);
    delete[] array;

    for (size_t i = 0; i < size - window + 1; ++i) {
        std::cout << result_array[i] << " ";
    }
    std::cout << std::endl;

    delete[]result_array;
    return 0;
}
