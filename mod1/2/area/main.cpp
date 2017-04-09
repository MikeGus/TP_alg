//2_2. ​Вычислить площадь выпуклого n-угольника, заданного координатами своих вершин. Вначале вводится
//количество вершин, затем последовательно целочисленные координаты всех вершин в порядке обхода
//против часовой стрелки.
//n < 1000, координаты < 10000.

#include <iostream>
#include <cmath>


struct Point {

    int x;
    int y;
};

//calculating double area of trap between two points
int double_trap_area(Point* first_point, Point* second_point)
{
    return (second_point->x - first_point->x) * (second_point->y + first_point->y);
}


int get_double_area(Point* points, size_t point_num)
{
    //check for invalid data
    if (point_num < 3) {
        return 0;
    }

    //calculating area for last and first points
    Point* end_marker = points + point_num - 1;
    int area = double_trap_area(end_marker, points);

    Point* first_ptr = points;
    Point* second_ptr = points + 1;

    //calculating area
    while (first_ptr != end_marker) {
        area += double_trap_area(first_ptr++, second_ptr++);
    }

    return abs(area);
}


int main(void)
{
    size_t point_num = 0;
    std::cin >> point_num;

    Point* points = new Point[point_num];
    Point* p_ptr = points;

    for (size_t i = 0; i < point_num; ++i) {
        std::cin >> p_ptr->x;
        std::cin >> p_ptr->y;
        p_ptr++;
    }

    double area = get_double_area(points, point_num) / 2.0;
    delete[] points;

    std::cout << area;
    return 0;
}
