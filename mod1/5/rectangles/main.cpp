//5_3. Прямоугольники.
//Дана последовательность N прямоугольников различной ширины и высоты (wi
//,hi
//). Прямоугольники
//расположены, начиная с точки (0, 0), на оси ОХ вплотную друг за другом (вправо). Требуется найти M -
//площадь максимального прямоугольника (параллельного осям координат), который можно вырезать из этой
//фигуры.
//Время работы - O(n).
//Формат входных данных. В первой строке задано число N (1 ≤ N ≤ 10000). Далее идет N строк. В каждой
//строке содержится два числа width и height: ширина и высота i-го прямоугольника. (0 < width ≤ 10000,
//0 ≤ height ≤ 10000)
//Формат выходных данных. вывести число M. (0 ≤ M ≤ 109).

#include <iostream>
#include <assert.h>

struct Rectangle {

    size_t width;
    size_t height;
};

template<class T>
class Stack {

    public:
        Stack();
        ~Stack();
        T pop();
        T peek();
        void push(T& val);
        bool is_empty();

    private:
        T* data;
        size_t capacity;
        size_t size;

        const size_t init_capacity = 5;
        const size_t mult = 2;

        void resize();
        void copy(T* new_data);
};

template<class T>
Stack<T>::Stack()
{
    size = 0;
    data = new T[init_capacity];
    capacity = init_capacity;
}

template<class T>
Stack<T>::~Stack()
{
    delete[] data;
    data = nullptr;
    size = capacity = 0;
}

template<class T>
void Stack<T>::push(T& val)
{
    if (size >= capacity) {
        resize();
    }
    data[size] = val;
    size++;
}

template<class T>
T Stack<T>::pop()
{
    assert(size > 0);
    size--;
    return data[size];
}

template<class T>
T Stack<T>::peek()
{
    assert(size > 0);
    return data[size - 1];
}

template<class T>
void Stack<T>::resize()
{
    size_t new_capacity = capacity * mult;
    T* new_data = new T[new_capacity];
    copy(new_data);
    capacity = new_capacity;
    delete[] data;
    data = new_data;
}

template<class T>
void Stack<T>::copy(T* new_data)
{
    for (size_t i = 0; i < size; ++i) {
        new_data[i] = data[i];
    }
}

template<class T>
bool Stack<T>::is_empty()
{
    return size <= 0;
}

int main(void)
{
    //entering number of rectangles
    size_t number = 0;
    std::cin >> number;

    Stack<Rectangle> stack;

    size_t max_area = 0;
    size_t curr_height = 0;

    //working with rectangles
    for (size_t i = 0; i < number; ++i) {
        //entering sizes of rectangle
        Rectangle rectangle;
        std::cin >> rectangle.width >> rectangle.height;

        //if it's taller then previous -> push
        if (rectangle.height >= curr_height) {
            stack.push(rectangle);
            curr_height = rectangle.height;
        }//else extract all previous rectangles higher then this
        else {
            size_t d_width = 0; //width of extracted segments
            Rectangle pop_rect = stack.peek();//looking at last rectangle

            //extracting all rectangles
            while ((pop_rect.height >= rectangle.height) && !stack.is_empty()) {
                pop_rect = stack.pop();
                d_width += pop_rect.width;
                size_t rect_area = pop_rect.height * d_width;
                if (rect_area > max_area) {
                    max_area = rect_area;
                }
                //checking if we need to extract last rectangle
                if (!stack.is_empty()) {
                    pop_rect = stack.peek();
                }
            }

            //forming long last rectangle
            rectangle.width += d_width;
            curr_height = rectangle.height;
            stack.push(rectangle);
        }
    }

    //extracting all elements
    size_t d_width = 0;
    while (!stack.is_empty()) {
        Rectangle pop_rect = stack.pop();
        d_width += pop_rect.width;
        size_t rect_area = pop_rect.height * d_width;
        if (rect_area > max_area) {
            max_area = rect_area;
        }
    }

    std::cout << max_area;
    return 0;
}
