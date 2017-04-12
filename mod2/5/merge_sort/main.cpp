//5_1. Первые k элементов длинной последовательности.
//Дана очень длинная последовательность целых чисел длины n. Требуется вывести в
//отсортированном виде её первые k элементов. Последовательность может не помещаться в
//память. Время работы O(n * log(k)). Память O(k). Использовать слияние.


#include <iostream>


template<class T>
void read_array(T* array, size_t size, std::istream& input)
{
    for (size_t i = 0; i < size; ++i) {
        input >> array[i];
    }
}


template<class T>
void print_array(std::ostream& output, T* array, size_t size)
{
    for (size_t i = 0; i < size; ++i) {
        output << array[i] << " ";
    }
    output << std::endl;
}


template<class T>
void copy_array(T* dest, T* src, size_t size)
{
    for (size_t i = 0; i < size; ++i) {
        dest[i] = src[i];
    }
}


template<class T>
void merge(T* left, T* right, size_t size_left, size_t size_right)
{
    T* buffer = new T[size_left];
    copy_array(buffer, left, size_left);

    size_t left_index = 0;
    size_t right_index = 0;
    size_t result_index = 0;

    for ( ; left_index < size_left && right_index < size_right; ++result_index) {
        if (buffer[left_index] < right[right_index]) {
            left[result_index] = buffer[left_index];
            left_index++;
        }
        else {
            left[result_index] = right[right_index];
            right_index++;
        }
    }

    if (left_index < size_left) {
        copy_array(left + result_index, buffer + left_index, size_left - left_index);
    }
    else {
        copy_array(left + result_index, right + right_index, size_right - right_index);
    }

    delete buffer;
}


template<class T>
void merge_sort(T* data, size_t begin, size_t end)
{
    size_t length = end - begin;
    size_t half_length = length / 2;
    if (length <= 1) {
        return;
    }

    size_t mid = begin + half_length;

    merge_sort(data, begin, mid);
    merge_sort(data, mid, end);

    merge(data + begin, data + mid, mid - begin, end - mid);
}


void print_first(std::ostream& output, std::istream& input, size_t length, size_t to_print)
{
    size_t array_length = to_print;
    if (array_length > length) {
        array_length = length;
    }

    int* left = new int[array_length * 2];
    int* right = left + array_length;

    read_array(left, array_length * 2, input);


    merge_sort(left, 0, array_length * 2);
    size_t managed = array_length * 2;

    while (managed < length) {
        if (length - managed < array_length) {
            array_length = length - managed;
        }
        read_array(right, array_length, input);
        merge_sort(right, 0, array_length);
        merge(left, right, to_print, array_length);
        managed += array_length;
    }

    print_array(output, left, to_print);

    delete[] left;
}


int main(void)
{
    size_t number = 0;
    size_t to_print = 0;
    std::cin >> number >> to_print;

    print_first(std::cout, std::cin, number, to_print);

    return 0;
}
