//​Дан отсортированный массив целых чисел A[0..n-1] и массив целых чисел B[0..m-1]. Для каждого
//элемента массива B[i] найдите минимальный индекс k минимального элемента массива A, равного или
//превосходящего B[i]: A[k] >= B[i]. Если такого элемента нет, выведите n. Время работы поиска k для каждого
//элемента B[i]: O(log(k)).

#include <iostream>


void find_bounds(int* array, size_t size, int elem, unsigned& begin, unsigned& end)
{
    unsigned step = 1;
    unsigned index = 0;

    while ((array[index] < elem) && (index < size)) {
        index += step;
        step *= 2;
    }

    end = index < size ? index : size - 1;
    begin = index - step / 2;
}


unsigned find_index(int* array, size_t size, int elem)
{
    if(array[size - 1] < elem) {
        return size;
    }

    int* first = array;
    int* last = array + size - 1;

    //binary search
    while (first < last) {
        int* mid = first + (last - first) / 2;
        if (elem <= (*mid)) {
            last = mid;
        }
        else {
            first = mid + 1;
        }
    }

    return (*first) >= elem ? (first - array) : (last - array);
}

int main(void)
{
    size_t n = 0;
    size_t m = 0;

    std::cin >> n;
    std::cin >> m;

    int* A = new int[n];
    int* B = new int[m];

    int* a_ptr = A;
    int* a_end = A + n;
    while (a_ptr != a_end){
        std::cin >> *a_ptr;
        a_ptr++;
    }

    int* b_ptr = B;
    int* b_end = B + m;
    while (b_ptr != b_end) {
        std::cin >> *b_ptr++;
    }

    b_ptr = B;
    while (b_ptr != b_end) {
        unsigned begin = 0;
        unsigned end = 1;
        find_bounds(A, n, *b_ptr, begin, end);
        unsigned result = begin + find_index(A + begin, end - begin + 1, *b_ptr);
        std::cout << result << std::endl;
        b_ptr++;
    }

    delete[] A;
    delete[] B;

    return 0;
}
