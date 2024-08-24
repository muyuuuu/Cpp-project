#ifndef DUMP_COMMON_H__
#define DUMP_COMMON_H__

#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include <vector>
#include <type_traits>
#include <cstddef>

struct Serializable
{
    virtual std::string Serialize() = 0;
    virtual std::size_t DeSerialize(std::string &) = 0;
    virtual void PrintParam() = 0;
};

template<typename T>
struct is_std_string : std::is_same<T, std::string> {};

template<typename T>
struct is_serializable : std::is_base_of<Serializable, T> {};

template<typename T>
struct not_std_string_serializable : std::integral_constant<bool, !is_serializable<T>::value && !is_std_string<T>::value> {};

#endif // DUMP_COMMON_H__