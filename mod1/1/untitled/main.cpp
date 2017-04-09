//1_4. ​Дано натуральное число N. Представить N в виде A + B, так, что НОД(A, B) максимален, A ≤ B. Вывести
//A и B. Если возможно несколько ответов - вывести ответ с минимальным A.
//n ≤ 107


#include <iostream>


unsigned long get_a(unsigned long n)
{
    if (n <= 1) { // if n is 1 or 0
        return 0;
    }

    if (!(n % 2)) { // if n is even
        return n / 2;
    }

    for (unsigned mult = 3; mult < n / 2; mult += 2) { //see n as mult * a
        unsigned a = n / mult;
        if (a * mult == n) {
            return a;
        }
    }

    return 1;
}


int main(void)
{
    unsigned long number = 1;
    std::cin >> number;

    unsigned long a = get_a(number);
    unsigned long b = number - a;

    std::cout << a << " " << b << std::endl;

    return 0;
}
