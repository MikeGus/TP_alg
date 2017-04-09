//4_3.​ Реализуйте стратегию выбора опорного элемента “случайный элемент”. Функцию Partition
//реализуйте методом прохода двумя итераторами от начала массива к концу.

#include <iostream>
#include <ctime>

namespace my {

template<class T>
void swap(T& first, T& second)
{
    T tmp = first;
    first = second;
    second = tmp;
}

template<class T>
int partition(T* data, int begin, int end)
{
    int pivot_pos = begin + rand() % (end - begin);
    T pivot = data[pivot_pos];

    my::swap(data[pivot_pos], data[end]);

    int i = 0; //first elem bigger then pivot
    int j = 0; //first not seen element

    while (j < end) {
        if (data[j] > pivot) {
            j++;
        }
        else {
            my::swap(data[i], data[j]);
            i++;
            j++;
        }
    }
    my::swap(data[i], data[end]);

    return i;
}

template<class T>
int find_order_stat(T* data, size_t size, int pos)
{
    srand(time(0));
    int begin = 0;
    int end = size - 1;

    while (begin < end) {

        int f_pos = partition(data, begin, end);
        if (f_pos == pos) {
            return data[f_pos]; // end of search
        }
        else if (pos > f_pos) { // search right
            begin = f_pos + 1;
        }
        else {
            end = f_pos - 1; // search left
        }
    }

    return data[end];
}
}



int main(void)
{
    size_t size = 0;
    size_t pos = 0;

    std::cin >> size >> pos;

    int* data = new int[size];
    for (size_t i = 0; i < size; ++i) {
        std::cin >> data[i];
    }

    std::cout << my::find_order_stat(data, size, pos);

    delete[] data;

    return 0;
}
