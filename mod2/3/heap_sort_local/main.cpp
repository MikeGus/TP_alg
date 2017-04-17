#include <iostream>
#include <assert.h>

//3_1. Реклама.
//В супермаркете решили оптимизировать показ рекламы. Известно расписание прихода и ухода
//покупателей (два целых числа). Каждому покупателю необходимо показать минимум 2 рекламы.
//Рекламу можно транслировать только в целочисленные моменты времени. Покупатель может
//видеть рекламу от момента прихода до момента ухода из магазина.
//В каждый момент времени может показываться только одна реклама. Считается, что реклама
//показывается мгновенно. Если реклама показывается в момент ухода или прихода, то считается,
//что посетитель успел её посмотреть. Требуется определить минимальное число показов рекламы.

struct Customer {

    int in;
    int out;

    int length();
    friend std::istream& operator>>(std::istream& input, Customer& data);
    friend std::ostream& operator<<(std::ostream& output, Customer& data);
    bool operator<(const Customer& other) const;
    bool operator>(const Customer& other) const;
};

int Customer::length()
{
    return out - in;
}

std::istream& operator>>(std::istream& input, Customer& data)
{
    input >> data.in >> data.out;
    return input;
}

std::ostream& operator<<(std::ostream& output, Customer& data)
{
    output << data.in << " " << data.out << std::endl;
    return output;
}

bool Customer::operator<(const Customer& other) const
{
    if (out != other.out) {
        return out < other.out;
    }
    else {
        return in > other.in;
    }
}
bool Customer::operator>(const Customer& other) const
{
    if (out != other.out) {
        return out > other.out;
    }
    else {
        return in < other.in;
    }
}

//functions for work with array
namespace my {

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
        output << array[i];
    }
}

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
void sift_down(T* data, size_t size, size_t pos)
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
        sift_down(data, size, largest);
    }
}

template<class T>
void sift_up(T* data, size_t size, int pos)
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
void build(T* data, size_t size)
{
    for (int i = (int)size / 2 - 1; i >= 0; --i) {
        sift_down(data, size, i);
    }
}

template<class T>
void add(T& elem, T* data, size_t& size)
{
    my::resize(data, size, size + 1);
    data[size] = elem;
    sift_up(data, size, size);
    size++;
}

template<class T>
void sort(T* data, size_t size)
{
    assert(size);

    while (size) {
        size--;
        my::swap(data[size], data[0]);
        sift_down(data, size, 0);
    }
}

size_t get_result(Customer* data, size_t size)
{
    // data is sorted by time out
    // data with equal time in is sorted by time in

    //empty array
    if (size == 0) {
        return 0;
    }

    //not empty array
    size_t result = 2;

    //place two points
    int right_point = data[0].out;
    int left_point = right_point - 1;

    for (size_t pos = 1; pos != size; ++pos) {
        //if both points inside
        if (left_point >= data[pos].in && right_point <= data[pos].out) {
        }
        //if only one point inside
        else if (right_point >= data[pos].in && right_point <= data[pos].out) {
            left_point = right_point;
            right_point = data[pos].out;
            result += 1;
        }
        //if no points inside
        else {
            right_point = data[pos].out;
            left_point = right_point - 1;
            result += 2;
        }
    }


    return result;
}

int main(void)
{
    size_t number = 0;
    std::cin >> number;

    if (number < 1) {
        std::cout << 0;
        return 0;
    }
    Customer* data = new Customer[number];
    my::read_array(data, number, std::cin);

    build(data, number);
    sort(data, number);

    size_t result = get_result(data, number);

    std::cout << result;

    delete[] data;
    return 0;
}
