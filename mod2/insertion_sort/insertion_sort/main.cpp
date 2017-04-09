//1_2. Ломаная 1.
//Задано N точек на плоскости. Указать (N-1)-звенную несамопересекающуюся незамкнутую
//ломаную, проходящую через все эти точки.
//Указание: стройте ломаную в порядке возрастания x-координаты. Если имеются две точки с
//одинаковой x-координатой, то расположите раньше ту точку, у которой y-координата меньше.

#include <iostream>

struct Point {
    int x;
    int y;
};

void input(Point* array, size_t size, std::istream& stream)
{
    Point buffer;
    for (size_t i = 0; i < size; ++i) {
        stream >> buffer.x >> buffer.y;
        array[i]  = buffer;
    }
}

void output(std::ostream& stream, Point* array, size_t size)
{
    for (size_t i = 0; i < size; ++i) {
        stream << array[i].x << " " << array[i].y << std::endl;
    }
}

int cmp(const Point& first, const Point& second)
{
    if (first.x > second.x) {
        return 1;
    }
    else if (second.x > first.x) {
        return -1;
    }
    else {
        if (first.y > second.y) {
            return 1;
        }
        else if (second.y > first.y) {
            return -1;
        }
        else {
            return 0;
        }
    }
}

void insertion_sort(Point* array, size_t size, int (*cmp)(const Point& first, const Point& second))
{
    for (int i = 1; i < (int)size; ++i) {
        Point tmp = array[i];
        int j = i - 1;
        //shifting elements bigger then tmp to the right
        for  ( ; j >= 0 && cmp(tmp, array[j]) == -1; --j) {
            array[j + 1] = array[j];
        }
        //placing tmp at the right place
        array[j + 1] = tmp;
    }
}



int main(void)
{

    size_t size = 0;
    std::cin >> size;

    Point* array = new Point[size];

    input(array, size, std::cin);

    insertion_sort(array, size, cmp);

    output(std::cout, array, size);

    delete[] array;
    return 0;
}
