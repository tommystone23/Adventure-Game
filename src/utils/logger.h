#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <sstream>
#include <string>

class Logger 
{
public:
    Logger() {}
    
    ~Logger() { std::cout << _data << std::endl; }

    template <typename T>
    Logger& operator<<(const T& msg) {
        _data += reinterpret_cast<const char*>(msg);
        return *this;
    }

private:
    std::string _data;
};

#endif // LOGGER_H