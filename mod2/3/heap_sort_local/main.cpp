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

    friend std::istream& operator>>(std::istream& input, Customer& data);
    friend std::ostream& operator<<(std::ostream& output, Customer& data);
    bool operator<(const Customer& other) const;
    bool operator>(const Customer& other) const;
};

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
    if (in != other.in) {
        return in < other.in;
    }
    else {
        return out < other.out;
    }
}
bool Customer::operator>(const Customer& other) const
{
    if (in != other.in) {
        return in > other.in;
    }
    else {
        return out > other.out;
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

int main(void)
{
    size_t number = 0;
    std::cin >> number;
    Customer* data = new Customer[number];
    my::read_array(data, number, std::cin);

    build(data, number);
    sort(data, number);



    delete[] data;
    return 0;
}
