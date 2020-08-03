#include <map>
#include <optional>
#include <stdexcept>
#include <utility>
#include <vector>

template<typename Key1, typename Key2, typename Value>
class BiMap {
private:
    std::vector<Value> data;
    std::map<Key1, size_t> Primary;
    std::map<Key2, size_t> Secondary;

public:
    void Insert(const std::optional<Key1>& key1, const std::optional<Key2>& key2,
                const Value& value) {
        if ((!key1.has_value() && !key2.has_value()) ||
            (key1.has_value() && Primary.find(key1.value()) != Primary.end()) ||
            (key2.has_value() && Secondary.find(key2.value()) != Secondary.end())) {
            throw std::invalid_argument("some text");
        }
        data.push_back(std::move(value));
        if (key1.has_value())
            Primary[key1.value()] = data.size() - 1;
        if (key2.has_value())
            Secondary[key2.value()] = data.size() - 1;
    }

    Value& GetByPrimaryKey(const Key1& key) {
        if (Primary.find(key) == Primary.end())
            throw std::out_of_range("some text");
        return data[Primary[key]];
    }
    const Value& GetByPrimaryKey(const Key1& key) const {
        if (Primary.find(key) == Primary.end())
            throw std::out_of_range("some text");
        return data[Primary[key]];
    }

    Value& GetBySecondaryKey(const Key2& key) {
        if (Secondary.find(key) == Secondary.end())
            throw std::out_of_range("some text");
        return data[Secondary[key]];
    }
    const Value& GetBySecondaryKey(const Key2& key) const {
        if (Secondary.find(key) == Secondary.end())
            throw std::out_of_range("some text");
        return data[Secondary[key]];
    }
};