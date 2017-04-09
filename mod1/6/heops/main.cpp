//6_2. Широкая пирамида.​ Каждый вышележащий слой пирамиды должен быть строго меньше
//нижележащего.
//N ≤ 300.


#include <iostream>
#include <cmath>

//get minimal number of blocks if first row (O(n))
unsigned get_min_bottom(unsigned k)
{
    double n = (sqrt(1.0 + 8.0 * (double)k) - 1.0) / 2.0;
    unsigned n_long = (unsigned) n;

    if (n_long * (n_long + 1) == 2 * k) {
        return n_long;
    }

    return n_long + 1;
}

//need to write with no recursion
unsigned get_num_recursive(unsigned k, unsigned max_bottom)
{
    if (get_min_bottom(k) > max_bottom) {
        return 0;
    }
    if (k <= 2) {
        return 1;
    }

    unsigned sum = 0;
    for (unsigned bottom = max_bottom; bottom > 0; --bottom) {
        sum += get_num_recursive(k - bottom, bottom - 1);
    }

    return sum;
}


//unsigned get_num(unsigned k)
//{
//    if (k <= 2) {
//        return 1;
//    }

//    unsigned* data = new unsigned[k];

//    for (unsigned pos = 3; pos <= k; ++pos)
//    {

//    }

//    delete[] data;
//}


int main(void)
{
    unsigned k = 0;
    std::cin >> k;
    unsigned result = get_num_recursive(k, k);
    std::cout << result << std::endl;
    return 0;
}
