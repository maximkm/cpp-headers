#include <algorithm>
#include <iostream>
#include <list>
#include <tuple>
#include <utility>
#include <vector>

template<class KeyType, class ValueType, class Hash = std::hash<KeyType>>
class HashMap {
public:
    typedef typename std::list<std::pair<const KeyType, ValueType>>::iterator iterator;
    typedef typename std::list<std::pair<const KeyType, ValueType>>::const_iterator const_iterator;

private:
    std::list<std::pair<const KeyType, ValueType>> data;
    std::vector<std::pair<iterator, size_t>> link;
    std::vector<bool> check;
    Hash hasher;
    size_t sz{};
    size_t cp = 2;

    void resize() {
        if (2 * sz < cp)
            return;
        cp *= 2;
        this->allocate();
    }

    void allocate(bool clear = false) {
        std::list<std::pair<const KeyType, ValueType>> new_data;
        std::vector<std::pair<iterator, size_t>> new_link(cp);
        std::vector<bool> new_check(cp, false);
        swap(data, new_data);
        swap(link, new_link);
        swap(check, new_check);
        sz = 0;
        if (clear)
            return;
        for (const auto& item : new_data)
            this->insert(item);
    }

public:
    HashMap(Hash _hasher = Hash()) : hasher(_hasher) { this->allocate(); }

    template<class it>
    HashMap(it begin, it end, Hash _hasher = Hash()) : hasher(_hasher) {
        this->allocate();
        while (begin != end)
            this->insert(*begin++);
    }

    HashMap(std::initializer_list<std::pair<KeyType, ValueType>> lol, Hash _hasher = Hash())
        : hasher(_hasher) {
        this->allocate();
        for (const auto& item : lol)
            this->insert(item);
    }

    void insert(std::pair<KeyType, ValueType> lol) {
        size_t idx = hasher(lol.first) % cp;
        auto begin = this->find(lol.first);
        if (begin != data.end())
            return;
        if (!check[idx]) {
            link[idx] = {data.begin(), 0};
            check[idx] = true;
        }
        link[idx].first = data.insert(link[idx].first, lol);
        ++link[idx].second;
        ++sz;
        this->resize();
    }

    void erase(KeyType key) {
        size_t idx = hasher(key) % cp;
        if (!check[idx])
            return;
        auto begin = this->find(key);
        if (begin != data.end()) {
            if (begin == link[idx].first)
                link[idx].first = data.erase(begin);
            else
                data.erase(begin);
            --sz;
            --link[idx].second;
            if (link[idx].second == 0)
                check[idx] = false;
            return;
        }
    }

    Hash hash_function() const { return hasher; }

    iterator find(KeyType key) {
        size_t idx = hasher(key) % cp;
        if (check[idx]) {
            auto begin = link[idx].first;
            size_t cnt = link[idx].second;
            for (size_t id = 0; id < cnt; ++id) {
                if (begin->first == key)
                    return begin;
                ++begin;
            }
        }
        return data.end();
    }

    const_iterator find(KeyType key) const {
        size_t idx = hasher(key) % cp;
        if (check[idx]) {
            auto begin = link[idx].first;
            size_t cnt = link[idx].second;
            for (size_t id = 0; id < cnt; ++id) {
                if (begin->first == key)
                    return begin;
                ++begin;
            }
        }
        return data.end();
    }

    ValueType& operator[](const KeyType& key) {
        auto lol = this->find(key);
        if (lol == data.end()) {
            this->insert({key, {}});
            lol = this->find(key);
        }
        return lol->second;
    }

    const ValueType& at(const KeyType& key) const {
        auto lol = this->find(key);
        if (lol == data.end())
            throw std::out_of_range("");
        return lol->second;
    }

    void clear() { this->allocate(true); }

    size_t size() const { return sz; }
    bool empty() const { return sz == 0; }

    iterator begin() { return data.begin(); }
    iterator end() { return data.end(); }
    const_iterator begin() const { return data.begin(); }
    const_iterator end() const { return data.end(); }

    HashMap& operator=(const HashMap& other) {
        if (&other == this)
            return *this;
        hasher = other.hash_function();
        cp = other.cp;
        this->clear();
        auto begin = other.begin();
        while (begin != other.end())
            this->insert(*begin++);
        return *this;
    }
};
