//6_2. Широкая пирамида.​ Каждый вышележащий слой пирамиды должен быть строго меньше
//нижележащего.
//N ≤ 300.

#include <iostream>
#include <cstring>
#include <inttypes.h>

//creating square table with size n
uint64_t** create_table(size_t n)
{
    uint64_t** table = new uint64_t*[n + 1];
    for (size_t i = 0; i <= n; ++i) {
        table[i] = new uint64_t[n + 1];
    }

    return table;
}

//destroying table
void del_table(uint64_t**& table, size_t n)
{
    for (size_t i = 0; i < n + 1; ++i) {
        delete[] table[i];
    }
    delete[] table;
}

//initializing table
void form_table(uint64_t** table, size_t n)
{
    //values of first 2 strings
    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j <= n; ++j) {
            table[i][j] = 1;
        }
    }
    table[1][0] = 0;
    //other initialized w/ max val
    for (size_t i = 2; i <= n; ++i) {
        for (size_t j = 0; j <=n; ++j) {
            table[i][j] = UINT64_MAX;
        }
    }
}

uint64_t get_number(uint64_t** table, size_t number, size_t bottom)
{
    // check if pyramid is possible
    if ((2 * number) > (bottom + 1) * bottom) {
        return 0;
    }

    // 0 blocks
    if (number == 0) {
        return 1;
    }

    size_t val = 0;
    if (table[number][bottom] != UINT64_MAX) {
        val = table[number][bottom];
    }
    else {
        if (number >= bottom) {
            table[number][bottom] = get_number(table, number - bottom, bottom - 1)\
                    + get_number(table, number, bottom - 1);
        }
        else {
            table[number][bottom] = get_number(table, number, bottom - 1);
        }
        val = table[number][bottom];
    }

    return val;
}

int main(void)
{
    size_t number = 0;
    std::cin >> number;

    uint64_t** table = create_table(number);
    form_table(table, number);

    uint64_t result = get_number(table, number, number);

    del_table(table, number);
    std::cout << result << std::endl;
    return 0;
}
