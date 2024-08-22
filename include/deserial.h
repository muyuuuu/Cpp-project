#ifndef DESERIAL_H__
#define DESERIAL_H__

#include "common.h"

// normal type
template<typename T>
inline std::size_t DeSerialize(std::string &str, T &a, typename std::enable_if<not_std_string_serializable<T>::value>::type* = nullptr)
{
    std::memcpy(&a, str.data(), sizeof(T));
    return sizeof(T);
}

template<typename T>
inline std::size_t DeSerialize(std::string &str, std::string &a, typename std::enable_if<is_std_string<T>::value>::type* = nullptr)
{
    std::size_t len;
    DeSerialize(str, len);
    a = str.substr(sizeof(std::size_t), len);
    return sizeof(std::size_t) + len;
}

template<typename T>
inline std::size_t DeSerialize(std::string &str, T &a, typename std::enable_if<is_serializable<T>::value>::type* = nullptr)
{
    return a.DeSerialize(str);
}

struct InStream
{
    std::string str;
    std::size_t m_total;

    InStream() = default;
    InStream(std::string &s)
    {
        str = s;
        m_total = s.size();
    }

    std::size_t size()
    {
        return m_total - str.size();
    }

    template<typename T>
    InStream & operator>> (T &a)
    {
        int size = DeSerialize<T>(str, a);
        str = str.substr(size);
        return *this;
    }

    template<typename T>
    InStream & operator>> (std::vector<T> &a)
    {
        std::size_t size = 0;
        auto res = DeSerialize(str, size);
        str = str.substr(res);
        a.resize(size);

        for (std::size_t i = 0 ; i < size; i++)
        {
            auto size = DeSerialize(str, a[i]);
            str = str.substr(size);
        }

        return *this;
    }

    void Read(const std::string &path)
    {
        std::ifstream file(path, std::ios::binary);
        if (file.is_open())
        {
            file.seekg(0, std::ios::end);
            std::size_t size = file.tellg();
            file.seekg(0, std::ios::beg);
            str.resize(size);

            file.read(&str[0], size);
        }
    }

};


#endif // DESERIAL_H__