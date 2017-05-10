//1_2.​ Для разрешения коллизий используйте двойное хеширование.

#include <iostream>
#include <string>
#include <cstring>
#include <cmath>

const size_t __init_size = 8;
const char _deleted[] = "$$$$$$$$";

const char add_hash = '+';
const char del_hash = '-';
const char check_hash = '?';


class hash_1 {
public:
    size_t operator() (std::string& key, size_t a, size_t M) const
    {
        size_t weight = 0;
        for (const char ch : key) {
            weight = weight * a + ch;
        }
        return weight % M;
    }
};

class hash_2 {
public:
    size_t operator ()(std::string& key, size_t a, size_t M) const
    {
        size_t weight = 0;
        for (auto it = key.rbegin(); it != key.rend(); ++it) {
            weight = weight * a + *it;
        }

        return weight % M;
    }
};

class hash {
public:
    size_t operator ()(std::string& key, size_t M, size_t i) const
    {
        hash_1 func_1;
        hash_2 func_2;
        size_t a_1 = M / 2 - 1;
        size_t a_2 = a_1 + 2;
        size_t pos = (func_1(key, a_1, M) + i * (2 * func_2(key, a_2, M) + 1)) % M;
        return pos;
    }
};

class hashtable {
public:
    hashtable(size_t init_size=__init_size);
    virtual ~hashtable();

    bool has(std::string& key) const;
    void add(std::string& key);
    bool del(std::string& key);

    size_t size() const;
    size_t capacity() const;

    void print() const;

private:
    std::string* _data;
    size_t _size;
    size_t _capacity;
    hash function;

    bool _rehash_factor() const;
    void _rehash();

    const size_t _resize_multiplificator = 2;

    const double _rehash_coefficient = 0.75;
};

hashtable::hashtable(size_t init_size)
{
    if (init_size != 0) {
        _data = new std::string[init_size];
    }
    _capacity = init_size;
    _size = 0;
}

hashtable::~hashtable()
{
    if (_data) {
        delete[] _data;
    }
}

//getters
size_t hashtable::size() const
{
    return _size;
}

size_t hashtable::capacity() const
{
    return _capacity;
}

bool hashtable::_rehash_factor() const
{
    return (_size / _capacity) > _rehash_coefficient;
}

void hashtable::_rehash()
{
    size_t old_capacity = _capacity;

    _capacity *= _resize_multiplificator;
    std::string* data_buffer = new std::string[_capacity];
    std::swap(data_buffer, _data);

    for (size_t i = 0; i < old_capacity; ++i) {
        if (!data_buffer[i].empty() && (data_buffer[i] != _deleted)) {
            add(data_buffer[i]);
        }
    }

    delete[] data_buffer;
}

bool hashtable::has(std::string& key) const
{
    for (size_t i = 0; i < _capacity; ++i) {
        size_t pos = function(key, _capacity, i);
        if (_data[pos].empty()) {
            return false;
        }
        if (key == _data[pos]) {
            return true;
        }
    }
    return false;
}

void hashtable::add(std::string& key)
{
    if (_rehash_factor()) {
        _rehash();
    }
    for (size_t i = 0; i < _capacity; ++i) {
        size_t pos = function(key, _capacity, i);
        if (_data[pos].empty() || _data[pos] == _deleted) {
            _data[pos] = key;
            ++_size;
            break;
        }
    }
}

bool hashtable::del(std::string& key)
{
    for (size_t i = 0; i < _capacity; ++i) {
        size_t pos = function(key, _capacity, i);
        if (_data[pos].empty()) {
            return false;
        }
        if (_data[pos] == key) {
            _data[pos] = _deleted;
            --_size;
            return true;
        }
    }
    return false;
}

void hashtable::print() const
{
    std::cout << "table:" << std::endl;
    std::cout << "SIZE: " << _size << " CAPACITY: " << _capacity << std::endl;
    for (size_t i = 0; i < _capacity; ++i) {
        std::cout << i << " : " << _data[i] << std::endl;
    }
}

bool read_command(std::istream& in, hashtable& table)
{
    char cmd = 0;
    in >> cmd;
    if (in.fail()) {
        return false;
    }

    std::string buf;
    in >> buf;

    switch (cmd) {
    case add_hash:
        if (!table.has(buf)) {
            table.add(buf);
        }
        else {
            std::cout << "FAIL" << std::endl;
            return true;
        }
        break;
    case del_hash:
        if (table.has(buf)) {
            table.del(buf);
        }
        else {
            std::cout << "FAIL" << std::endl;
            return true;
        }
        break;
    case check_hash:
        if (!table.has(buf)) {
            std::cout << "FAIL" << std::endl;
            return true;
        }
    }

    std::cout << "OK" << std::endl;
    return true;
}

int main(void)
{
    hashtable table;

    while (read_command(std::cin, table)) {
    }

    return 0;
}
