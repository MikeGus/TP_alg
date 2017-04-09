//5_1. Первые k элементов длинной последовательности.
//Дана очень длинная последовательность целых чисел длины n. Требуется вывести в
//отсортированном виде её первые k элементов. Последовательность может не помещаться в
//память. Время работы O(n * log(k)). Память O(k). Использовать слияние.

#include <iostream>

template<class T>
void merge_sort(T* data, size_t begin, size_t end)
{
    if (begin == end) {
        return;
    }

    size_t length = end - begin + 1;
    T* result_data = new T[length];

    size_t mid = (begin + end) / 2;
    merge_sort(data, begin, mid); // quicksort preferred
    merge_sort(data, mid + 1, end);

    size_t i = begin;
    size_t j = mid + 1;

    size_t pos = 0;

    //merging
    while (pos != length) {
        //all parts not checked
        if (i <= mid && j <= end) {
            if (data[i] < data[j]) {
                result_data[pos] = data[i];
                i++;
            }
            else {
                result_data[pos] = data[j];
                j++;
            }
        }
        // left part checked
        else if (i > mid) {
            result_data[pos] = data[j];
            j++;
        }
        //right part checked
        else {
            result_data[pos] = data[i];
            i++;
        }
        pos++;
    }

    for (size_t i = begin; i <= end; ++i) {
        data[i] = result_data[i - begin];
    }
    delete[] result_data;
}

template<class T>
void get_first(T* result, std::istream& input, size_t size, size_t number)
{
    size_t len_buf = (size > number * 2) ? (number * 2) : size;
    T* buffer = new T[len_buf];

    // read first buffer
    for (size_t i = 0; i < len_buf; ++i) {
        input >> buffer[i];
    }
    merge_sort(buffer, 0, len_buf - 1);

    size_t pos = len_buf;

    while (pos < size) {
        size_t i = 0;
        for ( ; i < number && pos < size; ++i, ++pos) {
            input >> buffer[number + i];
        }
        if (pos == size) {
            len_buf -= (number - i);
        }
        merge_sort(buffer, 0, len_buf - 1);
    }

    //getting first half
    for (size_t i = 0; i < number; ++i) {
        result[i] = buffer[i];
    }
    delete[] buffer;
}


int main(void)
{
    size_t number_of_elements = 0;
    std::cin >> number_of_elements;

    size_t number_to_print = 0;
    std::cin >> number_to_print;

    int* result = new int[number_to_print];
    get_first(result, std::cin, number_of_elements, number_to_print);

    for (size_t i = 0; i < number_to_print; ++i) {
        std::cout << result[i] << " ";
    }

    delete[] result;
    return 0;
}
