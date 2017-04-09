//7_1.​ Атлеты.
//В город N приехал цирк с командой атлетов. Они хотят удивить горожан города N — выстроить из своих тел
//башню максимальной ысоты. Башня — это цепочка атлетов, первый стоит на земле, второй стоит у него на
//плечах, третий стоит на плечах у второго и т.д.
//Каждый атлет характеризуется силой si
//(kg) и массой mi
//(kg). Сила — это максимальная масса, которую
//атлет способен держать у себя на плечах.
//К сожалению ни один из атлетов не умеет программировать, так как всю жизнь они занимались физической
//подготовкой, и у них не было времени на изучение языков программирования. Помогите им, напишите
//программу, которая определит максимальную высоту башни, которую они могут составить.
//Известно, что если атлет тяжелее, то он и сильнее:
//если mi>mj
//, то si
//> sj
//.
//Атлеты равной массы могут иметь различную силу.
//Формат входных данных:
//Вход содержит только пары целых чисел — массу и силу атлетов. Число атлетов 1 ≤ n ≤ 100000. Масса и
//сила являются положительными целыми числами меньше, чем 2000000.
//Формат выходных данных:
//Выход должен содержать натуральное число — максимальную высоту башни.

#include <iostream>

struct Acrobat {

    unsigned mass;
    unsigned strength;

    bool operator<=(Acrobat& other);
};

bool Acrobat::operator <=(Acrobat& other)
{
    if ((mass <= other.mass) && (strength <= other.strength)) {
        return true;
    }
    return false;
}

template<class T>
class Vector {
public:
    Vector();
    ~Vector();
    void push_back(T& value);
    T& operator[](size_t index);
    void qsort(int left, int right);
    int partition(int left, int right);
    void bubblesort();
    size_t get_size();

private:

    T* data;
    size_t size;
    size_t capacity;

    const size_t init_capacity = 5;
    const size_t mult = 2;

    void resize();
    void copy(T* new_data);
};

template<class T>
Vector<T>::Vector()
{
    data = new T[init_capacity];
    capacity = init_capacity;
    size = 0;
}

template<class T>
Vector<T>::~Vector()
{
    delete[] data;
    capacity = 0;
    size = 0;
}

template<class T>
void Vector<T>::resize()
{
    size_t new_capacity = capacity * mult;
    T* new_data = new T[new_capacity];
    copy(new_data);
    delete[] data;
    data = new_data;
    capacity = new_capacity;
}

template<class T>
void Vector<T>::copy(T* new_data)
{
    for (size_t i = 0; i < size; ++i) {
        new_data[i] = data[i];
    }
}

template<class T>
void Vector<T>::push_back(T &value)
{
    if (size >= capacity) {
        resize();
    }
    data[size] = value;
    size++;
}

template<class T>
T& Vector<T>::operator [](size_t index)
{
    return data[index];
}

template<class T>
int Vector<T>::partition(int left, int right)
{
        T pivot = data[right];
        int i = left - 1;
        for (int j = left; j < right; ++j) {
            if (data[j] <= pivot) {
                i++;
                T temp = data[i];
                data[i] = data[j];
                data[j] = temp;
            }
        }
        T temp = data[i + 1];
        data[i + 1] = data[right];
        data[right] = temp;
        return i + 1;
}

template<class T>
void Vector<T>::qsort(int left, int right)
{

    if(left < right){
        int current = partition(left, right);
        qsort(left, current - 1);
        qsort(current, right);
    }
}

template<class T>
void Vector<T>::bubblesort()
{
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = i + 1; j < size; ++j) {
            if (data[j] < data[i]) {
                Acrobat temp = data[j];
                data[j] = data[i];
                data[i] = temp;
            }
        }
    }
}

template<class T>
size_t Vector<T>::get_size()
{
    return size;
}

int main(void)
{
    Acrobat buf;
    Vector<Acrobat> vector;
    // reading elements
    do {
        std::cin >> buf.mass;
        if (!std::cin.fail()) {
            std::cin >> buf.strength;
            if (!std::cin.fail()) {
                vector.push_back(buf);
            }
        }
    } while (!std::cin.fail());

    // sorting vector
    size_t size = vector.get_size();
    vector.qsort(0, size - 1);

    // greedy algorithm from rear end
    unsigned curr_mass = 0;
    unsigned curr_height = 0;
    for (size_t i = 0; i < size; ++i) {
        if (vector[i].strength >= curr_mass) {
            curr_height++;
            curr_mass += vector[i].mass;
        }
    }

    // result
    std::cout << curr_height;
    return 0;
}
