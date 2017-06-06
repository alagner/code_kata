#include "hashtable.hpp"
#include <stdint.h>
#include <iostream>
#include <vector>
#include <iterator>

int
main(int argc, char* const argv[]) {
    using ht = customHashtable::hashtable<uint16_t, uint16_t>;
    ht  t;
    t.put(12, 33);
    t.put(1, 3);
    t.put(1, 5);
    t.put(5, 8);
    std::cout<<t.get(12) <<std::endl;
    std::cout<<t.get(1) <<std::endl;
    auto keys = t.getKeys();
    std::ostream_iterator<uint16_t> oit(std::cout, "|");
    std::copy(keys.begin(), keys.end(), oit);
    std::cout << std::endl;
    t.remove(1);

    keys = t.getKeys();

    std::copy(keys.begin(), keys.end(), oit);
    std::cout << std::endl;
    return 0;
}

