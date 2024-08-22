#ifndef SERIAL_H__
#define SERIAL_H__

#include "common.h"
#include "my_class.h"
#include <iostream>

// normal type
template<typename T>
inline std::string Serialize(T &a, typename std::enable_if<not_std_string_serializable<T>::value>::type* = nullptr)
{
    std::string res;
    res.append(reinterpret_cast<const char *>(&a), sizeof(T));
    return res;
}

// special for string
template<typename T>
inline std::string Serialize(T &a, typename std::enable_if<is_std_string<T>::value>::type* = nullptr)
{
    std::string res;
    std::size_t len = a.size();
    res.append(Serialize(len));
    res.append(a.data(), len);
    return res;
}

// special for custom class
template<typename T>
inline std::string Serialize(T &a, typename std::enable_if<is_serializable<T>::value>::type* = nullptr)
{
    return a.Serialize();
}

struct OutStream
{
    std::ostringstream oss;

    OutStream() : oss{std::ios::binary} {};

    template<typename T>
    OutStream & operator<< (T &a)
    {
        auto str = Serialize(a);
        oss.write(str.data(), str.size());
        return *this;
    }

    std::string Str()
    {
        return oss.str();
    }

    template<typename T>
    OutStream & operator<< (std::vector<T> &a)
    {
        std::size_t size = a.size();
        auto str = Serialize(size);
        oss.write(str.data(), str.size());

        for (std::size_t i = 0; i < size; i++)
        {
            str = Serialize(a[i]);
            oss.write(str.data(), str.size());
        }
        return *this;
    }

    void Save(const std::string &path)
    {
        std::ofstream file(path, std::ios::binary);
        if (file.is_open())
        {
            file << oss.str();
        }
        file.close();
    }
};

#endif // SERIAL_H__