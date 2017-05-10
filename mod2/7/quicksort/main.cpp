#include <iostream>
#include <vector>


template <class T>
void read_array(std::vector<T>& data, std::istream& input)
{
    int value = 0;
    while (true) {
        input >> value;
        if (input.fail()) {
            break;
        }
        data.push_back(value);
    }
}


template <class T>
void print_ten(std::vector<T>& data, std::ostream& output)
{
    for (size_t i = 0; i < data.size(); ++i) {
        if ((i + 1) % 10 == 0) {
            output << data[i] << " ";
        }
    }
}


template <class T>
size_t partition(std::vector<T>& data, size_t begin, size_t right)
{

}


int main()
{
    std::vector<int> data;
    read_array(data, std::cin);

    print_ten(data, std::cout);

    return 0;
}
