//4_1. ​Реализовать очередь с динамическим зацикленным буфером.

#include <iostream>

//operations
const int pop = 2;
const int push = 3;

template<class T>
class Queque {

    public:
        //constructor and destructor
        Queque();
        ~Queque();

        //interface
        T pop_front();
        void push_back(T& value);

    private:
        //const
        const int init_val = 2;
        const int mult = 2;
        const int def_ret = -1;

        //params
        size_t size;
        size_t capacity;

        //vault
        T* data;

        //pointers
        T* head; //ptr to head
        T* tail; //ptr after tail

        T* begin;//beginning of array
        T* end; //ending of array

        void resize();
        void copy(T*& new_data);
};

template<class T>
Queque<T>::Queque()
{
    size = 0;
    capacity = init_val;
    data = new T[init_val];
    head = data;
    tail = data;
    begin = data;
    end = data + capacity;
}

template<class T>
Queque<T>::~Queque()
{
    delete[] data;
    head = nullptr;
    tail = nullptr;
    begin = nullptr;
    end = nullptr;
    size = 0;
    capacity = 0;
}

template<class T>
T Queque<T>::pop_front()
{
    if (size == 0) {
        return def_ret;
    }

    T ret_value = *head;
    if ((head + 1) != end) {
        head++;
    }
    else {
        head = begin;
    }

    size--;

    return ret_value;
}


template<class T>
void Queque<T>::push_back(T& value)
{
    if (size >= capacity) {
        resize();
    }
    if (tail != end) {
        tail++;
    }
    else {
        tail = begin + 1;
    }
    *(tail - 1) = value;
    size++;
}


template<class T>
void Queque<T>::copy(T*& new_data)
{
    T* src_ptr = head;
    T* dest_ptr = new_data;

    if (!size) {
        return;
    }

    if (tail <= head) {
        while (src_ptr != end) {
            (*dest_ptr) = (*src_ptr);
            dest_ptr++;
            src_ptr++;
        }
        src_ptr = begin;
    }

    while (src_ptr != tail) {
        (*dest_ptr) = (*src_ptr);
        dest_ptr++;
        src_ptr++;
    }
}

template<class T>
void Queque<T>::resize()
{
    int new_capacity = 0;
    if (capacity) {
        new_capacity = capacity * mult;
    }
    else {
        new_capacity = init_val;
    }

    T* new_data = new T[new_capacity];
    copy(new_data);

    head = new_data;
    tail = new_data + size;
    begin = new_data;
    end = new_data + new_capacity;

    capacity = new_capacity;
    data = new_data;
}

struct Cmd {
    int cmd;
    int val;
};


int main(void)
{
    int num_of_cmd = 0;
    std::cin >> num_of_cmd;

    bool fail = false;
    Queque<int> my_queque;

    for (int i = 0; i < num_of_cmd; ++i) {
        Cmd buf_command;
        buf_command.cmd = 0;
        buf_command.val = -1;

        std::cin >> buf_command.cmd >> buf_command.val;
        if (buf_command.cmd == push) {
            my_queque.push_back(buf_command.val);
        }
        else if (buf_command.cmd == pop) {
            if (my_queque.pop_front() != buf_command.val) {
                fail = true;
            }
        }
    }

    if (fail) {
        std::cout << "NO" << std::endl;
    }
    else {
        std::cout << "YES" << std::endl;
    }

    return 0;
}
