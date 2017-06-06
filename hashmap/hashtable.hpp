#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP
#include <cstddef>
#include <algorithm>
#include <vector>
#include <utility>
#include <list>
#include <vector>
#include <stdexcept>

namespace customHashtable 
{

template <typename TKey, typename TVal>
class hashtable 
{

using THashEntry = std::pair<TKey, TVal>;
using TSlot = std::list<THashEntry>;
using TContents = std::vector<TSlot>;

private:
    TContents contents;
    size_t maxCountToResize;
    const double maxLoadFactor;
    size_t count;

public:
    hashtable(size_t initialSize=8, double maxLoadFactor_=0.75):
        maxLoadFactor(maxLoadFactor_),
        maxCountToResize(static_cast<size_t>(initialSize*maxLoadFactor_)),
        contents(TContents{initialSize}),
        count(0u)
    {
        if (maxLoadFactor < 0) {
            throw std::logic_error("maxLoadFactor<0");
        }

        if (initialSize < 1) {
            throw std::logic_error("initialSize<1");
        }
    }

    size_t calcHashCode(const TKey& arg) const {
        return (arg % contents.size());    
    }
    
    void rehash() {
        TContents oldContents = contents;
        contents.clear();
        contents.reserve(2*oldContents.size());
        std::for_each(oldContents.begin(), oldContents.end(),
                [this] (const TSlot& slot) {
                    std::for_each(slot.begin(), slot.end(),
                            [this] (const THashEntry& entry) { 
                                put(entry.first, entry.second); 
                            }
                    );
                }
        );
        maxCountToResize*=2;
    }



public:
    void put(const TKey& key, const TVal& val) {
        size_t hashCode = calcHashCode(key);
        auto& entries = contents[hashCode];
        auto result = std::find_if(entries.begin(), entries.end(), [&key](const THashEntry& arg) {return arg.first == key;});
        THashEntry entry = THashEntry(key, val);
        if (result == entries.end()) {
            entries.emplace_front(entry);
            ++count;
        } else {
            *result = entry;
        }

        if (count >= maxCountToResize) {
            rehash();
        }
    }

    const TVal get(TKey key) const {
        size_t hashCode = calcHashCode(key);

        auto& entries = contents[hashCode];
        auto result = std::find_if(entries.begin(), entries.end(), [&key](const THashEntry& arg) {return arg.first == key;});
        if (result == entries.end()) {
            throw std::logic_error("Tried to access nonexistant key"); 
        }
        return result->second;
    }

    const std::vector<TKey> getKeys () const {
        std::vector<TKey> ret {};
        for (const auto& el : contents) {
            if (!el.empty()) {
                std::for_each(el.begin(), el.end(), [&ret] (const auto& el) { ret.push_back(el.first); });
            }
        }
        return ret;
    }

    void remove(TKey key) {
        auto& entries = contents[calcHashCode(key)];
        auto it = std::remove_if(entries.begin(), entries.end(), [&key] (const THashEntry& x) { return x.first == key; });
        if (it == entries.end()) {
            throw std::logic_error("Tried to remove nonexistant key");
        }
        entries.erase(it, entries.end());
        --count;
    }

    size_t size() {
        return count;
    }
}; //class hashtable

}//namespace custmhashtable
#endif //HASHTABLE_HPP
