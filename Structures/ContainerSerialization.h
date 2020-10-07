#include <iostream>
#include <map>
#include <string>
#include <vector>

template<typename T>
void Serialize(T pod, std::ostream& out);

void Serialize(const std::string& str, std::ostream& out);

template<typename T>
void Serialize(const std::vector<T>& data, std::ostream& out);

template<typename T1, typename T2>
void Serialize(const std::map<T1, T2>& data, std::ostream& out);

template<typename T>
void Deserialize(std::istream& in, T& pod);

void Deserialize(std::istream& in, std::string& str);

template<typename T>
void Deserialize(std::istream& in, std::vector<T>& data);

template<typename T1, typename T2>
void Deserialize(std::istream& in, std::map<T1, T2>& data);

template<typename T>
void Serialize(T pod, std::ostream& out) {
    out.write(reinterpret_cast<char*>(&pod), sizeof(pod));
}

void Serialize(const std::string& str, std::ostream& out) {
    Serialize(str.size(), out);
    for (const auto& item : str)
        Serialize(item, out);
}

template<typename T>
void Serialize(const std::vector<T>& data, std::ostream& out) {
    Serialize(data.size(), out);
    for (const auto& item : data)
        Serialize(item, out);
}

template<typename T1, typename T2>
void Serialize(const std::map<T1, T2>& data, std::ostream& out) {
    Serialize(data.size(), out);
    for (const auto& [key, value] : data) {
        Serialize(key, out);
        Serialize(value, out);
    }
}

template<typename T>
void Deserialize(std::istream& in, T& pod) {
    in.read(reinterpret_cast<char*>(&pod), sizeof(T));
}

void Deserialize(std::istream& in, std::string& str) {
    size_t sz;
    Deserialize(in, sz);
    str.resize(sz);
    for (char& item : str)
        Deserialize(in, item);
}

template<typename T>
void Deserialize(std::istream& in, std::vector<T>& data) {
    size_t sz;
    Deserialize(in, sz);
    data.resize(sz);
    for (T& item : data)
        Deserialize(in, item);
}

template<typename T1, typename T2>
void Deserialize(std::istream& in, std::map<T1, T2>& data) {
    size_t sz;
    Deserialize(in, sz);
    for (size_t i = 0; i < sz; ++i) {
        T1 key;
        Deserialize(in, key);
        Deserialize(in, data[key]);
    }
}